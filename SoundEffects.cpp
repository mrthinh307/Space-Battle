#include "SoundEffects.h"

 Mix_Chunk* gBulletSound[NUMBER_OF_BULLET_SOUND];
 Mix_Chunk* gExpSound[NUMBER_OF_EXPLODE_SOUND];
 Mix_Chunk* gRocketSound;
 Mix_Chunk* gameOver;
 Mix_Music* battleMusic;
 Mix_Chunk* getGold;
 Mix_Chunk* breakGold;
 Mix_Chunk* menuButton;
 Mix_Chunk* buttonAction;
 Mix_Music* menuMusic;
 Mix_Chunk* warningBoss;
 Mix_Chunk* bossDie;
 Mix_Music* bossBattle;
 Mix_Chunk* haveShield;
 Mix_Chunk* breakShield;
 Mix_Chunk* haveTele;
 Mix_Chunk* finishTele;
 Mix_Chunk* bulletUpgrade;
 Mix_Chunk* defaultSkill;
 Mix_Chunk* treasureSound;
 Mix_Chunk* boosterSound;
 Mix_Chunk* stunSound;


bool SDLCommonFunc::loadSoundEffects(){
    bool check = true;

    gBulletSound[0] = Mix_LoadWAV("images/SoundEffects/roundabout.wav");
    Mix_VolumeChunk(gBulletSound[0], 70);

    gBulletSound[1] = Mix_LoadWAV(gNameBulletSoundOfTank);

    gBulletSound[2] = Mix_LoadWAV("images/SoundEffects/new_1.wav");

    gBulletSound[3] = Mix_LoadWAV("images/SoundEffects/phitieu.wav");
    Mix_VolumeChunk(gBulletSound[3], 128);

    gBulletSound[4] = Mix_LoadWAV("images/SoundEffects/tia.wav");
    Mix_VolumeChunk(gBulletSound[4], 20);

    gExpSound[0] = Mix_LoadWAV(gNameExplodeSoundOfThreat);
    Mix_VolumeChunk(gExpSound[0], 128);

    gExpSound[1] = Mix_LoadWAV(gNameExplodeSoundOfTank);
    Mix_VolumeChunk(gExpSound[1], 120);

    gameOver = Mix_LoadWAV(gGameOveMusic);

    battleMusic = Mix_LoadMUS(gBattleMusic);

    getGold = Mix_LoadWAV(gGetGoldSound);

    Mix_VolumeChunk(getGold, 50);

    breakGold = Mix_LoadWAV(gBreakGoldSound);

    Mix_VolumeChunk(breakGold, 110);

    menuButton = Mix_LoadWAV("images/SoundEffects/menu.wav");
    Mix_VolumeChunk(menuButton, 128);

    buttonAction = Mix_LoadWAV("images/SoundEffects/start.wav");
    Mix_VolumeChunk(buttonAction, 128);

    menuMusic = Mix_LoadMUS("images/SoundEffects/menuMusic.wav");

    warningBoss = Mix_LoadWAV("images/SoundEffects/warning_boss.wav");
    Mix_VolumeChunk(warningBoss, 30);

    bossDie = Mix_LoadWAV(gNameBossDie);
    Mix_VolumeChunk(bossDie, 110);

    bossBattle = Mix_LoadMUS(gBossMusic);

    haveShield = Mix_LoadWAV("images/SoundEffects/shield.wav");
    Mix_VolumeChunk(haveShield, 100);
    breakShield = Mix_LoadWAV("images/SoundEffects/break_shield.wav");
    Mix_VolumeChunk(breakShield, 120);

    haveTele = Mix_LoadWAV("iamges/SoundEffects/tele1.wav");
    finishTele = Mix_LoadWAV("iamges/SoundEffects/tele2.wav");
    bulletUpgrade = Mix_LoadWAV("images/SoundEffects/bullet_upgrade.wav");
    defaultSkill = Mix_LoadWAV("images/SoundEffects/default.wav");
    treasureSound = Mix_LoadWAV("images/SoundEffects/treasure.wav");
    boosterSound = Mix_LoadWAV("images/SoundEffects/booster.wav");
    stunSound = Mix_LoadWAV("images/SoundEffects/stun.wav");

    Mix_VolumeMusic(45);

    return check;
}