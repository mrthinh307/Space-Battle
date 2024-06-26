#include "ThreatsObject.h"

ThreatsObject::ThreatsObject(){
    x_val = 0;
    y_val = 0;

    pos.x = SCREEN_WIDTH / 2;
    pos.y = SCREEN_HEIGHT / 2;
    pos.w = WIDTH_THREATS_OBJECT;
    pos.h = HEIGHT_THREATS_OBJECT;

    flipType = SDL_FLIP_NONE;

    heal_bar_tex = NULL;
    num_blood = 0;
}

ThreatsObject::~ThreatsObject(){
    if(bulletOfThreatsList.size() > 0){
        for(int i = 0; i < bulletOfThreatsList.size(); i++){
            BulletObject* t_bull = bulletOfThreatsList.at(i);
            if(t_bull != NULL){
                delete t_bull;
            }
            t_bull = NULL;
        }
        bulletOfThreatsList.clear();
    }

}

int ThreatsObject::frame = 0;

void ThreatsObject::Set_sprite_clips(){
    spriteBoss_1[0].x = 0;
    spriteBoss_1[0].y = 0;
    spriteBoss_1[0].w = 200;
    spriteBoss_1[0].h = 100;

    spriteBoss_1[1].x = 200;
    spriteBoss_1[1].y = 0;
    spriteBoss_1[1].w = 200;
    spriteBoss_1[1].h = 100;

    spriteBoss_1[2].x = 400;
    spriteBoss_1[2].y = 0;
    spriteBoss_1[2].w = 200;
    spriteBoss_1[2].h = 100;
    
    spriteBoss_1[3].x = 600;
    spriteBoss_1[3].y = 0;
    spriteBoss_1[3].w = 200;
    spriteBoss_1[3].h = 100;

    spriteBoss_1[4].x = 800;
    spriteBoss_1[4].y = 0;
    spriteBoss_1[4].w = 200;
    spriteBoss_1[4].h = 100;

    spriteBoss_1[5].x = 1000;
    spriteBoss_1[5].y = 0;
    spriteBoss_1[5].w = 200;
    spriteBoss_1[5].h = 100;

    spriteBoss_1[6].x = 1200;
    spriteBoss_1[6].y = 0;
    spriteBoss_1[6].w = 200;
    spriteBoss_1[6].h = 100;

    spriteBoss_1[7].x = 1400;
    spriteBoss_1[7].y = 0;
    spriteBoss_1[7].w = 200;
    spriteBoss_1[7].h = 100;

}

void ThreatsObject::Set_sprite_clips_1(){
    spriteThreats_1[0].x = 0;
    spriteThreats_1[0].y = 0;
    spriteThreats_1[0].w = 70;
    spriteThreats_1[0].h = 61;

    spriteThreats_1[1].x = 70;
    spriteThreats_1[1].y = 0;
    spriteThreats_1[1].w = 70;
    spriteThreats_1[1].h = 61;

    spriteThreats_1[2].x = 140;
    spriteThreats_1[2].y = 0;
    spriteThreats_1[2].w = 70;
    spriteThreats_1[2].h = 61;
    
    spriteThreats_1[3].x = 210;
    spriteThreats_1[3].y = 0;
    spriteThreats_1[3].w = 70;
    spriteThreats_1[3].h = 61;

    spriteThreats_1[4].x = 280;
    spriteThreats_1[4].y = 0;
    spriteThreats_1[4].w = 70;
    spriteThreats_1[4].h = 61;

    spriteThreats_1[5].x = 350;
    spriteThreats_1[5].y = 0;
    spriteThreats_1[5].w = 70;
    spriteThreats_1[5].h = 61;

}

void ThreatsObject::set_heal_bar(){
    for(int i = 0; i < 15; i++){
        heal_bar[i].y = 0;
        heal_bar[i].h = 10;
    }

    heal_bar[0].w = 228;
    heal_bar[1].w = 193;
    heal_bar[2].w = 181;
    heal_bar[3].w = 169;
    heal_bar[4].w = 159;
    heal_bar[5].w = 147;
    heal_bar[6].w = 134;
    heal_bar[7].w = 123;
    heal_bar[8].w = 96;
    heal_bar[9].w = 82;
    heal_bar[10].w = 71;
    heal_bar[11].w = 59;
    heal_bar[12].w = 26;
    heal_bar[13].w = 15;
    heal_bar[14].w = 228;

    heal_bar[0].x = 0;
    heal_bar[1].x = 228;
    heal_bar[2].x = 421;
    heal_bar[3].x = 602;
    heal_bar[4].x = 771;
    heal_bar[5].x = 930;
    heal_bar[6].x = 1077;
    heal_bar[7].x = 1211;
    heal_bar[8].x = 1334;
    heal_bar[9].x = 1430;
    heal_bar[10].x = 1512;
    heal_bar[11].x = 1583;
    heal_bar[12].x = 1642;
    heal_bar[13].x = 1668;
    heal_bar[14].x = 1683;

}

void ThreatsObject::handleMove(const int& x_border, const int& y_border){
    float rad_angle = degrees * M_PI / 180.0;
    x_val = cos(rad_angle) * SPEED_THREATS; 
    y_val = sin(rad_angle) * SPEED_THREATS;

    pos.x += x_val / 2;
    pos.y += y_val / 2;
    if(pos.x < 0 || pos.x > x_border || pos.y < 0 || pos.y > y_border){
        int tmp = rand() % 4;

        if(tmp == 0){
            pos.x = -0;
            pos.y = rand() % SCREEN_HEIGHT;
        }
        else if(tmp == 1){
            pos.x = rand() % SCREEN_WIDTH;
            pos.y = -0;
        }
        else if(tmp == 2){
            pos.x = SCREEN_WIDTH + 0;
            pos.y = rand() % SCREEN_HEIGHT;
        }
        else if(tmp == 3){
            pos.x = rand() % SCREEN_WIDTH;
            pos.y = SCREEN_HEIGHT + 0;
        }
    }
}

float calculateAdjustedAngle(float target_angle, int index) {
    const float MAX_DEVIATION = 11; 
    float deviation = (index * MAX_DEVIATION) - (NUM_THREATS - 1) * MAX_DEVIATION / 2;
    return target_angle + deviation;
}

void ThreatsObject::setDegrees(const SDL_Rect& posTank, int index){
    SDL_Rect current_pos = getPos();

    float delta_x = posTank.x - current_pos.x;
    float delta_y = posTank.y - current_pos.y;

    float angle = atan2(delta_y, delta_x) * (180.0 / M_PI);

    degrees = calculateAdjustedAngle(angle, index);
}

void ThreatsObject::initBullet(BulletObject* t_bull){
    if(t_bull != NULL){
        bool check = t_bull->loadIMG(gNameBulletOfThreatsObject);
        if(check){
            t_bull->setIsMove(true);
            t_bull->setWidthHeight(WIDTH_BULLET_1_ENEMY, HEIGHT_BULLET_1_ENEMY);
            t_bull->setBulletType(BulletObject::SPHERE);

            t_bull->sety_val(SPEED_BULLET_THREATS_OBJECT);
            t_bull->setDegrees(degrees);

            int bullet_start_x = pos.x + pos.w / 2 - t_bull->getPos().w / 2;
            int bullet_start_y = pos.y + pos.h / 2 - t_bull->getPos().h / 2;
            t_bull->setPos(bullet_start_x, bullet_start_y + t_bull->getPos().h / 2); 

            bulletOfThreatsList.push_back(t_bull);
        }
    }
}

void ThreatsObject::runBullet(const int& x_limit, const int& y_limit){
    for(int i = 0; i < bulletOfThreatsList.size(); ++i){
        BulletObject* aBullet = bulletOfThreatsList.at(i);
        if(aBullet != NULL){
            if(aBullet->getIsMove()){
                SDL_Rect posBullet = aBullet->getPos();
                double flipBullet = aBullet->getDegrees();
                aBullet->renderCopy(posBullet, 0.0, NULL, SDL_FLIP_NONE);
                aBullet->handleMoveThreats(x_limit, y_limit);
            }
            else{
                if(aBullet != NULL){
                    aBullet->setIsMove(true);
                    // Set new position
                    int bullet_start_x = pos.x + HEIGHT_THREATS_OBJECT / 2 - WIDTH_BULLET_1_ENEMY / 2;
                    int bullet_start_y = pos.y + HEIGHT_THREATS_OBJECT / 2 - HEIGHT_BULLET_1_ENEMY / 2;
                    aBullet->setPos(bullet_start_x, bullet_start_y - HEIGHT_SPHERE / 2);  
                    // Set new flip degrees     
                    aBullet->setDegrees(degrees);            
                }
            }
        }
    }
}

void ThreatsObject::init_bullet_boss1() {

    for (int i = 0; i < 4; i++) {
        BulletObject* new_bullet = new BulletObject();
        bool check = new_bullet->loadIMG("images/Bullets/bossbullet.png");
        new_bullet->setIsMove(true);
        new_bullet->setWidthHeight(BOSS_BULLET_WIDTH, BOSS_BULLET_HEIGHT);
        new_bullet->setBulletType(BulletObject::BOSS_1_ARROW);  
        new_bullet->set_boss_bullet();
        new_bullet->sety_val(SPEED_BULLET_THREATS_OBJECT);

        int bullet_start_x = pos.x + pos.w / 2 - BOSS_BULLET_WIDTH / 2;
        int bullet_start_y = pos.y + pos.h / 2 - BOSS_BULLET_HEIGHT / 2;
        new_bullet->setPos(bullet_start_x, bullet_start_y); 

        bulletOfThreatsList.push_back(new_bullet);
    }

}

void ThreatsObject::run_bullet_boss(const int& x_limit, const int& y_limit){
    for(int i = 0; i < bulletOfThreatsList.size(); i++){
        BulletObject* aBullet = bulletOfThreatsList.at(i);
        if(aBullet != NULL){
            if(aBullet->getIsMove()){
                aBullet->setDegrees(degrees + i*90 + 90);
                aBullet->run_boss_bullet();
                aBullet->handleMoveBoss(x_limit, y_limit);
            }
            else{
                if(aBullet != NULL){
                    aBullet->setIsMove(true);
                    int bullet_start_x = pos.x + pos.w / 2 - BOSS_BULLET_WIDTH / 2;
                    int bullet_start_y = pos.y + pos.h / 2 - BOSS_BULLET_HEIGHT / 2;
                    aBullet->setPos(bullet_start_x, bullet_start_y );      
                    aBullet->setDegrees(degrees + i*90 + 90);          
                }
            }
        }
    }        
}

void ThreatsObject::resetThreat(){
    int tmp = rand() % 4;

    if(tmp == 0){
        pos.x = 0;
        pos.y = rand() % SCREEN_HEIGHT;
    }
    else if(tmp == 1){
        pos.x = rand() % SCREEN_WIDTH;
        pos.y = 0;
    }
    else if(tmp == 2){
        pos.x = SCREEN_WIDTH;
        pos.y = rand() % SCREEN_HEIGHT;
    }
    else if(tmp == 3){
        pos.x = rand() % SCREEN_WIDTH;
        pos.y = SCREEN_HEIGHT;
    }

    for(int i = 0; i < bulletOfThreatsList.size(); i++){
        BulletObject* aBullet = bulletOfThreatsList.at(i);
        if(aBullet != NULL){
            resetBullet(aBullet);
        }
    }

}

void ThreatsObject::resetBullet(BulletObject* aBullet){
    int bullet_start_x = pos.x + pos.w / 2 - WIDTH_BULLET_1_ENEMY / 2;
    int bullet_start_y = pos.y + pos.h / 2 - HEIGHT_BULLET_1_ENEMY / 2;
    aBullet->setPos(bullet_start_x, bullet_start_y + HEIGHT_BULLET_1_ENEMY / 2); 
}

void ThreatsObject::removeBullet(const int& idx){
    for(int i = 0; i < bulletOfThreatsList.size(); i++){
        
        if(idx < bulletOfThreatsList.size()){
            BulletObject* aBullet = bulletOfThreatsList.at(idx);
            bulletOfThreatsList.erase(bulletOfThreatsList.begin() + idx);

            if(aBullet != NULL){
                delete aBullet;
                aBullet = NULL;
            }
        }
    }
}


void ThreatsObject::runThreats(){
    if(true){
        SDL_Rect* currentClip = &spriteThreats_1[frame / THREATS_1_FRAME];
        SDLCommonFunc::render_for_sprite(p_object, pos.x, pos.y, currentClip, degrees, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(gRenderer);
        frame++;
        if( frame / THREATS_1_FRAME >= THREATS_1_FRAME )
        {
            frame = 0;
        }
    }
}

int ThreatsObject::boss_frame = 0;

void ThreatsObject::runBoss(){
    SDL_Rect* currentClip = &spriteBoss_1[boss_frame / BOSS_1_FRAMES];
    SDLCommonFunc::render_for_sprite(p_object, pos.x, pos.y, currentClip, degrees, NULL, SDL_FLIP_NONE);
    run_heal_bar();
    SDL_RenderPresent(gRenderer);
    boss_frame++;
    if( boss_frame / BOSS_1_FRAMES >= BOSS_1_FRAMES )
    {
        boss_frame = 0;
    }
}


void ThreatsObject::run_heal_bar() {
    int heal_bar_x = pos.x - 10;
    int heal_bar_y = pos.y + pos.h + 18;

    SDL_Rect* currentClip = &heal_bar[num_blood % HEAL_BAR];
    SDLCommonFunc::render_for_sprite(heal_bar_tex, heal_bar_x, heal_bar_y, currentClip, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(gRenderer);
}

