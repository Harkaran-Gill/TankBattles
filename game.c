//
// Created by harka on 29-06-2025.
//

#include "./game.h"

int last_frame_time = 0;
int last_projectile_shot_time = 0;
static int surface_height;

void process_input(int *game_state) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                *game_state = FALSE;
            }
            if (event.key.keysym.sym == SDLK_SPACE && (SDL_GetTicks() - last_projectile_shot_time) > 500) {
                int x = 0;
                float y = 0;
                float angle = 0;
                float power = 0;
                get_tank_pos_and_angle(&x, &y, &angle, &power);
                create_projectile(x , y, angle, power);
                last_projectile_shot_time = (int) SDL_GetTicks();
            }
    }
}

void update(int window_width, int window_height) {
    int delta_time = (int) SDL_GetTicks() - last_frame_time;
    if (FRAME_TIME > delta_time) {
        SDL_Delay(FRAME_TIME - delta_time);
    }

    update_tanks(FRAME_TIME, window_width, window_height);
    update_projectiles((int) SDL_GetTicks() - last_frame_time);
    last_frame_time = (int) SDL_GetTicks();
    destroy_projectiles(window_width, surface_height);
}

void render(SDL_Renderer *renderer, int window_width, int height) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_power(renderer);
    draw_tank(renderer);
     draw_surface(renderer, window_width, height);
    draw_projectiles(renderer);

    SDL_RenderPresent(renderer);
}

void draw_surface(SDL_Renderer *renderer, int window_width, int window_height) {
    surface_height = (int)(0.80 * window_height);
    SDL_Rect surface = {0, surface_height, window_width, window_height-surface_height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &surface);
}
