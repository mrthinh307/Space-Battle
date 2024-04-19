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

