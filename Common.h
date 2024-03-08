#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

const string WINDOW_TITLE = "MARIO";

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Surface* gScreenSurface = NULL;

static SDL_Texture* gBackground = NULL;

static SDL_Event gEvent;

namespace SDLCommonFunc{
    SDL_Texture* loadImage(string path);
    void render(SDL_Texture* loadedTexture, int x, int y, SDL_Rect* clip );
    void Clear();
}

#endif