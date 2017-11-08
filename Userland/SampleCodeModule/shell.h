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


void startShell();
int graph(char input[][MAX_WORD_LENGTH], int words);

#endif
