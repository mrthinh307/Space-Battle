#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <windows.h>

using namespace std;

//NAME OF WINDOW
const string WINDOW_TITLE = "SPACE BATTLE";

//SCREEN
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 844;

const int NUM_THREATS = 4;

const int NUMBER_OF_EXPLODE_SOUND = 2;
const int NUMBER_OF_BULLET_SOUND = 3;

static SDL_Window* gWindow;
static SDL_Surface* gScreenSurface;
static SDL_Renderer* gRenderer;
static SDL_Texture* gBackground;

static Mix_Chunk* gBulletSound[NUMBER_OF_BULLET_SOUND];
static Mix_Chunk* gExpSound[NUMBER_OF_EXPLODE_SOUND];
static Mix_Chunk* gameOver;
static Mix_Music* battleMusic;

static char gNameBackground[] = {"background.jpg"};
static char gNameMainTank[] = {"tank2.png"};
static char gNameThreatsObject = {"60x49.png"};
static char gNameBulletOfMainTank = {"defbullet.png"};
static char gNameBulletOfThreatsObject = {"sphere.png"};

static char gNameBulletSoundOfThreat[] = {"images/SoundEffects/laser.wav"};
static char gNameBulletSoundOfTank[] = {"images/SoundEffects/playerBullet.wav"};

static char gNameExplodeSoundOfThreat[] = {"images/SoundEffects/explosionDefault.wav"};
static char gnameExplodeSoundOfTank[] = {"images/SoundEffects/player_die.wav"};

static char gGameOveMusic[] = {"images/SoundEffects/gameover"};
static char gBattleMusic[] = {"images/SoundEffects/battlemusic"};

namespace SDLCommonFunc
{
    SDL_Texture* loadImage( string path);
    void render(SDL_Texture* loadedTexture, SDL_Rect clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Clear();
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2, int offset);
    void render2(SDL_Texture* loadedTexture, const int& x,const int& y, SDL_Rect* clip);
}
#endif // COMMON_H_INCLUDED
