#ifndef TANKOBJECT_H_INCLUDED
#define TANKOBJECT_H_INCLUDED

#include "Common.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define WIDTH_TANK_OBJECT 60
#define HEIGHT_TANK_OBJECT 52

class TankObject : public BaseObject
{
public:
    TankObject();
    ~TankObject();

    void handleInputAction(SDL_Event e, Mix_Chunk* bulletSound[3]);
    void handleMove();

    double getDegrees() const {return degrees; }
    void setDegrees(double d) { degrees = d; }

    SDL_RendererFlip getFlipType() const { return flipType; }
    void setFlipType (SDL_RendererFlip type) { flipType = type; }

    void setBulletList(vector<BulletObject*> bulletList) { bulletOfTankList = bulletList; }
    vector<BulletObject*> getBulletList() const { return bulletOfTankList; }

    void runBullet();
    void removeBullet(const int& idx);
private:
    int x_val;
    int y_val;
    double degrees;
    SDL_RendererFlip flipType;

    vector<BulletObject*> bulletOfTankList;
};

#endif // TANKOBJECT_H_INCLUDED
//up