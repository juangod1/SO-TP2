#ifndef SHELL_H
#define SHELL_H

#include "stdLib.h"

#define MAX_PROCESSES 256
#define MAX_PROCESS_NAME_LENGTH 20
#define MAX_WORD_LENGTH 124
#define MAX_WORDS 32
#define MESSAGE_BOX_SIZE 100
#define CR 255
#define CG 255
#define CB 0
#define DR 0
#define DG 255
#define DB 255
#define NULL ((void*)0)
#define helpIns "\
				echo arguments ...          - Prints arguments\n\
				displayTime                 - Prints date and time to screen\n\
				setTimeZone timezone        - Set timezone \n\
				setFontColor color          - Changes font color\n\
				clear                       - Clears screen\n\
				calculate operation op1 op2 - Performs specified calculation on integer numbers\n\
				plot coef_a coef_b coef_c   - Plots a Quadratic function for the given values\n\
				help (optional)command      - Displays help instructions for command\n\
				exit                        - Exits the shell\n\
				opcode                      - Tests opcode exception\n\
				test module                 - Executes Kernel test suite\n\
				foreground process_ID       - Sends process to foreground\n\
				prodConsDemo size           - Executes a demo of the Producer Consumer Problem\n\
ps                          - Lists running processes.\n\
testBackgroundProcess       - Creates a test background process, use foreground command to see.\n"


#define ECHO_INS "Recieves a variable amount of arguments, prints them in the screen (max 32).\n"
#define DISPLAY_TIME_INS "Recieves no arguments. Prints current date and time.\n\
							Default timezone is UTC-3.\n"
#define SET_TIME_ZONE_INS "Recieves an integer between -11 and 12.\n\
							The parameter is set as the computer timezone in\n\
							future time printings.\n"
#define SET_FONT_COLOR_INS "Recieves a string (red, blue, green or default). \n\
							The fontcolor for future user printings is changed.\n"
#define CLEAR_INS "Removes information from screen, starts over.\n"
#define CALCULATE_INS "Recieves 3 arguments.\n\
							Arg 1: Operation (add, substract, multiply, divide).\n\
							Arg 2 and 3: Operands, integer numbers.\n"
#define PLOT_INS "Recieves 3 arguments.\n\
							The arguments correspond to the rational coefficients for\n\
							a quadratic function\n\
							Once inside navigate with the arrow keys and use +/- to zoom in/out\n"
#define EXIT_INS "Quits the shell.\n"
#define OPCODE_INS "Creates opcode exception for testing purposes.\n"
#define TEST_INS "Executes Kenel Testing Suite, the modules are: scheduler, ipc, all\n"
#define FOREGROUND_INS "Sends requested process to foreground.\n"
#define BACKGROUND_INS "Receives one argument, runs program argument in background. Shell programs can't be run in background. "
#define PRODCONS_INS "Parameter 'size' determines the size of the testing buffer\n\
											Once inside consumer and producer processes can be instantiated\n\
											with the '1' and '2' keys"

void startShell();
int graph(char input[][MAX_WORD_LENGTH], int words);
int callFunction(char * buffer, int backgroundFlag);
int echo(char input[][MAX_WORD_LENGTH], int words);
int clear(int words);
int overflowGenerator(int n);
int calculateVerifications(int words, char* input1, char* input2, char* input3);
int calculate(char* func, int param1, int param2);
extern void opcodeGenerator();
pid_t getForegroundPID();
void DEBUGPrintInt();
void DEBUGPrintString();
void wipeBuffer(char * buff, size_t size);
void listProcesses();

#endif
