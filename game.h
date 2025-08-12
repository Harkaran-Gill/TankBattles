//
// Created by harka on 29-06-2025.
//

#ifndef GAME_H
#define GAME_H

#define TRUE 1
#define FALSE 0
#define FRAMES 60
#define FRAME_TIME 1000/FRAMES

#include <stdio.h>
#include <SDL.h>
#include "tank.h"

void process_input();
void update();
void render(SDL_Renderer *renderer);
void draw_surface(SDL_Renderer *renderer);

#endif //GAME_H
