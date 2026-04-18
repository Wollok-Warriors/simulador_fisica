#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 750

typedef struct {
    float x;
    float y;
} Vec2;

typedef struct {
    Vec2 pos;
    Vec2 vel;
    Vec2 acc;
    int radius;
} Ball;

