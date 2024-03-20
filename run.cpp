#include "Common.h"
#include "TankObject.h"
#include "BulletObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "FontText.h"

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

    //Free music
    Mix_FreeMusic(battleMusic);
    battleMusic = NULL;
}


int main(int argc, char* args[]){
    initSDL();
    srand(time(NULL));

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

    BaseObject layoutBox;
    layoutBox.setPos(0, SCREEN_HEIGHT - LAYOUT_BOX_HEIGHT);
    layoutBox.setPos2(LAYOUT_BOX_WIDTH, LAYOUT_BOX_HEIGHT);
    bool ret = layoutBox.loadIMG("images/Backgrounds/layoutBox.png");
    
    BaseObject heart;
    heart.setPos(10, SCREEN_HEIGHT - LAYOUT_BOX_HEIGHT + 80);
    heart.setPos2(HEART_WIDTH, HEART_HEIGHT);
    bool ret1 = heart.loadIMG("images/Backgrounds/heart.png");    
    FontText heartNumber;
    heartNumber.setColor(WHITE_COLOR);

    BaseObject killEnemy;
    killEnemy.setPos(1350, 20);
    killEnemy.setPos2(KILL_ENEMY_WIDTH, KILL_ENEMY_HEIGHT);
    bool ret2 = killEnemy.loadIMG("images/Backgrounds/killenemy.png");  
    FontText Killed;
    Killed.setColor(WHITE_COLOR);

    BaseObject rocket;
    rocket.setPos(90, SCREEN_HEIGHT - LAYOUT_BOX_HEIGHT + 80);
    rocket.setPos2(HEART_WIDTH, HEART_HEIGHT);
    bool ret3 = rocket.loadIMG("images/Backgrounds/rocket.png");
    FontText rocketText;
    rocketText.setColor(WHITE_COLOR); 

    /* CREATE MAIN TANK - TANK OBJECT */
    TankObject mainTank;
    bool check = mainTank.loadIMG(gNameMainTank);
    if(check == false){
        cout << "Unable to load Main Tank! " << SDL_GetError() << endl;
        return 0;
    }
    
    /* INIT EXPLODE OBJECT */
    ExplosionObject explode;
    ExplosionObject explode1;
    explode.setTexture();
    explode1.setTexture();

    /* INIT SOUND EFFECTS */
    bool checkLoadSoundEffect = loadSoundEffects();
    if(!checkLoadSoundEffect) return 0; 
    

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

    bool quit = false;
    SDL_Event e;

    unsigned int currentHeart = 1;
    unsigned int currentKilled = 0;
    unsigned int currentRocket = 0;
    bool rocketAdded = false;
    while(!quit){
        
        /* PLAY BATTLE MUSIC */
        if(Mix_PlayingMusic() == 0){
            Mix_PlayMusic(battleMusic, -1);
        }

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            mainTank.handleInputAction(e, gBulletSound, currentRocket);
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
        rocket.renderCopy(rocket.getPos());

        /* LOAD TANK OBJECT */
        SDL_Rect posTank = mainTank.getPos();
        double flipTank = mainTank.getDegrees();
        SDL_RendererFlip typeFlipOfTank = mainTank.getFlipType();
        mainTank.handleMove();
        mainTank.renderCopy(posTank, flipTank, NULL, typeFlipOfTank);
        // Run bullets of tank object
        mainTank.runBullet();
        mainTank.runRocket(currentRocket);

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
                        SDL_Delay(88);
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
                        if(checkColl){

                            currentKilled++;
                            if(currentKilled != 0 && currentKilled % 2 == 0 && !rocketAdded) currentRocket++;

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
                        bool checkColl = SDLCommonFunc::CheckCollision(aRocket->getPos(), p_threat->getPos(), 0);
                        if(checkColl){
                            if(currentKilled != 0 && currentKilled % 2 == 0 && !rocketAdded) currentRocket++;
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
                            mainTank.removeRocket(r);
                        }
                    }
                }                

                if(currentKilled % 2 != 0) rocketAdded = false; 

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

        /* SHOW NUMBER OF HEARTS SCREEN */
        string heartToString = to_string(currentHeart);
        heartNumber.setText(heartToString);
        heartNumber.setPos(45, SCREEN_HEIGHT - HEART_HEIGHT - 2);
        heartNumber.setPos2(25, 25);
        heartNumber.createGameText(gFont);

        string killedToString = to_string(currentKilled);
        Killed.setText(killedToString);
        Killed.setPos(1418, 20);
        Killed.setPos2(45, 45);
        Killed.createGameText(gFont);

        string rocketToString = to_string(currentRocket);
        Killed.setText(rocketToString);
        Killed.setPos(123, SCREEN_HEIGHT - HEART_HEIGHT - 2);
        Killed.setPos2(25, 25);
        Killed.createGameText(gFont);


        SDL_RenderPresent(gRenderer);

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

    return check;
}



