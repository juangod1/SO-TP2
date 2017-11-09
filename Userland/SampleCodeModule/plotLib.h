#ifndef PLOTLIB_H_
#define PLOTLIB_H_

#include "mathLib.h"

#define BG_R 0
#define BG_G 255
#define BG_B 255
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define GRAPH_PARAMETERS 3
#define SCREEN_RATIO (SCREEN_WIDTH / SCREEN_HEIGHT)

void plotFunctionInt(int a, int b, int c);
void plotFunctionFloat(float a, float b, float c, int x_l, int x_r, int y_d, int y_u);
void plotLinearFloat(float x_left_boundary, float x_right_boundary,
		float y_down_boundary, float y_up_boundary ,float a, float b, float c);
void quadraticFunctionFloat(float a, float b, float c);

#endif
