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

}

BulletObject::~BulletObject() {
    free();
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

bool BulletObject::check_col_shield = false;

void BulletObject::handleMoveBoss(const int& x_border, const int& y_border){
    const double bullet_speed = y_val;
    pos.x += bullet_speed * sin(degrees * M_PI / 180.0);
    pos.y -= bullet_speed * cos(degrees * M_PI / 180.0); 
    
    if (pos.x < 0 || pos.x > x_border || pos.y < 0 || pos.y > y_border || check_col_shield == true) {
        isMove = false;
    }
}

void BulletObject::setRocketTexture(){
    for(int i = 0; i < 4; i++){
        rocket_tex[i].x = 40 * i;
        rocket_tex[i].y = 0;
        rocket_tex[i].w = 40;
        rocket_tex[i].h = 99;
    }
}

int BulletObject::frame_rocket = 0;

void BulletObject::runRocket(){
    SDL_Rect* currentClip = &rocket_tex[frame_rocket / 4];
    SDLCommonFunc::render_for_sprite(p_object, pos.x, pos.y, currentClip, degrees, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(gRenderer);
       frame_rocket++; 
    if( (frame_rocket / 4) >= 4 )
    {
        frame_rocket = 0;
    }
}

void BulletObject::set_boss_bullet(){
    for(int i = 0; i < 3; i++){
        boss_bullet[i].x = BOSS_BULLET_WIDTH * i;
        boss_bullet[i].y = 0;
        boss_bullet[i].w = BOSS_BULLET_WIDTH;
        boss_bullet[i].h = BOSS_BULLET_HEIGHT;
    }
}

int BulletObject::frame = 0;

void BulletObject::run_boss_bullet(){
    SDL_Rect* currentClip = &boss_bullet[frame / 3];
    SDLCommonFunc::render_for_sprite(p_object, pos.x, pos.y, currentClip, degrees, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(gRenderer);
       frame++; 
    if( (frame / 3) >= 3 )
    {
        frame = 0;
    }
}
