#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <vector>


class Game
{

public:
    Game(std::string );
    virtual void genererFichier();
    void genererSprites(SDL_Surface *screen, int [][18]);
    bool gagner();
    void incX(SDL_Surface*,SDL_Rect* );
    void redX(SDL_Surface*,SDL_Rect* );
    void incY(SDL_Surface*,SDL_Rect* );
    void redY(SDL_Surface*,SDL_Rect* );
    virtual int jouer(SDL_Surface*);
    void setFileMap(std::string file);
    int getNbMap();
    std::string getMap(int);

private:
    std::vector<std::string> nbMaps = {"map.txt","map2.txt"};
    std::vector<int>  coordX;
    std::vector<int> coordY ;
    int compteurX = 0;
    int compteurY=0;

protected:
    std::string fileMap;
    bool marioSpawned = false;
    SDL_Surface* mario;
    SDL_Surface* mur;
    SDL_Surface* caisse ;
    SDL_Surface* objectif ;
    SDL_Surface* caisse_ok;
    SDL_Rect dstrect;
    SDL_Rect posMario;int lab[18][18];



};
#endif // GAME_H_INCLUDED
