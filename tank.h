//
// Created by harka on 02-07-2025.
//

#ifndef TANK_H
#define TANK_H
#include <SDL.h>
#include <math.h>
#include <stdio.h>

#include "game.h"
#include "main.h"

#define PI 3.14159265358979323846
#define MAX_PROJECTILES 100

typedef struct {
    float pos;
    int health;
    float angle;
    int power;
} tank;

void draw_tank(SDL_Renderer *renderer);
void setup_tanks();
void update_tanks();
void get_tank_pos_and_angle(float* x, float* y, double* angle);
#endif //TANK_H
