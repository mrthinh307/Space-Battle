#include "HandleGiftItem.h"

vector<Tools*> gifts_list;

unsigned int currentGold = 0;
unsigned int currentHeart = 3;
unsigned int currentKilled = 0;

vector<Tools*> static_skills_a;
vector<Tools*> static_skills_b;
bool have_shield = false;
Uint32 start_shield;

bool have_magnet = false;
Uint32 start_skill;

vector<Tools*> teleport_a;
vector<Tools*> teleport_b;
bool have_tele = false;
bool run_animation = false;
Uint32 start_tele;

bool have_4_bullet = false;
Uint32 start_4_bullet;

bool have_super_bullet = false;
Uint32 start_super_bullet;

bool have_bullet_spread = false;
Uint32 start_bullet_spread;

bool have_straight_beam = false;
Uint32 start_straight_beam;

bool have_trap = false;
Uint32 start_trap;

vector<Tools*> booster_a;
vector<Tools*> booster_b;
bool have_booster = false;
Uint32 start_booster;

vector<Tools*> stun_a;
vector<Tools*> stun_b;
bool have_stun = false;
Uint32 start_stun;

bool have_default = false;
Uint32 start_default;

extern Mix_Chunk* gBulletSound[NUMBER_OF_BULLET_SOUND];
extern Mix_Chunk* gExpSound[NUMBER_OF_EXPLODE_SOUND];
extern Mix_Chunk* gRocketSound;
extern Mix_Chunk* gameOver;
extern Mix_Music* battleMusic;
extern Mix_Chunk* getGold;
extern Mix_Chunk* breakGold;
extern Mix_Chunk* menuButton;
extern Mix_Chunk* buttonAction;
extern Mix_Music* menuMusic;
extern Mix_Chunk* warningBoss;
extern Mix_Chunk* bossDie;
extern Mix_Music* bossBattle;
extern Mix_Chunk* haveShield;
extern Mix_Chunk* breakShield;
extern Mix_Chunk* haveTele;
extern Mix_Chunk* finishTele;
extern Mix_Chunk* bulletUpgrade;
extern Mix_Chunk* defaultSkill;
extern Mix_Chunk* treasureSound;
extern Mix_Chunk* boosterSound;
extern Mix_Chunk* stunSound;


void run_gift_item(vector<Tools*>& gifts_list, TankObject& mainTank, ThreatsObject* p_threat, vector<ThreatsObject*> p_threats,unsigned int& currentGold, string& gNameBulletOfMainTank, string& gNameRocket){
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
                if(gifts_list[a]->get_skill() == Tools::GOLD_1){
                    Mix_PlayChannel(-1, getGold, 0);
                    currentGold += gifts_list[a]->getGoldValue();
                }
                else if(gifts_list[a]->get_skill() == Tools::GOLD_2){
                    Mix_PlayChannel(-1, getGold, 0);
                    currentGold += gifts_list[a]->getGoldValue();
                }
                else if(gifts_list[a]->get_skill() == Tools::SHIELD){
                    if(have_shield == false){
                        Mix_PlayChannel(-1, haveShield, 0);
                        have_shield = true;
                        start_shield = SDL_GetTicks();
                        init_shield_skill(static_skills_a, static_skills_b, object::PLAYER, mainTank, p_threat);                   
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::MAGNET){
                    if(have_magnet == false){
                        Mix_PlayChannel(-1, getGold, 0);
                        start_skill = SDL_GetTicks();
                        have_magnet = true;
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::TELEPORT){
                    if(have_tele == false) {
                        Mix_PlayChannel(-1, haveTele, 0);
                        init_teleport(teleport_a, teleport_b, object::PLAYER, mainTank, p_threat);
                        have_tele = true;
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::X2GOLD){
                    Mix_PlayChannel(-1, getGold, 0);
                    currentGold = currentGold * 2;
                }
                else if(gifts_list[a]->get_skill() == Tools::ADD_ROCKET){
                    Mix_PlayChannel(-1, getGold, 0);
                    unsigned int num = rand() % 3 + 3;
                    mainTank.setRocket(mainTank.getRocket() + num);
                }
                else if(gifts_list[a]->get_skill() == Tools::FOUR_DIRECTIONS_BULLET){
                    if(have_4_bullet == false){
                        Mix_PlayChannel(-1, bulletUpgrade, 0);
                        mainTank.set_bullet_style(TankObject::FOUR_DIRECTIONS_BULLET);
                        have_4_bullet = true;
                        start_4_bullet = SDL_GetTicks();                        
                    }

                }
                else if(gifts_list[a]->get_skill() == Tools::SUPER_BULLET){
                    if(have_super_bullet  == false){
                        Mix_PlayChannel(-1, bulletUpgrade, 0);
                        mainTank.set_bullet_style(TankObject::SUPER_BULLET);
                        have_super_bullet = true;
                        start_super_bullet = SDL_GetTicks();                        
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::BULLET_SPREAD){
                    if(!have_bullet_spread){
                        Mix_PlayChannel(-1, bulletUpgrade, 0);
                        mainTank.set_bullet_style(TankObject::BULLET_SPREAD);
                        have_bullet_spread = true;
                        start_bullet_spread = SDL_GetTicks();                        
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::STRAIGHT_BEAM){
                    if(!have_straight_beam){
                        Mix_PlayChannel(-1, bulletUpgrade, 0);
                        mainTank.set_bullet_style(TankObject::STRAIGHT_BEAM);
                        have_straight_beam = true;
                        start_straight_beam = SDL_GetTicks();                        
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::NEW_BULLET_1){
                    Mix_PlayChannel(-1, bulletUpgrade, 0);
                    gNameBulletOfMainTank = nameBulletTank1[1];
                    mainTank.setBulletType(TankObject::NEW_1);
                }
                else if(gifts_list[a]->get_skill() == Tools::TRAP_BULLET){
                    if(!have_trap){
                        Mix_PlayChannel(-1, bulletUpgrade, 0);
                        mainTank.set_bullet_style(TankObject::TRAP);
                        have_trap = true;
                        start_trap = SDL_GetTicks();
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::ROUNDABOUT){
                    Mix_PlayChannel(-1, bulletUpgrade, 0);
                    gNameBulletOfMainTank = nameBulletTank1[2];
                    mainTank.setBulletType(TankObject::ROUNDABOUT);
                }
                else if(gifts_list[a]->get_skill() == Tools::DEFAULT){
                    Mix_PlayChannel(-1, defaultSkill, 0);
                    if(!have_default){
                        have_default = true;
                        start_default = SDL_GetTicks();
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::TREASURE){
                    Mix_PlayChannel(-1, treasureSound, 0);
                    currentGold += rand() % 21 + 30;
                }
                else if(gifts_list[a]->get_skill() == Tools::BOOSTER){
                    if(have_booster == false){
                        Mix_PlayChannel(-1, boosterSound, 0);
                        start_booster = SDL_GetTicks();
                        have_booster = true;
                        init_booster_skill(booster_a, booster_b, object::PLAYER, mainTank, p_threat);
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::HEART){
                    Mix_PlayChannel(-1, getGold, 0);
                    currentHeart += 1;
                }
                else if(gifts_list[a]->get_skill() == Tools::STUN){
                    if(have_stun == false){
                        Mix_PlayChannel(-1, stunSound, 0);
                        start_stun = SDL_GetTicks();
                        have_stun = true;
                        init_stun(stun_a, stun_b, object::PLAYER, mainTank, p_threats);
                    }
                }
                else if(gifts_list[a]->get_skill() == Tools::TIA_BULLET){
                    Mix_PlayChannel(-1, bulletUpgrade, 0);
                    gNameBulletOfMainTank = nameBulletTank1[3];
                    mainTank.setBulletType(TankObject::TIA_BULLET);                   
                }
                else if(gifts_list[a]->get_skill() == Tools::ROCKET_2){
                    Mix_PlayChannel(-1, bulletUpgrade, 0);
                    gNameRocket = nameRocket[1];
                    mainTank.setRocketType(TankObject::ROCKET_2);
                }
                else if(gifts_list[a]->get_skill() == Tools::PHI_TIEU){
                    Mix_PlayChannel(-1, bulletUpgrade, 0);
                    gNameBulletOfMainTank = nameBulletTank1[4];
                    mainTank.setBulletType(TankObject::PHI_TIEU);
                }
                else if(gifts_list[a]->get_skill() == Tools::SUPER_LASER){
                    Mix_PlayChannel(-1, bulletUpgrade, 0);
                    gNameBulletOfMainTank = nameBulletTank1[5];
                    mainTank.setBulletType(TankObject::SUPER_LASER);                    
                }
                else if(gifts_list[a]->get_skill() == Tools::SPEED_UP_BULLET){
                    Mix_PlayChannel(-1, bulletUpgrade, 0);
                    gNameBulletOfMainTank = nameBulletTank1[6];
                    mainTank.setBulletType(TankObject::SPEED_BULLET);
                }
                else if(gifts_list[a]->get_skill() == Tools::GOLD_5){
                    Mix_PlayChannel(-1, getGold, 0);
                    currentGold += 5;
                }
                else if(gifts_list[a]->get_skill() == Tools::GOLD_8){
                    Mix_PlayChannel(-1, getGold, 0);
                    currentGold += 8;
                }
                delete gifts_list[a];
                gifts_list.erase(gifts_list.begin() + a);
            }
            else ++a;
        }
    }
}

void push_back_gift_item(ThreatsObject* p_threat){
    int ran = rand() % 2 + 1;
    if(ran == 1){
        Tools* a_gift_item = new Tools();
        a_gift_item->set_explode_gift();
        if(a_gift_item != NULL){
            a_gift_item->setPos(p_threat->getPos().x, p_threat->getPos().y);
            bool check = a_gift_item->get_gift();
            gifts_list.push_back(a_gift_item);
        }
    }
}