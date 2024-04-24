#include "HandleSkill.h"

/* SHIELD */
extern Mix_Chunk* haveShield;
extern Mix_Chunk* breakShield;

extern bool have_default;

void init_shield_skill(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, ThreatsObject* p_threat){
    Tools* shield = new Tools();
    shield->loadIMG("images/Skills/Shield/Shield1.png");
    shield->set_sprite_for_shield();

    if(set_for_ == PLAYER) a.push_back(shield);
    else if(set_for_ == ENEMY) b.push_back(shield);
}

void handle_shield_skill(vector<Tools*>& a,const TankObject& mainTank, bool& have_shield,const Uint32& start){
    if(have_shield){
        if(SDL_GetTicks() - start < 10000 && !have_default){
            SDL_Rect posTank = mainTank.getPos();
            int x_ = posTank.x + (posTank.w - 100) / 2;
            int y_ = posTank.y + (posTank.h - 131) / 2;

            for(int i = 0; i < a.size(); i++){            
                a[i]->setDegrees(mainTank.getDegrees());
                a[i]->setPos(x_, y_);
                a[i]->run_shield();
            }
        }
        else{
            for(int i = 0; i < a.size(); i++) delete a[i];
            a.clear();
            have_shield = false;
        }
    }
}

/* MAGNET */
void implement_magnet_skill(vector<Tools*>& gift_list, const TankObject& mainTank, bool& have_magnet, const Uint32& start_skill){
    if(have_magnet){
        if(SDL_GetTicks() - start_skill <= 10000 && !have_default){
            for(int i = 0; i < gift_list.size(); i++){
                gift_list[i]->set_magnet(true);
            }
        }   
        else{
            for(int i = 0; i < gift_list.size(); i++){
                if(gift_list[i] != NULL){
                    gift_list[i]->set_magnet(false);               
                }
            }
            have_magnet = false;
        }     
    }
}

/* TELEPORT */
extern Mix_Chunk* haveTele;
extern Mix_Chunk* finishTele;
extern bool have_tele;
extern bool run_animation;
extern Uint32 start_tele;

void init_teleport(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, ThreatsObject* p_threat){
    Tools* tele = new Tools();
    tele->loadIMG("images/Skills/tele.png");
    tele->set_sprite_for_teleport();

    if(set_for_ == PLAYER) a.push_back(tele);
    else if(set_for_ == ENEMY) b.push_back(tele);
}

void run_teleport_for_player(vector<Tools*>& a, TankObject& mainTank, bool& have_tele) {
    static bool mouseClicked = false;

    if (a.empty() || !have_tele) return;

    if(!mouseClicked){
        SDL_Event event;
        while (!mouseClicked) {
            while(SDL_PollEvent(&event)){
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    mainTank.setPos(mouseX, mouseY);
                    start_tele = SDL_GetTicks();

                    int dx = mouseX - mainTank.getPos().x;
                    int dy = mouseY - mainTank.getPos().y;

                    if (dx == 0 && dy == 0) {
                        mainTank.setXVal(0);
                        mainTank.setYVal(0);
                    } else {
                        mainTank.setXVal(dx > 0 ? 1 : -1);
                        mainTank.setYVal(dy > 0 ? 1 : -1);
                        mainTank.setDegrees(atan2(dy, dx) * 180 / M_PI);
                    }
                    mouseClicked = true;
                    have_tele = false;
                    run_animation = true;
                    break;
                }                
            }
        }
    }

    Mix_PlayChannel(-1, finishTele, 0);
    
    lastX = mainTank.getPos().x;
    lastY = mainTank.getPos().y;

    mouseClicked = false;
    have_tele = false;
}

void run_animation_for_teleport(vector<Tools*>& a, const TankObject& mainTank, bool& run_animation){
    if(run_animation){
        if(SDL_GetTicks() - start_tele < 3000){
            for(int i = 0; i < a.size(); i++){
                SDL_Rect pos = mainTank.getPos();
                a[i]->setPos(pos.x + (pos.w - 80) / 2, pos.y + (pos.h - 141) / 2);
                a[i]->run_teleport();
            }
        }
        else{
            for(int i = 0; i < a.size(); i++) delete a[i];
            a.clear();
            run_animation = false;
        }
    }
}

/* 4_BULLET */
void set_time_for_4_bullet(TankObject& mainTank, bool& have_4_bullet, const Uint32& start){
    if(have_4_bullet){
        if(SDL_GetTicks() - start > 30000){
            mainTank.set_bullet_style(TankObject::NORMAL);
            have_4_bullet = false;
        }
    }
}

/* SUPER_BULLET*/
void set_time_for_super_bullet(TankObject& mainTank, bool& have_super_bullet, const Uint32& start){
    if(have_super_bullet){
        if(SDL_GetTicks() - start > 8000){
            mainTank.set_bullet_style(TankObject::NORMAL);
            have_super_bullet = false;
        }
    }
}

/* BULLET SPREAD */
void set_time_for_bullet_spread(TankObject& mainTank, bool& have_spread, const Uint32& start){
    if(have_spread){
        if(SDL_GetTicks() - start > 30000){
            mainTank.set_bullet_style(TankObject::NORMAL);
            have_spread = false;
        }
    }
}

/* STRAIGHT BEAM */
void set_time_for_straight_beam(TankObject& mainTank, bool& have_straight_beam, const Uint32& start){
    if(have_straight_beam){
        if(SDL_GetTicks() - start > 30000){
            mainTank.set_bullet_style(TankObject::NORMAL);
            have_straight_beam = false;
        }
    }
}

/* TRAP */
void set_time_for_trap(TankObject& mainTank, bool& have_zic_zac, const Uint32& start){
    if(have_zic_zac){
        if(SDL_GetTicks() - start > 20000){
            mainTank.set_bullet_style(TankObject::NORMAL);
            have_zic_zac = false;
        }
    }
}

/* BOOSTER */
void init_booster_skill(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, ThreatsObject* p_threat){
    Tools* booster = new Tools();
    booster->loadIMG("images/Skills/booster.png");
    booster->set_sprite_for_booster();

    if(set_for_ == PLAYER) a.push_back(booster);
    else if(set_for_ == ENEMY) b.push_back(booster);
}

void handle_booster_skill(vector<Tools*>& a, TankObject& mainTank, bool& have_booster, const Uint32& start){
    if(have_booster){
        if(SDL_GetTicks() - start < 10000 && !have_default){
            mainTank.set_tank_speed(DEFAULT_SPEED * 2 + 2);
            SDL_Rect posTank = mainTank.getPos();
            double deg = mainTank.getDegrees();
            int x_, y_;
            if(deg == 0){
                x_ = posTank.x + (posTank.w - 60) / 2;
                y_ = posTank.y + posTank.h - 5;                
            }
            else if(deg == 90){
                x_ = posTank.x - 60;
                y_ = posTank.y + (posTank.h - 88) / 2;
            }
            else if(deg == 180){
                x_ = posTank.x + (posTank.w - 60) / 2;
                y_ = posTank.y - 60;
            }
            else if(deg == -90){
                x_ = posTank.x + posTank.w;
                y_ = posTank.y + (posTank.h - 88) / 2;
            }

            for(int i = 0; i < a.size(); i++){
                a[i]->setPos(x_, y_);
                a[i]->setDegrees(mainTank.getDegrees());

                a[i]->run_booster();                
            }

        }
        else{
            for(int i = 0; i < a.size(); i++) delete a[i];
            a.clear();
            mainTank.set_tank_speed(DEFAULT_SPEED);
            have_booster = false;
        }
    }
}

/* STUN */
void init_stun(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, vector<ThreatsObject*> p_threats){
    if(set_for_ == PLAYER){
        for(int i = 0; i < p_threats.size(); i++){
            Tools* stun = new Tools();
            stun->loadIMG("images/Skills/stun.png");
            stun->set_sprite_for_stun();
            a.push_back(stun);
        }
    }
    else if(set_for_ == ENEMY){
        Tools* stun = new Tools();
        stun->loadIMG("images/Skills/stun.png");
        stun->set_sprite_for_stun();
        b.push_back(stun);
    }
}

void handle_stun(vector<Tools*>& a, vector<ThreatsObject*>& p_threats, bool& have_stun, const Uint32& start){
    if(have_stun){
        if(SDL_GetTicks() - start < 5000 && !have_default){
            for(int i = 0; i < a.size(); i++){
                SDL_Rect pos = p_threats[i]->getPos();
                a[i]->setPos(pos.x + (pos.w - 150) / 2, pos.y + (pos.h - 109) / 2);
                a[i]->run_stun();
            }
        }
        else{
            for(int i = 0; i < a.size(); i++) delete a[i];
            a.clear();
            have_stun = false;
        }
    }
}

/* DEFAULT */
void run_default_skill(TankObject& mainTank, bool& have_default, const Uint32& start, string &gNameBulletOfMainTank, string &gNameRocket){
    if(have_default){
        if(SDL_GetTicks() - start > 10000){
            have_default = false;
        }
        else{
            gNameBulletOfMainTank = nameBulletTank1[0];
            gNameRocket = nameRocket[0];
            mainTank.set_speed_bullet(SPEED_BULLET_MAIN_TANK);
            mainTank.setBulletType(TankObject::SPHERE1);
            mainTank.setRocketType(TankObject::ROCKET);
            mainTank.set_speed_rocket(SPEED_ROCKET_MAIN_TANK);
            mainTank.set_bullet_style(TankObject::NORMAL);
        }
    }
}
