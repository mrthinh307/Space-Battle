#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "Common.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void renderCopy( int x, int y, SDL_Rect* clip = NULL, double degrees = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    bool loadIMG(string path);

    void setRect(int x_, int y_) { rect.x = x_; rect.y = y_; }
    SDL_Rect getRect() const { return rect; }
    SDL_Texture* getTexture() const { return p_object; }

protected:
    SDL_Texture* p_object;
    SDL_Rect rect;
};

#endif // BASEOBJECT_H_INCLUDED
