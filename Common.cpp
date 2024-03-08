#include "Common.h"

SDL_Texture* SDLCommonFunc::loadImage( string path){
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* optimizedSurface = NULL; // the final optimized image

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){
        cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << endl;
    }
    else{
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface -> format, 0);

        if(optimizedSurface == NULL){
            cout << "Unable to optimized surface! SDL Error: " << SDL_GetError() << endl;
        }

        SDL_FreeSurface(loadedSurface);
        newTexture = SDL_CreateTextureFromSurface(gRenderer, optimizedSurface);

        if(newTexture == nullptr){
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(optimizedSurface);
    }
    return newTexture;
}

void SDLCommonFunc::render(SDL_Texture* loadedTexure, int x, int y, SDL_Rect* clip ) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad;
    renderQuad.x = x;
    renderQuad.y = y;
    renderQuad.w = SCREEN_WIDTH;
    renderQuad.h = SCREEN_HEIGHT;

    //Set clip rendering dimmensions
    if(clip != NULL){
        renderQuad.w = clip -> w;
        renderQuad.h = clip -> h;
    }

    //Render to screen 
    SDL_RenderCopy(gRenderer, loadedTexure, clip, &renderQuad);
}

void SDLCommonFunc::Clear()
{
    //Free loaded image
    SDL_DestroyTexture( gBackground );
    gBackground = NULL;

}

