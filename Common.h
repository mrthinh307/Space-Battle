#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <windows.h>

using namespace std;

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 844;

const int NUM_THREATS = 4;

const string WINDOW_TITLE = "SPACE BATTLE";

static SDL_Window* gWindow;
static SDL_Surface* gScreenSurface;
static SDL_Renderer* gRenderer;
static SDL_Texture* gBackground;

static Mix_Chunk* gBulletSound[3];
static Mix_Chunk* gExpSound[2];
static Mix_Chunk* gameOver;

namespace SDLCommonFunc
{
    SDL_Texture* loadImage( string path);
    void render(SDL_Texture* loadedTexture, SDL_Rect clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Clear();
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2, int offset);
    void render2(SDL_Texture* loadedTexture, const int& x,const int& y, SDL_Rect* clip);
}
#endif // COMMON_H_INCLUDED
