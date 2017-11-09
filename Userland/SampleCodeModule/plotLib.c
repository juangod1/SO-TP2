#include "plotLib.h"
#include "mathLib.h"
#include "stdLib.h"
#include <stdint.h>
#include "shell.h"


int graphMain(float a, float b, float c){
	float x_r=DEFAULT_PLOT;
	float x_l=-DEFAULT_PLOT;
	float y_d=x_l;
	float y_u=x_r;
	float x_offset=0,y_offset=0, ready_to_exit = 0,draw=1;
	float factor=1;
	char ch = 0;

	while (!ready_to_exit) {
		sysGetChar(&ch);
		if (ch == '\n') {
			sysClear();
			sysPrintString("Exited plot Successfully\n", CB, CG, CR);

			ready_to_exit = 1;
		}
		if (ch == '+') {
			factor/=FACTOR;
			draw=1;
		}
		if (ch == '-') {
			factor*=FACTOR;
			draw=1;
		}
		if (ch == 15) { //UPARROW
			y_offset+=(5*factor);
			draw=1;
		}
		if (ch == 14) { //DOWNARROW
			y_offset-=(5*factor);
			draw=1;
		}
		if (ch == 13) { //RIGHTARROW
			x_offset-=(5*factor);
			draw=1;
		}
		if (ch == 12) { //LEFTARROW
			x_offset+=(5*factor);
			draw=1;
		}
		if(draw){
			draw=0;
			plotWrapper((x_l*factor)+x_offset,(x_r*factor)+x_offset,(y_d*factor)+y_offset,(y_u*factor)+y_offset,a, b, c);
		}
	}

	return 0;
}

void plotFunction(float x_left_boundary, float x_right_boundary,
	float y_down_boundary, float y_up_boundary, float a, float b, float c) {
	float x_val, y_val;
	float diff;
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
float plotAxis(float x_l, float x_r, float y_d, float y_u){
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
			if(absInt(x-scale*i)<1){
				return 1;
			}
		}
		return 0;
}
int scaleMarkY(int y){
	int scale = SCREEN_HEIGHT/SCALE_AMOUNT;
	for (int i=0; i<SCALE_AMOUNT+1; i++){
		if(absInt(y-scale*i)<1){
			return 1;
		}
	}
	return 0;
}


void plotWrapper(int x_l, int x_r, int y_d, int y_u, float a, float b, float c) {
	sysClear();
	float scale = plotAxis(x_l,x_r,y_d,y_u);
	plotFunction(x_l,x_r,y_d,y_u,a,b,c);
	sysPrintString("Scale = ", A_B,A_G,A_R);
	sysPrintFloat(scale,A_B,A_G,A_R);
}
