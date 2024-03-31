#include <stdio.h>
#include <SDL2/SDL.h>
#include "headers/allheaders.h"
#include "headers/buttons.h"

button initialize_start_button(int width, SDL_Renderer * renderer){
    button start_button;

    TTF_Init();
    start_button.font = TTF_OpenFont("font.ttf", 16);
    SDL_Color col = {255, 255, 255, 255};
    SDL_Surface *stext = TTF_RenderText_Blended_Wrapped(start_button.font, "huy v zhope", col, 600);
    SDL_Texture *main_text = SDL_CreateTextureFromSurface(renderer, stext);

    if (!start_button.font){
        printf("Cannot download font!");
        exit(0);
    }

    start_button.drect.h = 100;
    start_button.drect.w = 250;

    start_button.drect.x = width/2 - start_button.drect.w/2;
    start_button.drect.y = 200;
    
    start_button.is_selected = false;

    return start_button;
}

button initialize_exit_button(int width, SDL_Renderer * renderer){
    button exit_button;
    TTF_Init();
    exit_button.font = TTF_OpenFont("font.ttf", 16);
    SDL_Color col = {255, 255, 255, 255};
    SDL_Surface *stext = TTF_RenderText_Blended_Wrapped(exit_button.font, "huy v zhope", col, 600);
    SDL_Texture *main_text = SDL_CreateTextureFromSurface(renderer, stext);
    if (!exit_button.font){
        printf("Cannot download font!");
        exit(0);
    }

    exit_button.drect.h = 100;
    exit_button.drect.w = 250;

    exit_button.drect.x = width/2 - exit_button.drect.w/2;
    exit_button.drect.y = 330;
    
    exit_button.is_selected = false;

    return exit_button;
}

button update_button(button current_button, SDL_Rect mouse_point){
    if (SDL_HasIntersection(&current_button.drect, &mouse_point)){
        current_button.is_selected = true;

    }
    else{
        current_button.is_selected = false;

    }
    return current_button;
}

void draw_button(button current_button, SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, current_button.font, NULL, &current_button.drect);
}