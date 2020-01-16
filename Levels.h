#ifndef LEVELS_H_INCLUDED
#define LEVELS_H_INCLUDED
#include <iostream>
#include <vector>

class Levels
{

public:
    Levels();
    int ChoisirNiveau(SDL_Surface*);
    std::string getNiveau(int i);
private:
    std::vector<std::string> niveaux = {"map1.txt","map2.txt"};
    SDL_Surface* choixNiveau;


};

#endif // LEVELS_H_INCLUDED
