#ifndef HANDLE_SKILL_H_INCLUDED
#define HANDLE_SKILL_H_INCLUDED

#include "TankObject.h"
#include "ThreatsObject.h"
#include "AdditionalTools.h"
#include "Common.h"
#include "SoundEffects.h"

enum object{
    PLAYER = 0,
    ENEMY = 1,
    BULLET = 2
};

//SHIELD
void init_shield_skill(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, ThreatsObject* p_threat);
void handle_shield_skill(vector<Tools*>& a, const TankObject& mainTank, bool& have_shield, const Uint32& start);

//MAGNET
void implement_magnet_skill(vector<Tools*>& gift_list, const TankObject& mainTank, bool& have_magnet, const Uint32& start_skill);

//TELEPORT
void init_teleport(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, ThreatsObject* p_threat);
void run_teleport_for_player(vector<Tools*>& a, TankObject& mainTank, bool& have_tele);
static int lastX, lastY;
void run_animation_for_teleport(vector<Tools*>& a, const TankObject& mainTank, bool& run_animation);

// 4_BULLET
void set_time_for_4_bullet(TankObject& mainTank, bool& have_4_bullet, const Uint32& start);

// SUPER_BULLET
void set_time_for_super_bullet(TankObject& mainTank, bool& have_super_bullet, const Uint32& start);

// BULLET_SPREAD
void set_time_for_bullet_spread(TankObject& mainTank, bool& have_spread, const Uint32& start);

// STRAIGHT BEAM
void set_time_for_straight_beam(TankObject& mainTank, bool& have_straight_beam, const Uint32& start);

// TRAP BULLET
void set_time_for_trap(TankObject& mainTank, bool& have_zic_zac, const Uint32& start);

// BOOSTER
void init_booster_skill(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, ThreatsObject* p_threat);
void handle_booster_skill(vector<Tools*>&a, TankObject& mainTank, bool& have_booster, const Uint32& start);

// STUN
void init_stun(vector<Tools*>& a, vector<Tools*>& b, object set_for_, const TankObject& mainTank, vector<ThreatsObject*> p_threats);
void handle_stun(vector<Tools*>& a, vector<ThreatsObject*>& p_threats, bool& have_stun, const Uint32& start);

#endif
