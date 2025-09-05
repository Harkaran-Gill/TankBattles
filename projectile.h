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

void create_projectile(float tank_middle_pos, float tank_y, double angle);
void update_projectiles(int delta_time);
void draw_projectiles();
void destroy_projectiles(int window_width);
#endif //PROJECTILE_H
