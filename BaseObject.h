#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "Common.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void renderCopy(SDL_Rect clip, double degrees = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    bool loadIMG(string path);

    void setPos(int x_, int y_) { pos.x = x_; pos.y = y_; }
    void setPos2(int w_, int h_) { pos.w = w_; pos.h = h_; }
    SDL_Rect getPos() const { return pos; }
    SDL_Texture* getTexture() const { return p_object; }

protected:
    SDL_Texture* p_object;
    SDL_Rect pos;
};

#endif // BASEOBJECT_H_INCLUDED
//up