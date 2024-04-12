#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "BaseObject.h"
#include "Common.h"

const int EXP_WIDTH = 180;
const int EXP_HEIGHT = 180;

const int EXPLODE_ANIMATION_FRAMES = 12;

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void setFrame(const int& fr) { frame = fr; }
    void setTexture();
    void renderCopy2();

    void clearTexture();

    void set_expode_sprite_for_boss();
    void run_explode_boss();
private:
    int frame;
    vector<SDL_Texture*> expTexture;
    SDL_Rect boss[5];
    

};

#endif