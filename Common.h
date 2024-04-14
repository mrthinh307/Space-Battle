#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <windows.h>

using namespace std;

//NAME OF WINDOW
const string WINDOW_TITLE = "SPACE BATTLE";

//SCREEN
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 844;

const int LAYOUT_BOX_WIDTH = 238;
const int LAYOUT_BOX_HEIGHT = 126;

const int HEART_WIDTH = 28;
const int HEART_HEIGHT = 39;

const int KILL_ENEMY_WIDTH = 50;
const int KILL_ENEMY_HEIGHT = 50;

const int ROCKET_WIDTH = 38;
const int ROCKET_HEIGHT = 63;

static int NUM_THREATS = 3; // 4 5 6 

const int NUMBER_OF_EXPLODE_SOUND = 2;
const int NUMBER_OF_BULLET_SOUND = 3;

static SDL_Window* gWindow;
static SDL_Surface* gScreenSurface;
static SDL_Renderer* gRenderer;
static SDL_Texture* gBackground;

static TTF_Font* gFont = NULL;

static Mix_Chunk* gBulletSound[NUMBER_OF_BULLET_SOUND];
static Mix_Chunk* gExpSound[NUMBER_OF_EXPLODE_SOUND];
static Mix_Chunk* gRocketSound = NULL;
static Mix_Chunk* gameOver;
static Mix_Music* battleMusic;
static Mix_Chunk* getGold;
static Mix_Chunk* breakGold;
static Mix_Chunk* menuButton;
static Mix_Chunk* buttonAction;
static Mix_Music* menuMusic;
static Mix_Chunk* warningBoss;
static Mix_Chunk* bossDie;
static Mix_Music* bossBattle;

static char gNameBackground[] = {"images/Backgrounds/background.jpg"};
static char gNameMainTank[] = {"images/TankObject/tank1/image1.png"};
static char gNameThreatsObject[] = {"images/ThreatsObject/minithreats.png"};
static char gNameBoss1[] = {"images/ThreatsObject/boss1/image1.png"};

static char gNameBulletOfMainTank[] = {"images/Bullets/defbullet.png"};
static char gNameBulletOfThreatsObject[] = {"images/Bullets/sphere.png"};

static char gNameBulletSoundOfTank[] = {"images/SoundEffects/playerBullet.wav"};
static char gNameRocketSoundOfTank[] = {"images/SoundEffects/runRocket.wav"};

static char gNameExplodeSoundOfThreat[] = {"images/SoundEffects/explosionDefault.wav"};
static char gNameExplodeSoundOfTank[] = {"images/SoundEffects/player_die.wav"};
static char gNameBossDie[] = {"images/SoundEffects/bossdie.wav"};

static char gGameOveMusic[] = {"images/SoundEffects/gameover.wav"};
static char gBattleMusic[] = {"images/SoundEffects/battlemusic.wav"};
static char gGetGoldSound[] = {"images/SoundEffects/getGold.wav"};
static char gBreakGoldSound[] = {"images/SoundEffects/breakglass.wav"};
static char gBossMusic[] = {"images/SoundEffects/boss_bg.wav"};

static bool done = false; // check resume music after finish boss's time

namespace SDLCommonFunc
{
    SDL_Texture* loadImage( string path);
    SDL_Texture* loadText(string textureText, SDL_Color textColor, TTF_Font* gFont);
    void render(SDL_Texture* loadedTexture, SDL_Rect clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Clear();
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2, int offset);
    void render2(SDL_Texture* loadedTexture, const int& x,const int& y, SDL_Rect* clip);
    void render_for_sprite(SDL_Texture* mTexture, int x, int y, SDL_Rect* clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    bool checkFocusWidthRect(const int& x,const int& y,const SDL_Rect& rect);
    int showMenu();
    bool loadSoundEffects();
}
#endif // COMMON_H_INCLUDED
