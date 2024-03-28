#include "BulletObject.h"

BulletObject::BulletObject() {

    x_val = 0;
    y_val = 0;
    isMove = false;
    bulletType = NONE;
    
    pos.x = 0;
    pos.y = 0;
    pos.w = WIDTH_LASER;
    pos.h = HEIGHT_LASER;

    rocketTexture.resize(ROCKET_ANIMATION_FRAMES, NULL);
    frame = 0;
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

void BulletObject::handleMoveThreats(const int& x_border, const int& y_border) {
    const double bullet_speed = y_val;
    pos.x += bullet_speed * cos(degrees * M_PI / 180.0);
    pos.y -= bullet_speed * sin(degrees * M_PI / 180.0); 
    
    if (pos.x < 0 || pos.x > x_border || pos.y < 0 || pos.y > y_border) {
        isMove = false;
    }
}

void BulletObject::handleInputAction(SDL_Event e) {
    ;
}

void BulletObject::setRocketTexture(){
    rocketTexture[0] = SDLCommonFunc::loadImage("images/P103720/rocket1.png");
    rocketTexture[1] = SDLCommonFunc::loadImage("images/P103720/rocket2.png");
    rocketTexture[2] = SDLCommonFunc::loadImage("images/P103720/rocket3.png");
    rocketTexture[3] = SDLCommonFunc::loadImage("images/P103720/rocket4.png");
}

void BulletObject::clearRocketTexture(){
    for(int i = 0; i < ROCKET_ANIMATION_FRAMES; i++){
        SDL_Texture* aTexture = rocketTexture.at(i);
        if(aTexture != NULL){
            SDL_DestroyTexture(aTexture);
            aTexture = NULL;
        }
    }
}

void BulletObject::renderCopy2(){
    SDLCommonFunc::render(rocketTexture[frame], pos, degrees);
}

