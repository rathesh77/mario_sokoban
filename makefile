CPP=g++ 
CFLAGS=-O3 
LDFLAGS= `sdl-config --cflags --libs` `pkg-config --cflags --libs SDL_image`
EXEC=mario  

all: ${EXEC}

${EXEC}: ${EXEC}.o
	${CPP} $(CFLAGS) -o ${EXEC} ${EXEC}.o ${LDFLAGS}

${EXEC}.o: ${EXEC}.cpp
	${CPP} $(CFLAGS) -o ${EXEC}.o -c ${EXEC}.cpp


clean:	
	rm -fr *.o

mrproper: clean
	rm -fr ${EXEC}

	// g++ *.cpp -o mario `sdl-config --cflags --libs` `pkg-config --cflags --libs SDL_image` 