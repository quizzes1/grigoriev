#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

struct bullet
{
    float x, y;
    float was_x, was_y;
    float vel;
    float angle;
};

typedef struct bullet bullet;

void fire(bullet *, float, float, float, float);
void update_pos_b(bullet *, float, float, float);
void render_text(float, float, float,  SDL_Renderer *);
bool render_b(SDL_Renderer *, bullet *, SDL_Rect *, SDL_Texture *);

int main(int, char **)
{

    // init shit
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event e;
    bullet b;
    int x, y;

    // for bullet
    bool is_run = true;
    bool was_fire = false;
    SDL_Texture *texture = IMG_LoadTexture(renderer, "a.png");
    SDL_Rect dst;
    dst.h = 20;
    dst.w = 20;

    // constant

    float vel = 500;
    float g = 9.8f;
    float angle = 0.6f;

    // render_text(info, renderer);

    while (is_run)
    {
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                is_run = false;
            }

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_run = false;
                }

                if (e.key.keysym.sym == SDLK_z && was_fire == false)
                {
                    if (vel - 10 > 0)
                    {
                        vel = vel - 10;
                    }
                }

                if (e.key.keysym.sym == SDLK_x && was_fire == false)
                {
                    vel = vel + 10;
                }

                if (e.key.keysym.sym == SDLK_c && was_fire == false)
                {
                    if (g - 0.1 > 0)
                    {
                        g = g - 0.1;
                    }
                }

                if (e.key.keysym.sym == SDLK_v && was_fire == false)
                {
                    g = g + 0.1;
                }

                if (e.key.keysym.sym == SDLK_LCTRL && was_fire == false)
                {
                    angle = angle - 0.01;
                }

                if (e.key.keysym.sym == SDLK_LSHIFT && was_fire == false)
                {
                    angle = angle + 0.01;
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&x, &y);
                    fire(&b, x, y, -(M_PI / 3), vel);
                    was_fire = true;
                }
            }
        }

        if (was_fire)
        {
            update_pos_b(&b, 0.016f, g, angle);
            was_fire = render_b(renderer, &b, &dst, texture);
        }

        render_text(vel, g, angle, renderer);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void fire(bullet *b, float x, float y, float angle, float vel)
{
    b->x = x;
    b->y = y;
    b->angle = angle;
    b->vel = vel;
}

void update_pos_b(bullet *b, float time_wased, float g, float angle)
{
    float dx = b->vel * cos(b->angle) * time_wased;
    float dy = b->vel * sin(b->angle) * time_wased - 0.5f * g * time_wased * time_wased;

    b->was_x = b->x;
    b->was_y = b->y;
    b->x += dx;
    b->y += dy;
    b->angle += angle * time_wased;
}

bool render_b(SDL_Renderer *renderer, bullet *b, SDL_Rect *dst, SDL_Texture *texture)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderDrawPointF(renderer, b->was_x, b->was_y);

    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderDrawPointF(renderer, b->x, b->y);

    dst->x = b->was_x;
    dst->y = b->was_y;

    SDL_RenderFillRect(renderer, dst);

    dst->x = b->x;
    dst->y = b->y;

    if (dst->x >= 640 || dst->y >= 640)
    {
        return false;
    }

    SDL_RenderCopy(renderer, texture, NULL, dst);

    return true;
}

void render_text(float vel, float g, float angle, SDL_Renderer *renderer)
{
    char info[100];

    sprintf(info, "Your vel: %d\nYour g (gravity): %.1f\nYour angle %.2f", (int)vel, g, angle);

    SDL_Color col = {255, 255, 255, 255};
    TTF_Init();
    TTF_Font *fnt = TTF_OpenFont("OpenSans-Bold.ttf", 16);
    SDL_Surface *stext = TTF_RenderText_Blended_Wrapped(fnt, info, col, 600);
    SDL_Texture *main_text = SDL_CreateTextureFromSurface(renderer, stext);
    SDL_Rect dd;
    dd.x = 0;
    dd.y = 0;
    dd.w = stext->w;
    dd.h = stext->h;

    SDL_RenderCopy(renderer, main_text, NULL, &dd);
}