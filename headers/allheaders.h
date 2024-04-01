typedef enum bool {false, true} bool;

typedef struct point {
    int coordinates_x;
    int coordinates_y;
} point;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "system_params.h"
#include "buttons.h"