//
// Created by harka on 02-07-2025.
//

#include "tank.h"

const int tank_width = 35;
const int tank_height = 15;
const int cannon_offset = 17; // Distance between the back of the tank and base of the cannon

struct Cannon {
    int x;
    int y;
    int l;
};

struct Wheel {
    int x;
    int y;
    int r;
};

struct Tank {
    float pos_x;
    float pos_y;
    int health;
    double angle;
    int power;
    struct Cannon cannon;
    struct Wheel wheel[2];
} tank1;


void setup_tanks() {
    tank1.pos_x = 75;
    tank1.health = 100;
    tank1.angle = 2.2;
    tank1.power = 30;
    tank1.wheel[0] = (struct Wheel){tank1.pos_x + 5, 498, 5};
    tank1.wheel[1] = (struct Wheel){tank1.pos_x + 27, 498, 5};

    tank1.cannon.l = 35;
    tank1.cannon.x = (int) tank1.pos_x + cannon_offset + tank1.cannon.l;
    tank1.cannon.y = 475;
    // 475 is in terms of pixels to determine height from ground, ignoring changeable height for now
}


void update_tanks(float frame_time, int window_width) {
    const Uint8 *states = SDL_GetKeyboardState(NULL);
    if (states[SDL_SCANCODE_LEFT]) {
        if (tank1.pos_x > 0) {
            tank1.pos_x -= 130.0f * frame_time / 1000;
        }
    }
    if (states[SDL_SCANCODE_RIGHT]) {
        if (tank1.pos_x < (float) window_width - 25) {
            tank1.pos_x += 130.0f * frame_time / 1000;
        }
    }

    if (states[SDL_SCANCODE_UP]) {
        if (tank1.angle > 0) {
            tank1.angle -= 0.5 * frame_time / 1000;
        }
    }
    if (states[SDL_SCANCODE_DOWN]) {
        if (tank1.angle < PI) {
            tank1.angle += 0.5 * frame_time / 1000;
        }
    }
    /*
        if (states[SDL_SCANCODE_SPACE]) {
            printf("Spacebar pressed\n");
            create_projectile();
        }*/
    tank1.cannon.x = cannon_offset + (int) tank1.pos_x;
}


int c = 0;

void draw_tank(SDL_Renderer *renderer) {
    //drawing the main body
    SDL_Rect body1 = {(int) tank1.pos_x, 482, tank_width, tank_height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &body1);

    int x2 = tank1.cannon.x - (int) (35 * cos(tank1.angle));
    int y2 = tank1.cannon.y - (int) (35 * sin(tank1.angle));
    //SDL_RenderDrawLine(renderer, (int)tank1.pos_x + cannon_offset, 475, x2, y2);
    draw_cannon(renderer, (int) tank1.pos_x + cannon_offset, x2, tank1.cannon.y, y2);


    int cx = tank1.pos_x + 7;
    int cy = tank1.wheel[0].y;
    int r = tank1.wheel[0].r;
    draw_wheels(renderer, cx, cy, r);

    cx = (int) tank1.pos_x + 26;
    cy = tank1.wheel[1].y;
    r = tank1.wheel[1].r;
    draw_wheels(renderer, cx, cy, r);
}

void draw_cannon(SDL_Renderer *renderer, int x1, int x2, int y1, int y2) {
    for (int dy = -2; dy < 2; ++dy) {
        for (int dx = -1; dx < 1; ++dx) {
            SDL_RenderDrawLine(renderer, x1+dx, y1+dy, x2+dx, y2+dy);
        }
    }
}

void draw_cannon1(SDL_Renderer *renderer, int x1, int x2, int y1, int y2) {
    for (int i = -2; i <= 2; ++i) {
        SDL_RenderDrawLine(renderer, x1 + (int) round(sin(i)), y1 + (int) round(cos(i)),
                           x2 + (int) round(sin(i)), y2 + (int) round(cos(i)));
    }
}


void draw_wheels(SDL_Renderer *renderer, int cx, int cy, int r) {
    //drawing the wheels
    for (int i = cx - r; i <= cx + r; i++) {
        for (int j = cy - r; j <= cy + r; j++) {
            int ci = i - cx;
            int cj = j - cy;
            if (ci * ci + cj * cj < r * r) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
}

void get_tank_pos_and_angle(float *x, float *y, double *angle) {
    *x = tank1.pos_x;
    *y = (float) tank1.cannon.y;
    *angle = tank1.angle;
}
