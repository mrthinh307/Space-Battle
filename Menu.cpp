#include "Menu.h"

int SDLCommonFunc::handleSettingMenu(SDL_Renderer* gRenderer){
    SDL_Texture* setting[3];

    setting[0] = SDLCommonFunc::loadImage("images/Backgrounds/setting1.png");
    setting[1] = SDLCommonFunc::loadImage("images/Backgrounds/setting2.png");
    setting[2] = SDLCommonFunc::loadImage("images/Backgrounds/setting0.png");

    const int settingItems = 2;
    SDL_Rect posItem[settingItems];

    posItem[0] = {160, 520, 320, 105};
    posItem[1] = {955, 515, 320, 105};

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
        cout << "HAVE" << " ";
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
