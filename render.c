#include "render.h"


void init(SDL_Window** window, SDL_Renderer** renderer) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return;
	}

	if (!SDL_CreateWindowAndRenderer("SDL3 Pure C Window", WINDOW_WIDTH, WINDOW_HEIGHT, 0, window, renderer)) {
		SDL_Log("Window/Renderer creation failed: %s", SDL_GetError());
		SDL_Quit();
		return;
	}
}

void close_SDL(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// ALGORITMO DE CHAD SUPER EFICIENTE
void draw_filled_circle(SDL_Renderer* renderer, int x0, int y0, int radius) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y) {
		SDL_RenderLine(renderer, x0 - x, y0 + y, x0 + x, y0 + y);
		SDL_RenderLine(renderer, x0 - x, y0 - y, x0 + x, y0 - y);
		SDL_RenderLine(renderer, x0 - y, y0 + x, x0 + y, y0 + x);
		SDL_RenderLine(renderer, x0 - y, y0 - x, x0 + y, y0 - x);

		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void draw(SDL_Renderer* renderer, Ball* balls, int num_balls, Segment* segments, int num_segments, bool paused) {
	SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
	SDL_RenderClear(renderer);

	// Segments
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int s = 0; s < num_segments; s++)
		SDL_RenderLine(renderer, segments[s].x0, segments[s].y0, segments[s].x1, segments[s].y1);

	// Balls
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i < num_balls; i++)
		draw_filled_circle(renderer, (int)balls[i].pos.x, (int)balls[i].pos.y, balls[i].radius);

	if (paused) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderLine(renderer, WINDOW_WIDTH/2 - 5, WINDOW_HEIGHT/2 - 15 , WINDOW_WIDTH/2 - 5, WINDOW_HEIGHT/2 + 15);
		SDL_RenderLine(renderer, WINDOW_WIDTH/2 + 5, WINDOW_HEIGHT/2 - 15 , WINDOW_WIDTH/2 + 5, WINDOW_HEIGHT/2 + 15);
	}

	SDL_RenderPresent(renderer);
}
