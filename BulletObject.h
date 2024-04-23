#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED

#include "BaseObject.h"

#define WIDTH_LASER 8
#define HEIGHT_LASER 8

#define WIDTH_SPHERE 17
#define HEIGHT_SPHERE 17

#define WIDTH_NEW_1 16
#define HEIGHT_NEW_1 25

#define WIDTH_ROUNDABOUT 70
#define HEIGHT_ROUNDABOUT 32

#define WIDTH_BULLET_1_ENEMY 20
#define HEIGHT_BULLET_1_ENEMY 21

#define ROCKET_WIDTH 40
#define ROCKET_HEIGHT 99

#define BOSS_BULLET_WIDTH 50
#define BOSS_BULLET_HEIGHT 131


static int ROCKET_ANIMATION_FRAMES = 4;

class BulletObject : public BaseObject
{
public:
    enum BulletType {
        NONE = 0,
        SPHERE = 1,
        SPHERE1 = 2,
        LASER = 3,
        ROCKET = 4,
        BOSS_1_ARROW = 5,
        NEW_1 = 6
    };

    BulletObject();
    ~BulletObject();

    void handleInputAction(SDL_Event e);
    void handleMove(const int& x_border, const int& y_border);
    void handleMoveThreats(const int& x_border, const int& y_border);

    int getBulletType() const { return bulletType; }
    void setBulletType(int type) { bulletType = type; }

    bool getIsMove() const { return isMove; }
    void setIsMove(bool input) { isMove = input; }

    void setWidthHeight(const int& x, const int& y) { pos.w = x; pos.h = y; }
    
    void setDegrees( double deg) { degrees = deg; }
    double getDegrees() const { return degrees; }
    

    void setx_val(const double& x) { x_val = x; }
    double getx_val() const { return x_val; }
    void sety_val(const double& y) { y_val = y; }
    double gety_val() const { return y_val; }

    void setRocketTexture();
    void runRocket();

    void set_rocket_2();
    void run_rocket_2();

    void setFrame(const int& fr) {frame = fr;}
    int getFrame() { return frame; }

    void handleMoveBoss(const int& x_border, const int& y_border);

    void set_boss_bullet();
    void run_boss_bullet();


private:
    double x_val;
    double y_val;

    bool isMove;

    int bulletType;

    double degrees;

    static int frame;

    SDL_Rect boss_bullet[3];
    SDL_Rect rocket_tex[4];
    SDL_Rect rocket_tex_2[5];

    static int frame_rocket;
    static int frame_rocket_2;

    static bool check_col_shield;
};


#endif
//up