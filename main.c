#include "physics.h"
#include "render.h"
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	init(&window, &renderer);

	// Declaracion de PELOTAS podria agregarles el color y dsp masa y toda la pija
	Ball balls[] = {
		{ .pos = { 200.0f,  60.0f }, .vel = { 0, 0 }, .radius = 20 },
		{ .pos = { 400.0f, 100.0f }, .vel = { 0, 0 }, .radius = 25 },
		{ .pos = { 900.0f,  20.0f }, .vel = { 0, 0 }, .radius = 15 },
		{ .pos = {1000.0f,  20.0f }, .vel = { 0, 0 }, .radius = 10 },
	};
	int num_balls = sizeof(balls) / sizeof(balls[0]);

	// Declaracion de segmentos x0, y0, x1, y1, restitucion, friccion dinamica, friccion estatica
	Segment segments[] = {
		{ 0,              0,             WINDOW_WIDTH/2, WINDOW_HEIGHT, 0.8f, 0.02f, 0.03f },
		{ WINDOW_WIDTH/2, WINDOW_HEIGHT, WINDOW_WIDTH,   0,             0.8f, 0.02f, 0.03f },
	};
	int num_segments = sizeof(segments) / sizeof(segments[0]);

	bool quit = false;
	bool paused = false;
	SDL_Event event;

	// calculo de tiempo entre frames CHAD
	uint64_t now = SDL_GetPerformanceCounter();
	uint64_t last = 0;
	float dt = 0;
	float period = 1.0f / (float)SDL_GetPerformanceFrequency();

	while (!quit) {
		last = now;
		now = SDL_GetPerformanceCounter();
		dt = (float)(now - last) * period;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT)
				quit = true;
			// CON ESPACIO SE FRENA !!!!!
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE) {
				paused = !paused;
				if (!paused) now = SDL_GetPerformanceCounter();
			}
		}

		// siempre dibujar y solo updatear las phisics si NO esta passado
		if (!paused)
			update(balls, num_balls, segments, num_segments, dt);
		draw(renderer, balls, num_balls, segments, num_segments, paused);

		SDL_Delay(1);
	}

	close_SDL(window, renderer);
	return 0;
}
