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

void plotAxis();
void plotFunctionInt(int a, int b, int c);
void plotFunctionFloat(float a, float b, float c);
void plotLinearFloat(float x_right_boundary, float x_left_boundary, float pixelSize, float m, float b);

#endif
