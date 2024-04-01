all:
	gcc -o result system_update.c buttons.c system_params.c windows.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf --pedantic -Wall
	./result
