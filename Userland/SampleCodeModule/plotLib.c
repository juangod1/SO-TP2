#include "plotLib.h"
#include "mathLib.h"
#include "stdLib.h"
#include <stdint.h>


// Finds the closest float to x that is multiple of the given interval
void plotLinearFloat(float x_left_boundary, float x_right_boundary,
		float y_down_boundary, float y_up_boundary, float a, float b, float c) {
	float x_val, y_val;
	float diff;
	sysPrintFloat(x_left_boundary,213,123,123);
	sysPrintString(" x_left\n", 255, 0, 0);
	sysPrintFloat(x_right_boundary,213,123,123);
	sysPrintString(" x_right\n", 255, 0, 0);
	sysPrintFloat(y_down_boundary,213,123,123);
	sysPrintString(" y_down\n", 255, 0, 0);
	sysPrintFloat(y_up_boundary,213,123,123);
	sysPrintString(" y_up\n", 255, 0, 0);
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT ; j++) {
			x_val = x_left_boundary + (i * (x_right_boundary - x_left_boundary)) / SCREEN_WIDTH;
			y_val = y_up_boundary - (j * (y_up_boundary - y_down_boundary)) / SCREEN_HEIGHT;

			diff = absFloat(fxFloat(x_val, a, b, c) - y_val);

			if (diff < 0.1) {
				sysPaintPixel(i, j, BG_B, BG_G, BG_R);
			}
			if(absFloat(x_val)<0.1 || absFloat(y_val)<0.1){ //PLOT AXIS
				sysPaintPixel(i,j, 0, 255,255);
			}
		}
	}
}

// Plots y = m*x + b
void linearFunctionFloat(float m, float b) {
	float pixelSize;

	float x_left_boundary, x_right_boundary;
	float y_up_boundary, y_down_boundary;
	float r; // The root of the function (f(x) = 0)

	if (b < 0.001 && b > -0.001) {
		r = 0.0;

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
	plotLinearFloat(x_left_boundary, x_right_boundary, y_down_boundary,y_up_boundary,0, m, b);
}

void plotFunctionFloat(float a, float b, float c) {
	sysClear();
	// If a ~~ 0 ==> linear function ==> y = bx + c
	if (a < 0.001 && a > -0.001) {
		linearFunctionFloat(b, c);
	} else {
		sysPrintFloat(a,0,0,123);
		sysPrintFloat(b,0,0,123);
		sysPrintFloat(c,0,0,123);
		sysPrintString("\n",0,0,0);
		quadraticFunctionFloat(a, b, c);
	}
}

void quadraticFunctionFloat(float a, float b, float c) {
	// interesting y coordinates
	float y_vertex = c - ((b * b) / (4 * a));
	float y_incept= c;




	float determinant=(b * b) - (4 * a * c);
	float sqrt_abc = sqrt(determinant);

	float r1;
	float r2;

	if(sqrt_abc==-1){ //sqrt of a negative number
			float x_vertex=-b/(2*a);
			r1=x_vertex;
			r2=x_vertex;
	}
	else{ // First and second root x coordinates
	r1 = (-b + sqrt_abc) / (2 * a);
	r2 = (-b - sqrt_abc) / (2 * a);
	}
	// The relation between r1 and r2 should be such that r1 < r2
	if (r1 > r2) {
		float aux = r1;
		r1 = r2;
		r2 = aux;
	}

	// The distance between the two roots
	float abs_root_dx = absFloat(r2 - r1);
	float x_left_boundary=-10;
	float x_right_boundary=10;
	float y_up_boundary;
	float y_down_boundary;
	int flag=0;
	if (abs_root_dx < 2 && abs_root_dx > 2) {
		// The distance between the two roots is minimal ==> there is only one
		// root
		flag=1;
	} else {
		x_left_boundary = r1 - (abs_root_dx / 2);
		x_right_boundary = r2 + (abs_root_dx / 2);
	}

	float abs_dist_y=absFloat(y_incept-y_vertex);

	if (abs_dist_y < 2 && abs_dist_y > 2) {
		// The distance between the two points is minimal ==> there is only one point of interest
		y_down_boundary = x_left_boundary;
		y_up_boundary = x_right_boundary;
	} else {
		y_down_boundary = y_vertex - (abs_dist_y / 2);
		y_up_boundary = y_incept + (abs_dist_y / 2);
	}
	if(flag){
		x_left_boundary = y_down_boundary;
		x_right_boundary = y_up_boundary;
	}
	plotLinearFloat(x_left_boundary, x_right_boundary, y_down_boundary,y_up_boundary,a, b, c);
}
