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

#define BLOCK_WIDTH 50
#define BLOCK_HEIGHT 30

#define	REL_HEIGHT_1 0
#define REL_HEIGHT_2 0

#define VEL_1 70
#define VEL_2 -70

#define MASS_1 100
#define MASS_2 200

typedef struct {
	Vector2 pos;
	float dy;
	float vel;
	float mass;
	float width;
	float height;
} Block;

typedef struct {
	Vector2 pos;
	float radius;
	float string_len;
} Polley;

void integrate_block(Block* b, Polley* polley, float acc, float dt) 
{
	b->vel += acc * dt;
	b->dy += b->vel * dt;
	b->pos.y = polley->pos.y + (polley->string_len - PI * polley->radius)/2 + b->dy;
}

void draw_block(Block* b) 
{
	DrawRectangle(
			b->pos.x,
			b->pos.y,
			b->width,
			b->height,
			GRAY
		     );
	DrawCircle(
			b->pos.x + b->width/2,
			b->pos.y + b->height/2,
			4,
			RED
		  );
}

void draw_polley(Polley* polley, Block* b1, Block* b2) 
{
	DrawCircle(polley->pos.x, polley->pos.y, polley->radius, BLACK);
	DrawLine(
			polley->pos.x - polley->radius,
			polley->pos.y,
			polley->pos.x - polley->radius,
			b1->pos.y,
			BLACK
		);

	DrawLine(
			polley->pos.x + polley->radius,
			polley->pos.y,
			polley->pos.x + polley->radius,
			b2->pos.y,
			BLACK
		);
}

void update_state(float polley_x, float polley_y, float polley_radius, float string_length, float block_width, float block_height, float mass1, float mass2, Block* b1, Block* b2, Polley* polley)
{
	polley->pos.x = polley_x;
	polley->pos.y = polley_y;
	polley->radius = polley_radius;
	polley->string_len = string_length;
	
	b1->mass = mass1;
	b1->pos.x = polley_x - polley_radius - block_width/2;
	b1->pos.y = polley_y + (string_length - PI * polley_radius)/2;
	b1->width = block_width;
	b1->height = block_height;

	b2->mass = mass2;
	b2->pos.x = polley_x - polley_radius - block_width/2;
	b2->pos.y = polley_y + (string_length - PI * polley_radius)/2;
	b2->width = block_width;
	b2->height = block_height;
}

int main(void) 
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Polley system");
	SetTargetFPS(60);

	float gravity;
	float polley_x;
	float polley_y;
	float polley_radius;
	float string_length;
	float rest_height;
	float block_width;
	float block_height;
	float mass1;
	float mass2;
	float vel1;
	float vel2;
	float rel_height1;
	float rel_height2;
	
	float dt;
	float time;
	char str[16];
	bool paused;
	bool end;
	float acc;

	gravity = GRAVITY;
	polley_x = POLLEY_POS_X;
	polley_y = POLLEY_POS_Y;
	polley_radius = POLLEY_R;
	string_length = STRING_LENGTH;
	rest_height = (string_length - PI * polley_radius)/2;
	block_width = BLOCK_WIDTH;
	block_height = BLOCK_HEIGHT;
	mass1 = MASS_1;
	mass2 = MASS_2;
	vel1 = VEL_1;
	vel2 = VEL_2;
	rel_height1 = REL_HEIGHT_1;
	rel_height2 = REL_HEIGHT_2;

	Polley polley = {
		.pos = {
			.x = polley_x,
			.y = polley_y,
		},
		.radius = polley_radius,
		.string_len = string_length,
	};

	Block b1 = {
		.dy = rel_height1,
		.vel = vel1,
		.mass = mass1,
		.pos = {
			.x = polley.pos.x - polley.radius - block_width/2,
			.y = polley.pos.y + rest_height,
		},
		.width = block_width,
		.height = block_height,
	};

	Block b2 = {
		.dy = rel_height2,
		.vel = vel2,
		.mass = mass2,
		.pos = {
			.x = polley.pos.x + polley.radius - block_width/2,
			.y = polley.pos.y + rest_height,
		},
		.width = block_width,
		.height = block_height,
	};

	acc = gravity*(b1.mass - b2.mass)/(b1.mass + b2.mass);
	paused = true;
	time = 0;
	dt = 0;
	end = false;

	while (!WindowShouldClose()) {
		dt = GetFrameTime();
		if (IsKeyPressed(KEY_SPACE) && !end) {
			paused = !paused;
		}

		if(!paused) {
			time += dt;

			integrate_block(&b1, &polley, acc, dt);
			integrate_block(&b2, &polley, -acc, dt);

			if(b1.pos.y <= polley_y) {
				if(b1.mass < b2.mass) {
					end = true;
					paused = true;
				}
				b1.dy = -rest_height;
				b2.dy = rest_height;
				b1.vel = 0;
				b2.vel = 0;
			}
			if(b2.pos.y <= polley_y) {
				if(b2.mass < b1.mass) {
					end = true;
					paused = true;
				}
				b2.dy = -rest_height;
				b1.dy = rest_height;
				b2.vel = 0;
				b1.vel = 0;
			}
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		draw_block(&b1);
		draw_block(&b2);
		draw_polley(&polley, &b1, &b2);

		DrawFPS(0, 0);
		sprintf(str, "Time: %.5f", time);
		DrawText(str, 0, 20, 20, BLACK);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
