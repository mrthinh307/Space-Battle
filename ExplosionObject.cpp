#include "ExplosionObject.h"

ExplosionObject::ExplosionObject(){

}

ExplosionObject::~ExplosionObject(){

}

void ExplosionObject::setClips(){
    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = EXP_WIDTH;
    clip[0].h = EXP_HEIGHT;

    clip[1].x = EXP_WIDTH;
    clip[1].y = 0;
    clip[1].w = EXP_WIDTH;
    clip[1].h = EXP_HEIGHT;

    clip[2].x = EXP_WIDTH*2;
    clip[2].y = 0;
    clip[2].w = EXP_WIDTH;
    clip[2].h = EXP_HEIGHT;

    clip[3].x = EXP_WIDTH*3;
    clip[3].y = 0;
    clip[3].w = EXP_WIDTH;
    clip[3].h = EXP_HEIGHT;

    clip[4].x = EXP_WIDTH*4;
    clip[4].y = 0;
    clip[4].w = EXP_WIDTH;
    clip[4].h = EXP_HEIGHT;

    clip[5].x = 0;
    clip[5].y = EXP_HEIGHT;
    clip[5].w = EXP_WIDTH;
    clip[5].h = EXP_HEIGHT;

    clip[6].x = EXP_WIDTH;
    clip[6].y = EXP_HEIGHT;
    clip[6].w = EXP_WIDTH;
    clip[6].h = EXP_HEIGHT;

    clip[7].x = EXP_WIDTH*2;
    clip[7].y = EXP_HEIGHT;
    clip[7].w = EXP_WIDTH;
    clip[7].h = EXP_HEIGHT;

    clip[8].x = EXP_WIDTH*3;
    clip[8].y = EXP_HEIGHT;
    clip[8].w = EXP_WIDTH;
    clip[8].h = EXP_HEIGHT;

    clip[9].x = EXP_WIDTH*4;
    clip[9].y = EXP_HEIGHT;
    clip[9].w = EXP_WIDTH;
    clip[9].h = EXP_HEIGHT;

}

void ExplosionObject::renderCopy2(){
    if(frame >= EXPLODE_ANIMATION_FRAMES){
        frame = 0;
    }

    SDLCommonFunc::render2(this->p_object, pos.x , pos.y, &clip[frame]);
}