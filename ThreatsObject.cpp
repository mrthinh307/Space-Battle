#include "ThreatsObject.h"

ThreatsbObject::ThreatsbObject(){
    x_val = 0;
    y_val = 0;

    rect.x = 0;
    rect.y = 0;
    rect.w = WIDTH_THREATS_OBJECT;
    rect.h = HEIGHT_THREATS_OBJECT;

    // VI TRI THREAT XUAT HIEN
    pos.x = SCREEN_WIDTH;
    pos.y = SCREEN_HEIGHT * 0.5;
    pos.w = WIDTH_THREATS_OBJECT;
    pos.h = HEIGHT_THREATS_OBJECT;
}