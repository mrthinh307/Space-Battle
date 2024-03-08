#include "Common.h"

void logSDLError(ostream& os, const string& msg, bool fatal = false);
void initSDL();
void quitSDL();
void waitUntilKeyPressed();

int main(int argc, char* args[]){
    initSDL();

    gBackground = SDLCommonFunc::loadImage("images/background.jpg");

    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255);
    SDL_RenderClear( gRenderer );

    SDLCommonFunc::render(gBackground, 0, 0, NULL);
    SDL_RenderPresent(gRenderer);

    bool quit = false;
    
    while(!quit){
        while(gEvent.type == SDL_QUIT){
            quit = true;
            break;
        }
    }
    SDLCommonFunc::Clear();
    quitSDL();
    return 0;
}   

void initSDL(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(cout, "SDL_Init", true);
    }

    gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(gWindow == nullptr){
        logSDLError(cout, "Create Window", true);
    }


    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(gRenderer == nullptr){
        logSDLError(cout, "Create Renderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(){

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

void logSDLError(ostream& os,const string& msg, bool fatal ){
    cout << msg << "Error: " << SDL_GetError() << endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(cout, "SDL_Init", true);
    }

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr){
        logSDLError(cout, "Create Window", true);
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    gScreenSurface = SDL_GetWindowSurface(window);     // HERE

    if(renderer == nullptr){
        logSDLError(cout, "Create Renderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void waitUntilKeyPressed(){
    SDL_Event e;
    while(true){
        if(SDL_WaitEvent(&e) && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)){
            return;

        }
        SDL_Delay(100);
    }
}



