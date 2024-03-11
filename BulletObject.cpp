#include "BulletObject.h"

BulletObject::BulletObject() {
    // LẤY TOÀN BỘ KÍCH THƯỚC ĐẠN
    rect.x = 0;
    rect.y = 0;
    rect.w = WIDTH_LASER;
    rect.h = HEIGHT_LASER;

    x_val = 0;
    y_val = 0;
    isMove = false;
    bulletType = NONE;

    // VỊ TRÍ ĐẠN XUẤT HIỆN
    pos.x = 0;
    pos.y = 0;
    pos.w = WIDTH_LASER;
    pos.h = HEIGHT_LASER;
}

BulletObject::~BulletObject() {
    ;
}

void BulletObject::handleMove(const int& x_border, const int& y_border) {
    const double bullet_speed = x_val;
    pos.x += bullet_speed * sin(degrees * M_PI / 180.0);
    pos.y -= bullet_speed * cos(degrees * M_PI / 180.0); 
    
    if (pos.x < 0 || pos.x > x_border || pos.y < 0 || pos.y > y_border) {
        isMove = false;
    }
}
//up
void BulletObject::handleMoveThreats(const int& x_border, const int& y_border) {
    const double bullet_speed = y_val;
    pos.x += bullet_speed * sin(degrees * M_PI / 180.0);
    pos.y -= bullet_speed * cos(degrees * M_PI / 180.0); 
    
    if (pos.x < 0 || pos.x > x_border || pos.y < 0 || pos.y > y_border) {
        isMove = false;
    }
}

void BulletObject::handleInputAction(SDL_Event e) {
    ;
}