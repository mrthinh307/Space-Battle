
#include "AdditionalTools.h"

Tools::Tools(){

    goldItem[0] = SDLCommonFunc::loadImage("images/Utils/1gold.png");
    goldItem[1] = SDLCommonFunc::loadImage("images/Utils/3gold.png");


    goldWidth[0] = 21;
    goldWidth[1] = 40;


    goldHeight[0] = 26;
    goldHeight[1] = 23;


    value = 0;
}

Tools::~Tools(){
    // TODO: Implement if needed
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
