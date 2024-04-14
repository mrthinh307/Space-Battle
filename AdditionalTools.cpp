
#include "AdditionalTools.h"

Tools::Tools(){
    gift_items.resize(NUM_SKILLS);
    item_width.resize(NUM_SKILLS);
    item_height.resize(NUM_SKILLS);

    gift_items[0] = "images/Utils/1gold.png";
    item_width[0] = 33;   item_height[0] = 41;
    gift_items[1] = "images/Utils/3gold.png";
    item_width[1] = 55;   item_height[1] = 32;

    gift_items[2] = "images/Utils/gift/shield.png";
    gift_items[3] = "images/Utils/gift/preventenemy.png";
    gift_items[4] = "images/Utils/gift/x2gold.png";
    gift_items[5] = "images/Utils/gift/booster.png";
    gift_items[6] = "images/Utils/gift/plusrocket.png";
    gift_items[7] = "images/Utils/gift/changetank.png";
    gift_items[8] = "images/Utils/gift/dan4phia.png";
    gift_items[9] = "images/Utils/gift/danloang.png";
    gift_items[10] = "images/Utils/gift/4dan.png";
    gift_items[11] = "images/Utils/gift/new1.png";
    gift_items[12] =  "images/Utils/gift/new2.png";
    gift_items[13] = "images/Utils/gift/gold.png";

    for(int i = 2; i < gift_items.size(); i++){
        item_width[i] = 55;
        item_height[i] = 55;
    }

    value = 0;
    idx_skill = -1;

    startTime = SDL_GetTicks();

    expGold.resize(EXPLODE_GOLD_ANIMATION_FRAMES, NULL);
}

Tools::~Tools(){
    for(int i = 0; i < expGold.size(); i++){
        SDL_Texture* aTexture = expGold.at(i);
        if(aTexture != NULL){
            SDL_DestroyTexture(aTexture);
            aTexture = NULL;
        }
    }
    expGold.clear();  
    free();
}

bool Tools::get_gift() {
    int randomNumber = rand() % 100 + 1;

    if (randomNumber <= 40 ) {
        value = 1;
        pos.w = item_width[0];
        pos.h = item_height[0];
        return loadIMG(gift_items[0]);
    }
    else if(randomNumber <= 30) {
        value = 3;
        pos.w = item_width[1];
        pos.h = item_height[1];
        return loadIMG(gift_items[1]);
    }
    else{
        int random_skill = rand() % (NUM_SKILLS - 2) + 2;
        value = 0;
        idx_skill = random_skill;
        pos.w = item_width[random_skill];
        pos.h = item_height[random_skill];
        return loadIMG(gift_items[random_skill]);
    }
}

void Tools::handleMove(const int& x_border, const int& y_border){
    int move_x = rand() % 3 - 1; 
    int move_y = rand() % 3 - 1; 

    int speed = rand() % 3 + 1; 

    int new_x = pos.x + move_x * speed;
    int new_y = pos.y + move_y * speed;

    new_x = max(0, min(x_border - pos.w, new_x));
    new_y = max(0, min(y_border - pos.h, new_y));

    if (new_x >= x_border || new_x < 0 || new_y >= y_border || new_y < 0) {
        setPos(-100, -100); 
    } else {
        setPos(new_x, new_y);
    }
}

Uint32 Tools::timer(){
    return SDL_GetTicks() - startTime;
}

void Tools::set_explode_gift(){
    expGold[0] = SDLCommonFunc::loadImage("images/Utils/P103947/exp1.png");
    expGold[1] = SDLCommonFunc::loadImage("images/Utils/P103947/exp2.png");
    expGold[2] = SDLCommonFunc::loadImage("images/Utils/P103947/exp3.png");
    expGold[3] = SDLCommonFunc::loadImage("images/Utils/P103947/exp4.png");
    expGold[4] = SDLCommonFunc::loadImage("images/Utils/P103947/exp5.png");
    expGold[5] = SDLCommonFunc::loadImage("images/Utils/P103947/exp6.png");
    expGold[6] = SDLCommonFunc::loadImage("images/Utils/P103947/exp7.png");
    expGold[7] = SDLCommonFunc::loadImage("images/Utils/P103947/exp8.png");
    expGold[8] = SDLCommonFunc::loadImage("images/Utils/P103947/exp9.png");
}

void Tools::renderCopy2(){
    SDLCommonFunc::render(expGold[frame], pos);
}
