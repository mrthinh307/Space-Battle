#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <windows.h>

using namespace std;

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 800;

const int NUM_THREATS = 4;

const string WINDOW_TITLE = "SPACE BATTLE";

static SDL_Window* gWindow;
static SDL_Surface* gScreenSurface;
static SDL_Renderer* gRenderer;
static SDL_Texture* gBackground;

namespace SDLCommonFunc
{
    SDL_Texture* loadImage( string path);
    void render(SDL_Texture* loadedTexture, SDL_Rect clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Clear();
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2, int offset);
}
#endif // COMMON_H_INCLUDED
//up