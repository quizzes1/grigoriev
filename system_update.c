#include "headers/allheaders.h"

int WIDTH = 1280, HEIGHT = 720;

int main(int argc, char *argv[]){
    system_open();
    Menu_qualities menu = system_init();
    SDL_Init( SDL_INIT_EVERYTHING );
    for(int i = 0; i < menu.windows_counter; i++){
        WIDTH = menu.windows[i].width;
        HEIGHT = menu.windows[i].height;
        

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

        SDL_SetRenderDrawColor(renderer, menu.windows[i].color.r, menu.windows[i].color.g, menu.windows[i].color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        button buttons_to_draw[menu.buttons_counter+1];

        for(int j = 0; j < menu.buttons_counter; j++){
           buttons_to_draw[j] = initialize_button(WIDTH, menu.buttons[j].height, menu.buttons[j].width, menu.buttons[j].name, menu.buttons[j].color, menu.buttons[j].highlight_colour, menu.buttons[j].position, renderer);
        }
        SDL_Event windowEvent;
        
        while (1) {
            SDL_Rect mouse_point;
            mouse_point.h = 1;
            mouse_point.w = 1;
            SDL_GetMouseState(&mouse_point.x, &mouse_point.y);
            for(int j = 0; j < menu.buttons_counter; j++){
                buttons_to_draw[j] = update_button(renderer, buttons_to_draw[j], mouse_point);
                draw_button(buttons_to_draw[j], renderer);
            }

            if ( SDL_PollEvent ( &windowEvent ) ){
                if ( SDL_QUIT == windowEvent.type ){
                    break;
                }
                if ( SDL_MOUSEBUTTONUP == windowEvent.type){
                    if (windowEvent.button.button == SDL_BUTTON_LEFT){
                        if (buttons_to_draw[0].is_selected == true){
                            printf("start something\n");
                        }
                        if (buttons_to_draw[1].is_selected == true){
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
    }
    SDL_Quit();
    system_close();
    return EXIT_SUCCESS;
}