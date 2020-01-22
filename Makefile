# fichier Makefile 

# installer SDL 1.2 tout d'abord 
# sous linux :  sudo apt-get install libsdl2.1-dev

CPP=g++#compilateur
CPPFLAGS=`sdl-config --cflags --libs` `pkg-config --cflags --libs SDL_image`# Flags
LDFLAGS=#Linker
LDLIBS =`sdl-config --libs SDL_image`
EXEC=mario#Nom du programme 
SOURCES= main.cpp Editor.cpp Editor.h Levels.cpp Levels.h Game.cpp Game.h Menu.h

#install: 
#	sudo apt-get install libsdl1.2-dev


.DEFAULT_GOAL = help

.PHONY: clean mrproper compile exec help

help: script.sh
	./script.sh

compile: $(SOURCES) 		#Compiler le programme
	${CPP} *.cpp -o ${EXEC} ${CPPFLAGS}

clean:	
	rm -fr *.o

mrproper: clean			#supprimer l'executable
	rm -fr $(EXEC)

exec: ${EXEC}  			#executer le programme 
	./${EXEC}	