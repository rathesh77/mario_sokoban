#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>


Game::Game(std::string file)
{
    fileMap = file;
}
int Game::jouer(SDL_Surface* screen)
{
    //  DECLARATION DES TEXTURES ET COORDONNEES DES SPRITES
    mario = IMG_Load("textures/mario_bas.gif");
    mur = IMG_Load("textures/mur.jpg");
    caisse = IMG_Load("textures/caisse.jpg");
    objectif = IMG_Load("textures/objectif.png");
    caisse_ok = IMG_Load("textures/caisse_ok.jpg");
    bool leave = false;
    dstrect.x = 0;
    dstrect.y = 0;
    //  ----------------------------------------------------

    // GENERATION DE LA MAP
    genererFichier();
    // -----------------------------------------------------

    SDL_Event event;
    SDL_EnableKeyRepeat(100,80);
    while (!leave)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_KEYDOWN:

            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                incX(screen,&posMario);
                mario = IMG_Load("textures/mario_droite.gif");
                break;
            case SDLK_LEFT:
                redX(screen,&posMario);
                mario = IMG_Load("textures/mario_gauche.gif");
                break;
            case SDLK_DOWN:
                incY(screen,&posMario);
                mario = IMG_Load("textures/mario_bas.gif");
                break;
            case SDLK_UP:
                redY(screen,&posMario);
                mario = IMG_Load("textures/mario_haut.gif");
                break;
            case SDLK_ESCAPE:
                leave = true;
                break;
            }
            break;
        }

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

        // GENERATION DES MURS, CAISSES ET OBJECTIF
        genererSprites(screen,lab);
        // -------------------------------------------------------------

        if ( gagner())
            leave = true;
        // on fait apparaitre mario a une position innocup� par un mur
        SDL_BlitSurface(mario,0,screen,&posMario);
        // on rafraichit les textures
        SDL_Flip(screen);
    }
    // On libere l'espace memoire
    coordX.clear();
    coordY.clear();
    marioSpawned = false;

    SDL_EnableKeyRepeat(0,0);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(mario);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(caisse_ok);

    // -----------------------------
    return 0;
}


// FONCTIONS VISANT A DEPLACER MARIO HORIZONTALEMENT ET VERTICALEMENT
void Game::incX(SDL_Surface* screen,SDL_Rect* dist)
{
    if(compteurX<11) // si mario se trouve dans la fenetre horizonalement
    {
        if ( lab[compteurY][compteurX+1] ==0|| lab[compteurY][compteurX+1] ==3)
        {
            // si l'emplacement suivant est vide ou comporte l'objectif
            dist->x+=35;
            compteurX++;
        }
        else if( lab[compteurY][compteurX+1] == 2 &&(lab[compteurY][compteurX+2]==0 || lab[compteurY][compteurX+2]==3 ) )
        {
            // si l'emplacement suivant est une caisse vide ou comporte l'objectif et le prochain vide ou l'objectif

            lab[compteurY][compteurX+1] = 0;
            lab[compteurY][compteurX+2] = 2;
            dist->x+=35;
            compteurX++;

        }
    }
}
void Game::redX(SDL_Surface* screen,SDL_Rect* dist)
{
    if(compteurX>0) // si mario se trouve dans la fenetre horizonalement
    {
        if ( lab[compteurY][compteurX-1] ==0 || lab[compteurY][compteurX-1] ==3)
        {
            dist->x-=35;
            compteurX--;
        }
        else if( lab[compteurY][compteurX-1] == 2 &&(lab[compteurY][compteurX-2]==0 || lab[compteurY][compteurX-2]==3 ) )
        {
            lab[compteurY][compteurX-1] = 0;
            lab[compteurY][compteurX-2] = 2;
            dist->x-=35;
            compteurX--;

        }
    }
}
void Game::incY(SDL_Surface* screen,SDL_Rect* dist)
{

    if(compteurY<11)
    {

        if ( lab[compteurY+1][compteurX] ==0|| lab[compteurY+1][compteurX] ==3 )
        {
            dist->y+=33;
            compteurY++;
        }
        else if( lab[compteurY+1][compteurX] == 2 &&(lab[compteurY+2][compteurX]==0 || lab[compteurY+2][compteurX]==3 ) )
        {

            lab[compteurY+1][compteurX] = 0;
            lab[compteurY+2][compteurX] = 2;
            dist->y+=33;
            compteurY++;

        }
    }
}
void Game::redY(SDL_Surface* screen,SDL_Rect* dist)
{

    if(compteurY>0)
    {
        if ( lab[compteurY-1][compteurX] ==0|| lab[compteurY-1][compteurX] ==3)
        {
            dist->y-=33;
            compteurY--;
        }
        else if( lab[compteurY-1][compteurX] == 2 &&(lab[compteurY-2][compteurX]==0 || lab[compteurY-2][compteurX]==3 ) )
        {
            lab[compteurY-1][compteurX] = 0;
            lab[compteurY-2][compteurX] = 2;
             dist->y-=33;
            compteurY--;
        }
    }
}

// ------------------------------------------------------------------

void Game::genererFichier()
{
// LECTURE DU FICHIER CONTENANT LA MAP

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
void Game::setFileMap(std::string file)
{
    fileMap = file;
}
void Game::genererSprites(SDL_Surface *screen, int lab[][18])
{
    for ( int i = 0 ; i < (screen->w/mur->w)+1; i++)
    {
        for ( int j = 0 ; j <12; j++ )
        {
            if (lab[i][j] == 1) SDL_BlitSurface(mur,0,screen,&dstrect);
            else if (!marioSpawned)
            {
                posMario.x = dstrect.x;
                posMario.y = dstrect.y;
                marioSpawned = true;
                compteurY = i;
                compteurX = j;
            }
            else if (lab[i][j] == 2) SDL_BlitSurface(caisse,0,screen,&dstrect);
            else if ( lab[i][j] ==3)
            {
                SDL_BlitSurface(objectif,0,screen,&dstrect);
                coordY.push_back(i);
                coordX.push_back(j);
            }
            else if ( lab[i][j] == 4) SDL_BlitSurface(caisse_ok,0,screen,&dstrect);
            dstrect.x+=mur->w;
        }
        dstrect.y+=mur->h;
        dstrect.x = 0;
    }
    dstrect.x = 0;
    dstrect.y = 0;
}
bool Game::gagner()
{
    int objectifAtteint = 0;
    for ( int i = 0 ; i < coordX.size(); i++)
    {
        if ( lab[coordY[i]][coordX[i]] !=3)
        {
            lab[coordY[i]][coordX[i]] = 4;
            objectifAtteint++;
        }
    }
    return( objectifAtteint==coordX.size());
}
