typedef struct button{
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Rect drect;
    SDL_Color main_col;
    SDL_Color highlight_col;
    bool is_selected;
    char name[100];
} button;

button initialize_button(int window_width, int height, int width, char *name, rgb_colour color, rgb_colour highlight_color, point position, int size,  SDL_Renderer * renderer);
button update_button(SDL_Renderer * renderer, button current_button, SDL_Rect mouse_point);
void draw_button(button current_button, SDL_Renderer* renderer); 