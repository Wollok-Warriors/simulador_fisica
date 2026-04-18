#include "physics.h"
#include <math.h>

// ajustable
float g = 980.0f;

// rebote / colision de una superficie
// nx y ny describen el vector normal de la superficio (apunttando a donde esta la bola) (normalizado)
void bounce(Ball* ball, float nx, float ny, float dist, float restitution, float mu_kinetic, float mu_static) {
	if (dist >= (float)ball->radius) return;

	float vel_toward = ball->vel.x * nx + ball->vel.y * ny;
	if (vel_toward >= 0) return;

	float vn_x = vel_toward * nx;
	float vn_y = vel_toward * ny;
	float vt_x = ball->vel.x - vn_x;
	float vt_y = ball->vel.y - vn_y;
	float vt_speed_sq = vt_x*vt_x + vt_y*vt_y;

	float new_vn = -restitution * vel_toward;
	if (fabsf(new_vn) < 20.0f) new_vn = 0.0f;

	if (vt_speed_sq < SQ(mu_static * fabsf(vel_toward))) {
		ball->vel.x = new_vn * nx;
		ball->vel.y = new_vn * ny;
	} else {
		ball->vel.x = new_vn * nx + (1.0f - mu_kinetic) * vt_x;
		ball->vel.y = new_vn * ny + (1.0f - mu_kinetic) * vt_y;
	}

	float penetration = (float)ball->radius - dist;
	ball->pos.x += nx * penetration;
	ball->pos.y += ny * penetration;
}

// para una linea descrita como ax + by + c = 0, consigo nx y ny normalizados
void line_bounce(Ball* ball, float a, float b, float c, float restitution, float mu_kinetic, float mu_static) {
	float len = sqrtf(a*a + b*b);
	float nx = a / len, ny = b / len;
	float d = fabsf((a * ball->pos.x + b * ball->pos.y + c) / len);
	bounce(ball, nx, ny, d, restitution, mu_kinetic, mu_static);
}

// paro un segmentto consigo a b y c
void segment_bounce(Ball* ball, float x0, float y0, float x1, float y1, float restitution, float mu_kinetic, float mu_static) {
	float dx = x1 - x0;
	float dy = y1 - y0;
	float a = dy;
	float b = -dx;
	float c = -(a * x0 + b * y0);
	line_bounce(ball, a, b, c, restitution, mu_kinetic, mu_static);
}

void ball_bounce(Ball* a, Ball* b, float restitution) {
	float dx = b->pos.x - a->pos.x;
	float dy = b->pos.y - a->pos.y;
	float dist = sqrtf(dx*dx + dy*dy);
	float min_dist = (float)(a->radius + b->radius);

	if (dist >= min_dist || dist < 0.0001f) return;

	float nx = dx / dist;
	float ny = dy / dist;

	float dvx = a->vel.x - b->vel.x;
	float dvy = a->vel.y - b->vel.y;
	float vel_toward = dvx * nx + dvy * ny;

	if (vel_toward <= 0) return;

	float j = -(1.0f + restitution) * vel_toward / 2.0f;

	a->vel.x += j * nx;
	a->vel.y += j * ny;
	b->vel.x -= j * nx;
	b->vel.y -= j * ny;

	float penetration = min_dist - dist;
	a->pos.x -= nx * penetration / 2.0f;
	a->pos.y -= ny * penetration / 2.0f;
	b->pos.x += nx * penetration / 2.0f;
	b->pos.y += ny * penetration / 2.0f;
}

void update(Ball* balls, int num_balls, Segment* segments, int num_segments, float dt) {
	for (int i = 0; i < num_balls; i++) {
		// Balls
		balls[i].pos.x += balls[i].vel.x * dt;
		balls[i].pos.y += balls[i].vel.y * dt;
		balls[i].vel.y += g * dt;

		// Walls
		line_bounce(&balls[i],  1.0f,  0.0f,  0.0f,                1.0f, 0.0f, 0.0f);
		line_bounce(&balls[i], -1.0f,  0.0f,  (float)WINDOW_WIDTH, 1.0f, 0.0f, 0.0f);
		line_bounce(&balls[i],  0.0f,  1.0f,  0.0f,                1.0f, 0.0f, 0.0f);
		line_bounce(&balls[i],  0.0f, -1.0f,  (float)WINDOW_HEIGHT, 1.0f, 0.0f, 0.0f);

		// Segments
		for (int s = 0; s < num_segments; s++)
			segment_bounce(&balls[i],
					segments[s].x0, segments[s].y0,
					segments[s].x1, segments[s].y1,
					segments[s].restitution, 
					segments[s].mu_kinetic, segments[s].mu_static);
	}

	// Ball-ball collisions
	for (int i = 0; i < num_balls; i++)
		for (int j = i + 1; j < num_balls; j++)
			ball_bounce(&balls[i], &balls[j], 0.9f);
}
