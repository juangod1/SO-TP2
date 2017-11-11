#ifndef PLOTLIB_H_
#define PLOTLIB_H_

#include "mathLib.h"

#define G_R 0
#define G_G 255
#define G_B 255
#define A_R 255
#define A_G 255
#define A_B 0
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define GRAPH_PARAMETERS 3
#define SCREEN_RATIO (SCREEN_WIDTH / SCREEN_HEIGHT)
#define DIFFERENTIAL_FACTOR 0.1/20
#define AXIS_FACTOR 4.5
#define SCALE_AMOUNT 10
#define FACTOR 1.5
#define DEFAULT_PLOT 10

void plotWrapper(float x_l, float x_r, float y_d, float y_u, float a, float b, float c);
int scaleMarkY(int y);
int scaleMarkX(int x);
float plotAxis(float x_l, float x_r, float y_d, float y_u);
void plotFunction(float x_left_boundary, float x_right_boundary,
	float y_down_boundary, float y_up_boundary, float a, float b, float c);
int graphMain(float a, float b, float c);

#endif
