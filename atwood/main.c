#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720

#define GRAVITY 20



#define POLLEY_POS_X 400
#define POLLEY_POS_Y 200

#define POLLEY_R 30

#define STRING_LENGTH 600

#define REST_HEIGHT (STRING_LENGTH - PI * POLLEY_R)/2

#define BLOCK_WIDTH 50
#define BLOCK_HEIGHT 30

#define	INIT_HEIGHT_1 0
#define INIT_HEIGHT_2 0

#define INIT_VEL_1 10
#define INIT_VEL_2 -10

#define MASS_1 100
#define MASS_2 200



typedef struct {
	Vector2 pos;
	float dy;
	float vel;
	float mass;
} Block;


int main(void) {
	float dt;
	float time;
	char str[16];
	bool paused;
	float acc;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Polley system");
	SetTargetFPS(60);
	
	Block mass1 = {
		.dy = INIT_HEIGHT_1,
		.vel = INIT_VEL_1,
		.mass = MASS_1,
		.pos = {
			.x = POLLEY_POS_X - POLLEY_R - BLOCK_WIDTH/2,
			.y = POLLEY_POS_Y + REST_HEIGHT,
		},
	};

	Block mass2 = {
		.dy = INIT_HEIGHT_2,
		.vel = INIT_VEL_2,
		.mass = MASS_2,
		.pos = {
			.x = POLLEY_POS_X + POLLEY_R - BLOCK_WIDTH/2,
			.y = POLLEY_POS_Y + REST_HEIGHT,
		},
	};

	acc = GRAVITY*(mass1.mass - mass2.mass)/(mass1.mass + mass2.mass);
	paused = true;
	time = 0;
	dt = 0;

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_SPACE)) {
			paused = !paused;
		}

		if(!paused) {
			dt = GetFrameTime();
			time += dt;

			mass1.vel += acc * dt;
			mass2.vel -= acc * dt;

			mass1.dy += mass1.vel * dt;
			mass2.dy += mass2.vel * dt;

			mass1.pos.y = POLLEY_POS_Y + REST_HEIGHT + mass1.dy;
			mass2.pos.y = POLLEY_POS_Y + REST_HEIGHT + mass2.dy;

			if(mass1.pos.y <= POLLEY_POS_Y) {
				paused = true;
				mass1.dy = -REST_HEIGHT;
				mass2.dy = REST_HEIGHT;
				mass1.vel = 0;
				mass2.vel = 0;
			}
			if(mass2.pos.y <= POLLEY_POS_Y) {
				paused = true;
				mass2.dy = -REST_HEIGHT;
				mass1.dy = REST_HEIGHT;
				mass2.vel = 0;
				mass1.vel = 0;
			}
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);


		DrawRectangle(
				mass1.pos.x,
				mass1.pos.y,
				BLOCK_WIDTH,
				BLOCK_HEIGHT,
				GRAY
			     );
		DrawCircle(
				mass1.pos.x + BLOCK_WIDTH/2,
				mass1.pos.y + BLOCK_HEIGHT/2,
				4,
				RED
			 );

		DrawRectangle(
				mass2.pos.x,
				mass2.pos.y,
				BLOCK_WIDTH,
				BLOCK_HEIGHT,
				GRAY
			     );
		DrawCircle(
				mass2.pos.x + BLOCK_WIDTH/2,
				mass2.pos.y + BLOCK_HEIGHT/2,
				4,
				RED
			 );

		DrawCircle(POLLEY_POS_X, POLLEY_POS_Y, POLLEY_R, BLACK);

		DrawLine(
			POLLEY_POS_X - POLLEY_R,
			POLLEY_POS_Y,
			POLLEY_POS_X - POLLEY_R,
			mass1.pos.y,
			BLACK
			);

		DrawLine(
			POLLEY_POS_X + POLLEY_R,
			POLLEY_POS_Y,
			POLLEY_POS_X + POLLEY_R,
			mass2.pos.y,
			BLACK
			);


		DrawFPS(0, 0);
		sprintf(str, "Time: %.5f", time);
		DrawText(str, 0, 20, 20, BLACK);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
