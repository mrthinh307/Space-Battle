#ifndef MENU_H
#define MENU_H

#include "Common.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "TankObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "HandleSkill.h"
#include "SoundEffects.h"
#include "FontText.h"
extern int currentMethod;

int SDLCommonFunc::handleSettingMenu(SDL_Renderer* gRenderer);
int SDLCommonFunc::showMenu(SDL_Renderer* gRenderer);

int showEndGame(SDL_Renderer* gRenderer, TTF_Font* gFont, FontText& timeEndGame, const string& current_time, FontText& killedEndGame, FontText& goldEndGame);
void setRecord();
bool Achievement(SDL_Renderer* gRenderer, TTF_Font* gFont, FontText& recordText, FontText& exp);

#endif // HANDLE_COLLISION_H