//
// Created by harka on 12-08-2025.
//

#include "projectile.h"

float proj_velocity = 450.0f;

struct Projectile {
    float x;
    float y;
    int r;
    float v_y;
    float v_x;
};

const int acceleration = 150;
struct Projectile* projectiles[MAX_PROJECTILES] = {NULL};

/**
 * Creating a projectile
 */
void create_projectile(int tank_middle_pos, float tank_y, float angle, float power) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i] == NULL) {
            struct Projectile *p = malloc(sizeof(struct Projectile));
            p->x = (float)tank_middle_pos - (35.0f * cosf(angle));
            p->y = tank_y - (35.0f * sinf(angle));
            p->r = 3;
            // Square root the function to counter the quadratic growth of the projectile's range
            p->v_x = sqrtf(power) * -proj_velocity * cosf(angle);
            p->v_y = sqrtf(power) * -proj_velocity * sinf(angle);
            projectiles[i] = p;
            break;
        }
    }
}

void update_projectiles(int delta_time){
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i] != NULL) {
            //printf("old Projectile %f\n", projectiles[i]->x);
            projectiles[i]->x += (float)delta_time/1000.0f * projectiles[i]->v_x;
            //printf("new Projectile %.5f\n", (float)delta_time/1000);
            projectiles[i]->y += (float)delta_time/1000.0f * projectiles[i]->v_y;
            projectiles[i]->v_y += (float)acceleration * (float)delta_time/1000.0f;
        }
    }
}

void draw_projectiles(SDL_Renderer *renderer) {
    for (int k = 0; k < MAX_PROJECTILES; k++) {
        if (projectiles[k] != NULL) {
            int cx = (int)projectiles[k]->x;
            int cy = (int)projectiles[k]->y;
            int r = projectiles[k]->r;
            for (int i = cx - r; i < cx + r; i++) {
                for (int j = cy - r; j < cy + r; j++) {
                    int ci = i - cx;
                    int cj = j - cy;
                    if (ci * ci + cj * cj < r * r) {
                        SDL_RenderDrawPoint(renderer, i, j);
                    }
                }
            }

        }
    }
}

void destroy_projectiles(int window_width, int surface_height) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i] != NULL) {
            int cx = (int)projectiles[i]->x;
            int cy = (int)projectiles[i]->y;
            if (cx < 0 || cx > window_width || cy < 0 || cy > surface_height) {
                free(projectiles[i]);
                projectiles[i] = NULL;
            }
        }
    }
}
