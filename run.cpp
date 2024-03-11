#include "Common.h"
#include "TankObject.h"
#include "BulletObject.h"
#include "ThreatsObject.h"
void logSDLError(ostream& os, const string& msg, bool fatal = false);
void initSDL();
void quitSDL();

SDL_Texture* SDLCommonFunc::loadImage( string path){
    SDL_Texture* newTexture = NULL;

    SDL_Surface* optimizedSurface = NULL; // the final optimized image

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){
        cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << endl;
    }
    else{
        //SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 43, 43, 43));

        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface -> format, 0);

        if(optimizedSurface == NULL){
            cout << "Unable to optimized surface! SDL Error: " << SDL_GetError() << endl;
        }

        SDL_FreeSurface(loadedSurface);
        newTexture = SDL_CreateTextureFromSurface(gRenderer, optimizedSurface);

        if(newTexture == nullptr){
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(optimizedSurface);
    }
    return newTexture;
}

void SDLCommonFunc::render(SDL_Texture* loadedTexture, int x, int y, SDL_Rect* clip, double angle , SDL_Point* center , SDL_RendererFlip flip ) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad;
    renderQuad.x = x;
    renderQuad.y = y;
    renderQuad.w = SCREEN_WIDTH;
    renderQuad.h = SCREEN_HEIGHT;

    //Set clip rendering dimmensions
    if(clip != NULL){
        renderQuad.w = clip -> w;
        renderQuad.h = clip -> h;
    }

    //Render to screen
    SDL_RenderCopyEx(gRenderer, loadedTexture, clip, &renderQuad, angle, center, flip);
}

void SDLCommonFunc::Clear()
{
    //Free loaded image
    SDL_DestroyTexture( gBackground );
    gBackground = NULL;
}

int main(int argc, char* args[]){
    initSDL();
    srand(time(NULL));
    // Create background
    gBackground = SDLCommonFunc::loadImage("images/background2.jpg");

    // Make Main Tank
    TankObject mainTank;
    bool check = mainTank.loadIMG("images/bluetank.png");
    SDL_Rect rectTank = mainTank.getRect();
    if(check == false){
        cout << "Unable to load Main Tank! " << SDL_GetError() << endl;
        return 0;
    }



    // Make bullet for threat
    ThreatsObject * p_threats = new ThreatsObject[NUM_THREATS];
    for(int i = 0; i < NUM_THREATS; ++i){
        // Make Threat Object
        ThreatsObject* p_threat = p_threats + i;
        if(p_threat != NULL){
            bool check1 = p_threat->loadIMG("images/tankfix.png");
            if(!check1){
                cout <<"Unable to load Threat Images! " << endl;
                return 0;
            }
            int rand_x, rand_y;
            int tmp = rand() % 4;
            if(tmp == 0){
                rand_x = 0;
                rand_y = rand() % SCREEN_HEIGHT;
            }
            else if(tmp == 1){
                rand_x = rand() % SCREEN_WIDTH ;
                rand_y = 0;
            }
            else if(tmp == 2){
                rand_x = SCREEN_WIDTH;
                rand_y = rand() % SCREEN_HEIGHT;
            }
            else if(tmp == 3){
                rand_x = rand() % SCREEN_WIDTH;
                rand_y = SCREEN_HEIGHT;
            }

            p_threat->setPos(rand_x, rand_y);
        
            BulletObject* t_bull = new BulletObject();
            p_threat->initBullet(t_bull);
        }

    }

    bool quit = false;
    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            mainTank.handleInputAction(e);
        }
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255);
        SDL_RenderClear( gRenderer );

        //Load background
        SDLCommonFunc::render(gBackground, 0, 0, NULL);
      
        SDL_Rect posTank = mainTank.getPos();
        double flipTank = mainTank.getDegrees();
        SDL_RendererFlip typeFlipOfTank = mainTank.getFlipType();
        mainTank.renderCopy(posTank.x, posTank.y , &rectTank, flipTank, NULL, typeFlipOfTank);

        mainTank.handleMove(); 

        for(int i = 0; i < mainTank.getBulletList().size(); i++){
            vector<BulletObject*> bull_list = mainTank.getBulletList();
            BulletObject* p_bullet = bull_list.at(i);
            if(p_bullet != NULL){
                if(p_bullet->getIsMove()){
                    SDL_Rect rectBullet = p_bullet->getRect();
                    SDL_Rect posBullet = p_bullet->getPos();
                    double flipBullet = p_bullet->getDegrees();
                    p_bullet->renderCopy(posBullet.x, posBullet.y, &rectBullet, flipBullet, NULL, SDL_FLIP_NONE);
                    p_bullet->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT); 
                }
                else{
                    if(p_bullet != NULL){
                        bull_list.erase(bull_list.begin() + i);
                        mainTank.setBulletList(bull_list);
                        delete p_bullet; 
                        p_bullet = NULL;
                    }
                }
            }
        }
        for(int i = 0; i < NUM_THREATS; i++){
            ThreatsObject* p_threat = (p_threats + i);
            if(p_threat != NULL){
                SDL_Rect posThreat = p_threat->getPos() ;
                SDL_Rect rectThreat = p_threat->getRect();

                p_threat->setDegrees(mainTank.getPos(), i);
                double degThreat = p_threat->getDegrees();
                
                p_threat->renderCopy(posThreat.x, posThreat.y, &rectThreat, degThreat, NULL, SDL_FLIP_NONE);
                p_threat->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);

                //Run bullet of threat
            
                p_threat->runBullet(SCREEN_WIDTH, SCREEN_HEIGHT);
            }

        } 

        //Run threat


        SDL_RenderPresent(gRenderer);
    }
     
    delete[] p_threats;
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

    gScreenSurface = SDL_GetWindowSurface(gWindow);     // HERE

    if(gRenderer == nullptr){
        logSDLError(cout, "Create Renderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" );
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(){

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

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
//up



