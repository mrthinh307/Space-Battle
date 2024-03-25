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

TankObject::~TankObject(){
    ;
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
            BulletObject* bullet = new BulletObject();
            bullet->setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
            bullet->loadIMG(gNameBulletOfMainTank);
            bullet->setBulletType(BulletObject::SPHERE1);

            //Mix_PlayChannel(-1, bulletSound[1], 0);

            bullet->setx_val(SPEED_BULLET_MAIN_TANK);
            bullet->setDegrees(degrees);
            bullet->setIsMove(true);

            int bullet_start_x = pos.x + WIDTH_TANK_OBJECT / 2 - WIDTH_SPHERE / 2;
            int bullet_start_y = pos.y + HEIGHT_TANK_OBJECT / 2 - HEIGHT_SPHERE / 2;
            bullet->setPos(bullet_start_x, bullet_start_y - HEIGHT_SPHERE / 2); // Điều chỉnh để đạn bắt đầu từ giữa đầu xe tăng

            bulletOfTankList.push_back(bullet);
        }

        else if(e.button.button == SDL_BUTTON_RIGHT){
            if (!rocketOfTankList.empty()) {  // Kiểm tra xem có bullet đang di chuyển không
                return;  // Nếu có, không cho phép bắn thêm
            }
            if (currentRocket <= 0) {  // Kiểm tra xem còn rocket để bắn không
                return;  // Nếu không, không cho phép bắn
            }
            currentRocket--;  // Giảm số lượng rocket khi bắn

            BulletObject* rocket = new BulletObject();
            rocket->setWidthHeight(ROCKET_WIDTH, ROCKET_HEIGHT);
            rocket->loadIMG(gNameRocket);
            rocket->setBulletType(BulletObject::ROCKET);

            Mix_PlayChannel(-1, gRocketSound, 0);

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

    // Check screen boundaries and wrap around if necessary
    if (pos.x < 0) {
        pos.x = SCREEN_WIDTH - pos.w; // Xuất hiện ở phía đối diện của màn hình
    } else if (pos.x + pos.w > SCREEN_WIDTH) {
        pos.x = 0; // Xuất hiện ở phía đối diện của màn hình
    }

    if (pos.y < 0) {
        pos.y = SCREEN_HEIGHT - pos.h; // Xuất hiện ở phía đối diện của màn hình
    } else if (pos.y + pos.h > SCREEN_HEIGHT) {
        pos.y = 0; // Xuất hiện ở phía đối diện của màn hình
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
                    bulletOfTankList.erase(bulletOfTankList.begin() + i);
                    delete p_bullet; 
                    p_bullet = NULL;
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

void TankObject::runRocket(){
    for(int i = 0; i < rocketOfTankList.size(); i++){
        BulletObject* aRocket = rocketOfTankList.at(i);
        if(aRocket != NULL){
            if(aRocket->getIsMove()){
                SDL_Rect posRocket = aRocket->getPos();
                double flipRocket = aRocket->getDegrees();
                aRocket->renderCopy(posRocket, flipRocket, NULL, SDL_FLIP_NONE);
                aRocket->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT); 
            }
            else{
                if(aRocket != NULL){
                    rocketOfTankList.erase(rocketOfTankList.begin() + i);
                    delete aRocket; 
                    aRocket = NULL;
                }
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
                delete aRocket;
                aRocket = NULL;
            } 
        }
    }
}
