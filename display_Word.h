#ifndef  _DISPLAY_WORD_H_
#define  _DISPLAY_WORD_H_

#include "test_ledMatrix.h"
#include "Tetris.h"
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
void display_S(int x, int y, int colour);
void display_C(int x, int y, int colour);
void display_O(int x, int y, int colour);
void display_R(int x, int y, int colour);
void display_E(int x, int y, int colour);
void init_display();
void display_0(int x, int y, int colour);
void display_1(int x, int y, int colour);
void display_2(int x, int y, int colour);
void display_3(int x, int y, int colour);
void display_4(int x, int y, int colour);
void display_5(int x, int y, int colour);
void display_6(int x, int y, int colour);
void display_7(int x, int y, int colour);
void display_8(int x, int y, int colour);
void display_9(int x, int y, int colour);
void displayNumber(int x, int y, int colour, int number);

void displayScore(int score);
void displayMaxScore(int maxScore);
void displayStatus();
void displayNextElement(int index);
void displayGameArea(int area[ROW][COL]);
void displayLevel(int level);


#endif
