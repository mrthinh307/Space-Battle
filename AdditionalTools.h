#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include "BaseObject.h"

class Tools : public BaseObject
{
public:
    Tools();
    ~Tools();

    SDL_Texture* getGoldItem();
    
    void setGoldValue(const unsigned int& v);
    unsigned  getGoldValue() { return value; }

    void handleMove(const int& x_border, const int& y_border);
private:
    SDL_Texture* goldItem[4];
    int goldWidth[2];
    int goldHeight[2];
    unsigned  value;
};

#endif


