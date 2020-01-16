#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Editor.h"
#include <fstream>


int Editor::jouer(SDL_Surface *screen)
{
    mario = IMG_Load("textures/mario_bas.gif");
    mur = IMG_Load("textures/mur.jpg");
    caisse = IMG_Load("textures/caisse.jpg");
    objectif = IMG_Load("textures/objectif.png");
    caisse_ok = IMG_Load("textures/caisse_ok.jpg");

    bool leave = false;
    bool clicGauche = false;
    bool clicDroit = false;

    SDL_Event event;
    SDL_EnableKeyRepeat(100,100);

    genererFichier();

    while (!leave)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            leave = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if ( event.button.button == SDL_BUTTON_LEFT)
            {
                clicGauche = true;
                clicDroit = false;

            }
            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                clicDroit = true;
                clicGauche = false;
            }
            break;

        case SDL_MOUSEMOTION:
            if(clicGauche) lab[event.button.y/34][event.button.x/34] = item;
            else if (clicDroit) lab[event.button.y/34][event.button.x/34] = 0;
            break;

        case SDL_MOUSEBUTTONUP:
            clicGauche = false;
            clicDroit = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                leave = true;
                break;
            case SDLK_KP1:
                item = 1;
                break;
            case SDLK_KP2:
                item = 2;
                break;
            case SDLK_KP3:
                item = 3;
                break;
            case SDLK_KP4:
                save();
                leave = true;
                break;

            }
            break;
        }
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));
        genererSprites(screen,lab);
        SDL_Flip(screen);
    }
    return 0;
}
void Editor::genererFichier()
{

    std::ifstream infile("maps/"+fileMap);
    std::string a;
    int x = 0;
    int y = 0;

    while (infile >> a[x] )
    {
        lab[y][x] = (a[x])-'0';
        x++;
        if ( x ==12)
        {
            x = 0;
            y+=1;
        }
    }
    infile.clear();
    infile.close();
// -----------------------------------
}
void Editor::save()
{

    std::ofstream offFile;
    offFile.open("maps/"+fileMap);
    for ( int i = 0 ; i < 12; i++)
    {
        for ( int j = 0 ; j < 12 ; j++)
        {
            offFile<< lab[i][j];
        }
    }
    offFile.close();
}
