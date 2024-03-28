
#include "AdditionalTools.h"

Tools::Tools(){

    goldItem[0] = SDLCommonFunc::loadImage("images/Utils/1gold.png");
    goldItem[1] = SDLCommonFunc::loadImage("images/Utils/3gold.png");


    goldWidth[0] = 21;
    goldWidth[1] = 40;


    goldHeight[0] = 26;
    goldHeight[1] = 23;


    value = 0;

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
}

SDL_Texture* Tools::getGoldItem() {
    int randomNumber = rand() % 100 + 1;

    if (randomNumber <= 80 ) { // 40% chance (5% + 40%)
        value = 1;
        pos.w = goldWidth[0];
        pos.h = goldHeight[0];
        return goldItem[0];
    } else { // 30% chance (5% + 40% + 30%)
        value = 3;
        pos.w = goldWidth[1];
        pos.h = goldHeight[1];
        return goldItem[1];
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

void Tools::setGoldTexture(){
    expGold[0] = SDLCommonFunc::loadImage("images/Utils/P103947/exp1.png");
    expGold[1] = SDLCommonFunc::loadImage("images/Utils/P103947/exp2.png");
    expGold[2] = SDLCommonFunc::loadImage("images/Utils/P103947/exp3.png");
    expGold[3] = SDLCommonFunc::loadImage("images/Utils/P103947/exp4.png");
    expGold[4] = SDLCommonFunc::loadImage("images/Utils/P103947/exp5.png");
    expGold[5] = SDLCommonFunc::loadImage("images/Utils/P103947/exp6.png");
    expGold[6] = SDLCommonFunc::loadImage("images/Utils/P103947/exp7.png");
    expGold[7] = SDLCommonFunc::loadImage("images/Utils/P103947/exp8.png");
    expGold[7] = SDLCommonFunc::loadImage("images/Utils/P103947/exp9.png");
}

void Tools::renderCopy2(){
    SDLCommonFunc::render(expGold[frame], pos);
}
