#ifndef THREATSOBJECT_H_INCLUDED
#define THREATSOBJECT_H_INCLUDED

#include "BaseObject.h"

#define WIDTH_THREATS_OBJECT 30
#define HEIGHT_THREATS_OBJECT 55


class ThreatsbObject : public BaseObject
{
public:
    ThreatsbObject();
    ~ThreatsbObject();

    void handleMove(const int& x_border,const int& y_border);
    void handleInputAction(SDL_Event e);
private:
    int x_val;
    int y_val;

    SDL_Rect pos;
};



#endif