# fichier Makefile 

# installer SDL 1.2 tout d'abord 
# sous linux :  sudo apt-get install libsdl2.1-dev

CPP=g++#compilateur
CPPFLAGS=`sdl-config --cflags --libs` `pkg-config --cflags --libs SDL_image`# Flags
LDFLAGS=#Linker
LDLIBS =`sdl-config --libs SDL_image`
EXEC=mario#Nom du programme 


all: main.cpp Editor.cpp Editor.h Levels.cpp Levels.h Game.cpp Game.h Menu.h 
	${CPP} *.cpp -o ${EXEC} ${CPPFLAGS} && ./$(EXEC)

#install: 
#	sudo apt-get install libsdl1.2-dev
	
.PHONY: clean mrproper

clean:	
	rm -fr *.o

mrproper: clean
	rm -fr ${EXEC}
