#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include "BaseObject.h"

const int TIME_TO_EXPLODE_GOLD = 5000;
const int EXPLODE_GOLD_ANIMATION_FRAMES = 9;

const int EXP_GOLD_WIDTH = 60;
const int EXP_GOLD_HEIGHT = 90;

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

    void setFrame(const int& fr) { frame = fr; }
    void setGoldTexture();
    void renderCopy2();

    void freeGoldTexture();

private:
    SDL_Texture* goldItem[2];
    int goldWidth[2];
    int goldHeight[2];
    unsigned  value;
    Uint32 startTime;

    int frame;
    vector<SDL_Texture*> expGold;
};

#endif


