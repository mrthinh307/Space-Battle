#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "BaseObject.h"
#include "Common.h"

const int EXP_WIDTH = 120;
const int EXP_HEIGHT = 108;

const int EXPLODE_ANIMATION_FRAMES = 10;

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void setClips();
    void setFrame(const int& fr) { frame = fr; }

    void renderCopy2();
private:
    int frame;
    SDL_Rect clip[EXPLODE_ANIMATION_FRAMES];

};



#endif