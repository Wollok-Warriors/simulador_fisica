#pragma once
#include <stdbool.h>

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 780
#define SQ(x) ((x)*(x))

typedef struct { float x, y; } Vec2;

typedef struct {
	Vec2 pos, vel;
	int radius;
} Ball;

typedef struct {
	float x0, y0, x1, y1;
	float restitution, mu_kinetic, mu_static;
} Segment;

extern float g;

void bounce(Ball* ball, float nx, float ny, float signed_dist, float restitution, float mu_kinetic, float mu_static);
void line_bounce(Ball* ball, float a, float b, float c, float restitution, float mu_kinetic, float mu_static);
void segment_bounce(Ball* ball, float x0, float y0, float x1, float y1, float restitution, float mu_kinetic, float mu_static);
void ball_bounce(Ball* a, Ball* b, float restitution);
void update(Ball* balls, int num_balls, Segment* segments, int num_segments, float dt);
