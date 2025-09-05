//
// Created by harka on 29-06-2025.
//

#ifndef GAME_H
#define GAME_H

#define TRUE 1
#define FALSE 0
#define FRAMES 120
#define FRAME_TIME 1000/FRAMES

#include <stdio.h>
#include <SDL.h>
#include "tank.h"
#include "projectile.h"

void process_input();
void update(int width, int height);
void render(SDL_Renderer *renderer, int width, int height);
void draw_surface(SDL_Renderer *renderer, int window_width, int window_height);

#endif //GAME_H
