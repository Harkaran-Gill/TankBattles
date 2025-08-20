//
// Created by harka on 02-07-2025.
//

#include "tank.h"

const int tank_width = 35;
const int tank_height = 15;

struct tank {
    float pos_x;
    float pos_y;
    int health;
    double angle;
    int power;
} tank1;

struct cannon {
    int x;
    int y;
    int l;
} cannon1;

struct tires {
    float x;
    int y;
    int r;
} wheel1, wheel2;

void setup_tanks() {
    tank1.pos_x = 75.0f;
    tank1.health = 100;
    tank1.angle = 2.2;
    tank1.power = 30;

    wheel1.x = tank1.pos_x + 8;
    wheel1.y =  498;
    wheel1.r = 5;

    wheel2.x = tank1.pos_x + 24;
    wheel2.y =  498;
    wheel2.r = 5;

    cannon1.l = 35;
    cannon1.x = (int) tank1.pos_x + 17 + cannon1.l; //17 is middle of the tank in terms of pixels
    cannon1.y = 475; // 475 is in terms of pixels to determine height from ground, ignoring changeable height for now


}

int c = 0;
void draw_tank(SDL_Renderer *renderer) {
    //drawing the main body
    SDL_Rect body1 = {(int)tank1.pos_x, 482, tank_width, tank_height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &body1);

    //drawing the cannon, as of now drawing it using lines so the following code is not useful
    SDL_Rect cannons_rect = {(int) tank1.pos_x + 17, 475, 35, 5};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderFillRect(renderer, &cannons_rect);


    int x2 = cannons_rect.x - (int)(35 * cos(tank1.angle));
    int y2 = cannons_rect.y - (int)(35 * sin(tank1.angle));
    SDL_RenderDrawLine(renderer, (int)tank1.pos_x+17, 475, x2, y2);


    int cx = (int)tank1.pos_x + 8;
    int cy = wheel1.y;
    //drawing the tires
    for (int i = cx - wheel1.r; i <= cx + wheel1.r; i++) {
        for (int j = cy - wheel1.r; j <= cy + wheel1.r; j++) {
            int ci = i - cx;
            int cj = j - cy;
            if (ci*ci + cj*cj < wheel1.r*wheel1.r) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
    cx = (int)tank1.pos_x + 24;
    cy = wheel2.y;

    for (int i = cx - wheel2.r; i <= cx + wheel2.r; i++) {
        for (int j = cy - wheel2.r; j <= cy + wheel2.r; j++) {
            int ci = i - cx;
            int cj = j - cy;
            if (ci*ci + cj*cj <  wheel1.r*wheel1.r) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
}

void update_tanks() {
    const Uint8 *states = SDL_GetKeyboardState(NULL);
    if (states[SDL_SCANCODE_LEFT]) {
        if (tank1.pos_x > 0) {
            tank1.pos_x -= 130.0f * (float)FRAME_TIME/1000;
        }
    }
    if (states[SDL_SCANCODE_RIGHT]) {
        if (tank1.pos_x < WINDOW_WIDTH - 25) {
            tank1.pos_x += 130.0f * (float)FRAME_TIME/1000;
        }
    }

    if (states[SDL_SCANCODE_UP]) {
        if (tank1.angle > 0) {
            tank1.angle -= 0.5 * (double)FRAME_TIME/1000;
        }
    }
    if (states[SDL_SCANCODE_DOWN]) {
        if (tank1.angle < PI) {
            tank1.angle += 0.5 * (double)FRAME_TIME/1000;
        }
    }
/*
    if (states[SDL_SCANCODE_SPACE]) {
        printf("Spacebar pressed\n");
        create_projectile();
    }*/
    cannon1.x = 17 + tank1.pos_x;
}

void get_tank_pos_and_angle(float* x, float* y, double* angle) {
    *x = tank1.pos_x;
    *y = cannon1.y;
    *angle = tank1.angle;
}



