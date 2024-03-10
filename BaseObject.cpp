#include "BaseObject.h"

BaseObject::BaseObject(){
    rect.x = 0;
    rect.y = 0;
    p_object = NULL;
}

BaseObject::~BaseObject(){
    //Free texture if it exists
    if( p_object != NULL )
    {
        SDL_DestroyTexture( p_object );
        p_object = NULL;
    }
}

bool BaseObject::loadIMG(string path){
    p_object = SDLCommonFunc::loadImage(path);
    return p_object != NULL;
}

void BaseObject::renderCopy( int x, int y, SDL_Rect* clip, double degrees, SDL_Point* center, SDL_RendererFlip flip){
    if(p_object != NULL){
        SDLCommonFunc::render(p_object, x, y, clip, degrees, center, flip);
    }
}
