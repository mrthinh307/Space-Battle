#ifndef TANKOBJECT_H_INCLUDED
#define TANKOBJECT_H_INCLUDED

#include "Common.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define WIDTH_TANK_OBJECT 30
#define HEIGHT_TANK_OBJECT 55

class TankObject : public BaseObject
{
public:
    TankObject();
    ~TankObject();

    void handleInputAction(SDL_Event e);
    void handleMove();
    void updateDirectionAndSpeed(bool key_w, bool key_s, bool key_a, bool key_d);

    SDL_Rect getPos() const { return pos; }
    void setPos(int x, int y) { pos.x  = x; pos.y = y;}

    double getDegrees() const {return degrees; }
    void setDegrees(double d) { degrees = d; }

    SDL_RendererFlip getFlipType() const { return flipType; }
    void setFlipType (SDL_RendererFlip type) { flipType = type; }

    void setBulletList(vector<BulletObject*> bulletList) { bulletOfTankList = bulletList; }
    vector<BulletObject*> getBulletList() const { return bulletOfTankList; }
private:
    int x_val;
    int y_val;
    SDL_Rect pos;
    double degrees;
    SDL_RendererFlip flipType;

    vector<BulletObject*> bulletOfTankList;
};

#endif // TANKOBJECT_H_INCLUDED
