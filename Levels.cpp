#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Levels.h"
#include "Game.h"

Levels::Levels()
{

}
int Levels::ChoisirNiveau(SDL_Surface* screen)
{
     choixNiveau = IMG_Load("textures/choix.png");
    bool leave = false;
    SDL_Rect choixPos;
    choixPos.x = 0;
    choixPos.y = 0;
    SDL_Event event;
    Game g("");

    while (!leave)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {

        case SDL_KEYDOWN:

            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                leave = true;
                break;
            case SDLK_KP1:
                g.setFileMap(getNiveau(0));
                g.jouer(screen);

                break;
            case SDLK_KP2:
                g.setFileMap(getNiveau(1));
                g.jouer(screen);

                break;

            }

        }
        SDL_BlitSurface(choixNiveau,0,screen,&choixPos);
        // on rafraichit l'ecran
        SDL_Flip(screen);
    }
    return 1;
}
std::string Levels::getNiveau(int i)
{

    return niveaux[i];
}
