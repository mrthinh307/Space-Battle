#ifndef TANKOBJECT_H_INCLUDED
#define TANKOBJECT_H_INCLUDED

#include "Common.h"
#include "BaseObject.h"

#define WIDTH_TANK_OBJECT 71
#define HEIGHT_TANK_OBJECT 92

class TankObject : public BaseObject
{
public:
    TankObject();
    ~TankObject();

    void handleInputAction(SDL_Event e);
    void handleMove();
private:
    int x_val;
    int y_val;
};

#endif // TANKOBJECT_H_INCLUDED
