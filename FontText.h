#ifndef FONTTEXT_H_INCLUDED
#define FONTTEXT_H_INCLUDED

#include "BaseObject.h"
#include "SDL2/SDL_ttf.h"

static const SDL_Color CYAN_COLOR = {0, 255, 255};
static const SDL_Color BLUE_COLOR = {0, 0, 255};
static const SDL_Color ORANGE_COLOR = {255, 165, 0};
static const SDL_Color YELLOW_COLOR = {255, 255, 0};
static const SDL_Color LIME_COLOR = {0, 255, 0};
static const SDL_Color PURPLE_COLOR = {128, 0, 128};
static const SDL_Color RED_COLOR = {255, 0, 0};
static const SDL_Color WHITE_COLOR = {255, 255, 255};
static const SDL_Color BLACK_COLOR = {0, 0, 0};
static const SDL_Color GREEN_COLOR = {0, 128, 0};
static const SDL_Color DEFAULT_COLOR = BLACK_COLOR;

class FontText : public BaseObject
{
public:
    FontText();
    ~FontText();

    void setText(const string& content) { text = content; }
    void setColor(SDL_Color color) { textColor = color; }
    void createGameText(TTF_Font* font);
private:
    string text;
    SDL_Color textColor;
};
#endif