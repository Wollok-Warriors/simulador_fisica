#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>
#include "physics.h"

void init(SDL_Window** window, SDL_Renderer** renderer);
void close_SDL(SDL_Window* window, SDL_Renderer* renderer);
void DrawFilledCircle(SDL_Renderer* renderer, int x0, int y0, int radius);
void draw(SDL_Renderer* renderer, Ball* balls, int num_balls, Segment* segments, int num_segments, bool paused);
