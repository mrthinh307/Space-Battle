#include "TankObject.h"

TankObject::TankObject(){
    x_val = 0;
    y_val = 0;

    pos.x = (SCREEN_WIDTH - WIDTH_TANK_OBJECT) / 2;
    pos.y = (SCREEN_HEIGHT - HEIGHT_TANK_OBJECT) / 2;
    pos.w = WIDTH_TANK_OBJECT;
    pos.h = HEIGHT_TANK_OBJECT;

    degrees = 0;
    flipType = SDL_FLIP_NONE;

    currentRocket = 0;
}

int TankObject::bullet_style = TankObject::NORMAL;

TankObject::~TankObject() {
    for (int i = 0; i < bulletOfTankList.size(); ++i) {
        BulletObject* p_bullet = bulletOfTankList.at(i);
        if(p_bullet != NULL){
            delete p_bullet;
            p_bullet = NULL;            
        }
    }
    bulletOfTankList.clear();

    for (int i = 0; i < rocketOfTankList.size(); ++i) {
        BulletObject* p_rocket = rocketOfTankList.at(i);
        if (p_rocket != nullptr) {
            if(gNameRocketSoundOfTank != NULL){
                Mix_FreeChunk(gRocketSound);
                gRocketSound = NULL;
            }
            delete p_rocket;
            p_rocket = NULL;
        }
    }
    rocketOfTankList.clear();
}


void TankObject::handleInputAction(SDL_Event e, Mix_Chunk* bulletSound[NUMBER_OF_BULLET_SOUND]) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                y_val = -1;
                if (x_val == 1) {
                    degrees = 45;
                } else if (x_val == -1) {
                    degrees = -45; 
                } else {
                    degrees = 0; 
                }
                break;
            case SDLK_d:
                x_val = 1;
                if (y_val == -1) {
                    degrees = 45; 
                } else if (y_val == 1) {
                    degrees = 135; 
                } else {
                    degrees = 90; 
                }
                break;
            case SDLK_a:
                x_val = -1;
                if (y_val == -1) {
                    degrees = -45; 
                } else if (y_val == 1) {
                    degrees = -135; 
                } else {
                    degrees = -90; 
                }
                break;
            case SDLK_s:
                y_val = 1;
                if (x_val == 1) {
                    degrees = 135; 
                } else if (x_val == -1) {
                    degrees = -135;
                } else {
                    degrees = 180;
                }
                break;
            default:
                break;
        }
    }else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s:
                y_val = 0;
                if (x_val == 1) {
                    degrees = 90; 
                } else if (x_val == -1) {
                    degrees = -90; 
                }
                break;
            case SDLK_d:
            case SDLK_a:
                x_val = 0;
                // Cập nhật lại góc xoay khi thả phím di chuyển theo trục x
                if (y_val == 1) {
                    degrees = 180; // Hướng xuống dưới
                } else if (y_val == -1) {
                    degrees = 0; // Hướng lên trên
                }
                break;
            default:
                break;
        }
    }
    if(e.type == SDL_MOUSEBUTTONDOWN){
        if(e.button.button == SDL_BUTTON_LEFT){
            if(bullet_style == TankObject::NORMAL){
                BulletObject* bullet = new BulletObject();
                bullet->setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
                bullet->loadIMG(gNameBulletOfMainTank);
                bullet->setBulletType(BulletObject::SPHERE1);
    
                Mix_PlayChannel(-1, bulletSound[1], 0);

                bullet->setx_val(SPEED_BULLET_MAIN_TANK);
                bullet->setDegrees(degrees);
                bullet->setIsMove(true);

                int bullet_start_x = pos.x + WIDTH_TANK_OBJECT / 2 - WIDTH_SPHERE / 2;
                int bullet_start_y = pos.y + HEIGHT_TANK_OBJECT / 2 - HEIGHT_SPHERE / 2;
                bullet->setPos(bullet_start_x, bullet_start_y - HEIGHT_SPHERE / 2); // Điều chỉnh để đạn bắt đầu từ giữa đầu xe tăng

                bulletOfTankList.push_back(bullet);                
            }
            else if(bullet_style == TankObject::FOUR_DIRECTIONS_BULLET){
                four_directions_bullet();
            }

        }

        else if(e.button.button == SDL_BUTTON_RIGHT){
            if (!rocketOfTankList.empty()) {
                return; 
            }
            if (currentRocket <= 0) {  
                return; 
            }
            currentRocket--;  

            Mix_PlayChannel(-1, gRocketSound, 0);

            BulletObject* rocket = new BulletObject();
            rocket->loadIMG("images/Bullets/rocket.png");
            rocket->setWidthHeight(ROCKET_WIDTH, ROCKET_HEIGHT);
            rocket->setRocketTexture();
            rocket->setBulletType(BulletObject::ROCKET);

            rocket->setx_val(SPEED_ROCKET_MAIN_TANK);
            rocket->setDegrees(degrees);
            rocket->setIsMove(true);

            int rocket_start_x = pos.x + WIDTH_TANK_OBJECT / 2 - ROCKET_WIDTH / 2;
            int rocket_start_y = pos.y + HEIGHT_TANK_OBJECT / 2 - ROCKET_HEIGHT / 2;
            rocket->setPos(rocket_start_x, rocket_start_y);

            rocketOfTankList.push_back(rocket);
        }
    }
    
}

void TankObject::handleMove() {
    pos.x += x_val * (WIDTH_TANK_OBJECT / 15);
    pos.y += y_val * (HEIGHT_TANK_OBJECT / 15);

    if (pos.x < 0) {
        pos.x = SCREEN_WIDTH - pos.w;
    } else if (pos.x + pos.w > SCREEN_WIDTH) {
        pos.x = 0;
    }

    if (pos.y < 0) {
        pos.y = SCREEN_HEIGHT - pos.h;
    } else if (pos.y + pos.h > SCREEN_HEIGHT) {
        pos.y = 0;
    }

    flipType = SDL_FLIP_NONE;
}

void TankObject::runBullet(){  
    for(int i = 0; i < bulletOfTankList.size(); i++){
        BulletObject* p_bullet = bulletOfTankList.at(i);
        if(p_bullet != NULL){
            if(p_bullet->getIsMove()){
                SDL_Rect posBullet = p_bullet->getPos();
                double flipBullet = p_bullet->getDegrees();
                p_bullet->renderCopy(posBullet, flipBullet, NULL, SDL_FLIP_NONE);
                p_bullet->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT); 
            }
            else{
                if(p_bullet != NULL){
                    delete p_bullet; 
                    p_bullet = NULL;
                    bulletOfTankList.erase(bulletOfTankList.begin() + i);
                }
            }
        }
    }  
}

void TankObject::removeBullet(const int& idx){
    for(int i = 0; i < bulletOfTankList.size(); i++){
        if(idx < bulletOfTankList.size()){

            BulletObject* aBullet = bulletOfTankList.at(idx);
            bulletOfTankList.erase(bulletOfTankList.begin() + idx);

            if(aBullet != NULL){
                delete aBullet;
                aBullet = NULL;
            } 
        }
    }
}

void TankObject::runRocket() {
    for (int i = rocketOfTankList.size() - 1; i >= 0; i--){
        BulletObject* aRocket = rocketOfTankList.at(i);
        if (aRocket != NULL && aRocket->getIsMove()) {
            aRocket->runRocket(); 
            aRocket->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT); 
            
            if (!aRocket->getIsMove()) {
                removeRocket(i);
            }
        }
    }
}

void TankObject::removeRocket(const int& idx){
    for(int i = 0; i < rocketOfTankList.size(); i++){
        if(idx < rocketOfTankList.size()){
            BulletObject* aRocket = rocketOfTankList.at(idx);
            rocketOfTankList.erase(rocketOfTankList.begin() + idx);
            if(aRocket != NULL){
                aRocket->free();
                aRocket = NULL;
            } 
        }
    }
}

int TankObject::frame = 0;

void TankObject::Set_sprite_clips(){
    spriteTank_1[0].x = 0;
    spriteTank_1[0].y = 0;
    spriteTank_1[0].w = 70;
    spriteTank_1[0].h = 67;

    spriteTank_1[1].x = 70;
    spriteTank_1[1].y = 0;
    spriteTank_1[1].w = 70;
    spriteTank_1[1].h = 67;

    spriteTank_1[2].x = 140;
    spriteTank_1[2].y = 0;
    spriteTank_1[2].w = 70;
    spriteTank_1[2].h = 67;
    
    spriteTank_1[3].x = 210;
    spriteTank_1[3].y = 0;
    spriteTank_1[3].w = 70;
    spriteTank_1[3].h = 67;

    spriteTank_1[4].x = 280;
    spriteTank_1[4].y = 0;
    spriteTank_1[4].w = 70;
    spriteTank_1[4].h = 67;
}

void TankObject::runMainTank(){
    SDL_Rect* currentClip = &spriteTank_1[frame / TANK_1_FRAME];
    SDLCommonFunc::render_for_sprite(p_object, pos.x, pos.y, currentClip, degrees, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(gRenderer);
       frame++; 
    if( (frame / TANK_1_FRAME) >= TANK_1_FRAME )
    {
        frame = 0;
    }
}

void TankObject::four_directions_bullet() {
    for (int i = 0; i < 4; i++) {
        BulletObject* new_bullet = new BulletObject();
        bool check = new_bullet->loadIMG(gNameBulletOfMainTank);
        new_bullet->setIsMove(true);
        new_bullet->setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
        new_bullet->setBulletType(BulletObject::SPHERE1);  
        new_bullet->setDegrees((i*90)%360);
        new_bullet->setx_val(SPEED_BULLET_MAIN_TANK);

        Mix_PlayChannel(-1, gBulletSound[1], 0);

        int bullet_start_x = pos.x + pos.w / 2 - WIDTH_SPHERE / 2;
        int bullet_start_y = pos.y + pos.h / 2 - HEIGHT_SPHERE / 2;
        new_bullet->setPos(bullet_start_x, bullet_start_y + HEIGHT_SPHERE / 2); 

        bulletOfTankList.push_back(new_bullet);
    }
}

void TankObject::run_four_bullet(const int& x_limit, const int& y_limit){
    for(int i = 0; i < bulletOfTankList.size(); i++){
        BulletObject* aBullet = bulletOfTankList.at(i);
        if(aBullet != NULL){
            if(aBullet->getIsMove()){
                aBullet->renderCopy(aBullet->getPos(), aBullet->getDegrees(), NULL, SDL_FLIP_NONE);
                aBullet->handleMove(x_limit, y_limit);
            }
            else{
                if(aBullet != NULL){
                    delete aBullet; 
                    aBullet = NULL;
                    bulletOfTankList.erase(bulletOfTankList.begin() + i);
                }
            }
        }
    }        
}
