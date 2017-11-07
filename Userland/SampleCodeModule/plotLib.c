#include "plotLib.h"
#include "mathLib.h"
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

void plotFunctionInt(int a, int b, int c) {
	sysClear();
	plotAxis();

	/*if (a == 0) {
		int r = (int) -c / b;


	} else {

	}*/

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

/*
void plotFunction(float a, float b, float c) {
	sysClear();
  plotAxis();

	// If a != 0 ===> quadratic function
	if (a >= 0.001 || a <= -0.001) {
		// x and y coordinates for the vertex
		float h = -(b / (2 * a));
		float k = c - ((b * b) / (4 * a));

		float sqrt_arg = (b * b) - (4 * a * c);

		// First and second root x and y coordinates
		// The relation between r1 and r2 should be such that r1 < r2
		float x_r1 = (-b + sqrt(sqrt_arg)) / (2 * a);
		float x_r2 = (-b - sqrt(sqrt_arg)) / (2 * a);

		if (x_r1 > x_r2) {
			float aux = x_r1;
			x_r1 = x_r2;
			x_r2 = aux;
		}

		float abs_dx = abs(x_r2 - x_r1);

		float x_left_boundary = x_r1 - (abs_dx / 2);
		float x_right_boundary = x_r2 + (abs_dx / 2);

		// Aligning the x axis boundaries to plot the function
		if (x_left_boundary >= 0.001 || x_right_boundary <= -0.001) {
			// code
		}
	} else {
		// It's linear ===> y = bx + c
    a = 0;

		float r = - c / b;

		int x_left_boundary = SCREEN_WIDTH;
		int x_right_boundary = 3;

		for (int i = x_left_boundary; i <= x_right_boundary; i++) {
			float fx = fx(i, a, b, c);
			int fx_to_int = (int)fx;
			float diff = abs((fx - (int)fx));
			int y = diff - 0.5 < 0.5 ? fx_to_int : (fx > 0 ? (fx_to_int+1) : (fx_to_int-1));

			sysPaintPixel(i, y, BG_B, BG_G, BG_R);
		}
	}
}
*/
