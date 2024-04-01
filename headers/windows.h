typedef struct _window {
    SDL_Rect window;
    SDL_Texture * tex;
} _window;

_window initialize_window(int width, int height, int x, int y, int r, int g, int b, SDL_Renderer * renderer);
void draw_window(SDL_Renderer * renderer, _window current_window);
