#include "TankObject.h"

TankObject::TankObject(){
    rect.x = 0;
    rect.y = 0;
    rect.w = WIDTH_TANK_OBJECT;
    rect.h = HEIGHT_TANK_OBJECT;
    x_val = 0;
    y_val = 0;
}

TankObject::~TankObject(){
    ;
}

void TankObject::handleInputAction(SDL_Event e){
    //todo
    ;
}

void TankObject::handleMove(){
    //todo
    ;
}
