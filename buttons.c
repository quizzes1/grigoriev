#include "headers/allheaders.h"


button initialize_button(int window_width, int height, int width, char *name, rgb_colour color, rgb_colour highlight_color,  SDL_Renderer * renderer){
    button initializing_button;

    TTF_Init();
    initializing_button.font = TTF_OpenFont("font.ttf", 100);

    SDL_Color col = {color.r, color.g, color.b, 0};
    SDL_Color highlight_colour = {highlight_color.r, highlight_color.g, highlight_color.b, 0};
    initializing_button.main_col = col;
    initializing_button.highlight_col = highlight_colour;

    SDL_Surface *stext = TTF_RenderText_Blended_Wrapped(initializing_button.font, name, col, 600);
    SDL_Texture *main_text = SDL_CreateTextureFromSurface(renderer, stext);
    initializing_button.texture = main_text;
    strcpy(initializing_button.name, name);

    if (!initializing_button.font){
        printf("Cannot download font!");
        exit(0);
    }

    initializing_button.drect.h = height;
    initializing_button.drect.w = width;

    initializing_button.drect.x = window_width/2 - initializing_button.drect.w/2;
    initializing_button.drect.y = 200;
    
    initializing_button.is_selected = false;

    return initializing_button;
}


button update_button(SDL_Renderer * renderer, button current_button, SDL_Rect mouse_point){
    if (SDL_HasIntersection(&current_button.drect, &mouse_point)){
        current_button.is_selected = true;
        SDL_Color col = {current_button.highlight_col.r, current_button.highlight_col.g, current_button.highlight_col.b, 0};
        SDL_Surface *stext = TTF_RenderText_Blended_Wrapped(current_button.font,current_button.name, col, 600);
        SDL_Texture *main_text = SDL_CreateTextureFromSurface(renderer, stext);
        current_button.texture = main_text;
    }
    else{
        current_button.is_selected = false;
        SDL_Color col = {current_button.main_col.r, current_button.main_col.g, current_button.main_col.b, 0};
        SDL_Surface *stext = TTF_RenderText_Blended_Wrapped(current_button.font, current_button.name, col, 600);
        SDL_Texture *main_text = SDL_CreateTextureFromSurface(renderer, stext);
        current_button.texture = main_text;
    }
    return current_button;
}

void draw_button(button current_button, SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, current_button.texture, NULL, &current_button.drect);
}