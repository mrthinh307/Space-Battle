#include "ThreatsObject.h"

ThreatsObject::ThreatsObject(){
    x_val = 0;
    y_val = 0;

    rect.x = 0;
    rect.y = 0;
    rect.w = WIDTH_THREATS_OBJECT;
    rect.h = HEIGHT_THREATS_OBJECT;

    // VI TRI THREAT XUAT HIEN
    pos.x = SCREEN_WIDTH;
    pos.y = SCREEN_HEIGHT * 0.5;
    pos.w = WIDTH_THREATS_OBJECT;
    pos.h = HEIGHT_THREATS_OBJECT;
}

ThreatsObject::~ThreatsObject(){
    ;
}

void ThreatsObject::handleMove(const int& x_border, const int& y_border){
    // Tính toán vector di chuyển dựa trên góc degrees
    float rad_angle = degrees * M_PI / 180.0;
    x_val = cos(rad_angle) * THREATS_SPEED; // THREATS_SPEED là tốc độ di chuyển cố định của ThreatsObject
    y_val = sin(rad_angle) * THREATS_SPEED;

    // Cập nhật vị trí của ThreatsObject
    pos.x += x_val / 2;
    pos.y += y_val / 2;
    if(pos.x < 0 || pos.x > x_border || pos.y < 0 || pos.y > y_border){
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
    }
}

void ThreatsObject::setDegrees(const SDL_Rect& posTank){
    SDL_Rect current_pos = getPos();

    float delta_x = posTank.x - current_pos.x;
    float delta_y = posTank.y - current_pos.y;

    float angle = atan2(delta_y, delta_x) * (180.0 / M_PI);

    degrees = angle + 45; // Giả sử hướng mặc định của ThreatsObject là hướng lên trên
}

void ThreatsObject::initBullet(BulletObject* t_bull){
    if(t_bull != NULL){
        bool check = t_bull->loadIMG("images/sphere.png");
        if(check){
            t_bull->setIsMove(true);
            t_bull->setWidthHeight(WIDTH_SPHERE, WIDTH_SPHERE);
            t_bull->setBulletType(BulletObject::SPHERE);
            t_bull->setDegrees(degrees);

            int bullet_start_x = pos.x + WIDTH_THREATS_OBJECT / 2 - WIDTH_SPHERE / 2;
            int bullet_start_y = pos.y + HEIGHT_THREATS_OBJECT / 2 - HEIGHT_SPHERE / 2;
            t_bull->setPos(bullet_start_x, bullet_start_y - HEIGHT_SPHERE / 2); // Điều chỉnh để đạn bắt đầu từ giữa đầu xe tăng

            bulletOfThreatsList.push_back(t_bull);
        }
    }
}

void ThreatsObject::runBullet(const int& x_limit, const int& y_limit){
    for(int i = 0; i < bulletOfThreatsList.size(); ++i){
        BulletObject* aBullet = bulletOfThreatsList.at(i);
        if(aBullet != NULL){
            if(aBullet->getIsMove()){
                SDL_Rect rectBullet = aBullet->getRect();
                SDL_Rect posBullet = aBullet->getPos();
                double flipBullet = aBullet->getDegrees();
                aBullet->renderCopy(posBullet.x, posBullet.y, &rectBullet, flipBullet, NULL, SDL_FLIP_NONE);
                aBullet->handleMoveThreats(x_limit, y_limit);
            }
            else{
                if(aBullet != NULL){
                    aBullet->setIsMove(true);
                    // Set new position
                    int bullet_start_x = pos.x + HEIGHT_THREATS_OBJECT / 2 - WIDTH_SPHERE / 2;
                    int bullet_start_y = pos.y + HEIGHT_THREATS_OBJECT / 2 - HEIGHT_SPHERE / 2;
                    aBullet->setPos(bullet_start_x, bullet_start_y - HEIGHT_SPHERE / 2);  
                    // Set new flip degrees     
                    aBullet->setDegrees(degrees);            
                }
            }
        }
    }
}

void ThreatsObject::handleInputAction(SDL_Event e){
    ;
}
