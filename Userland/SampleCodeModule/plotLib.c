#include "plotLib.h"
#include "mathLib.h"
#include "stdLib.h"
#include <stdint.h>


void plotLinearFloat(float x_left_boundary, float x_right_boundary,
		float y_down_boundary, float y_up_boundary, float a, float b, float c) {
	float x_val, y_val;
	float diff;
	/*sysPrintFloat(x_left_boundary,213,123,123);
	sysPrintString(" x_left\n", 255, 0, 0);
	sysPrintFloat(x_right_boundary,213,123,123);
	sysPrintString(" x_right\n", 255, 0, 0);
	sysPrintFloat(y_down_boundary,213,123,123);
	sysPrintString(" y_down\n", 255, 0, 0);
	sysPrintFloat(y_up_boundary,213,123,123);
	sysPrintString(" y_up\n", 255, 0, 0);*/
	float differential = (x_right_boundary-x_left_boundary)*DIFFERENTIAL_FACTOR;
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT ; j++) {
			x_val = x_left_boundary + (i * (x_right_boundary - x_left_boundary)) / SCREEN_WIDTH;
			y_val = y_up_boundary - (j * (y_up_boundary - y_down_boundary)) / SCREEN_HEIGHT;
			diff = absFloat(fxFloat(x_val, a, b, c) - y_val);

			if (diff < differential) {
				sysPaintPixel(i, j, G_B, G_G, G_R);
			}
		}
	}
}
plotAxis(float x_l, float x_r, float y_d, float y_u){
	float differential = (x_r-x_l)*DIFFERENTIAL_FACTOR;
	float scale = (x_r-x_l)/SCALE_AMOUNT;
	float x_val, y_val;
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT ; j++) {
			x_val = x_l + (i * (x_r- x_l)) / SCREEN_WIDTH;
			y_val = y_u - (j * (y_u- y_d)) / SCREEN_HEIGHT;

			if(absFloat(x_val)<differential/AXIS_FACTOR || absFloat(y_val)<differential/AXIS_FACTOR){ //PLOT AXIS
				sysPaintPixel(i,j, A_B, A_G,A_R);
			}
			if(absFloat(y_val)<differential && scaleMarkX(i)){
				sysPaintPixel(i,j, A_B, A_G,A_R);
			}
			else if(absFloat(x_val)<differential && scaleMarkY(j)){
				sysPaintPixel(i,j, A_B, A_G,A_R);
			}
		}
	}
	return scale;
}
int scaleMarkX(int x){
		int scale = SCREEN_WIDTH/SCALE_AMOUNT;
		for (int i=0; i<SCALE_AMOUNT+1; i++){
			if(absInt(x-scale*i)<5){
				return 1;
			}
		}
		return 0;
}
int scaleMarkY(int y){
	int scale = SCREEN_HEIGHT/SCALE_AMOUNT;
	for (int i=0; i<SCALE_AMOUNT+1; i++){
		if(absInt(y-scale*i)<5){
			return 1;
		}
	}
	return 0;
}


void plotFunctionFloat(int x_l, int x_r, int y_d, int y_u, float a, float b, float c) {
	sysClear();
	int scale = plotAxis(x_l,x_r,y_d,y_u);
	plotLinearFloat(x_l,x_r,y_d,y_u,a,b,c);
	sysPrintString("Scale = ", A_B,A_G,A_R);
	sysPrintInt(scale,A_B,A_G,A_R);
}
