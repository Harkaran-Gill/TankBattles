//
// Created by harka on 29-06-2025.
//

#include "./game.h"

int last_frame_time = 0;
int last_projectile_shot_time = 0;

void process_input(int *game_state) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                *game_state = FALSE;
            }
            if (event.key.keysym.sym == SDLK_SPACE && (SDL_GetTicks() - last_projectile_shot_time) > 500) {
                float x = 0;
                float y = 0;
                double angle = 0;
                get_tank_pos_and_angle(&x, &y, &angle);
                create_projectile(x + 17, 475, angle);
                last_projectile_shot_time = (int) SDL_GetTicks();
            }
    }
}

void update(int window_width, int height) {
    int delta_time = (int) SDL_GetTicks() - last_frame_time;
    if (FRAME_TIME > delta_time) {
        SDL_Delay(FRAME_TIME - delta_time);
    }

    update_tanks(FRAME_TIME, window_width);
    update_projectiles((int) SDL_GetTicks() - last_frame_time);
    last_frame_time = (int) SDL_GetTicks();
    destroy_projectiles(window_width);
}

void render(SDL_Renderer *renderer, int window_width, int height) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_tank(renderer);
    draw_surface(renderer, window_width, height);
    draw_projectiles(renderer);

    SDL_RenderPresent(renderer);
}

void draw_surface(SDL_Renderer *renderer, int window_width, int window_height) {
    int surface_height = 0.69 * window_height;
    SDL_Rect surface = {0, 502, window_width, surface_height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &surface);
}
