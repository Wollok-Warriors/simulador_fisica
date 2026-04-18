#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 780

typedef struct {
    float x;
    float y;
} Vec2;

typedef struct {
    Vec2 pos;
    Vec2 vel;
    int radius;
} Ball;

void DrawFilledCircle(SDL_Renderer* renderer, int x0, int y0, int radius) {
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

int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	init(&window, &renderer);

	Ball ball = {
		.pos = { .x = WINDOW_WIDTH / 2.0f, .y = WINDOW_HEIGHT / 2.0f },
		.vel = { .x = 5.0f, .y = 5.0f },
		.radius = 20
	};

	bool quit = false;
	SDL_Event event;

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}

		ball.pos.x += ball.vel.x;
		ball.pos.y += ball.vel.y;

		if (ball.pos.x - ball.radius <= 0 || ball.pos.x + ball.radius >= WINDOW_WIDTH) {
			ball.vel.x = -ball.vel.x; 
		}
		if (ball.pos.y - ball.radius <= 0 || ball.pos.y + ball.radius >= WINDOW_HEIGHT) {
			ball.vel.y = -ball.vel.y; 
		}

		SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		DrawFilledCircle(renderer, (int)ball.pos.x, (int)ball.pos.y, ball.radius);

		SDL_RenderPresent(renderer);

		SDL_Delay(16); 
	}

	close_SDL(window, renderer);
	return 0;
}
