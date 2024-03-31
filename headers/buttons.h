#include <SDL2/SDL_ttf.h>
typedef struct button{
    TTF_Font* font;
    SDL_Rect drect;
    bool is_selected;
} button;

button initialize_start_button(int width, SDL_Renderer * renderer);
button initialize_exit_button(int width, SDL_Renderer * renderer);
button update_button(button current_button, SDL_Rect mouse_point);
void draw_button(button current_button, SDL_Renderer* renderer);