#include "HandleSkill.h"

/* SHIELD */
void init_shield_skill(vector<Tools*>& static_skills_a, vector<Tools*>& static_skills_b,const object& set_for_){
    Tools* shield = new Tools();
    if(shield == NULL) return;
    shield->loadIMG("images/Skills/Shield/cayvcl.png");
    shield->set_sprite_for_shield();
    if(set_for_ == PLAYER){
        static_skills_a.push_back(shield);
    }
    else if(set_for_ == ENEMY){
        static_skills_b.push_back(shield);
    }
}

void handle_move_shield(Tools* shield,const TankObject& mainTank, ThreatsObject* p_threat,const object& set_for_){
    if(shield == NULL || p_threat == NULL) return;
    if(set_for_ == PLAYER){
        shield->setDegrees(mainTank.getDegrees());
        int x_ = mainTank.getPos().x - ((SHIELD_WIDTH - mainTank.getPos().w) / 2);
        int y_ = mainTank.getPos().y - ((SHIELD_HEIGHT - mainTank.getPos().h) / 2);
        shield->setPos(x_, y_);
        shield->run_shield();
    }
    else if(set_for_ == ENEMY){
        shield->setDegrees(p_threat->getDegrees());
        int x_ = p_threat->getPos().x - ((SHIELD_WIDTH - p_threat->getPos().w) / 2);
        int y_ = p_threat->getPos().y - ((SHIELD_HEIGHT - p_threat->getPos().h) / 2);
        shield->setPos(x_, y_);
        shield->run_shield();
    }
}

void shield_vs_bullet(vector<Tools*>& static_skills_a,const TankObject& mainTank, ThreatsObject* p_threat, BulletObject* aBulletOfThreat, const enemy& cur_enemy){
    for(int idx = static_skills_a.size() - 1; idx >= 0; idx--){
        Tools* skill = static_skills_a.at(idx);
        skill->setDegrees(mainTank.getDegrees());
        handle_move_shield(skill, mainTank, p_threat, object::PLAYER);
        bool check_col = SDLCommonFunc::CheckCollision(skill->getPos(), aBulletOfThreat->getPos(), 0);
        if(check_col){
            if(cur_enemy == MINI_THREATS) p_threat->resetBullet(aBulletOfThreat);
            else if(cur_enemy == BOSS) aBulletOfThreat->setIsMove(false);

            //skill->set_shield_frame(skill->get_shield_frame() + 1);
            // if(skill->get_shield_frame() == 3){
                if(static_skills_a[idx] != nullptr) delete static_skills_a[idx];
                static_skills_a.clear();
            // }

        }
    }
}

// bool shield_vs_enemy(vector<Tools*>& static_skills_a,const TankObject& mainTank, ThreatsObject* p_threat){
//     for(int idx = static_skills_a.size() - 1; idx >= 0; idx--){
//         Tools* skill = static_skills_a.at(idx);
//         skill->setDegrees(mainTank.getDegrees());
//         handle_move_shield(skill, mainTank, p_threat, object::PLAYER);
//         bool check_col = SDLCommonFunc::CheckCollision(skill->getPos(), aBulletOfThreat->getPos(), 0);
//         if(check_col){
//             //skill->set_shield_frame(skill->get_shield_frame() + 1);
//             // if(skill->get_shield_frame() == 3){
//                 if(static_skills_a[idx] != nullptr) delete static_skills_a[idx];
//                 static_skills_a.clear();
//             // }
//             return true;
//         }
//     }
//     return false;
// }

/* MAGNET */
void implement_magnet_skill(vector<Tools*>& gift_list, TankObject& mainTank, bool& have_magnet, const Uint32& start_skill){
    if(have_magnet){
        if(SDL_GetTicks() - start_skill <= 10000){
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
void init_teleport(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, ThreatsObject* p_threat){
    Tools* tele = new Tools();
    tele->loadIMG("images/Skills/image1.png");
    tele->set_sprite_for_teleport();

    if(set_for_ == PLAYER) a.push_back(tele);
    else if(set_for_ == ENEMY) b.push_back(tele);
}

void run_teleport_for_player(vector<Tools*>& a, TankObject& mainTank, bool& have_tele) {
    static bool mouseClicked = false;
    static int lastPosX = 0;
    static int lastPosY = 0;

    if (a.empty() || !have_tele) return;

    if(!mouseClicked){
        SDL_Event event;
        while (!mouseClicked) {
            while(SDL_PollEvent(&event)){
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    mainTank.setPos(mouseX, mouseY);
                    Mix_PlayChannel(-1, finishTele, 0);

                    lastPosX = mainTank.getPos().x;
                    lastPosY = mainTank.getPos().y;

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
                }                
            }
        }
    }

    for (int i = 0; i < a.size(); i++) {
        delete a[i];
    }
    a.clear();
    mouseClicked = false;
    have_tele = false;
}

/* 4_BULLET */
void set_time_for_4_bullet(TankObject& mainTank, bool& have_4_bullet, Uint32& start){
    if(have_4_bullet){
        if(SDL_GetTicks() - start > 30000){
            mainTank.set_bullet_style(TankObject::NORMAL);
            have_4_bullet = false;
        }
    }
}

/* SUPER_BULLET*/
void set_time_for_super_bullet(TankObject& mainTank, bool& have_super_bullet, Uint32& start){
    if(have_super_bullet){
        if(SDL_GetTicks() - start > 8000){
            mainTank.set_bullet_style(TankObject::NORMAL);
            have_super_bullet = false;
        }
    }
}

/* BULLET SPREAD */
void set_time_for_bullet_spread(TankObject& mainTank, bool& have_spread, Uint32& start){
    if(have_spread){
        if(SDL_GetTicks() - start > 30000){
            mainTank.set_bullet_style(TankObject::NORMAL);
            have_spread = false;
        }
    }
}

/* STRAIGHT BEAM */
void set_time_for_straight_beam(TankObject& mainTank, bool& have_straight_beam, Uint32& start){
    if(have_straight_beam){
        if(SDL_GetTicks() - start > 30000){
            mainTank.set_bullet_style(TankObject::NORMAL);
            have_straight_beam = false;
        }
    }
}

/* TRAP */
void set_time_for_trap(TankObject& mainTank, bool& have_zic_zac, Uint32& start){
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

void handle_booster_skill(vector<Tools*>& a, TankObject& mainTank, bool& have_booster, Uint32& start){
    if(have_booster){
        if(SDL_GetTicks() - start < 10000){
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
            // else if(deg == 45){
            //     x_ = posTank.x + posTank.w - (30 / 2) + cos(deg * M_PI / 180.0) * posTank.h / 2 - 100;
            //     y_ = posTank.y + posTank.h + sin(deg * M_PI / 180.0) * posTank.h / 2 - 30;
            // }
            // else if(deg == 135){
            //     x_ = posTank.x + posTank.w + cos(deg * M_PI / 180.0) * posTank.h / 2 - 70;
            //     y_ = posTank.y + posTank.h + sin(deg * M_PI / 180.0) * posTank.h / 2 - 120;                
            // }
            // else if(deg == -135){
            //     x_ = posTank.x + posTank.w / 2 - 30 / 2;
            //     y_ = posTank.y + posTank.h;
            // }
            // else if(deg == -45){
            //     x_ = posTank.x + cos(deg * M_PI / 180.0) * posTank.h / 2 - 70;
            //     y_ = posTank.y + sin(deg * M_PI / 180.0) * posTank.h / 2 - 120;
            // }

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

void handle_stun(vector<Tools*>& a, vector<ThreatsObject*>& p_threats, bool& have_stun, Uint32& start){
    if(have_stun){
        if(SDL_GetTicks() - start < 5000){
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