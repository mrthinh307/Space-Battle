#include "Common.h"
#include "TankObject.h"
#include "BulletObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "FontText.h"
#include "AdditionalTools.h"

void logSDLError(ostream& os, const string& msg, bool fatal = false);
void initSDL();
void quitSDL();
bool loadSoundEffects();

SDL_Texture* SDLCommonFunc::loadImage( string path){
    SDL_Texture* newTexture = NULL;

    SDL_Surface* optimizedSurface = NULL; // the final optimized image

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){
        cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << endl;
    }
    else{
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0));

        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface -> format, 0);

        if(optimizedSurface == NULL){
            cout << "Unable to optimized surface! SDL Error: " << SDL_GetError() << endl;
        }

        SDL_FreeSurface(loadedSurface);
        newTexture = SDL_CreateTextureFromSurface(gRenderer, optimizedSurface);

        if(newTexture == nullptr){
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(optimizedSurface);
    }
    return newTexture;
}

SDL_Texture* SDLCommonFunc::loadText(string textureText, SDL_Color textColor, TTF_Font* gFont){
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface =TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

    SDL_FreeSurface(loadedSurface);
    
    return newTexture;
}

void SDLCommonFunc::render(SDL_Texture* loadedTexture, SDL_Rect clip, double angle , SDL_Point* center , SDL_RendererFlip flip ) {

    //Render to screen
    SDL_RenderCopyEx(gRenderer, loadedTexture, NULL, &clip, angle, center, flip);
}

void SDLCommonFunc::Clear()
{
    //Free loaded image
    SDL_DestroyTexture( gBackground );
    gBackground = NULL;

    //Free the sound effects
    for(int i = 0; i < NUMBER_OF_BULLET_SOUND; i++){
        Mix_FreeChunk(gBulletSound[i]);
        gBulletSound[i] = NULL;
    }

    for(int i = 0; i < NUMBER_OF_EXPLODE_SOUND; i++){
        Mix_FreeChunk(gExpSound[i]);
        gExpSound[i] = NULL;
    }

    Mix_FreeChunk(gameOver);
    gameOver = NULL;

    Mix_FreeChunk(gRocketSound);
    gRocketSound = NULL;

    //Free music
    Mix_FreeMusic(battleMusic);
    battleMusic = NULL;

    Mix_FreeChunk(menuButton);
    menuButton = NULL;

    Mix_FreeChunk(buttonAction);
    buttonAction = NULL;
}

int SDLCommonFunc::showMenu(){
    SDL_Texture* gMenu[4];
    gMenu[3] = SDLCommonFunc::loadImage("images/Backgrounds/menu.jpg");
    gMenu[0] = SDLCommonFunc::loadImage("images/Backgrounds/menu0.jpg");
    gMenu[1] = SDLCommonFunc::loadImage("images/Backgrounds/menu1.jpg");
    gMenu[2] = SDLCommonFunc::loadImage("images/Backgrounds/menu2.jpg");

    const int MenuItems = 3;
    SDL_Rect posItem[MenuItems];
    
    posItem[0] = {590, 390, 290, 40};
    posItem[1] = {590, 460, 290, 40};
    posItem[2] = {590, 530, 290, 40};

    bool selected[MenuItems] = {0, 0, 0};

    SDL_Event m_event; 
    int x_m = 0;
    int y_m =  0;
    int lastMenuIndex = -1;
    SDL_RenderCopy(gRenderer, gMenu[3], NULL, NULL);
    while(true){
        if( Mix_PlayingMusic() == 0 )
        {
            //Play the music
            Mix_PlayMusic( menuMusic, -1 );
        }
        int menuIndex = -1;
        while(SDL_PollEvent(&m_event)){
            switch(m_event.type){
                case SDL_QUIT:
                {
                   if(Mix_PlayingMusic() == 1 && Mix_PausedMusic() != 1){
                        Mix_PauseMusic();
                        Mix_FreeMusic(menuMusic);
                        menuMusic = NULL;
                        for(int i = 0; i < 4; i++){
                            SDL_DestroyTexture(gMenu[i]);
                            gMenu[i] = NULL;
                        }
                   }
                    return 1;
                }
                case SDL_MOUSEMOTION:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;
                        
                        for(int i = 0; i < MenuItems; i++){
                            if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posItem[i])){
                                menuIndex = i;
                                break;
                            }
                        }

                        if (menuIndex != -1) {
                            SDL_RenderCopy(gRenderer, gMenu[menuIndex], NULL, NULL);
                            if(lastMenuIndex != menuIndex)
                                Mix_PlayChannel(-1, menuButton, 0);
                        } else {
                            SDL_RenderCopy(gRenderer, gMenu[3], NULL, NULL);
                        }
                        SDL_RenderPresent(gRenderer);
                        lastMenuIndex = menuIndex;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;

                        for(int i = 0; i < MenuItems; i++){
                            if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posItem[i])){
                                Mix_PlayChannel(-1, buttonAction, 0);
                                if(i != 2){
                                    if(Mix_PlayingMusic() == 1 && Mix_PausedMusic() != 1){
                                        Mix_PauseMusic();
                                        Mix_FreeMusic(menuMusic);
                                        menuMusic = NULL;
                                        for(int i = 0; i < 4; i++){
                                            SDL_DestroyTexture(gMenu[i]);
                                            gMenu[i] = NULL;
                                        }
                                    }
                                }
                                SDL_Delay(1000);
                                return i;
                            }
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if(m_event.key.keysym.sym == SDLK_ESCAPE){
                        SDL_RenderCopy(gRenderer, gMenu[1], NULL, NULL);
                        if(Mix_PlayingMusic() == 1 && Mix_PausedMusic() != 1){
                            Mix_PauseMusic();
                            Mix_FreeMusic(menuMusic);
                            menuMusic = NULL;
                            for(int i = 0; i < 4; i++){
                                SDL_DestroyTexture(gMenu[i]);
                                gMenu[i] = NULL;
                            }
                        }
                        SDL_RenderPresent(gRenderer);
                        return 1;
                    }
                    break;
                default:
                    break;
            }
        }

        if (menuIndex != -1) {
            SDL_RenderCopy(gRenderer, gMenu[menuIndex], NULL, NULL);
        } else {
            SDL_RenderCopy(gRenderer, gMenu[3], NULL, NULL);
        }
        SDL_RenderPresent(gRenderer);
        
    }
    return 1;
}

BaseObject layoutBox;
BaseObject heart;
FontText heartNumber;

BaseObject timer;
FontText timeGame;

BaseObject killEnemy;
FontText Killed;
BaseObject killIcon;

ExplosionObject explode;
ExplosionObject explode1;

BaseObject rocket;
FontText rocketText;

BaseObject gold;
FontText goldText;
BaseObject goldIcon;
vector<Tools*> goldItems;

int main(int argc, char* args[]){
    initSDL();
    srand(time(NULL));

    /* INIT TIME START GAME*/
    string str_minute = "00 : ";
    
    /* INIT SOUND EFFECTS */
    bool checkLoadSoundEffect = loadSoundEffects();
    if(!checkLoadSoundEffect) return 0; 

    /* CREATE BACKGROUND */
    gBackground = SDLCommonFunc::loadImage(gNameBackground);
    SDL_Rect bkg;
    bkg.x = 0;
    bkg.y = 0;
    bkg.w = SCREEN_WIDTH;
    bkg.h = SCREEN_HEIGHT;

    SDL_Rect bkg1;
    bkg1.x = 0;
    bkg1.y = 0;
    bkg1.w = SCREEN_WIDTH;
    bkg1.h = SCREEN_HEIGHT;

    //BaseObject layoutBox;
    layoutBox.setPos(0, SCREEN_HEIGHT - LAYOUT_BOX_HEIGHT);
    layoutBox.setPos2(LAYOUT_BOX_WIDTH, LAYOUT_BOX_HEIGHT);
    bool ret = layoutBox.loadIMG("images/Backgrounds/layoutBox.png");
    
    //BaseObject heart;
    heart.setPos(10, SCREEN_HEIGHT - LAYOUT_BOX_HEIGHT + 80);
    heart.setPos2(HEART_WIDTH, HEART_HEIGHT);
    bool ret1 = heart.loadIMG("images/Backgrounds/heart.png");    
    //FontText heartNumber;
    heartNumber.setColor(RED_COLOR);

    //BaseObject killEnemy;
    killEnemy.setPos(1320, 20);
    killEnemy.setPos2(KILL_ENEMY_WIDTH, KILL_ENEMY_HEIGHT);
    bool ret2 = killEnemy.loadIMG("images/Backgrounds/killenemy.png");  
    //FontText Killed;
    Killed.setColor(CYAN_COLOR);
    //BaseObject killIcon;
    killIcon.setPos(1440, 28);
    killIcon.setPos2(33, 28);
    bool ret21 = killIcon.loadIMG("images/Backgrounds/killicon.png");

    //BaseObject rocket;
    rocket.setPos(90, SCREEN_HEIGHT - LAYOUT_BOX_HEIGHT + 80);
    rocket.setPos2(HEART_WIDTH, HEART_HEIGHT);
    bool ret3 = rocket.loadIMG("images/Backgrounds/rocket.png");
    //FontText rocketText;
    rocketText.setColor(GREEN_COLOR); 

    //BaseObject gold;
    gold.setPos(1320, 100);
    gold.setPos2(50, 50);
    bool ret4 = gold.loadIMG("images/Backgrounds/gold.png");
    //FontText goldText;
    goldText.setColor(YELLOW_COLOR);
    //BaseObject goldIcon;
    goldIcon.setPos(1440, 108);
    goldIcon.setPos2(30, 34);
    bool ret41 = goldIcon.loadIMG("images/Backgrounds/goldicon.png");

    //BaseObject timer;
    timer.setPos(10, 20);
    timer.setPos2(50, 50);
    bool ret51 = timer.loadIMG("images/Backgrounds/timer.png");
    timeGame.setColor(WHITE_COLOR);


    /* CREATE MAIN TANK - TANK OBJECT */
    TankObject mainTank;
    bool check = mainTank.loadIMG(gNameMainTank);
    if(check == false){
        cout << "Unable to load Main Tank! " << SDL_GetError() << endl;
        return 0;
    }
    
    /* INIT EXPLODE OBJECT */
    // ExplosionObject explode;
    // ExplosionObject explode1;
    explode.setTexture();
    explode1.setTexture();

    /* INIT THREATS OBJECT + BULLET OF THREATS OBJECT */
    ThreatsObject * p_threats = new ThreatsObject[NUM_THREATS];
    for(int i = 0; i < NUM_THREATS; ++i){

        // THREATS OBJECT
        ThreatsObject* p_threat = p_threats + i;
        if(p_threat != NULL){
            bool check1 = p_threat->loadIMG(gNameThreatsObject);
            if(!check1){
                cout <<"Unable to load Threat Images! " << endl;
                return 0;
            }
            int rand_x, rand_y;
            int tmp = rand() % 4;
            if(tmp == 0){
                rand_x = 0;
                rand_y = rand() % SCREEN_HEIGHT;
            }
            else if(tmp == 1){
                rand_x = rand() % SCREEN_WIDTH ;
                rand_y = 0;
            }
            else if(tmp == 2){
                rand_x = SCREEN_WIDTH;
                rand_y = rand() % SCREEN_HEIGHT;
            }
            else if(tmp == 3){
                rand_x = rand() % SCREEN_WIDTH;
                rand_y = SCREEN_HEIGHT;
            }

            p_threat->setPos(rand_x, rand_y);

            // BULLET OF THREATS OBJECT
            BulletObject* t_bull = new BulletObject();
            p_threat->initBullet(t_bull);
        }

    }

    /*-----------------------RUN GAME---------------------------*/
    const int FPS = 60;
    const int frameDelay = 888 / FPS;

    Uint32 frameStart;
    int frameTime;

    bool quit = false;
    SDL_Event e;

    unsigned int currentHeart = 1;
    unsigned int currentKilled = 0;
    bool rocketAdded = false;
    unsigned int currentGold = 0;

    int MENU = SDLCommonFunc::showMenu();
    if(MENU == 1) quit = true;

    while(!quit){
        frameStart = SDL_GetTicks();
        /* PLAY BATTLE MUSIC */
        if(Mix_PlayingMusic() == 0){
            Mix_PlayMusic(battleMusic, -1);
        }

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            mainTank.handleInputAction(e, gBulletSound);
        }

        /* HANDLE MOVE:  ĐỒNG TIỀN */
        for (auto& goldItem : goldItems) {
            goldItem->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        /* CLEAR SCREEN */
        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255);
        SDL_RenderClear( gRenderer );


        /* LOAD BACKGROUND */
        bkg.x -= 1;
        bkg1.x = bkg.x + SCREEN_WIDTH;
        SDL_RenderCopy(gRenderer, gBackground, NULL, &bkg);
        SDL_RenderCopy(gRenderer, gBackground, NULL, &bkg1);
        if(bkg.x < -SCREEN_WIDTH){
            bkg.x = 0;
        }

        layoutBox.renderCopy(layoutBox.getPos());
        heart.renderCopy(heart.getPos());
        killEnemy.renderCopy(killEnemy.getPos());
        killIcon.renderCopy(killIcon.getPos());
        rocket.renderCopy(rocket.getPos());
        gold.renderCopy(gold.getPos());
        goldIcon.renderCopy(goldIcon.getPos());
        timer.renderCopy(timer.getPos());

        /* LOAD TANK OBJECT */
        SDL_Rect posTank = mainTank.getPos();
        double flipTank = mainTank.getDegrees();
        SDL_RendererFlip typeFlipOfTank = mainTank.getFlipType();
        mainTank.handleMove();
        mainTank.renderCopy(posTank, flipTank, NULL, typeFlipOfTank);
        // Run bullets of tank object
        mainTank.runBullet();
        mainTank.runRocket();

        /* IMPLEMENT THREATS OBJECT */
        for(int i = 0; i < NUM_THREATS; i++){
            ThreatsObject* p_threat = (p_threats + i);
            if(p_threat != NULL){
                SDL_Rect posThreat = p_threat->getPos() ;

                p_threat->setDegrees(mainTank.getPos(), i);
                double degThreat = p_threat->getDegrees();
                
                p_threat->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->renderCopy(posThreat, degThreat, NULL, SDL_FLIP_NONE);

                //Run bullet of a threat
                p_threat->runBullet(SCREEN_WIDTH, SCREEN_HEIGHT);

                //CHECK COLLISION: TANK OBJECT -> THREAT OBJECT
                bool isCol = SDLCommonFunc::CheckCollision(mainTank.getPos(), p_threat->getPos(), 0);
                if(isCol){

                    currentHeart--;

                    //Handle EXPLOSION between TANK OBJECT -> THREAT OBJECT
                    for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                    
                        int x_pos = mainTank.getPos().x + WIDTH_TANK_OBJECT / 2 - EXP_WIDTH / 2;
                        int y_pos = mainTank.getPos().y + HEIGHT_TANK_OBJECT / 2 - EXP_HEIGHT / 2;
                        explode.setPos(x_pos, y_pos);

                        int x1_pos = p_threat->getPos().x + WIDTH_THREATS_OBJECT / 2 - EXP_WIDTH / 2;
                        int y1_pos = p_threat->getPos().y + HEIGHT_THREATS_OBJECT / 2 - EXP_HEIGHT / 2;
                        explode1.setPos(x1_pos, y1_pos);

                        explode.setFrame(ex);
                        explode1.setFrame(ex);

                        explode.renderCopy2();
                        explode1.renderCopy2();
                        SDL_Delay(48);
                        SDL_RenderPresent(gRenderer);
                    }

                    // Play sound effect of event
                    Mix_PauseMusic();
                    Mix_PlayChannel(-1, gExpSound[1], 0);
                    Mix_PlayChannel(-1, gExpSound[0], 0);
                    SDL_Delay(888);
                    Mix_PlayChannel(-1, gameOver, 0);

                    if(MessageBox(NULL, "Game Over", "Info", MB_OK) == IDOK){
                        delete[] p_threats;
                        SDLCommonFunc::Clear();
                        quitSDL();
                        return 0;
                    }
                }
                
                /* CHECK COLLISON: BULLET OF TANK OBJECT -> THREAT OBJECT */
                vector<BulletObject*> bull_list = mainTank.getBulletList();
                for(int j = 0; j < bull_list.size(); j++){
                    BulletObject* aBullet = bull_list.at(j);
                    if(aBullet != NULL){
                        bool checkColl = SDLCommonFunc::CheckCollision(aBullet->getPos(), p_threat->getPos(), 0);
                        int x, y;
                        if(checkColl){
                            int ran = rand() % 3 + 1;
                            if(ran == 1){
                                Tools* aGoldItem = new Tools();
                                aGoldItem->setGoldTexture();
                                aGoldItem->setTexture(aGoldItem->getGoldItem());
                                if(aGoldItem != NULL){
                                    x = p_threat->getPos().x; 
                                    y = p_threat->getPos().y;        
                                    aGoldItem->setPos(x, y);
                                    goldItems.push_back(aGoldItem);                    
                                }                                
                            }
                            
                            currentKilled++;
                            unsigned int currentRocket = mainTank.getRocket();
                            if(currentKilled != 0 && currentKilled % 2 == 0 && !rocketAdded) mainTank.setRocket(++currentRocket);

                            //Handle EXPLOSION between BULLET OF TANK OBJECT -> THREAT OBJECT
                            for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                                int x_pos = p_threat->getPos().x + WIDTH_THREATS_OBJECT / 2 - EXP_WIDTH / 2;
                                int y_pos = p_threat->getPos().y + HEIGHT_THREATS_OBJECT / 2 - EXP_HEIGHT / 2;
                                explode.setPos(x_pos, y_pos);

                                explode.setFrame(ex);
                                
                                explode.renderCopy2();
                            }

                            //Handle sound effects
                            Mix_PlayChannel(-1, gExpSound[0], 0);

                            p_threat->resetThreat();
                            mainTank.removeBullet(j);
                            
                        }
                    }                 
                }

                if(currentKilled % 2 != 0) rocketAdded = false; 

                /* CHECK COLLISON: ROCKET OF TANK OBJECT -> THREAT OBJECT */
                vector<BulletObject*> rocket_list = mainTank.getRocketList();
                for(int r = 0; r < rocket_list.size(); r++){
                    BulletObject* aRocket = rocket_list.at(r);
                    if(aRocket != NULL){
                        int x, y;
                        bool checkColl = SDLCommonFunc::CheckCollision(aRocket->getPos(), p_threat->getPos(), 0);
                        if(checkColl){
                            int ran = rand() % 3 + 1;
                            if(ran == 1){
                                Tools* aGoldItem = new Tools();
                                aGoldItem->setGoldTexture();
                                aGoldItem->setTexture(aGoldItem->getGoldItem());
                                if(aGoldItem != NULL){
                                    x = p_threat->getPos().x; 
                                    y = p_threat->getPos().y;        
                                    aGoldItem->setPos(x, y);
                                    goldItems.push_back(aGoldItem);                    
                                }                                
                            }

                            currentKilled++;
                            //Handle EXPLOSION between ROCKET OF TANK OBJECT -> THREAT OBJECT
                            for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                                int x_pos = p_threat->getPos().x + WIDTH_THREATS_OBJECT / 2 - EXP_WIDTH / 2;
                                int y_pos = p_threat->getPos().y + HEIGHT_THREATS_OBJECT / 2 - EXP_HEIGHT / 2;
                                explode.setPos(x_pos, y_pos);

                                explode.setFrame(ex);
                                
                                explode.renderCopy2();
                            }

                            //Handle sound effects
                            Mix_PlayChannel(-1, gExpSound[0], 0);
                            p_threat->resetThreat();
                        }
                    }
                }       

                /* HANDLE GOLD*/
                for (int a = 0; a < goldItems.size();) {
                    goldItems[a]->renderCopy(goldItems[a]->getPos());
                    if(goldItems[a]->timer() > TIME_TO_EXPLODE_GOLD || SDLCommonFunc::CheckCollision(goldItems[a]->getPos(), p_threat->getPos(), 5)){
                        int x_pos = goldItems[a]->getPos().x + goldItems[a]->getPos().w / 2 - EXP_GOLD_WIDTH / 2;
                        int y_pos = goldItems[a]->getPos().y + goldItems[a]->getPos().h / 2 - EXP_GOLD_HEIGHT / 2;
                        int w_pos = EXP_GOLD_WIDTH;
                        int h_pos = EXP_GOLD_HEIGHT;
                        for(int ex = 0; ex < EXPLODE_GOLD_ANIMATION_FRAMES; ex++){
                            goldItems[a]->setPos(x_pos, y_pos);
                            goldItems[a]->setPos2(w_pos, h_pos);
                            goldItems[a]->setFrame(ex);
                            goldItems[a]->renderCopy2();    
                        }
                        Mix_PlayChannel(-1, breakGold, 0);
                        delete goldItems[a];
                        goldItems.erase(goldItems.begin() + a);
                    }
                    else {
                        bool checkGetGold = SDLCommonFunc::CheckCollision(goldItems[a]->getPos(), mainTank.getPos(), 0);
                        if(checkGetGold){
                            Mix_PlayChannel(-1, getGold, 0);
                            currentGold += goldItems[a]->getGoldValue();
                            delete goldItems[a];
                            goldItems.erase(goldItems.begin() + a);
                        }
                        else ++a;                    
                    }
                }

                /* CHECK COLLISON: TANK OBJECT -> BULLET OF THREAT OBJECT */
                vector<BulletObject*> bull_listThreats = p_threat->getBulletList();
                for(int k = 0; k < bull_listThreats.size(); k++){
                    BulletObject* aBulletOfThreat = bull_listThreats.at(k);
                    if(aBulletOfThreat != NULL){
                        bool checkColl = SDLCommonFunc::CheckCollision(aBulletOfThreat->getPos(), mainTank.getPos(), 0);
                        if(checkColl){
                            currentHeart--;
                            //Handle EXPLOSION between TANK OBJECT -> BULLET OF THREAT
                            for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                                int x_pos = mainTank.getPos().x + WIDTH_TANK_OBJECT / 2 - EXP_WIDTH / 2;
                                int y_pos = mainTank.getPos().y + HEIGHT_TANK_OBJECT / 2 - EXP_WIDTH / 2;
                                explode.setPos(x_pos, y_pos);

                                explode.setFrame(ex);
                                
                                explode.renderCopy2();
                                
                                SDL_RenderPresent(gRenderer);
                            }

                            //Handle sound effects
                            Mix_PauseMusic();
                            Mix_PlayChannel(-1, gExpSound[1], 0);
                            SDL_Delay(888);
                            Mix_PlayChannel(-1, gameOver, 0);

                            if(MessageBox(NULL, "Game Over", "Info", MB_OK) == IDOK){
                                p_threat->removeBullet(k);
                                SDLCommonFunc::Clear();
                                quitSDL();
                                return 0;
                            }
                        }
                    }
                }
            }
        }

        static int minute = 0;
        Uint32 timeValue = SDL_GetTicks() / 1000; 
        static Uint32 lastTimeValue = 0;

        if(timeValue % 60 == 0 && lastTimeValue % 60 == 59){
            minute++; 
        }

        lastTimeValue = timeValue;

        if(minute < 10) str_minute = "0" + to_string(minute) + " : ";
        else str_minute = to_string(minute) + " : ";

        string timeString = to_string(timeValue % 60);
        if (timeString.length() < 2) {
            timeString = "0" + timeString;
        }

        timeGame.setText(str_minute + timeString);
        timeGame.setPos(75, 20);
        timeGame.setPos2(60, 50);
        timeGame.createGameText(gFont);




        string heartToString = to_string(currentHeart);
        heartNumber.setText(heartToString);
        heartNumber.setPos(45, SCREEN_HEIGHT - HEART_HEIGHT - 2);
        heartNumber.setPos2(22, 22);
        heartNumber.createGameText(gFont);

        string killedToString = to_string(currentKilled);
        Killed.setText(killedToString);
        Killed.setPos(1388, 20);
        Killed.setPos2(45, 45);
        Killed.createGameText(gFont);

        string rocketToString = to_string(mainTank.getRocket());
        rocketText.setText(rocketToString);
        rocketText.setPos(123, SCREEN_HEIGHT - HEART_HEIGHT - 2);
        rocketText.setPos2(22, 22);
        rocketText.createGameText(gFont);

        string goldToString = to_string(currentGold);
        goldText.setText(goldToString);
        goldText.setPos(1388, 100);
        goldText.setPos2(45, 45);
        goldText.createGameText(gFont);

        SDL_RenderPresent(gRenderer);
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
     
    delete[] p_threats;
    SDLCommonFunc::Clear();
    quitSDL();
    return 0;
}

void initSDL(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(cout, "SDL_Init", true);
    }

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ){
		logSDLError(cout, "SDL_Init", true);
	}

    gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(gWindow == nullptr){
        logSDLError(cout, "Create Window", true);
    }


    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    gScreenSurface = SDL_GetWindowSurface(gWindow);     // HERE

    if(gRenderer == nullptr){
        logSDLError(cout, "Create Renderer", true);
    }
    else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if( !( IMG_Init( imgFlags ) & imgFlags ) )
		{
			cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();
		}

		//Initialize SDL_mixer
		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		{
			cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError();
		}

        //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        }
	}
    
    gFont = TTF_OpenFont("images/Fonts/OpenSans-Bold.ttf", 28);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(){
    // Giải phóng biến Killed
    Killed.free();

    // Giải phóng biến rocketText
    rocketText.free();

    // Giải phóng biến goldText
    goldText.free();

    // Giải phóng biến heartNumber
    heartNumber.free();

    // Giải phóng biến layoutBox
    layoutBox.free();

    // Giải phóng biến heart
    heart.free();

    // Giải phóng biến killEnemy
    killEnemy.free();

    // Giải phóng biến killIcon
    killIcon.free();

    // Giải phóng biến rocket
    rocket.free();

    // Giải phóng biến gold
    gold.free();

    // Giải phóng biến goldIcon
    goldIcon.free();

    explode.free();
    explode1.free();

    timer.free();

    // Giải phóng các đối tượng trong vector goldItems
    for (auto& item : goldItems) {
        item->free();
        delete item;
    }
    goldItems.clear();

    // Giải phóng các biến khác
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}


void logSDLError(ostream& os,const string& msg, bool fatal ){
    cout << msg << "Error: " << SDL_GetError() << endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}

bool loadSoundEffects(){
    bool check = true;
    gBulletSound[0] = Mix_LoadWAV(gNameBulletSoundOfThreat);

    if(gBulletSound[0] == NULL){
        cout << "Unable to load sphere sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }

    gBulletSound[1] = Mix_LoadWAV(gNameBulletSoundOfTank);

    if(gBulletSound[1] == NULL){
        cout << "Unable to load sphere1 sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }

    gBulletSound[2] = Mix_LoadWAV("images/SoundEffects/laser.wav");

    if(gBulletSound[2] == NULL){
        cout << "Unable to load laser sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }

    gExpSound[0] = Mix_LoadWAV(gNameExplodeSoundOfThreat);

    if(gExpSound[0] == NULL){
        cout << "Unable to load explosion default sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }

    gExpSound[1] = Mix_LoadWAV(gNameExplodeSoundOfTank);
    if(gExpSound[1] == NULL){
        cout << "Unable to load player die sound effect. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }

    gameOver = Mix_LoadWAV(gGameOveMusic);

    if(gameOver == NULL){
        cout << "Unable to load game over music. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }

    battleMusic = Mix_LoadMUS(gBattleMusic);

    if(battleMusic == NULL){
        cout << "Unable to load battle music. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }

    getGold = Mix_LoadWAV(gGetGoldSound);

    if(getGold == NULL){
        cout << "Unable to load get gold sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeChunk(getGold, 50);

    breakGold = Mix_LoadWAV(gBreakGoldSound);

    if(breakGold == NULL){
        cout << "Unable to load break gold sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeChunk(breakGold, 128);

    menuButton = Mix_LoadWAV("images/SoundEffects/menu.wav");
    if(menuButton == NULL){
        cout << "Unable to load menu button sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeChunk(menuButton, 128);

    buttonAction = Mix_LoadWAV("images/SoundEffects/button.wav");
    if(buttonAction == NULL){
        cout << "Unable to load menu button action sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeChunk(buttonAction, 128);

    menuMusic = Mix_LoadMUS("images/SoundEffects/menuMusic.wav");
    if(menuMusic == NULL){
        cout << "Unable to load menu music. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeMusic(100);
    
    return check;
}



