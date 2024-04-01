#include "headers/allheaders.h"

_window initialize_window(int width, int height, int x, int y, int r, int g, int b, SDL_Renderer * renderer){
    _window initializing_window;
    SDL_Rect rect = {width, height, x, y};
    initializing_window.window = rect;
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 200, 150, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    initializing_window.tex = texture;
    return initializing_window;
}

void draw_window(SDL_Renderer * renderer, _window current_window){
    SDL_RenderCopy(renderer, current_window.tex, NULL, &current_window.window);
}