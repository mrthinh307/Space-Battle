#ifndef HANDLEGIFTITEM_H
#define HANDLEGIFTITEM_H

#include "Common.h"
#include "BaseObject.h"
#include "AdditionalTools.h"
#include "BulletObject.h"
#include "TankObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "HandleSkill.h"
#include "SoundEffects.h"  

extern unsigned int currentGold;
extern unsigned int currentHeart;
extern unsigned int currentKilled;

extern vector<Tools*> static_skills_a;
extern vector<Tools*> static_skills_b;
extern bool have_shield;
extern Uint32 start_shield;

extern bool have_magnet;
extern Uint32 start_skill;

extern vector<Tools*> teleport_a;
extern vector<Tools*> teleport_b;
extern bool have_tele;
extern bool run_animation;
extern Uint32 start_tele;

extern bool have_4_bullet;
extern Uint32 start_4_bullet;

extern bool have_super_bullet;
extern Uint32 start_super_bullet;

extern bool have_bullet_spread;
extern Uint32 start_bullet_spread;

extern bool have_straight_beam;
extern Uint32 start_straight_beam;

extern bool have_trap;
extern Uint32 start_trap;

extern vector<Tools*> booster_a;
extern vector<Tools*> booster_b;
extern bool have_booster;
extern Uint32 start_booster;

extern vector<Tools*> stun_a;
extern vector<Tools*> stun_b;
extern bool have_stun;
extern Uint32 start_stun;

extern vector<Tools*> gifts_list;

extern bool have_speed_up_bullet;
extern Uint32 start_speed_up_bullet;


void run_gift_item(vector<Tools*>& gifts_list, TankObject& mainTank, ThreatsObject* p_threat, vector<ThreatsObject*> p_threats, unsigned int& currentGold, string& gNameBulletOfMainTank, string& gNameRocket);
void push_back_gift_item(ThreatsObject* p_threat);

#endif // HANDLEGIFTITEM_H