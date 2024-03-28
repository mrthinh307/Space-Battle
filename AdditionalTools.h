#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include "BaseObject.h"

const int TIME_TO_EXPLODE_GOLD = 5000;

class Tools : public BaseObject
{
public:
    Tools();
    ~Tools();

    SDL_Texture* getGoldItem();
    
    void setGoldValue(const unsigned int& v);
    unsigned  getGoldValue() { return value; }

    void handleMove(const int& x_border, const int& y_border);

    Uint32 timer();
private:
    SDL_Texture* goldItem[4];
    int goldWidth[2];
    int goldHeight[2];
    unsigned  value;
    Uint32 startTime;
};

#endif


