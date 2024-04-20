#include "Common.h"
#include "TankObject.h"
#include "BulletObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "FontText.h"
#include "AdditionalTools.h"
#include "HandleSkill.h"

void logSDLError(ostream& os, const string& msg, bool fatal = false);
void initSDL();
void quitSDL();
bool loadSoundEffects();

SDL_Texture* SDLCommonFunc::loadImage( string path);

SDL_Texture* SDLCommonFunc::loadText(string textureText, SDL_Color textColor, TTF_Font* gFont);

void SDLCommonFunc::render(SDL_Texture* loadedTexture, SDL_Rect clip, double angle , SDL_Point* center , SDL_RendererFlip flip ) {
    SDL_RenderCopyEx(gRenderer, loadedTexture, NULL, &clip, angle, center, flip);
}

void SDLCommonFunc::render_for_sprite(SDL_Texture* mTexture, int x, int y, SDL_Rect* clip, double angle , SDL_Point* center , SDL_RendererFlip flip ){
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, clip->w, clip->h};

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void SDLCommonFunc::Clear();

int SDLCommonFunc::showMenu();

void blinkImage(SDL_Texture* texture, const SDL_Rect& position, const string& target_time, const string& current_time, Mix_Chunk* sound);

/* HANDLE GIFT ITEM */
void push_back_gift_item(ThreatsObject* p_threat);
void run_gift_item(vector<Tools*>& gifts_list, ThreatsObject* p_threat, unsigned int& currentGold);

/* INIT THREATS */
void initializeThreats(vector<ThreatsObject*>& p_threats, const int& num_threats, const string& path, const int& type_bullet);
void clearThreats(vector<ThreatsObject*>& p_threats, const int& num_threats, const int& idx);

TankObject mainTank;
static vector<ThreatsObject*> p_threats;

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
vector<Tools*> gifts_list;

BaseObject warningNoti;

static Uint32 delay;

vector<Tools*> static_skills_a;
vector<Tools*> static_skills_b;

static bool have_magnet = false;
static Uint32 start_skill = 0;

vector<Tools*> teleport_a;
vector<Tools*> teleport_b;
static bool have_tele = false;
static Uint32 start = 0;

static bool have_4_bullet = false;
static Uint32 start_4_bullet;

static bool have_super_bullet = false;
static Uint32 start_super_bullet;

static bool have_bullet_spread = false;
static Uint32 start_bullet_spread;

static bool have_straight_beam = false;
static Uint32 start_straight_beam;

static bool have_trap = false;
static Uint32 start_trap;

int main(int argc, char* args[]){
    initSDL();
    srand(time(NULL));

    /* INIT TIME START GAME*/
    string str_minute = "00 : ";

    /* INIT SOUND EFFECTS */
    bool checkLoadSoundEffect = SDLCommonFunc::loadSoundEffects();
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

    gold.setPos(1320, 100);
    gold.setPos2(50, 50);
    bool ret4 = gold.loadIMG("images/Backgrounds/gold.png");
    goldText.setColor(YELLOW_COLOR);
    goldIcon.setPos(1440, 108);
    goldIcon.setPos2(30, 34);
    bool ret41 = goldIcon.loadIMG("images/Backgrounds/goldicon.png");

    timer.setPos(10, 20);
    timer.setPos2(50, 50);
    bool ret51 = timer.loadIMG("images/Backgrounds/timer.png");
    timeGame.setColor(WHITE_COLOR);

    warningNoti.setPos((SCREEN_WIDTH - 1000) / 2, (SCREEN_HEIGHT - 177) / 2);
    warningNoti.setPos2(1000, 177);
    bool ret6 = warningNoti.loadIMG("images/Backgrounds/warningboss.png");


    /* CREATE MAIN TANK - TANK OBJECT */
    bool check = mainTank.loadIMG(gNameMainTank);
    mainTank.Set_sprite_clips();

    /* INIT EXPLODE OBJECT */
    explode.setTexture();
    explode1.setTexture();

    /* INIT THREATS OBJECT + BULLET OF THREATS OBJECT */
    initializeThreats(p_threats, NUM_THREATS, gNameThreatsObject, 0);
    for(int i = 0; i < p_threats.size(); i++){
        p_threats[i]->Set_sprite_clips_1();
    }

    /*-----------------------RUN GAME---------------------------*/

    /* SET FPS */
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    bool quit = false;
    SDL_Event e;

    unsigned int currentHeart = 1;
    unsigned int currentKilled = 0;
    bool rocketAdded = false;
    // static unsigned int currentGold = 10;

    int MENU = SDLCommonFunc::showMenu();
    if(MENU == 1) quit = true;

    Uint32 timeStart = SDL_GetTicks();

    while(!quit){
        frameStart = SDL_GetTicks();

        static string current_time;

        /* PLAY BATTLE MUSIC */
        if(Mix_PlayingMusic() == 0){
            Mix_PlayMusic(battleMusic, -1);
        }

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            mainTank.handleInputAction(e, gBulletSound, gNameBulletOfMainTank);
        }

        /* HANDLE MOVE:  ĐỒNG TIỀN */
        for(int i = 0; i < gifts_list.size(); i++){
            gifts_list[i]->set_deg_for_item(mainTank.getPos(), i);
            gifts_list[i]->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
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
        mainTank.runMainTank();
        mainTank.handleMove();
        // Run bullets of tank object
        mainTank.runRocket();
        if(mainTank.get_bullet_style() == TankObject::NORMAL)
            mainTank.runBullet();
        else if(mainTank.get_bullet_style() == TankObject::FOUR_DIRECTIONS_BULLET)
            mainTank.run_four_bullet(SCREEN_WIDTH, SCREEN_HEIGHT);
        else if(mainTank.get_bullet_style() == TankObject::SUPER_BULLET)
            mainTank.run_super_bullet(SCREEN_WIDTH, SCREEN_HEIGHT);
        else if(mainTank.get_bullet_style() == TankObject::BULLET_SPREAD)
            mainTank.run_bullet_spread(SCREEN_WIDTH, SCREEN_HEIGHT);
        else if(mainTank.get_bullet_style() == TankObject::STRAIGHT_BEAM)
            mainTank.run_straight_beam(SCREEN_WIDTH, SCREEN_HEIGHT);
        else if(mainTank.get_bullet_style() == TankObject::TRAP)
            mainTank.run_trap(SCREEN_WIDTH, SCREEN_HEIGHT);

        /* RUN BOSS LEVEL 1*/
        static bool add = false;
        static int idx_Boss_1 = -1;
        bool boss_alive;
        if(SDL_GetTicks() - timeStart >= 5000 && add == false){
            NUM_THREATS++;
            boss_alive = true;
            initializeThreats(p_threats, 1, gNameBoss1, 1);
            idx_Boss_1 = p_threats.size() - 1;
            p_threats[idx_Boss_1]->Set_sprite_clips();
            p_threats[idx_Boss_1]->setPos2(BOSS_WIDTH, BOSS_HEIGHT);
            p_threats[idx_Boss_1]->set_heal_bar();
            p_threats[idx_Boss_1]->set_heal_bar_texture(SDLCommonFunc::loadImage("images/ThreatsObject/heal_bar.png"));
            add = true;
            done = false;
            // Pause music
            if(Mix_PlayingMusic() != 0){
                Mix_PauseMusic();
            }
            if(bossBattle != NULL){
                Mix_PlayMusic(bossBattle, -1);
            }
        }

        /* IMPLEMENT THREATS OBJECT & HANDLE EXPLODE */
        for(int i = 0; i < p_threats.size(); i++){
            ThreatsObject* p_threat = p_threats.at(i);
            if(p_threat != NULL){
                SDL_Rect posThreat = p_threat->getPos();
                p_threat->setDegrees(mainTank.getPos(), i);
                double degThreat = p_threat->getDegrees();

                if(i == idx_Boss_1){
                    p_threat->runBoss();
                    explode1.setPos2(480, 480);
                    p_threat->run_bullet_boss(SCREEN_WIDTH, SCREEN_HEIGHT);
                    cur_enemy = BOSS;
                }
                else{
                    p_threat->runThreats();
                    p_threat->runBullet(SCREEN_WIDTH, SCREEN_HEIGHT);
                    cur_enemy = MINI_THREATS;
                }
                p_threat->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                


                /* ------------------CHECK COLLISION-------------------*/
                
                //CHECK COLLISION: TANK OBJECT -> THREAT OBJECT + RENDER HEAL BAR OF BOSS
                // bool check_col_of_shield = handle_shield1(static_skills_a, mainTank, p_threat, NULL, object::ENEMY);
                // if(check_col_of_shield) p_threat->resetThreat();

                bool isCol = SDLCommonFunc::CheckCollision(mainTank.getPos(), p_threat->getPos(), 0);
                if(isCol){
                    currentHeart--;
                    //Handle EXPLOSION between TANK OBJECT -> THREAT OBJECT
                    int x_pos = mainTank.getPos().x + WIDTH_TANK_OBJECT / 2 - explode.getPos().w / 2;
                    int y_pos = mainTank.getPos().y + HEIGHT_TANK_OBJECT / 2 - explode.getPos().h / 2;
                    explode.setPos(x_pos, y_pos);

                    int x1_pos = p_threat->getPos().x + p_threat->getPos().w / 2 - explode1.getPos().w / 2;
                    int y1_pos = p_threat->getPos().y + p_threat->getPos().h / 2 - explode1.getPos().h / 2;
                    explode1.setPos(x1_pos, y1_pos);

                    for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                        explode.setFrame(ex);
                        explode1.setFrame(ex);

                        explode.renderCopy2();
                        explode1.renderCopy2();
                        SDL_RenderPresent(gRenderer);
                    }

                    // Play sound effect of event
                    Mix_PauseMusic();
                    Mix_PlayChannel(-1, gExpSound[1], 0);
                    Mix_PlayChannel(-1, (i != idx_Boss_1) ? gExpSound[0] : bossDie, 0);
                    Mix_PlayChannel(-1, gameOver, 0);

                    if(MessageBox(NULL, "Game Over", "Info", MB_OK) == IDOK){
                        clearThreats(p_threats, p_threats.size() - 1, 0);
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
                        if(checkColl ){
                            unsigned int currentRocket = mainTank.getRocket();
                            int x_pos = p_threat->getPos().x + p_threat->getPos().w / 2 - explode1.getPos().w / 2;
                            int y_pos = p_threat->getPos().y + p_threat->getPos().h / 2 - explode1.getPos().h / 2;
                            explode1.setPos(x_pos, y_pos);

                            if(p_threat->get_heal_bar_texture() == NULL){

                                currentKilled++;
                                
                                if(currentKilled != 0 && currentKilled % 2 == 0 && !rocketAdded) mainTank.setRocket(++currentRocket);

                                push_back_gift_item(p_threat);

                                //Handle EXPLOSION between BULLET OF TANK OBJECT -> THREAT OBJECT
                                for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                                    explode1.setFrame(ex);
                                    explode1.renderCopy2();
                                }
                                Mix_PlayChannel(-1,gExpSound[0], 0);
                                p_threat->resetThreat();
                            }
                            else{
                                p_threat->set_num_blood(p_threat->get_num_blood() + 1);
                                if(p_threat->get_num_blood() == 15){
                                    boss_alive = false;
                                    currentKilled++;
                                    for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                                        explode1.setFrame(ex);
                                        explode1.renderCopy2();
                                    }
                                    mainTank.setRocket(++currentRocket);
                                    Mix_PlayChannel(-1, bossDie, 0);
                                    clearThreats(p_threats, idx_Boss_1, idx_Boss_1);
                                }
                            }
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
                            unsigned int currentRocket = mainTank.getRocket();
                            int x_pos = p_threat->getPos().x + p_threat->getPos().w / 2 - explode1.getPos().w / 2;
                            int y_pos = p_threat->getPos().y + p_threat->getPos().h / 2 - explode1.getPos().h / 2;
                            explode1.setPos(x_pos, y_pos);

                            if(p_threat->get_heal_bar_texture() == NULL){

                                currentKilled++;
                                
                                if(currentKilled != 0 && currentKilled % 2 == 0 && !rocketAdded) mainTank.setRocket(++currentRocket);

                                push_back_gift_item(p_threat);

                                //Handle EXPLOSION between ROCKET OF TANK OBJECT -> THREAT OBJECT
                                for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                                    explode1.setFrame(ex);
                                    explode1.renderCopy2();
                                }
                                Mix_PlayChannel(-1,gExpSound[0], 0);
                                p_threat->resetThreat();
                            }
                            else{
                                p_threat->set_num_blood(p_threat->get_num_blood() + 2);
                                if((p_threat->get_num_blood() == 15 || p_threat->get_num_blood() == 16)){
                                    boss_alive = false;
                                    currentKilled++;
                                    for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                                        explode1.setFrame(ex);
                                        explode1.renderCopy2();
                                    }
                                    mainTank.setRocket(++currentRocket);
                                    Mix_PlayChannel(-1, bossDie, 0);
                                    clearThreats(p_threats, idx_Boss_1, idx_Boss_1);
                                }
                                mainTank.removeRocket(r);
                            }
                        }
                    }
                }

                /* RUN + HANDLE GOLD */
                run_gift_item(gifts_list, p_threat, currentGold);

                /* CHECK COLLISON: TANK OBJECT -> BULLET OF THREAT OBJECT */
                vector<BulletObject*> bull_listThreats = p_threat->getBulletList();
                for(int k = 0; k < bull_listThreats.size(); k++){
                    BulletObject* aBulletOfThreat = bull_listThreats.at(k);

                    // for(int idx = static_skills_a.size() - 1; idx >= 0; idx--){
                    //     Tools* skill = static_skills_a.at(idx);
                    //     skill->setDegrees(mainTank.getDegrees());
                    //     run_shield_skill(skill, mainTank, p_threat, object::PLAYER);
                    //     bool check_col = SDLCommonFunc::CheckCollision(skill->getPos(), aBulletOfThreat->getPos(), 5);
                    //     if(check_col){
                    //         cout << "no";
                    //         p_threat->resetBullet(aBulletOfThreat);
                    //         //skill->set_shield_frame(skill->get_shield_frame() + 1);
                    //         // if(skill->get_shield_frame() == 3){
                    //                 if(static_skills_a[idx] != nullptr) delete static_skills_a[idx];
                    //                 static_skills_a.clear();
                    //         // }
                    //     }
                    // }

                    shield_vs_bullet(static_skills_a, mainTank, p_threat, aBulletOfThreat, cur_enemy);

                    if(static_skills_a.size() !=0) continue;

                    // if(aBulletOfThreat != NULL){
                    //     bool checkColl = SDLCommonFunc::CheckCollision(aBulletOfThreat->getPos(), mainTank.getPos(), 10);
                    //     if(checkColl){
                    //         currentHeart--;
                    //         //Handle EXPLOSION between TANK OBJECT -> BULLET OF THREAT
                    //         for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                    //             int x_pos = mainTank.getPos().x + WIDTH_TANK_OBJECT / 2 - explode.getPos().w / 2;
                    //             int y_pos = mainTank.getPos().y + HEIGHT_TANK_OBJECT / 2 - explode.getPos().h / 2;
                    //             explode.setPos(x_pos, y_pos);

                    //             explode.setFrame(ex);

                    //             explode.renderCopy2();

                    //             SDL_RenderPresent(gRenderer);
                    //         }

                    //         //Handle sound effects
                    //         Mix_PauseMusic();
                    //         Mix_PlayChannel(-1, gExpSound[1], 0);
                    //         SDL_Delay(888);
                    //         Mix_PlayChannel(-1, gameOver, 0);

                    //         if(MessageBox(NULL, "Game Over", "Info", MB_OK) == IDOK){
                    //             clearThreats(p_threats, p_threats.size() - 1, 0);
                    //             SDLCommonFunc::Clear();
                    //             quitSDL();
                    //             return 0;
                    //         }
                    //     }
                    // }
                }
            }
            explode1.setPos2(EXP_WIDTH, EXP_HEIGHT);
        }

        

        // RUN PREVENT SKILL
        implement_magnet_skill(gifts_list, mainTank, have_magnet, start_skill);
        // RUN TELEPORT SKILL
        run_teleport_for_player(teleport_a, mainTank, have_tele);
        // RUN 4 BULLET
        set_time_for_4_bullet(mainTank, have_4_bullet, start_4_bullet);
        // RUN SUPER BULLET
        set_time_for_super_bullet(mainTank, have_super_bullet, start_super_bullet);
        // RUN BULLET SPREAD
        set_time_for_bullet_spread(mainTank, have_bullet_spread, start_bullet_spread);
        // RUN STRAIGHT BREAM
        set_time_for_straight_beam(mainTank, have_straight_beam, start_straight_beam);
        // RUN ZIC ZAC
        set_time_for_trap(mainTank, have_trap, start_trap);

        // Resume music when get over Turn boss 
        if(boss_alive == false && done == false){
            if(Mix_PlayingMusic() != 0){
                Mix_PauseMusic();
            }
            if(battleMusic != NULL) Mix_PlayMusic(battleMusic, -1);
            done = true;
        }

        /* HANDLE TIME*/
        static int minute = 0;
        Uint32 timeValue = (SDL_GetTicks() - timeStart) / 1000;
        static Uint32 lastTimeValue = 0;

        if(timeValue % 60 == 0 && lastTimeValue % 60 == 59){
            minute++;
        }

        lastTimeValue = timeValue;

        if(minute < 10) str_minute = "0" + to_string(minute) + " : ";
        else str_minute = to_string(minute) + " : ";

        string secondString = to_string(timeValue % 60);
        if (secondString.length() < 2) {
            secondString = "0" + secondString;
        }

        current_time = str_minute + secondString;

        /* WARNING BOSS */
        blinkImage(warningNoti.getTexture(), warningNoti.getPos(), "00 : 01", current_time, warningBoss);
        blinkImage(warningNoti.getTexture(), warningNoti.getPos(), "00 : 02", current_time, warningBoss);


        timeGame.setText(current_time);
        timeGame.setPos(75, 20);
        timeGame.setPos2(60, 50);
        timeGame.free();
        timeGame.createGameText(gFont);


        string heartToString = to_string(currentHeart);
        heartNumber.setText(heartToString);
        heartNumber.setPos(45, SCREEN_HEIGHT - HEART_HEIGHT - 2);
        heartNumber.setPos2(22, 22);
        heartNumber.free();
        heartNumber.createGameText(gFont);

        string killedToString = to_string(currentKilled);
        Killed.setText(killedToString);
        Killed.setPos(1388, 20);
        Killed.setPos2(45, 45);
        Killed.free();
        Killed.createGameText(gFont);

        string rocketToString = to_string(mainTank.getRocket());
        rocketText.setText(rocketToString);
        rocketText.setPos(123, SCREEN_HEIGHT - HEART_HEIGHT - 2);
        rocketText.setPos2(22, 22);
        rocketText.free();
        rocketText.createGameText(gFont);

        string goldToString = to_string(currentGold);
        goldText.setText(goldToString);
        goldText.setPos(1388, 100);
        goldText.setPos2(45, 45);
        goldText.free();
        goldText.createGameText(gFont);

        SDL_RenderPresent(gRenderer);

        // SET FPS
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // CLEAR THREAT TEXTURE
    clearThreats(p_threats, p_threats.size() -1, 0);

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
    mainTank.free();

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

    explode.clearTexture();
    explode1.clearTexture();

    timer.free();
    timeGame.free();

    // Giải phóng các đối tượng trong vector goldItems
    for(auto& item : gifts_list) {
        item->free();
        delete item;
    }
    gifts_list.clear();

    warningNoti.free();

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

bool SDLCommonFunc::loadSoundEffects(){
    bool check = true;

    gBulletSound[0] = Mix_LoadWAV("images/SoundEffects/roundabout.wav");
    Mix_VolumeChunk(gBulletSound[0], 70);

    gBulletSound[1] = Mix_LoadWAV(gNameBulletSoundOfTank);

    if(gBulletSound[1] == NULL){
        cout << "Unable to load sphere1 sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }

    gBulletSound[2] = Mix_LoadWAV("images/SoundEffects/new_1.wav");

    if(gBulletSound[2] == NULL){
        cout << "Unable to load new_1 sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }

    gExpSound[0] = Mix_LoadWAV(gNameExplodeSoundOfThreat);

    if(gExpSound[0] == NULL){
        cout << "Unable to load explosion default sound effects. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeChunk(gExpSound[0], 120);

    gExpSound[1] = Mix_LoadWAV(gNameExplodeSoundOfTank);
    if(gExpSound[1] == NULL){
        cout << "Unable to load player die sound effect. SDL_mixer error: " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeChunk(gExpSound[1], 120);

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

    warningBoss = Mix_LoadWAV("images/SoundEffects/warning_boss.wav");
    if(warningBoss == NULL){
        cout << "Unable to load waring boss sound." << " " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeChunk(warningBoss, 70);

    bossDie = Mix_LoadWAV(gNameBossDie);
    if(bossDie == NULL){
        cout << "Unable to load boss sound." << " " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeChunk(bossDie, 110);

    bossBattle = Mix_LoadMUS(gBossMusic);
    if(bossBattle == NULL){
        cout << "Unable to load boss battle music." << " " << Mix_GetError() << endl;
        check = false;
    }
    Mix_VolumeMusic(80);


    return check;
}

void blinkImage(SDL_Texture* texture, const SDL_Rect& position, const string& target_time, const string& current_time, Mix_Chunk* sound) {
    static Uint32 lastBlinkTime = 0;
    static bool transparent = false;

    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastBlinkTime > 300) {
        transparent = !transparent;
        lastBlinkTime = currentTime;
    }

    if (current_time == target_time && !transparent) {
        if (transparent) {
            SDL_SetTextureAlphaMod(texture, 180);
        } else {
            SDL_SetTextureAlphaMod(texture, 255);
        }

        SDL_RenderCopy(gRenderer, texture, NULL, &position);
        Mix_PlayChannel(-1, sound, 0);
    }
}

void initializeThreats(vector<ThreatsObject*>& p_threats, const int& num_threats, const string& path, const int& type_bullet) {
    for (int i = 0; i < num_threats; ++i) {
        // THREATS OBJECT
        ThreatsObject* p_threat = new ThreatsObject();
        if (p_threat != nullptr) {
            bool check = p_threat->loadIMG(path);
            if (!check) {
                cout << "Unable to load Threat Images!" << endl;
                return;
            }
            int rand_x, rand_y;
            int tmp = rand() % 4;
            if (tmp == 0) {
                rand_x = 0;
                rand_y = rand() % SCREEN_HEIGHT;
            } else if (tmp == 1) {
                rand_x = rand() % SCREEN_WIDTH;
                rand_y = 0;
            } else if (tmp == 2) {
                rand_x = SCREEN_WIDTH;
                rand_y = rand() % SCREEN_HEIGHT;
            } else if (tmp == 3) {
                rand_x = rand() % SCREEN_WIDTH;
                rand_y = SCREEN_HEIGHT;
            }

            p_threat->setPos(rand_x, rand_y);

            // BULLET OF THREATS OBJECT

            if(type_bullet == 0){
                BulletObject* t_bull = new BulletObject();
                p_threat->initBullet(t_bull);
            }
            else if(type_bullet == 1){
                p_threat->init_bullet_boss1();
            }
        }
        p_threats.push_back(p_threat);
    }
}

void clearThreats(vector<ThreatsObject*>& p_threats, const int& num_threats, const int& idx){
    for(int i = num_threats; i >= idx; --i){
        if(p_threats[i] != NULL){
            p_threats[i]->free();
            delete p_threats[i];
            p_threats[i] = NULL;
            p_threats.erase(p_threats.begin() + i);
        }
    }
    if(idx == 0 && num_threats == p_threats.size()){
        p_threats.clear();
    }
}

void push_back_gift_item(ThreatsObject* p_threat){
    int ran = rand() % 2 + 1;
    if(ran == 1 || ran == 2){
        Tools* a_gift_item = new Tools();
        a_gift_item->set_explode_gift();
        if(a_gift_item != NULL){
            a_gift_item->setPos(p_threat->getPos().x, p_threat->getPos().y);
            bool check = a_gift_item->get_gift();
            gifts_list.push_back(a_gift_item);
        }
    }
}

SDL_Texture* SDLCommonFunc::loadImage( string path){
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){
        cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << endl;
    }
    else{
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
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

    if(gameOver != NULL){
        Mix_FreeChunk(gameOver);
        gameOver = NULL;
    }

    if(gRocketSound != NULL){
        Mix_FreeChunk(gRocketSound);
        gRocketSound = NULL;
    }

    if(battleMusic != NULL){
        //Free music
        Mix_FreeMusic(battleMusic);
        battleMusic = NULL;
    }

    if(menuButton != NULL){
        Mix_FreeChunk(menuButton);
        menuButton = NULL;
    }

    if(buttonAction != NULL){
        Mix_FreeChunk(buttonAction);
        buttonAction = NULL;
    }

    if(warningBoss != NULL){
        Mix_FreeChunk(warningBoss);
        warningBoss = NULL;
    }

    if(menuMusic != NULL){
        Mix_FreeMusic(menuMusic);
        menuMusic = NULL;
    }

    if(bossDie != NULL){
        Mix_FreeChunk(bossDie);
        bossDie = NULL;
    }

    if(gRocketSound != NULL){
        Mix_FreeChunk(gRocketSound);
        gRocketSound = NULL;
    }
}

int SDLCommonFunc::showMenu(){
    SDL_Texture* gMenu[4];

    gMenu[0] = SDLCommonFunc::loadImage("images/Backgrounds/menu0.jpg");
    gMenu[1] = SDLCommonFunc::loadImage("images/Backgrounds/menu1.jpg");
    gMenu[2] = SDLCommonFunc::loadImage("images/Backgrounds/menu2.jpg");
    gMenu[3] = SDLCommonFunc::loadImage("images/Backgrounds/menu.jpg");

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
    int menuIndex;

    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( menuMusic, -1 );
    }

    SDL_RenderCopy(gRenderer, gMenu[3], NULL, NULL);
    SDL_RenderPresent(gRenderer);

    while(true){
        menuIndex = -1;
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
                default:
                    break;
            }
        }

    }

    // Clean up resources
    for (int i = 0; i < 4; ++i) {
        SDL_DestroyTexture(gMenu[i]);
        gMenu[i] = NULL;
    }

    return 1;
}

void run_gift_item(vector<Tools*>& gifts_list, ThreatsObject* p_threat, unsigned int& currentGold){
    for (int a = 0; a < gifts_list.size();) {
        gifts_list[a]->renderCopy(gifts_list[a]->getPos(), gifts_list[a]->getDegrees());
        if(gifts_list[a]->timer() > TIME_TO_EXPLODE_GOLD || SDLCommonFunc::CheckCollision(gifts_list[a]->getPos(), p_threat->getPos(), 5)) {
            int x_pos = gifts_list[a]->getPos().x + gifts_list[a]->getPos().w / 2 - EXP_GOLD_WIDTH / 2;
            int y_pos = gifts_list[a]->getPos().y + gifts_list[a]->getPos().h / 2 - EXP_GOLD_HEIGHT / 2;
            int w_pos = EXP_GOLD_WIDTH;
            int h_pos = EXP_GOLD_HEIGHT;
            gifts_list[a]->setPos(x_pos, y_pos);
            gifts_list[a]->setPos2(w_pos, h_pos);            
            for(int ex = 0; ex < EXPLODE_GOLD_ANIMATION_FRAMES; ex++){
                gifts_list[a]->setFrame(ex);
                gifts_list[a]->renderCopy2();
            }
            Mix_PlayChannel(-1, breakGold, 0);
            delete gifts_list[a];
            gifts_list.erase(gifts_list.begin() + a);
        }
        else {
            bool checkGetGold = SDLCommonFunc::CheckCollision(gifts_list[a]->getPos(), mainTank.getPos(), 0);
            if(checkGetGold){
                Mix_PlayChannel(-1, getGold, 0);
                if(gifts_list[a]->get_skill() == Tools::GOLD_1){
                    currentGold += gifts_list[a]->getGoldValue();
                }
                else if(gifts_list[a]->get_skill() == Tools::GOLD_2){
                    currentGold += gifts_list[a]->getGoldValue();
                }
                else if(gifts_list[a]->get_skill() == Tools::SHIELD){
                    if(static_skills_a.empty() == 0){
                        for(int i = 0; i < static_skills_a.size(); i++){
                            delete static_skills_a[i];
                        }
                        static_skills_a.clear();                        
                    }
                    init_shield_skill(static_skills_a, static_skills_b, object::PLAYER);
                }
                else if(gifts_list[a]->get_skill() == Tools::MAGNET){
                    if(have_magnet == false){
                        start_skill = SDL_GetTicks();
                        have_magnet = true;
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::TELEPORT){
                    if(have_tele == false) {
                        init_teleport(teleport_a, teleport_b, object::PLAYER, mainTank, p_threat);
                        have_tele = true;
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::X2GOLD){
                    currentGold = currentGold * 2;
                }
                else if(gifts_list[a]->get_skill() == Tools::ADD_ROCKET){
                    unsigned int num = rand() % 5 + 5;
                    mainTank.setRocket(mainTank.getRocket() + num);
                }
                else if(gifts_list[a]->get_skill() == Tools::FOUR_DIRECTIONS_BULLET){
                    if(have_4_bullet == false){
                        mainTank.set_bullet_style(TankObject::FOUR_DIRECTIONS_BULLET);
                        have_4_bullet = true;
                        start_4_bullet = SDL_GetTicks();                        
                    }

                }
                else if(gifts_list[a]->get_skill() == Tools::SUPER_BULLET){
                    if(have_super_bullet  == false){
                        mainTank.set_bullet_style(TankObject::SUPER_BULLET);
                        have_super_bullet = true;
                        start_super_bullet = SDL_GetTicks();                        
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::BULLET_SPREAD){
                    if(!have_bullet_spread){
                        mainTank.set_bullet_style(TankObject::BULLET_SPREAD);
                        have_bullet_spread = true;
                        start_bullet_spread = SDL_GetTicks();                        
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::STRAIGHT_BEAM){
                    if(!have_straight_beam){
                        mainTank.set_bullet_style(TankObject::STRAIGHT_BEAM);
                        have_straight_beam = true;
                        start_straight_beam = SDL_GetTicks();                        
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::NEW_BULLET_1){
                    gNameBulletOfMainTank = nameBulletTank1[1];
                    mainTank.setBulletType(TankObject::NEW_1);
                }
                else if(gifts_list[a]->get_skill() == Tools::TRAP_BULLET){
                    if(!have_trap){
                        mainTank.set_bullet_style(TankObject::TRAP);
                        have_trap = true;
                        start_trap = SDL_GetTicks();
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::ROUNDABOUT){
                    gNameBulletOfMainTank = nameBulletTank1[2];
                    mainTank.setBulletType(TankObject::ROUNDABOUT);
                }
                delete gifts_list[a];
                gifts_list.erase(gifts_list.begin() + a);
            }
            else ++a;
        }
    }
}