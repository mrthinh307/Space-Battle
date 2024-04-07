#include "FontText.h"

FontText::FontText(){
    
}

FontText::~FontText(){
    free();
}

void FontText::createGameText(TTF_Font* font){
    p_object = SDLCommonFunc::loadText(text, textColor, font);
    renderCopy(pos);
}