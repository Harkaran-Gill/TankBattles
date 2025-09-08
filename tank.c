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
    float angle;
    float power;
    struct Cannon cannon;
    struct Wheel wheel[2];
} tank1;


void setup_tanks() {
    tank1.pos_x = 75;               // X-coordinate of Left most part of the tank's body
    tank1.pos_y = 0.8f * 720 - 22.0f;       // Y-coordinate of Top of the tank's body
    tank1.health = 100;
    tank1.angle = 2.2f;
    tank1.power = 0.3f;             // Power of the projectiles shot

    tank1.wheel[0] = (struct Wheel){(int)tank1.pos_x + 5, (int)tank1.pos_y + 17, 5};
    tank1.wheel[1] = (struct Wheel){(int)tank1.pos_x + 27, (int)tank1.pos_y + 17, 5}; // 498

    tank1.cannon.l = 35;
    tank1.cannon.x = (int) tank1.pos_x + cannon_offset + tank1.cannon.l;
    tank1.cannon.y = (int)tank1.pos_y - 3;
    // 475 is in terms of pixels to determine height from ground, ignoring changeable height for now
}

void update_tanks(float frame_time, int window_width, int window_height) {
    const Uint8 *states = SDL_GetKeyboardState(NULL);
    if (states[SDL_SCANCODE_A]) {
        if (tank1.pos_x > 0) {
            tank1.pos_x -= 130.0f * frame_time / 1000;
        }
    }
    if (states[SDL_SCANCODE_D]) {
        if (tank1.pos_x < (float) window_width - 25) {
            tank1.pos_x += 130.0f * frame_time / 1000;
        }
    }

    if (states[SDL_SCANCODE_W]) {
        if (tank1.angle > 0) {
            tank1.angle -= 0.5f * frame_time / 1000;
        }
    }
    if (states[SDL_SCANCODE_S]) {
        if (tank1.angle < PI) {
            tank1.angle += 0.5f * frame_time / 1000;
        }
    }
    if (states[SDL_SCANCODE_Q]) {
        if (tank1.power > 0.1f)
            tank1.power -= 0.1f * frame_time / 1000;
    }
    if (states[SDL_SCANCODE_E]) {
        if (tank1.power < 1.0f)
            tank1.power += 0.1f * frame_time / 1000;
    }
    //printf("Power: %f\n", tank1.power);

    tank1.cannon.x = cannon_offset + (int) tank1.pos_x;
    tank1.pos_y = (float)window_height * 0.8f - 22.0f;
    tank1.wheel[0].x = (int)tank1.pos_x + 7;
    tank1.wheel[1].x = (int)tank1.pos_x + 26;

    tank1.wheel[0].y = (int)tank1.pos_y + 17;
    tank1.wheel[1].y = (int)tank1.pos_y + 17;

}

void draw_power(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect power_bar = {20, 20, (int)(100*tank1.power), 10};
    SDL_RenderFillRect(renderer, &power_bar);
}

void draw_tank(SDL_Renderer *renderer) {
    //drawing the main body
    SDL_Rect body1 = {(int) tank1.pos_x, (int)tank1.pos_y, tank_width, tank_height}; //482
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &body1);

    int x2 = tank1.cannon.x - (int) (35 * cosf(tank1.angle));
    int y2 = tank1.cannon.y - (int) (35 * sinf(tank1.angle));

    draw_cannon(renderer, (int) tank1.pos_x + cannon_offset, x2, tank1.cannon.y, y2);

    draw_wheels(renderer, tank1.wheel[0].x, tank1.wheel[0].y, tank1.wheel[0].r);

    draw_wheels(renderer, tank1.wheel[1].x, tank1.wheel[1].y, tank1.wheel[1].r);

}

void draw_cannon(SDL_Renderer *renderer, int x1, int x2, int y1, int y2) {
    for (int dy = -2; dy < 2; ++dy) {
        for (int dx = -1; dx < 1; ++dx) {
            SDL_RenderDrawLine(renderer, x1+dx, y1+dy, x2+dx, y2+dy);
        }
    }
}

// My logic, works fine just a little more expensive on compute
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

void get_tank_pos_and_angle(int *x, float *y, float *angle, float* power) {
    *x = tank1.cannon.x;
    *y = (float) tank1.cannon.y;
    *angle = tank1.angle;
    *power = tank1.power;
}
