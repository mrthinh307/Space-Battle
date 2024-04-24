#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include "Common.h"
#include "BaseObject.h"

// SoundEffects.h
extern Mix_Chunk* gBulletSound[NUMBER_OF_BULLET_SOUND];
extern Mix_Chunk* gExpSound[2];
extern Mix_Chunk* gRocketSound;
extern Mix_Chunk* gameOver;
extern Mix_Music* battleMusic;
extern Mix_Chunk* getGold;
extern Mix_Chunk* breakGold;
extern Mix_Chunk* menuButton;
extern Mix_Chunk* buttonAction;
extern Mix_Music* menuMusic;
extern Mix_Chunk* warningBoss;
extern Mix_Chunk* bossDie;
extern Mix_Music* bossBattle;
extern Mix_Chunk* haveShield;
extern Mix_Chunk* breakShield;
extern Mix_Chunk* haveTele;
extern Mix_Chunk* finishTele;
extern Mix_Chunk* bulletUpgrade;
extern Mix_Chunk* defaultSkill;
extern Mix_Chunk* treasureSound;
extern Mix_Chunk* boosterSound;
extern Mix_Chunk* stunSound;

bool SDLCommonFunc::loadSoundEffects();

#endif // SOUNDEFFECTS_H