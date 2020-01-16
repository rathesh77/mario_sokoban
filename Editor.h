#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

#include <iostream>
#include "Game.h"

class Editor : public Game{

public:
    Editor(std::string file) : Game(file){};
    virtual int jouer(SDL_Surface*);
    void genererFichier();
    void save();

private:
    int item = 1;

};

#endif // EDITOR_H_INCLUDED
