//
// Created by harka on 12-08-2025.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>


#define MAX_PROJECTILES 100

void create_projectile(int tank_middle_pos, float tank_y, float angle, float power);
void update_projectiles(int delta_time);
void draw_projectiles();
void destroy_projectiles(int window_width, int surface_height);
#endif //PROJECTILE_H
