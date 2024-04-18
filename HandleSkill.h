#ifndef HANDLE_SKILL_H_INCLUDED
#define HANDLE_SKILL_H_INCLUDED

#include "TankObject.h"
#include "ThreatsObject.h"
#include "AdditionalTools.h"
#include "Common.h"

enum object{
    PLAYER = 0,
    ENEMY = 1,
    BULLET = 2
};

//SHIELD
void init_shield_skill(vector<Tools*>& static_skills_a, vector<Tools*>& static_skills_b,const object& set_for_);
void run_shield_skill(Tools* shield,const TankObject& mainTank, ThreatsObject* p_threat,const object& set_for_);
void shield_vs_bullet(vector<Tools*>& static_skills_a, const TankObject& mainTank, ThreatsObject* p_threat, BulletObject* aBulletOfThreat,const enemy& cur_enemy);

//MAGNET
void implement_magnet_skill(vector<Tools*>& gift_list, TankObject& mainTank, bool& have_magnet,const Uint32& start_skill);

//TELEPORT
void init_teleport(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, ThreatsObject* p_threat);
void run_teleport_for_player(vector<Tools*>& a, TankObject& mainTank, bool& have_tele);

#endif