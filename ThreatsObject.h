#ifndef THREATSOBJECT_H_INCLUDED
#define THREATSOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "BulletObject.h"

#define WIDTH_THREATS_OBJECT 60
#define HEIGHT_THREATS_OBJECT 49
#define SPEED_BULLET_THREATS_OBJECT 5.8
#define SPEED_THREATS 3

#define BOSS_WIDTH 200
#define BOSS_HEIGHT 100
#define SPEED_BULLET_BOSS 6.0
#define BOSS_1_SPEED 4

const int BOSS_1_FRAMES = 8;
const int THREATS_1_FRAME = 6;
const int NUM_BOSS = 1;


class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    void handleMove(const int& x_border,const int& y_border);
    void handleInputAction(SDL_Event e);

    void setx_val(const double& x) { x_val = x; }
    double getx_val() const { return x_val; }
    void sety_val(const double& y) { y_val = y; }
    double gety_val() const { return y_val; }

    double getDegrees() const {return degrees; }
    void setDegrees(const SDL_Rect& posTank, int index);
    SDL_RendererFlip getFlipType() const { return flipType; }
    void setFlipType (SDL_RendererFlip type) { flipType = type; }

    void setBulletList(vector<BulletObject*> bulletList) { bulletOfThreatsList = bulletList; }
    vector<BulletObject*> getBulletList() const { return bulletOfThreatsList; }

    void initBullet(BulletObject* t_bull);
    void runBullet(const int& x_limit, const int& y_limit);

    void resetThreat();
    void resetBullet(BulletObject* aBullet);

    void removeBullet(const int& idx);

    void Set_sprite_clips();
    void Set_sprite_clips_1();
    void runThreats();
    void runBoss();

    void init_bullet_boss1();
    void run_bullet_boss(const int& x_limit, const int& y_limit);
private:
    double x_val;
    double y_val;

    double degrees;
    SDL_RendererFlip flipType;

    vector<BulletObject*> bulletOfThreatsList;
    static int frame;
    
    SDL_Rect spriteBoss_1[BOSS_1_FRAMES];
    SDL_Rect spriteThreats_1[THREATS_1_FRAME];
};

#endif
//up