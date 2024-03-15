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
}

TankObject::~TankObject(){
    ;
}

void TankObject::handleInputAction(SDL_Event e) {
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
            bullet->loadIMG("images/defbullet.png");
            bullet->setBulletType(BulletObject::SPHERE);
            bullet->setx_val(8.0);
            bullet->setDegrees(degrees);
            bullet->setIsMove(true);

            int bullet_start_x = pos.x + WIDTH_TANK_OBJECT / 2 - WIDTH_SPHERE / 2;
            int bullet_start_y = pos.y + HEIGHT_TANK_OBJECT / 2 - HEIGHT_SPHERE / 2;
            bullet->setPos(bullet_start_x, bullet_start_y - HEIGHT_SPHERE / 2); // Điều chỉnh để đạn bắt đầu từ giữa đầu xe tăng

            bulletOfTankList.push_back(bullet);
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

            BulletObject* aBullet = bulletOfTankList.at(i);
            bulletOfTankList.erase(bulletOfTankList.begin() + idx);

            if(aBullet != NULL){
                delete aBullet;
                aBullet = NULL;
            } 
        }
    }
}
