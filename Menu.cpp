#include "Menu.h"

int SDLCommonFunc::handleSettingMenu(SDL_Renderer* gRenderer){
    SDL_Texture* setting[3];

    setting[0] = SDLCommonFunc::loadImage("images/Backgrounds/setting1.png");
    setting[1] = SDLCommonFunc::loadImage("images/Backgrounds/setting2.png");
    setting[2] = SDLCommonFunc::loadImage("images/Backgrounds/setting0.png");

    const int settingItems = 2;
    SDL_Rect posItem[settingItems];

    posItem[0] = {125, 555, 335, 120};
    posItem[1] = {955, 513, 335, 120};

    SDL_Event m_event;
    int x_m = 0;
    int y_m =  0;
    int lastSettingIndex = -1;
    int settingIndex;

    SDL_RenderCopy(gRenderer, setting[2], NULL, NULL);
    SDL_RenderPresent(gRenderer);

    while(true){
        settingIndex = -1;
        while(SDL_PollEvent(&m_event)){
            switch(m_event.type){
                case SDL_QUIT:
                {
                    for(int i = 0; i < settingItems; i++){
                        SDL_DestroyTexture(setting[i]);
                        setting[i] = NULL;
                    }
                    return 2;
                }
                case SDL_MOUSEMOTION:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;

                        for(int i = 0; i < settingItems; i++){
                            if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posItem[i])){
                                settingIndex = i;
                                break;
                            }
                        }

                        if (settingIndex != -1) {
                            SDL_RenderCopy(gRenderer, setting[settingIndex], NULL, NULL);
                            if(lastSettingIndex != settingIndex)
                                Mix_PlayChannel(-1, menuButton, 0);
                        } else {
                            SDL_RenderCopy(gRenderer, setting[2], NULL, NULL);
                        }
                        SDL_RenderPresent(gRenderer);
                        lastSettingIndex = settingIndex;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;

                        for(int i = 0; i < settingItems; i++){
                            if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posItem[i])){
                                Mix_PlayChannel(-1, buttonAction, 0);
                                SDL_Delay(500); 
                                for(int i = 0; i < settingItems; i++){
                                    SDL_DestroyTexture(setting[i]);
                                    setting[i] = NULL;
                                }
                                return i;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }

    }

    for(int i = 0; i < settingItems; i++){
        SDL_DestroyTexture(setting[i]);
        setting[i] = NULL;
    }

    return 2;
}

int currentMethod;

int SDLCommonFunc::showMenu(SDL_Renderer* gRenderer){
    SDL_Texture* gMenu[4];
    SDL_Texture* setGameController[3];

    gMenu[0] = SDLCommonFunc::loadImage("images/Backgrounds/menu1.jpg");
    gMenu[1] = SDLCommonFunc::loadImage("images/Backgrounds/menu2.jpg");
    gMenu[2] = SDLCommonFunc::loadImage("images/Backgrounds/menu3.jpg");
    gMenu[3] = SDLCommonFunc::loadImage("images/Backgrounds/menu.jpg");

    setGameController[0] = SDLCommonFunc::loadImage("images/Backgrounds/c0.png");
    setGameController[1] = SDLCommonFunc::loadImage("images/Backgrounds/c1.png");
    setGameController[2] = SDLCommonFunc::loadImage("images/Backgrounds/c2.png");

    const int MenuItems = 3;
    const int NumController = 2;
    SDL_Rect posItem[MenuItems];
    SDL_Rect posSetGameController[NumController];

    posItem[0] = {105, 660, 355, 85};
    posItem[1] = {575, 660, 355, 85};
    posItem[2] = {1045, 660, 355, 85};

    posSetGameController[0] = {60, 570, 470, 120};
    posSetGameController[1] = {900, 570, 490, 120};

    bool selected[MenuItems] = {0, 0, 0};
    bool selected2[NumController] = {0, 0};

    SDL_Event m_event;
    int x_m = 0;
    int y_m =  0;
    int lastMenuIndex = -1;
    int menuIndex;

    int controllerIndex;
    int lastControllerIndex = -1;

    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( menuMusic, -1 );
    }

    SDL_RenderCopy(gRenderer, gMenu[3], NULL, NULL);
    SDL_RenderPresent(gRenderer);

    while(true){
        menuIndex = -1;
        while(SDL_PollEvent(&m_event)){
            switch(m_event.type){
                case SDL_QUIT:
                {
                if(Mix_PlayingMusic() == 1 && Mix_PausedMusic() != 1){
                        Mix_PauseMusic();
                        Mix_FreeMusic(menuMusic);
                        menuMusic = NULL;
                        for(int i = 0; i < 4; i++){
                            SDL_DestroyTexture(gMenu[i]);
                            gMenu[i] = NULL;
                        }
                }
                    return 1;
                }
                case SDL_MOUSEMOTION:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;

                        for(int i = 0; i < MenuItems; i++){
                            if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posItem[i])){
                                menuIndex = i;
                                break;
                            }
                        }

                        if (menuIndex != -1) {
                            SDL_RenderCopy(gRenderer, gMenu[menuIndex], NULL, NULL);
                            if(lastMenuIndex != menuIndex)
                                Mix_PlayChannel(-1, menuButton, 0);
                        } else {
                            SDL_RenderCopy(gRenderer, gMenu[3], NULL, NULL);
                        }
                        SDL_RenderPresent(gRenderer);
                        lastMenuIndex = menuIndex;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;

                        for(int i = 0; i < MenuItems; i++){
                            if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posItem[i])){
                                Mix_PlayChannel(-1, buttonAction, 0);
                                if(i == 0){
                                    SDL_RenderCopy(gRenderer, setGameController[0], NULL, NULL);
                                    SDL_RenderPresent(gRenderer);

                                    bool controllerSelected = false;
                                    while(!controllerSelected) {
                                        controllerIndex = -1;
                                        while(SDL_PollEvent(&m_event)){
                                            switch(m_event.type){
                                                case SDL_QUIT:
                                                    {
                                                        if(Mix_PlayingMusic() == 1 && Mix_PausedMusic() != 1){
                                                            Mix_PauseMusic();
                                                            Mix_FreeMusic(menuMusic);
                                                            menuMusic = NULL;
                                                            for(int i = 0; i < 4; i++){
                                                                SDL_DestroyTexture(gMenu[i]);
                                                                gMenu[i] = NULL;
                                                            }
                                                        }
                                                        return 1;
                                                    }
                                                case SDL_MOUSEMOTION:
                                                    {
                                                        x_m = m_event.button.x;
                                                        y_m = m_event.button.y;

                                                        for(int i = 0; i < NumController; i++){
                                                            if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posSetGameController[i])){
                                                                controllerIndex = i;
                                                                break;
                                                            }
                                                        }

                                                        if (controllerIndex != -1) {
                                                            SDL_RenderCopy(gRenderer, setGameController[controllerIndex + 1], NULL, NULL);
                                                            if(lastControllerIndex != controllerIndex)
                                                                Mix_PlayChannel(-1, menuButton, 0);
                                                        } else {
                                                            SDL_RenderCopy(gRenderer, setGameController[0], NULL, NULL);
                                                        }
                                                        SDL_RenderPresent(gRenderer);
                                                        lastControllerIndex = controllerIndex;
                                                    }
                                                    break;
                                                case SDL_MOUSEBUTTONDOWN:
                                                    {
                                                        x_m = m_event.button.x;
                                                        y_m = m_event.button.y;

                                                        for(int i = 0; i < NumController; i++){
                                                            if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posSetGameController[i])){
                                                                Mix_PlayChannel(-1, buttonAction, 0);
                                                                if(i == 0){
                                                                    SDL_RenderCopy(gRenderer, setGameController[1], NULL, NULL);
                                                                    SDL_RenderPresent(gRenderer);
                                                                    SDL_Delay(100);
                                                                    currentMethod = ControllerMethod::KEYBOARD;
                                                                }
                                                                else if(i == 1){
                                                                    SDL_RenderCopy(gRenderer, setGameController[2], NULL, NULL);
                                                                    SDL_RenderPresent(gRenderer);
                                                                    SDL_Delay(100);
                                                                    currentMethod = ControllerMethod::JOYSTICK;
                                                                }
                                                                controllerSelected = true;
                                                            }
                                                        }

                                                    }
                                                    break;
                                                default:
                                                    break;
                                            }
                                            if(controllerSelected)  break;
                                        }
                                    }
                                    if(Mix_PlayingMusic() == 1 && Mix_PausedMusic() != 1){
                                        Mix_PauseMusic();
                                        for(int i = 0; i < 4; i++){
                                            SDL_DestroyTexture(gMenu[i]);
                                            gMenu[i] = NULL;
                                        }
                                        for(int i = 0; i < 3; i++){
                                            SDL_DestroyTexture(setGameController[i]);
                                            setGameController[i] = NULL;
                                        }
                                    }
                                }
                                SDL_Delay(500); 
                                return i;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }

    }

    // Clean up resources
    for (int i = 0; i < 4; ++i) {
        SDL_DestroyTexture(gMenu[i]);
        gMenu[i] = NULL;
    }

    for(int i = 0; i < 3; i++){
        SDL_DestroyTexture(setGameController[i]);
        setGameController[i] = NULL;
    }

    return 1;
}

extern unsigned int currentGold;
extern unsigned int currentKilled;

int showEndGame(SDL_Renderer* gRenderer, TTF_Font* gFont, FontText& timeEndGame, const string& current_time, FontText& killedEndGame, FontText& goldEndGame){
    setRecord();
    SDL_Texture* endGame[2];

    endGame[0] = SDLCommonFunc::loadImage("images/Backgrounds/endgame.png");
    endGame[1] = SDLCommonFunc::loadImage("images/Backgrounds/endgame1.png");

    SDL_Rect posEndGame = {150, 690, 365, 100};

    timeEndGame.setColor(WHITE_COLOR);
    timeEndGame.setText(current_time);
    timeEndGame.setPos(230, 600);
    timeEndGame.setPos2(230, 60);

    killedEndGame.setColor(WHITE_COLOR);
    string killedToString = to_string(currentKilled);
    killedEndGame.setText(killedToString);
    killedEndGame.setPos(230, 390);
    killedEndGame.setPos2(30 + (killedToString.size() - 1) * 10, 60);

    goldEndGame.setColor(WHITE_COLOR);
    string goldToString = to_string(currentGold);
    goldEndGame.setText(goldToString);
    goldEndGame.setPos(230, 490);
    goldEndGame.setPos2(30 + (goldToString.size() - 1) * 10, 60);

    SDL_RenderCopy(gRenderer, endGame[0], NULL, NULL);
    timeEndGame.createGameText(gFont);
    killedEndGame.createGameText(gFont);
    goldEndGame.createGameText(gFont);
    SDL_RenderPresent(gRenderer);

    SDL_Event m_event;
    int x_m = 0;
    int y_m =  0;
    int lastEndGameIndex = -1;
    int endGameIndex;

    while(true){
        endGameIndex = -1;
        while(SDL_PollEvent(&m_event)){
            switch(m_event.type){
                case SDL_QUIT:
                {
                    for(int i = 0; i < 2; i++){
                        SDL_DestroyTexture(endGame[i]);
                        endGame[i] = NULL;
                    }
                    return 0;
                }
                case SDL_MOUSEMOTION:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;

                        if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posEndGame)){
                            endGameIndex = 1;
                        }

                        if (endGameIndex != -1) {
                            SDL_RenderCopy(gRenderer, endGame[endGameIndex], NULL, NULL);
                                if(lastEndGameIndex != endGameIndex)
                                    Mix_PlayChannel(-1, menuButton, 0);
                        } else {
                            SDL_RenderCopy(gRenderer, endGame[0], NULL, NULL);
                        }
                        timeEndGame.free();
                        timeEndGame.createGameText(gFont);
                        killedEndGame.free();
                        killedEndGame.createGameText(gFont);
                        goldEndGame.free();
                        goldEndGame.createGameText(gFont);
                        SDL_RenderPresent(gRenderer);
                        lastEndGameIndex = endGameIndex;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;

                        if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posEndGame)){
                            Mix_PlayChannel(-1, buttonAction, 0);
                            SDL_Delay(200); 
                            for(int i = 0; i < 2; i++){
                                SDL_DestroyTexture(endGame[i]);
                                endGame[i] = NULL;
                                timeEndGame.free();
                                killedEndGame.free();
                                goldEndGame.free();
                            }
                            return 1;
                        }
                    }
                    break;
                default:
                    break;
            }
        }

    }

    for(int i = 0; i < 2; i++){
        SDL_DestroyTexture(endGame[i]);
        endGame[i] = NULL;
    }

    return 0;
}

void setRecord(){
    unsigned int gold_record;
    unsigned int killed_record;
    ifstream file("save_record.txt");
    if(!file.is_open()){
        cout << "Can't open file!\n";
    }
    else{
        file >> gold_record >> killed_record;
        gold_record += currentGold;
        killed_record = max(killed_record, currentKilled);
        file.close();
    }

    ofstream file2("save_record.txt");
    if(!file2.is_open()){
        cout << "Can't open file!\n";
    }
    else{
        file2 << gold_record << endl << killed_record;
        file2.close();
    }
}

bool Achievement(SDL_Renderer* gRenderer, TTF_Font* gFont, FontText& recordText, FontText& exp){
    unsigned int cur_gold, killed_record;
    ifstream file("save_record.txt");
    if(!file.is_open()){
        cout << "Can't open file!\n";
    }
    else{
        file >> cur_gold >> killed_record;
        file.close();
    }

    int idx = cur_gold / 500;
    int idx1 = idx;
    if(idx >= 4) idx1 = 4;
    if(idx >= 9) idx = 9;

    string nameMainTank = "images/Utils/tank" + to_string(idx1 + 1) + ".png";
    string gNameRank = "images/Utils/img-icon-Vip-" + to_string(idx + 1) + ".png";

    SDL_Texture* gRank = SDLCommonFunc::loadImage(gNameRank);
    SDL_Texture* gMainTank = SDLCommonFunc::loadImage(nameMainTank);

    SDL_Texture* gAchievement[2];
    gAchievement[0] = SDLCommonFunc::loadImage("images/Backgrounds/achieve.png");
    gAchievement[1] = SDLCommonFunc::loadImage("images/Backgrounds/achieve1.png");  

    SDL_Rect posOut = {20, 16, 95, 84};

    SDL_Rect posRank = {90, 340, 200, 200};
    SDL_Rect posMainTank = {428, 340, 200, 200};

    exp.setColor(YELLOW_COLOR);
    while(cur_gold > 500){
        cur_gold -= 500;
    }
    string expToString = to_string(cur_gold);
    exp.setText(expToString + " / 500 EXP");
    exp.setPos(110, 550);
    exp.setPos2(150, 80);

    recordText.setColor(WHITE_COLOR);
    string killedToString = to_string(killed_record);
    recordText.setText(killedToString);
    recordText.setPos(830, 340);
    recordText.setPos2(150, 150);

    SDL_Event m_event;
    int x_m = 0;
    int y_m = 0;
    int lastAchievementIndex = -1;
    int achievementIndex;

    SDL_RenderCopy(gRenderer, gAchievement[0], NULL, NULL);
    SDL_RenderCopy(gRenderer, gRank, NULL, &posRank);
    SDL_RenderCopy(gRenderer, gMainTank, NULL, &posMainTank);
    recordText.createGameText(gFont);
    exp.createGameText(gFont);
    SDL_RenderPresent(gRenderer);

    while(true){
        achievementIndex = -1;
        while(SDL_PollEvent(&m_event)){
            switch(m_event.type){
                case SDL_QUIT:
                {
                    SDL_DestroyTexture(gRank);
                    gRank = NULL;
                    SDL_DestroyTexture(gMainTank);
                    gMainTank = NULL;
                    for(int i = 0; i < 2; i++){
                        SDL_DestroyTexture(gAchievement[i]);
                        gAchievement[i] = NULL;
                    }
                    recordText.free();
                    exp.free();
                    return true;
                }
                case SDL_MOUSEMOTION:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;

                        if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posOut)){
                            achievementIndex = 1;
                        }

                        if (achievementIndex != -1) {
                            SDL_RenderCopy(gRenderer, gAchievement[achievementIndex], NULL, NULL);
                                if(lastAchievementIndex != achievementIndex)
                                    Mix_PlayChannel(-1, menuButton, 0);
                        } else {
                            SDL_RenderCopy(gRenderer, gAchievement[0], NULL, NULL);
                        }
                        SDL_RenderCopy(gRenderer, gRank, NULL, &posRank);
                        SDL_RenderCopy(gRenderer, gMainTank, NULL, &posMainTank);
                        recordText.free();
                        recordText.createGameText(gFont);
                        exp.free();
                        exp.createGameText(gFont);
                        SDL_RenderPresent(gRenderer);
                        lastAchievementIndex = achievementIndex;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    {
                        x_m = m_event.button.x;
                        y_m = m_event.button.y;

                        if(SDLCommonFunc::checkFocusWidthRect(x_m, y_m, posOut)){
                            Mix_PlayChannel(-1, buttonAction, 0);
                            SDL_Delay(100); 
                            SDL_DestroyTexture(gRank);
                            gRank = NULL;
                            SDL_DestroyTexture(gMainTank);
                            gMainTank = NULL;
                            for(int i = 0; i < 2; i++){
                                SDL_DestroyTexture(gAchievement[i]);
                                gAchievement[i] = NULL;
                            }
                            recordText.free();
                            exp.free();
                            return true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }

    }
    return true;
}
