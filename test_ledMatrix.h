/* **********************************************************************
 *  File Name:      test_ledMatrix.c
 *  Description:    Mini test program to test out Adafruit's LED Matrix
 *                  Adapted from experimental python code by Simon Monk
 *                  https://learn.adafruit.com/connecting-a-16x32-rgb-led-matrix-panel-to-a-raspberry-pi/experimental-python-code
 *  
 *  Created by:     Janet Mardjuki
 *  Year:           2016
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "general.h"

void exportAndOut(int pinNum);
void ledMatrix_setupPins(void);
void ledMatrix_writeGpioValue(int pinNum, int value);
void ledMatrix_clock(void);
void ledMatrix_latch(void);
void ledMatrix_bitsFromInt(int * arr, int input);
void ledMatrix_setRow(int rowNum);
void ledMatrix_setColourTop(int colour);
void ledMatrix_setColourBottom(int colour);
void ledMatrix_refresh(void);
void ledMatrix_fillRectangle(int x1, int y1, int x2, int y2, int colour);
void ledMatrix_setPixel(int x, int y, int colour);
void ledMatrix_printBoard();