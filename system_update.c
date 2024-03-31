#include "headers/allheaders.h"
#include "headers/buttons.h"
#include <SDL2/SDL.h>
#include "headers/system_initialize.h"

int WIDTH = 1280, HEIGHT = 720;

int main(int argc, char *argv[]){


    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (NULL == window){
        printf("Couldn't create window!");
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        printf("Couldn't create renderer!");
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 65, 105, 225, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    button start_button = initialize_start_button(WIDTH, renderer);
    button exit_button = initialize_exit_button(WIDTH, renderer);
    SDL_Event windowEvent;

    while (1) {
        SDL_Rect mouse_point;
        mouse_point.h = 1;
        mouse_point.w = 1;
        SDL_GetMouseState(&mouse_point.x, &mouse_point.y);
        start_button = update_button(start_button, mouse_point);
        exit_button = update_button(exit_button, mouse_point);
        draw_button(start_button, renderer);
        draw_button(exit_button, renderer);
        if ( SDL_PollEvent ( &windowEvent ) ){
            if ( SDL_QUIT == windowEvent.type ){
                break;
            }
            if ( SDL_MOUSEBUTTONUP == windowEvent.type){
                if (windowEvent.button.button == SDL_BUTTON_LEFT){
                    if (start_button.is_selected == true){
                        printf("start something\n");
                    }
                    if (exit_button.is_selected == true){
                        break;
                    }
                    
                }
            }
        } 
        
        
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return EXIT_SUCCESS;
}