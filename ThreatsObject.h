#ifndef THREATSOBJECT_H_INCLUDED
#define THREATSOBJECT_H_INCLUDED

#include "BaseObject.h"

#define WIDTH_THREATS_OBJECT 30
#define HEIGHT_THREATS_OBJECT 55

#define THREATS_SPEED 3
class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    void handleMove(const int& x_border,const int& y_border);
    void handleInputAction(SDL_Event e);

    void setx_val(const int& x) { x_val = x; }
    int getx_val() const { return x_val; }
    void sety_val(const int& y) { y_val = y; }
    int gety_val() const { return y_val; }

    double getDegrees() const {return degrees; }
    void setDegrees(const SDL_Rect& posTank);
    SDL_RendererFlip getFlipType() const { return flipType; }
    void setFlipType (SDL_RendererFlip type) { flipType = type; }

    SDL_Rect getPos() const { return pos; }
    void setPos(const int& x, const int& y) { pos.x = x; pos.y = y; }
private:
    int x_val;
    int y_val;

    SDL_Rect pos;

    double degrees;
    SDL_RendererFlip flipType;
};



#endif