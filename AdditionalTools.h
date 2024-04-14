#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include "BaseObject.h"

const int TIME_TO_EXPLODE_GOLD = 10000;
const int EXPLODE_GOLD_ANIMATION_FRAMES = 9;

const int EXP_GOLD_WIDTH = 60;
const int EXP_GOLD_HEIGHT = 90;

const int NUM_SKILLS = 14;

class Tools : public BaseObject
{
public:
    Tools();
    ~Tools();
    
    void setGoldValue(const unsigned int& v);
    unsigned  getGoldValue() { return value; }

    void handleMove(const int& x_border, const int& y_border);

    Uint32 timer();

    void setFrame(const int& fr) { frame = fr; }
    void set_explode_gift();
    void renderCopy2();

    bool get_gift();

private:
    unsigned value;
    Uint32 startTime;

    int frame;
    vector<SDL_Texture*> expGold;

    vector<string> gift_items;
    vector<int> item_width;
    vector<int> item_height;
    int idx_skill;
};

#endif


