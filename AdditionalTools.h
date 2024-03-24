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
    int getGoldValue() { return value; }
private:
    SDL_Texture* goldItem[4];
    int goldWidth[2];
    int goldHeight[2];
    int value;
};

#endif


