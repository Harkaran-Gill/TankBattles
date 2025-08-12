//
// Created by harka on 02-07-2025.
//

#include "tank.h"

#include <math.h>
#include <SDL_render.h>
#include <stdio.h>

#include "game.h"

struct tank {
    float pos;
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
    tank1.pos = 75.0f;
    tank1.health = 100;
    tank1.angle = 0.5;
    tank1.power = 30;

    wheel1.x = tank1.pos + 8;
    wheel1.y =  498;
    wheel1.r = 5;

    wheel2.x = tank1.pos + 24;
    wheel2.y =  498;
    wheel2.r = 5;

    cannon1.l = 35;
    cannon1.x = (int) tank1.pos + 17 + cannon1.l; //17 is middle of the tank in terms of pixels
    cannon1.y = 475; // 475 is in terms of pixels to determine height from ground, ignoring changeable height for now


}

int c = 0;
void draw_tank(SDL_Renderer *renderer) {
    //drawing the main body
    SDL_Rect body1 = {(int)tank1.pos, 482, 35, 15};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &body1);

    //drawing the cannon
    SDL_Rect cannon = {(int) tank1.pos + 17, 475, 35, 5};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderFillRect(renderer, &cannon);


    int x2 = cannon.x - (int)(35 * cos(tank1.angle));
    int y2 = cannon.y - (int)(35 * sin(tank1.angle));
    SDL_RenderDrawLine(renderer, (int)tank1.pos+17, 475, x2, y2);


    int cx = (int)tank1.pos + 8;
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
    cx = (int)tank1.pos + 24;
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
        if (tank1.pos > 0) {
            tank1.pos -= 130.0f * (float)FRAME_TIME/1000;
        }
    }
    if (states[SDL_SCANCODE_RIGHT]) {
        if (tank1.pos < 465) {
            tank1.pos += 130.0f * (float)FRAME_TIME/1000;
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
}

