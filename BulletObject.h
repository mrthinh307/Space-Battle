#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED

#include "BaseObject.h"

#define WIDTH_LASER 8
#define HEIGHT_LASER 8

#define WIDTH_SPHERE 5
#define HEIGHT_SPHERE 5

class BulletObject : public BaseObject
{
public:
    enum BulletType {
        NONE = 0,
        SPHERE = 1,
        LASER = 2
    };

    BulletObject();
    ~BulletObject();

    void handleInputAction(SDL_Event e);
    void handleMove(const int& x_border, const int& y_border);
    void handleMoveThreats(const int& x_border, const int& y_border);

    int getBulletType() const { return bulletType; }
    void setBulletType(int type) { bulletType = type; }

    bool getIsMove() const { return isMove; }
    void setIsMove(bool input) { isMove = input; }

    void setWidthHeight(const int& x, const int& y) { rect.w = x; rect.h = y; }

    SDL_Rect getPos() const { return pos; }
    void setPos(int x, int y) { pos.x = x; pos.y = y; }
    
    void setDegrees( double deg) { degrees = deg; }
    double getDegrees() const { return degrees; }

    void setx_val(const double& x) { x_val = x; }
    double getx_val() const { return x_val; }
    void sety_val(const double& y) { y_val = y; }
    double gety_val() const { return y_val; }

private:
    double x_val;
    double y_val;

    bool isMove;

    int bulletType;

    SDL_Rect pos;

    double degrees;
};


#endif
//up