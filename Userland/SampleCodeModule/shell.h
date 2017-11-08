#ifndef SHELL_H
#define SHELL_H

#define MAX_WORD_LENGTH 124
#define MAX_WORDS 32
#define CR 255
#define CG 255
#define CB 0
#define DR 0
#define DG 255
#define DB 255

#define helpIns "echo arguments ...          - Prints arguments\n\
				displayTime                 - Prints date and time to screen\n\
				setTimeZone timezone        - Set timezone \n\
				setFontColor color          - Changes font color\n\
				clear                       - Clears screen\n\
				calculate operation op1 op2 - Performs specified calculation \n\
				help (optional)command      - Displays help instructions for command\n\
				exit                        - Exits the shell\n"
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
							Arg 2 and 3: Operands, real numbers.\n"
#define EXIT_INS "Quits the shell.\n"
void startShell();
int graph(char input[][MAX_WORD_LENGTH], int words);
int callFunction(char * buffer);
int echo(char input[][MAX_WORD_LENGTH], int words);
int clear(int words);
int overflowGenerator(int n);
int calculateVerifications(int words, char* input2, char* input3);
int calculate(char* func, int param1, int param2);

#endif
