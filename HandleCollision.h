#ifndef HANDLE_COLLISION_H
#define HANDLE_COLLISION_H

#include "Common.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "TankObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "HandleSkill.h"
#include "SoundEffects.h"


void bullet_vs_threats(TankObject& mainTank, vector<ThreatsObject*>& p_threats, vector<ExplosionObject*>& exps, vector<Tools*>& gifts_list, unsigned int& currentGold, string& gNameBulletOfMainTank, string& gNameRocket);

#endif // HANDLE_COLLISION_H