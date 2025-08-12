//
// Created by harka on 02-07-2025.
//

#ifndef TANK_H
#define TANK_H
#include <SDL.h>

#define PI 3.14159265358979323846

typedef struct {
    float pos;
    int health;
    float angle;
    int power;
} tank;

void draw_tank(SDL_Renderer *renderer);
void setup_tanks();
void update_tanks();
#endif //TANK_H
