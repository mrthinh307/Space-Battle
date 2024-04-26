#include "Common.h"
#include "TankObject.h"
#include "BulletObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "FontText.h"
#include "AdditionalTools.h"
#include "HandleSkill.h"
#include "HandleGiftItem.h"
#include "SoundEffects.h"
#include "Menu.h"

void logSDLError(ostream& os, const string& msg, bool fatal = false);
void initSDL();
void quitSDL();
void quitSDL2(){
    // Giải phóng các biến khác
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    if(gFont != NULL){
        TTF_CloseFont(gFont);
        gFont = NULL;
    }

    if(menuButton != NULL){
        Mix_FreeChunk(menuButton);
        menuButton = NULL;
    }

    if(buttonAction != NULL){
        Mix_FreeChunk(buttonAction);
        buttonAction = NULL;
    }
    if(menuMusic != NULL){
        Mix_FreeMusic(menuMusic);
        menuMusic = NULL;
    }

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
}

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

void blinkImage(SDL_Texture* texture, const SDL_Rect& position,const Uint32& timeStart, const bool& boss_alive, Mix_Chunk* sound);

/* INIT THREATS */
void initializeThreats(vector<ThreatsObject*>& p_threats, const int& num_threats, const string& path, const int& type_bullet);
void clearThreats(vector<ThreatsObject*>& p_threats, const int& num_threats, const int& idx);

TankObject mainTank;
vector<ThreatsObject*> p_threats;

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

BaseObject warningNoti;

FontText timeEndGame;
FontText killedEndGame;
FontText goldEndGame;
FontText recordText;
FontText kinhnghiem;

int main(int argc, char* args[]){
    initSDL();
    srand(time(NULL));

    loadMusicForMenu();

    /*-----------------------RUN GAME---------------------------*/

    /* SET FPS */
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    Uint32 timeStart;

    bool quit = false;
    bool exit = false;
    SDL_Event e;

    bool rocketAdded = false;

    static bool boss_alive = false;

    Uint32 lastEnemyAddedTime;
    Uint32 lastBossAddedTime;

    int NUMBER_OF_TURNS_PLAYED = 0;

    while(!exit){

        if(quit == true) quit = false;

        int MENU = SDLCommonFunc::showMenu(gRenderer);
        if(MENU == 1){
            quit = true;
            exit = true;
            clearThreats(p_threats, p_threats.size() -1, 0);
            SDLCommonFunc::Clear();
            quitSDL();
            quitSDL2();
            return 0;
        }
        if(MENU == 2){
            bool ac = Achievement(gRenderer, gFont, recordText, kinhnghiem);
            if(ac == true){
                clearThreats(p_threats, p_threats.size() -1, 0);
                SDLCommonFunc::Clear();
                quitSDL();
                continue;
            }
            //quit = true;
        }

        if(MENU == 0 && NUMBER_OF_TURNS_PLAYED > 0) {
            delete_all_skills(mainTank);  
            clearThreats(p_threats, p_threats.size() -1, 0);
            SDLCommonFunc::Clear();
            quitSDL();
        }

        /* INIT SOUND EFFECTS */
        bool checkLoadSoundEffect = SDLCommonFunc::loadSoundEffects();
        if(!checkLoadSoundEffect) return 0;

        /* INIT TIME START GAME*/
        string str_minute = "00 : ";

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
        unsigned int goldRecord;
        ifstream file("save_record.txt");
        file >> goldRecord;
        file.close();
        gNameMainTank = nameTank[goldRecord / 500];
        if(goldRecord / 500 >= 4) gNameMainTank = nameTank[4];
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
 
        gNameBulletOfMainTank = nameBulletTank1[0];
        gNameRocket = nameRocket[0];

        timeStart = SDL_GetTicks();

        currentGold = 0;
        currentHeart = 3;
        currentKilled = 0;

        lastEnemyAddedTime = SDL_GetTicks();
        lastBossAddedTime = SDL_GetTicks();  

        while(!quit){

            NUMBER_OF_TURNS_PLAYED++;

            frameStart = SDL_GetTicks();

            static string current_time;

            /* PLAY BATTLE MUSIC */
            if(Mix_PlayingMusic() == 0){
                Mix_PlayMusic(battleMusic, -1);
            }

            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT){
                    quit = true;
                    exit = true;
                }
                else if(e.type == SDL_KEYDOWN){
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        {
                            Mix_HaltChannel(-1);
                            Mix_HaltMusic();
                            switch(SDLCommonFunc::handleSettingMenu(gRenderer)){
                                case 0:
                                {
                                    quit = true; 
                                    SDLCommonFunc::Clear();
                                }
                                    break;
                                case 1:
                                {
                                    //RESUME GAME
                                }
                                    break;
                                case 2:
                                {
                                    quit = true;
                                    exit = true;
                                }
                                    break;
                            }
                            Mix_ResumeMusic();
                            Mix_Resume(-1);                            
                        }
                            break;
                    }
                }
                mainTank.handleInputAction(e, gBulletSound, gNameBulletOfMainTank, gNameRocket, currentMethod);
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
            static int idx1 = 0;
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
            static int idx_Boss_1 = -1;

            if(boss_alive == false && SDL_GetTicks() - lastBossAddedTime >= TIME_TO_RESET_BOSS){
                boss_alive = true;
                initializeThreats(p_threats, 1, gNameBoss1, 1);
                idx_Boss_1 = p_threats.size() - 1;
                p_threats[idx_Boss_1]->Set_sprite_clips();
                p_threats[idx_Boss_1]->setPos2(BOSS_WIDTH, BOSS_HEIGHT);
                p_threats[idx_Boss_1]->set_heal_bar();
                p_threats[idx_Boss_1]->set_heal_bar_texture(SDLCommonFunc::loadImage("images/ThreatsObject/heal_bar.png"));
                battle_music = false;
                // Pause music
                if(Mix_PlayingMusic() != 0){
                    Mix_PauseMusic();
                }
                if(bossBattle != NULL){
                    Mix_PlayMusic(bossBattle, -1);
                }
                lastBossAddedTime = SDL_GetTicks();
            }

            if(SDL_GetTicks() - lastEnemyAddedTime >= TIME_TO_ADD_ENEMY && boss_alive == false){
                initializeThreats(p_threats, 1, gNameThreatsObject, 0);
                for(int i = p_threats.size() - 1; i >= p_threats.size() - 1; i--){
                    p_threats[i]->Set_sprite_clips_1();
                }
                lastEnemyAddedTime = SDL_GetTicks();
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

                    if(have_stun){
                        handle_stun(stun_a, p_threats, have_stun, start_stun);
                    }
                    else{
                        p_threat->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                    }

                    /* ------------------CHECK COLLISION-------------------*/   

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
                                    
                                    if(currentKilled != 0 && currentKilled % 5 == 0 && !rocketAdded) mainTank.setRocket(++currentRocket);

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
                                        lastEnemyAddedTime = SDL_GetTicks();
                                    }
                                }
                                mainTank.removeBullet(j);

                            }
                        }
                    }

                    if(currentKilled % 5 != 0) rocketAdded = false;

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
                                    
                                    if(currentKilled != 0 && currentKilled % 5 == 0 && !rocketAdded) mainTank.setRocket(++currentRocket);

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
                                        lastEnemyAddedTime = SDL_GetTicks();
                                    }
                                    mainTank.removeRocket(r);
                                }
                            }
                        }
                    }

                    // RUN SHIELD
                    handle_shield_skill(static_skills_a, mainTank, have_shield, start_shield);

                    if(!have_shield){
                        /* CHECK COLLISON: TANK OBEJCT -> THREATS OBJECT */
                        if(!have_shield){
                            bool isCol = SDLCommonFunc::CheckCollision(mainTank.getPos(), p_threat->getPos(), 0);
                            if(isCol){
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
                                Mix_PlayChannel(-1, gExpSound[1], 0);
                                Mix_PlayChannel(-1, (i != idx_Boss_1) ? gExpSound[0] : bossDie, 0);

                                p_threat->resetThreat();

                                SDL_GameControllerRumble(gController, 32767, 32767, 500);

                                currentHeart -= 1;
                                gNameBulletOfMainTank = nameBulletTank1[0];
                                mainTank.set_speed_bullet(SPEED_BULLET_MAIN_TANK);
                                mainTank.setBulletType(TankObject::SPHERE1);
                                mainTank.setRocketType(TankObject::ROCKET);
                                mainTank.set_speed_rocket(SPEED_ROCKET_MAIN_TANK);
                                mainTank.set_bullet_style(TankObject::NORMAL); 
                                gNameRocket = nameRocket[0];
                            }                    
                        }

                        /* CHECK COLLISON: TANK OBJECT -> BULLET OF THREAT OBJECT */
                        vector<BulletObject*> bull_listThreats = p_threat->getBulletList();
                        for(int k = 0; k < bull_listThreats.size(); k++){
                            BulletObject* aBulletOfThreat = bull_listThreats.at(k);

                            if(static_skills_a.size() !=0) continue;

                            if(aBulletOfThreat != NULL){
                                bool checkColl = SDLCommonFunc::CheckCollision(aBulletOfThreat->getPos(), mainTank.getPos(), 10);
                                if(checkColl){
                                    //Handle EXPLOSION between TANK OBJECT -> BULLET OF THREAT
                                    for(int ex = 0; ex < EXPLODE_ANIMATION_FRAMES; ex++){
                                        int x_pos = mainTank.getPos().x + WIDTH_TANK_OBJECT / 2 - explode.getPos().w / 2;
                                        int y_pos = mainTank.getPos().y + HEIGHT_TANK_OBJECT / 2 - explode.getPos().h / 2;
                                        explode.setPos(x_pos, y_pos);

                                        explode.setFrame(ex);

                                        explode.renderCopy2();

                                        SDL_RenderPresent(gRenderer);
                                    }
                                    SDL_GameControllerRumble(gController, 32767, 32767, 500);
                                    Mix_PlayChannel(-1, gExpSound[1], 0);

                                    p_threat->removeBullet(k);
                                    currentHeart -= 1;   
                                    
                                    gNameBulletOfMainTank = nameBulletTank1[0];
                                    mainTank.set_speed_bullet(SPEED_BULLET_MAIN_TANK);
                                    mainTank.setBulletType(TankObject::SPHERE1);
                                    mainTank.setRocketType(TankObject::ROCKET);
                                    mainTank.set_speed_rocket(SPEED_ROCKET_MAIN_TANK);
                                    mainTank.set_bullet_style(TankObject::NORMAL); 
                                    gNameRocket = nameRocket[0];                                                
                                }
                            }
                        }                
                    }

                    /* RUN + HANDLE GOLD */
                    run_gift_item(gifts_list,mainTank, p_threat, p_threats, currentGold, gNameBulletOfMainTank, gNameRocket);
                }
                explode1.setPos2(EXP_WIDTH, EXP_HEIGHT);

                if(currentHeart == 0){
                    Mix_PauseMusic();
                    SDL_GameControllerRumble(gController, 0, 0, 0);
                    SDL_GameControllerRumble(gController, 32767, 32767, 1000);
                    Mix_PlayChannel(-1, gameOver, 0);
                    SDL_Delay(200);
                    int idx = showEndGame(gRenderer, gFont, timeEndGame, current_time, killedEndGame, goldEndGame);
                    if(idx == 0){
                        clearThreats(p_threats, p_threats.size() - 1, 0);
                        SDLCommonFunc::Clear();
                        quitSDL();
                        quitSDL2();
                        return 0;
                    }
                    else if(idx == 1){
                        quit = true;
                    }
                }
                if(quit == true) break;
            }

            // RUN PREVENT SKILL
            implement_magnet_skill(gifts_list, mainTank, have_magnet, start_skill);
            // RUN TELEPORT SKILL
            run_teleport_for_player(teleport_a, mainTank, have_tele);
            run_animation_for_teleport(teleport_a, mainTank, run_animation);
            // RUN 4 BULLET
            set_time_for_4_bullet(mainTank, have_4_bullet, start_4_bullet);
            // RUN SUPER BULLET
            set_time_for_super_bullet(mainTank, have_super_bullet, start_super_bullet);
            // RUN BULLET SPREAD
            set_time_for_bullet_spread(mainTank, have_bullet_spread, start_bullet_spread);
            // RUN STRAIGHT BREAM
            set_time_for_straight_beam(mainTank, have_straight_beam, start_straight_beam);
            // RUN TRAP BULLET
            set_time_for_trap(mainTank, have_trap, start_trap);
            // RUN BOOSTER
            handle_booster_skill(booster_a, mainTank, have_booster, start_booster);
            // RUN DEFAULT
            run_default_skill(mainTank, have_default, start_default, gNameBulletOfMainTank, gNameRocket);

            // Resume music when get over Turn boss 
            if(boss_alive == false && battle_music == false){
                if(Mix_PlayingMusic() != 0){
                    Mix_PauseMusic();
                }
                if(battleMusic != NULL) Mix_PlayMusic(battleMusic, -1);
                battle_music = true;
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
            blinkImage(warningNoti.getTexture(), warningNoti.getPos(), timeStart, boss_alive, warningBoss);

            timeGame.setText(current_time);
            timeGame.setPos(75, 25);
            timeGame.setPos2(60, 45);
            timeGame.free();
            timeGame.createGameText(gFont);

            string heartToString = to_string(currentHeart);
            heartNumber.setText(heartToString);
            heartNumber.setPos(45, SCREEN_HEIGHT - HEART_HEIGHT + 3);
            heartNumber.setPos2(20, 20);
            heartNumber.free();
            heartNumber.createGameText(gFont);

            string killedToString = to_string(currentKilled);
            Killed.setText(killedToString);
            Killed.setPos(1390, 25);
            Killed.setPos2(40, 40);
            Killed.free();
            Killed.createGameText(gFont);

            string rocketToString = to_string(mainTank.getRocket());
            rocketText.setText(rocketToString);
            rocketText.setPos(123, SCREEN_HEIGHT - HEART_HEIGHT + 3);
            rocketText.setPos2(20, 20);
            rocketText.free();
            rocketText.createGameText(gFont);

            string goldToString = to_string(currentGold);
            goldText.setText(goldToString);
            goldText.setPos(1390, 105);
            goldText.setPos2(40, 40);
            goldText.free();
            goldText.createGameText(gFont);

            SDL_RenderPresent(gRenderer);

            // SET FPS
            frameTime = SDL_GetTicks() - frameStart;
            if(frameDelay > frameTime){
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }

    // CLEAR THREAT TEXTURE
    clearThreats(p_threats, p_threats.size() -1, 0);
    SDLCommonFunc::Clear();
    quitSDL();
    quitSDL2();
    return 0;
}

void initSDL(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(cout, "SDL_Init", true);
    }

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0 ){
        logSDLError(cout, "SDL_Init", true);
    }
    else{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Check for joysticks
		if( SDL_NumJoysticks() < 1 )
		{
			printf( "Warning: No joysticks connected!\n" );
		}
		else
		{
			//Load joystick
			gGameController = SDL_JoystickOpen( 0 );
			if( gGameController == NULL )
			{
				printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
			}
            gController = SDL_GameControllerOpen(0);
			if( gController == NULL )
			{
				printf( "Warning: Unable to open controller! SDL Error: %s\n", SDL_GetError() );
			}
            if (SDL_GameControllerHasRumble(gController)) {
                printf("Controller supports rumble.\n");
            } else {
                printf("Controller does not support rumble.\n");
            }
        }
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
        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        
        //Initialize SDL_ttf
        TTF_Init();
    }

    gFont = TTF_OpenFont("images/Fonts/Terminal.ttf", 25);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(){

    //Free loaded image
    if(gBackground != NULL)
        SDL_DestroyTexture( gBackground );
    gBackground = NULL;

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

    for(auto &item : teleport_a){
        item->free();
        delete item;
    }

    for(auto &item : teleport_b){
        item->free();
        delete item;
    }

    for(auto &item : static_skills_a){
        item->free();
        delete item;
    }

    for(auto &item : static_skills_b){
        item->free();
        delete item;
    }

    for(auto &item : booster_a){
        item->free();
        delete item;
    }

    for(auto &item : booster_b){
        item->free();
        delete item;
    }

    // Giải phóng các đối tượng trong vector p_threats
    for(auto& p_threat : p_threats){
        p_threat->free();
        delete p_threat;
    }
    p_threats.clear();

    SDL_JoystickClose( gGameController );
    gGameController = NULL;

    SDL_GameControllerClose(gController);
    SDL_GameControllerRumble(gController, 0, 0, 0);
    gController = NULL;

}

void logSDLError(ostream& os,const string& msg, bool fatal ){
    cout << msg << "Error: " << SDL_GetError() << endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}

void blinkImage(SDL_Texture* texture, const SDL_Rect& position,const Uint32& timeStart, const bool& boss_alive, Mix_Chunk* sound) {
    static Uint32 lastBlinkTime = 0;
    static bool transparent = false;

    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastBlinkTime > 300) {
        transparent = !transparent;
        lastBlinkTime = currentTime;
    }

    static int idx_mintue = 1;
    if (boss_alive == false && !transparent && (SDL_GetTicks() - timeStart) >= 54678 * idx_mintue && (SDL_GetTicks() - timeStart) <= 56800 * idx_mintue ) {
        if (transparent) {
            SDL_SetTextureAlphaMod(texture, 180);
        } else {
            SDL_SetTextureAlphaMod(texture, 255);
        }

        SDL_RenderCopy(gRenderer, texture, NULL, &position);
        Mix_PlayChannel(-1, sound, 0);
    }

    if (boss_alive == false && (SDL_GetTicks() - timeStart) > 56800 * idx_mintue)
        idx_mintue++;
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

SDL_Texture* SDLCommonFunc::loadImage( string path){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

SDL_Texture* SDLCommonFunc::loadText(string textureText, SDL_Color textColor, TTF_Font* gFont){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface =TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}
