//
// Created by harka on 12-08-2025.
//

#include "projectile.h"


struct Projectile {
    float x;
    float y;
    int r;
    float v_y;
    float v_x;
    int is_active;
};

const int acceleration = 150;
struct Projectile* projectiles[MAX_PROJECTILES] = {NULL};

/**
 * Creating a projectile
 */
void create_projectile(float tank_middle_pos, float tank_y, double angle) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i] == NULL) {
            struct Projectile *p = malloc(sizeof(struct Projectile));
            p->x = tank_middle_pos - (int)(35 * cos(angle));
            p->y = tank_y - (float)(35 * sin(angle));
            p->r = 3;
            p->v_x = -200.0f * cos(angle);
            p->v_y = -200.0f * sin(angle);
            p->is_active = 1;
            projectiles[i] = p;
            break;
        }
    }
}

void update_projectiles(int delta_time){
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i] != NULL) {
            //struct Projectile *p = projectiles[i];
            //printf("old Projectile %f\n", projectiles[i]->x);
            projectiles[i]->x += (float)delta_time/1000 * projectiles[i]->v_x;
            //printf("new Projectile %.5f\n", (float)delta_time/1000);
            projectiles[i]->y += (float)delta_time/1000 * projectiles[i]->v_y;
            projectiles[i]->v_y += acceleration * (float)delta_time/1000;
        }
    }
}

void draw_projectiles(SDL_Renderer *renderer) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i] != NULL) {
            int cx = projectiles[i]->x;
            int cy = projectiles[i]->y;
            int r = projectiles[i]->r;
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

void destroy_projectiles() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i] != NULL) {
            int cx = projectiles[i]->x;
            int cy = projectiles[i]->y;
            if (cx < 0 || cx > WINDOW_WIDTH || cy < 0 || cy > 500) {
                free(projectiles[i]);
                projectiles[i] = NULL;
            }
        }
    }
}
