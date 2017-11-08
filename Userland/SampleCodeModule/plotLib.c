#include "plotLib.h"
#include "mathLib.h"
#include "stdLib.h"
#include <stdint.h>

void plotAxis() {
	// Variables to represent the x and y origin coordinates respectively
	int x_0 = (SCREEN_WIDTH / 2) - 1;
	int y_0 = (SCREEN_HEIGHT / 2) - 1;

	// Paint the y-axis
	for (int j = 0; j < SCREEN_HEIGHT; j++) {
		if (j == y_0) {
			// Paint the x-axis
			for (int i = 0; i < SCREEN_WIDTH; i++) {
				sysPaintPixel(i, j, BG_R, BG_B, BG_G);
			}
		} else {
			sysPaintPixel(x_0, j, BG_R, BG_B, BG_G);
		}
	}
}
/*
void plotFunctionInt(int a, int b, int c) {
	sysClear();
	plotAxis();

	int x_left_boundary = -(SCREEN_WIDTH / 2) + 1;
	int x_right_boundary = SCREEN_WIDTH / 2;
	int y_down_boundary = -(SCREEN_HEIGHT / 2) + 1;
	int y_up_boundary = SCREEN_HEIGHT / 2;

	//float diff;
	//int y;
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		 int Fx = fx(x_left_boundary + i, a, b, c);
		//diff = absInt((Fx - (int)Fx));
		//y = (diff - 0.5 < 0.5) ? fx_to_int : (Fx > 0 ? (fx_to_int+1) : (fx_to_int-1));

		sysPaintPixel(i, - Fx + y_up_boundary, BG_R, BG_G, BG_B);
	}
}
*/

// Finds the closest float to x that is multiple of the given interval
float findFloor(float x, float interval) {
	float x_floor = 0;
	float abs_x = absFloat(x);

	while (x_floor < abs_x) {
		x_floor += interval;
	}

	return x > 0 ? x_floor : -x_floor;
}

void plotLinearFloat(float x_left_boundary, float x_right_boundary, float pixelSize, float m, float b) {
	for (float i = x_left_boundary; i <= x_right_boundary; i += pixelSize) {
		float fx = fxFloat(i, 0, m, b);
		float fx_floor = findFloor(fx, pixelSize);
		float diff = absFloat((fx - fx_floor));
		// Represents the closest float to 0 that multiple of pixelSize and bigger
		// than fx if fx > 0, or smaller than fx if fx < 0
		float fx_roof = fx > 0 ? (fx_floor + pixelSize) : (fx - pixelSize);
		int y = diff < (pixelSize / 2) ? fx_floor : fx_roof;

		sysPaintPixel((i / pixelSize), y, BG_B, BG_G, BG_R);
	}
}

// Plots y = m*x + b
void linearFunctionFloat(float m, float b) {
	float pixelSize;

	float x_left_boundary, x_right_boundary;
	float y_up_boundary, y_down_boundary;
	float r; // The root of the function (f(x) = 0)

	if (b == 0) {
		r = 0;

		// This is an arbitrary scale to have a pixelSize of 0.1
		y_up_boundary = SCREEN_HEIGHT / 20;
		y_down_boundary = -y_up_boundary;

		x_right_boundary = y_up_boundary * SCREEN_RATIO;
		x_left_boundary = -x_right_boundary;
	} else {
		r = -b / m;

		float dx = absFloat(r);	// The distance between (0,0) and (r,0)
		float dy = absFloat(b); // The distance between (0,0) and (0,b)

		// If the slope of the function is more vertical than horizontal
		if (absFloat(m) >= 1) {
			/*
			** Double the differential in the y axis will be the distance from b
			** (where the function "cuts" the y axis) to the upper and lower ends of
			** the screen
			*/
			y_up_boundary = b + (dy * 2);
			y_down_boundary = b - (dy * 2);

			x_right_boundary = y_up_boundary * SCREEN_RATIO;
			x_left_boundary = y_down_boundary * SCREEN_RATIO;
		} else {
			// If the slope of the function is more horizontal than vertical
			x_right_boundary = r + (dx * 2);
			x_left_boundary = r - (dx * 2);

			y_up_boundary = x_right_boundary / SCREEN_RATIO;
			y_down_boundary = x_left_boundary / SCREEN_RATIO;
		}
	}

	// The total range of the y axis divided by the screen's height
	pixelSize = (y_up_boundary * 2) / SCREEN_HEIGHT;

	plotLinearFloat(x_left_boundary, x_right_boundary, pixelSize, m, b);
}

void plotFunctionFloat(float a, float b, float c) {
	sysClear();
  //plotAxis();

	// If a ~~ 0 ==> linear function ==> y = bx + c
	if (a < 0.001 && a > -0.001) {
		linearFunctionFloat(b, c);
	} else {
		//quadraticFunctionFloat(a, b, c);
	}
}

/*
void quadraticFunctionFloat(float a, float b, float c) {
	// x and y coordinates for the vertex
	float h = -(b / (2 * a));
	float k = c - ((b * b) / (4 * a));

	float sqrt_abc = sqrt((b * b) - (4 * a * c));

	// First and second root x and y coordinates
	float r1 = (-b + sqrt_abc) / (2 * a);
	float r2 = (-b - sqrt_abc) / (2 * a);

	// The relation between r1 and r2 should be such that r1 < r2
	if (r1 > r2) {
		float aux = r1;
		r1 = r2;
		r2 = aux;
	}

	// The distance between the two roots
	float abs_root_dx = abs(r2 - r1);

	if (abs_root_dx < 0.001 && abs_root_dx > -0.001) {
		// The distance between the two roots is minimal ==> there is only one
		// root
		float r = 0;
	} else {
		float x_left_boundary = r1 - (abs_root_dx / 2);
		float x_right_boundary = r2 + (abs_root_dx / 2);
	}
}
*/
