#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <ctime>
#include "Levels.h"
#include "Editor.h"
// g++ *.cpp -o mario `sdl-config --cflags --libs` `pkg-config --cflags --libs SDL_image` 
int main ( int argc, char** argv )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout<<SDL_GetError()<<std::endl;
        return 1;
    }

    SDL_Surface* screen = SDL_SetVideoMode((34*12), (34*12), 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    IMG_INIT_JPG;
    IMG_INIT_PNG;
    SDL_WM_SetCaption("Mario Sokoban","");
    SDL_WM_SetIcon(IMG_Load("textures/caisse.jpg"),NULL);
    atexit(SDL_Quit);

    SDL_Surface* menuImg = IMG_Load("textures/menu.jpg");

    SDL_Rect menuRect;
    menuRect.x = 0;
    menuRect.y = 0;
    bool leave = false;

    if ( !screen )
    {
        std::cout<<SDL_GetError()<<std::endl;
        return 1;
    }

    SDL_Event event;
    Levels l;
    Editor e("map2.txt");


    while (!leave)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            leave = true;
            break;
        }
        switch(event.key.keysym.sym)
        {
        case SDLK_KP1:
            l.ChoisirNiveau(screen);
            break;
        case SDLK_KP2:
            e.jouer(screen);
        break;


        }
        SDL_BlitSurface(menuImg,0,screen,&menuRect);
        SDL_Flip(screen);
    }

    return 0;
}

