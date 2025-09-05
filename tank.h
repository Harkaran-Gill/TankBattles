//
// Created by harka on 02-07-2025.
//

#ifndef TANK_H
#define TANK_H

#include <math.h>
#include <SDL.h>
#include <stdio.h>


#define PI 3.14159265358979323846


typedef struct {
    float pos;
    int health;
    float angle;
    int power;
} tank;

void draw_cannon(SDL_Renderer *renderer, int x1, int x2, int y1, int y2);
void draw_tank(SDL_Renderer *renderer);
void draw_wheels(SDL_Renderer *renderer, int cx, int cy, int r);
void setup_tanks();
void update_tanks(float frame_time, int window_width);
void get_tank_pos_and_angle(float* x, float* y, double* angle);
#endif //TANK_H
