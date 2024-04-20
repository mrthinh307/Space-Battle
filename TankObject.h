#ifndef TANKOBJECT_H_INCLUDED
#define TANKOBJECT_H_INCLUDED

#include "Common.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define WIDTH_TANK_OBJECT 70
#define HEIGHT_TANK_OBJECT 67

#define SPEED_BULLET_MAIN_TANK 8.0
#define SPEED_ROCKET_MAIN_TANK 8.0

static unsigned int DEFAULT_SPEED = 4;

#define TANK_1_FRAME 5

class TankObject : public BaseObject
{
public:
    enum BULLET_STYLE {
        NONE = 0,
        NORMAL = 1,
        FOUR_DIRECTIONS_BULLET = 2,
        SUPER_BULLET = 3,
        BULLET_SPREAD = 4,
        STRAIGHT_BEAM = 5,
        TRAP = 6
    };

    enum BulletType {
        SPHERE1 = 0,
        ROCKET = 1,
        NEW_1 = 2,
        ROUNDABOUT = 3,
    };

    TankObject();
    ~TankObject();

    int getBulletType() const { return bulletType; }
    void setBulletType(int type) { bulletType = type; }

    void set_bullet_style(const int& s) {bullet_style = s; }
    int get_bullet_style() const { return bullet_style; }

    void handleInputAction(SDL_Event e, Mix_Chunk* bulletSound[NUMBER_OF_BULLET_SOUND], string gNameBulletOfMainTank);
    void handleMove();

    double getDegrees() const {return degrees; }
    void setDegrees(double d) { degrees = d; }

    void setXVal(int x) { x_val = x; }
    void setYVal(int y) { y_val = y; }

    SDL_RendererFlip getFlipType() const { return flipType; }
    void setFlipType (SDL_RendererFlip type) { flipType = type; }

    void setBulletList(vector<BulletObject*> bulletList) { bulletOfTankList = bulletList; }
    vector<BulletObject*> getBulletList() const { return bulletOfTankList; }

    void setRocketList(vector<BulletObject*> rocketlist) { rocketOfTankList = rocketlist; }
    vector<BulletObject*> getRocketList() const { return rocketOfTankList; }

    void runBullet();
    void removeBullet(const int& idx);

    void runRocket();
    void removeRocket(const int& idx);

    void setRocket(const unsigned int& c) { currentRocket = c; }
    unsigned int getRocket() { return currentRocket; }
    void setRocketTexture();
    
    void Set_sprite_clips();
    void runMainTank();

    void set_sprite_for_shield();
    void run_shield();

    void four_directions_bullet();
    void run_four_bullet(const int& x_limit, const int& y_limit);

    void super_bullet();
    void run_super_bullet(const int& x_limit, const int& y_limit);

    void bullet_spread();
    void run_bullet_spread(const int& x_limit, const int& y_limit);

    void straight_beam();
    void run_straight_beam(const int& x_limit, const int& y_limit);

    void trap();
    void run_trap(const int& x_limit, const int& y_limit);

    void set_tank_speed(const unsigned int& s) { tank_speed = s; }
    unsigned int get_tank_speed() { return tank_speed; }


private:
    int x_val;
    int y_val;
    double degrees;
    SDL_RendererFlip flipType;

    vector<BulletObject*> bulletOfTankList;
    vector<BulletObject*> rocketOfTankList;

    unsigned int currentRocket;
    SDL_Rect spriteTank_1[TANK_1_FRAME];
    static int frame;

    static int bullet_style;

    int width_bullet, height_bullet, speed_bullet;

    int bulletType;

    static unsigned int tank_speed;
};

#endif // TANKOBJECT_H_INCLUDED
//up