#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600


typedef struct {
	Vector2 pos, vel;
	Vector2 size;
	Color	color;
} Block;

void integrate_block(Block* block, float dt)
{
	block->pos.x += block->vel.x * dt;
	block->pos.y += block->vel.y * dt;
}

void draw_block(Block* block)
{
	DrawRectangleV(block->pos, block->size, block->color);
}


int main(void) {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Block on Slope");
	SetTargetFPS(60);

	Block block = {
		.pos = { 150, 80 },
		.vel = { 0, 0 },
		.size = { 50, 30 },
		.color = BLACK,
	};

	while (!WindowShouldClose()) {
		float dt = fminf(GetFrameTime(), 0.05f);

		if (IsKeyPressed(KEY_SPACE)) {
			block.pos         = (Vector2){ 150, 80 };
			block.vel         = (Vector2){ 0, 0 };
		}
		if (IsKeyPressed(KEY_RIGHT)) {
			block.vel.x      += 250.0f;
		}
		if (IsKeyPressed(KEY_LEFT)) {
			block.vel.x      -= 250.0f;
		}
		if (IsKeyPressed(KEY_DOWN)) {
			block.vel.y      += 250.0f;
		}
		if (IsKeyPressed(KEY_UP)) {
			block.vel.y      -= 250.0f;
		}

		integrate_block(&block, dt);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		draw_block(&block);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
