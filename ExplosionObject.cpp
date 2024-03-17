#include "ExplosionObject.h"

ExplosionObject::ExplosionObject(){
    int frame = 0;

    pos.x = 0;
    pos.y = 0;
    pos.w = EXP_WIDTH;
    pos.h = EXP_HEIGHT;

    expTexture.resize(EXPLODE_ANIMATION_FRAMES);
}

ExplosionObject::~ExplosionObject(){
    for(int i = 0; i < EXPLODE_ANIMATION_FRAMES; i++){
        SDL_Texture* aTexture = expTexture.at(i);
        if(aTexture != NULL){
            SDL_DestroyTexture( aTexture );
            aTexture = NULL;
        }
    }
}

void ExplosionObject::setTexture(){
    expTexture[0] = SDLCommonFunc::loadImage("images/P103578/314093101.png");
    expTexture[1] = SDLCommonFunc::loadImage("images/P103578/314093102.png");
    expTexture[2] = SDLCommonFunc::loadImage("images/P103578/314093103.png");
    expTexture[3] = SDLCommonFunc::loadImage("images/P103578/314093104.png");
    expTexture[4] = SDLCommonFunc::loadImage("images/P103578/314093105.png");
    expTexture[5] = SDLCommonFunc::loadImage("images/P103578/314093106.png");
    expTexture[6] = SDLCommonFunc::loadImage("images/P103578/314093107.png");
    expTexture[7] = SDLCommonFunc::loadImage("images/P103578/314093108.png");
    expTexture[8] = SDLCommonFunc::loadImage("images/P103578/314093109.png");
    expTexture[9] = SDLCommonFunc::loadImage("images/P103578/314093110.png");
    expTexture[10] = SDLCommonFunc::loadImage("images/P103578/314093111.png");
    expTexture[11] = SDLCommonFunc::loadImage("images/P103578/314093112.png");
}

void ExplosionObject::renderCopy2(){
    SDLCommonFunc::render(expTexture[frame], pos);
}

