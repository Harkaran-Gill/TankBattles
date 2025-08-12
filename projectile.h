//
// Created by harka on 12-08-2025.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "game.h"
#include <tgmath.h>

void create_projectile(float tank_middle_pos, float tank_y, double angle);
void update_projectiles(int delta_time);
void draw_projectiles();
void destroy_projectiles();
#endif //PROJECTILE_H
