#include "headers/allheaders.h"

int WIDTH = 1280, HEIGHT = 720;

int main(int argc, char *argv[]){
    system_open();
    Menu_qualities menu = system_init();
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
    button buttons_to_draw[menu.buttons_counter+1];
    _window windows_to_draw[menu.windows_counter+1];
    int windows_drawn = 1;
    int buttons_drawn = 1;

    for(int i = 0; i < menu.buttons_counter; i++){
        buttons_to_draw[i] = initialize_button(WIDTH, menu.buttons[i].height, menu.buttons[i].width, menu.buttons[i].name, menu.buttons[i].color, menu.buttons[i].highlight_colour, menu.buttons[i].position, menu.buttons[i].size, renderer);
    }

    for(int i = 0; i < menu.windows_counter; i++){
        windows_to_draw[i] = initialize_window(menu.windows[i].width, menu.windows[i].height, menu.windows[i].position.coordinates_x, menu.windows[i].position.coordinates_y, menu.windows[i].color.r, menu.windows[i].color.g, menu.windows[i].color.b, renderer);
    }


    SDL_Event windowEvent;
    
    while (1) {
        SDL_Rect mouse_point;
        mouse_point.h = 1;
        mouse_point.w = 1;
        SDL_GetMouseState(&mouse_point.x, &mouse_point.y);
        for(int i = 0; i < windows_drawn; i++){
            draw_window(renderer, windows_to_draw[i]);
        }
        for(int i = 0; i < buttons_drawn; i++){
            buttons_to_draw[i] = update_button(renderer, buttons_to_draw[i], mouse_point);
            draw_button(buttons_to_draw[i], renderer);
        }
        if ( SDL_PollEvent ( &windowEvent ) ){
            if ( SDL_QUIT == windowEvent.type ){
                break;
            }
            if ( SDL_MOUSEBUTTONUP == windowEvent.type){
                if (windowEvent.button.button == SDL_BUTTON_LEFT){
                    if (buttons_to_draw[0].is_selected == true){
                        if(windows_drawn < menu.windows_counter){
                            windows_drawn++;
                        }
                        if(buttons_drawn < menu.buttons_counter){
                            buttons_drawn++;
                        }
                    }
                    else if (buttons_to_draw[1].is_selected == true){
                        if(windows_drawn != 1){
                            windows_drawn--;
                        }
                        if(buttons_drawn != 1){
                            buttons_drawn--;
                        } 
                    }
                    else if (buttons_to_draw[2].is_selected == true){
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
    system_close();
    return EXIT_SUCCESS;
}

