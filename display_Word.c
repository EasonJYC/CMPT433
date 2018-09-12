#include "display_Word.h"
#include "Tetris.h"
void display_S(int x, int y, int colour)
{
    ledMatrix_setPixel(x,y,colour);
    ledMatrix_setPixel(x,y+1,colour);
    ledMatrix_setPixel(x,y+2,colour);
    ledMatrix_setPixel(x+1,y,colour);
    ledMatrix_setPixel(x+2,y,colour);
    ledMatrix_setPixel(x+2,y+1,colour);
    ledMatrix_setPixel(x+2,y+2,colour);
    ledMatrix_setPixel(x+3,y+2,colour);
    ledMatrix_setPixel(x+4,y+2,colour);
    ledMatrix_setPixel(x+4,y+1,colour);
    ledMatrix_setPixel(x+4,y,colour);
}

void display_C(int x, int y, int colour)
{
    ledMatrix_setPixel(x,y,colour);
    ledMatrix_setPixel(x,y+1,colour);
    ledMatrix_setPixel(x,y+2,colour);
    ledMatrix_setPixel(x+1,y,colour);
    ledMatrix_setPixel(x+2,y,colour);
    ledMatrix_setPixel(x+3,y,colour);
    ledMatrix_setPixel(x+4,y,colour);
    ledMatrix_setPixel(x+4,y+1,colour);
    ledMatrix_setPixel(x+4,y+2,colour);
}

void display_O(int x, int y, int colour)
{
    for(int i = 0; i < 5; i++)
    {
        ledMatrix_setPixel(x+i,y,colour);
        ledMatrix_setPixel(x+i,y+2,colour);
    }
    ledMatrix_setPixel(x,y+1,colour);
    ledMatrix_setPixel(x+4,y+1,colour);
}

void display_R(int x, int y, int colour)
{
    for(int j = 0; j < 5; j++)
    {
        ledMatrix_setPixel(x+j,y,colour);
    }
    ledMatrix_setPixel(x,y+1,colour);
    ledMatrix_setPixel(x,y+2,colour);
    ledMatrix_setPixel(x+1,y+2,colour);
    ledMatrix_setPixel(x+2,y+2,colour);
    ledMatrix_setPixel(x+2,y+1,colour);
    ledMatrix_setPixel(x+3,y+1,colour);
    ledMatrix_setPixel(x+4,y+2,colour);
}

void display_E(int x, int y, int colour)
{
    for(int i = 0; i < 3; i++)
    {
        ledMatrix_setPixel(x,y+i,colour);
        ledMatrix_setPixel(x+2,y+i,colour);
        ledMatrix_setPixel(x+4,y+i,colour);
    }
    ledMatrix_setPixel(x+1,y,colour);
    ledMatrix_setPixel(x+3,y,colour);
}

void display_1(int x, int y, int colour)
{
    for(int i = 0; i < 5; i++)
    {
        ledMatrix_setPixel(x+i,y+2,colour);
    }
}

void display_2(int x, int y, int colour)
{
    for(int i = 0; i < 3; i++)
    {
        ledMatrix_setPixel(x,y+i,colour);
        ledMatrix_setPixel(x+2,y+i,colour);
        ledMatrix_setPixel(x+4,y+i,colour);
    }
    ledMatrix_setPixel(x+1,y+2,colour);
    ledMatrix_setPixel(x+3,y,colour);
}

void display_3(int x, int y, int colour)
{
    for(int i = 0; i < 3; i++)
    {
        ledMatrix_setPixel(x,y+i,colour);
        ledMatrix_setPixel(x+2,y+i,colour);
        ledMatrix_setPixel(x+4,y+i,colour);
    }
    ledMatrix_setPixel(x+1,y+2,colour);
    ledMatrix_setPixel(x+3,y+2,colour);
}

void display_4(int x, int y, int colour)
{
    ledMatrix_setPixel(x,y,colour);
    ledMatrix_setPixel(x+1,y,colour);
    ledMatrix_setPixel(x+2,y,colour);
    ledMatrix_setPixel(x+2,y+1,colour);
    for(int i = 0; i < 5; i++)
    {
        ledMatrix_setPixel(x+i,y+2,colour);
    }
}

void display_5(int x, int y, int colour)
{
    ledMatrix_setPixel(x,y,colour);
    ledMatrix_setPixel(x,y+1,colour);
    ledMatrix_setPixel(x,y+2,colour);
    ledMatrix_setPixel(x+1,y,colour);
    ledMatrix_setPixel(x+2,y,colour);
    ledMatrix_setPixel(x+2,y+1,colour);
    ledMatrix_setPixel(x+2,y+2,colour);
    ledMatrix_setPixel(x+3,y+2,colour);
    ledMatrix_setPixel(x+4,y+2,colour);
    ledMatrix_setPixel(x+4,y+1,colour);
    ledMatrix_setPixel(x+4,y,colour);
}

void display_6(int x, int y, int colour)
{
    for(int i = 0; i < 3; i++)
    {
        ledMatrix_setPixel(x,y+i,colour);
        ledMatrix_setPixel(x+2,y+i,colour);
        ledMatrix_setPixel(x+4,y+i,colour);
    }
    ledMatrix_setPixel(x+1,y,colour);
    ledMatrix_setPixel(x+3,y,colour);
    ledMatrix_setPixel(x+3,y+2,colour);
}

void display_7(int x, int y, int colour)
{
    for(int i = 0; i < 5; i++)
    {
        ledMatrix_setPixel(x+i,y+2,colour);
    }
    ledMatrix_setPixel(x,y,colour);
    ledMatrix_setPixel(x,y+1,colour);
}

void display_8(int x, int y, int colour)
{
    for(int i = 0; i < 3; i++)
    {
        ledMatrix_setPixel(x,y+i,colour);
        ledMatrix_setPixel(x+2,y+i,colour);
        ledMatrix_setPixel(x+4,y+i,colour);
    }
    ledMatrix_setPixel(x+1,y,colour);
    ledMatrix_setPixel(x+3,y,colour);
    ledMatrix_setPixel(x+1,y+2,colour);
    ledMatrix_setPixel(x+3,y+2,colour);
}

void display_9(int x, int y, int colour)
{
    for(int i = 0; i < 3; i++)
    {
        ledMatrix_setPixel(x,y+i,colour);
        ledMatrix_setPixel(x+2,y+i,colour);
        ledMatrix_setPixel(x+4,y+i,colour);
    }
    ledMatrix_setPixel(x+1,y,colour);
    ledMatrix_setPixel(x+1,y+2,colour);
    ledMatrix_setPixel(x+3,y+2,colour);
}

void display_0(int x, int y, int colour)
{
    for(int i = 0; i < 5; i++)
    {
        ledMatrix_setPixel(x+i,y,colour);
        ledMatrix_setPixel(x+i,y+2,colour);
    }
    ledMatrix_setPixel(x,y+1,colour);
    ledMatrix_setPixel(x+4,y+1,colour);
}




//display word "score"
void init_display()
{
    // for(int i = 0; i < 32; i++)
    // {
    //     ledMatrix_setPixel(5,y+i,20);
    // }

    // initial the frame
    for(int i = 0; i < 16; i++)
    {
        ledMatrix_setPixel(i,4,20);
        ledMatrix_setPixel(i,16,20);
    }

    for(int j = 17; j < 32; j++)
    {
        ledMatrix_setPixel(6,j,30);
        ledMatrix_setPixel(9,j,30);
    }
    // displayNumber(11,17,50,max);
}

//display number: 0000 to 9999
//make sure there are 12 bit available space
void displayNumber(int x, int y, int colour, int number)
{
    if((number < 0) || (number > 999))
    {
        printf("Number out of range! should be in 000 to 999\n\n");
        return;
    }
    //clean the old Number
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            ledMatrix_setPixel(x+i, y+j, 0);
        }
    }
    int hundred = number / 100;
    int decent = (number - hundred * 100)/10;
    int digit = number - hundred * 100 - decent * 10;

    // for (int i = 0; i < 8; i+=4) {
    //     display_8(x, y+i, 0);
    // }

    if(hundred == 0){}
    else if(hundred == 1){display_1(x,y,colour);}
    else if(hundred == 2){display_2(x,y,colour);}
    else if(hundred == 3){display_3(x,y,colour);}
    else if(hundred == 4){display_4(x,y,colour);}
    else if(hundred == 5){display_5(x,y,colour);}
    else if(hundred == 6){display_6(x,y,colour);}
    else if(hundred == 7){display_7(x,y,colour);}
    else if(hundred == 8){display_8(x,y,colour);}
    else if(hundred == 9){display_9(x,y,colour);}

    if(decent == 0 && hundred == 0){}
    else if (hundred != 0 && decent == 0) {display_0(x,y+4,colour);}
    else if(decent == 1){display_1(x,y+4,colour);}
    else if(decent == 2){display_2(x,y+4,colour);}
    else if(decent == 3){display_3(x,y+4,colour);}
    else if(decent == 4){display_4(x,y+4,colour);}
    else if(decent == 5){display_5(x,y+4,colour);}
    else if(decent == 6){display_6(x,y+4,colour);}
    else if(decent == 7){display_7(x,y+4,colour);}
    else if(decent == 8){display_8(x,y+4,colour);}
    else if(decent == 9){display_9(x,y+4,colour);}

    if(digit == 0){display_0(x,y+8,colour);}
    else if(digit == 1){display_1(x,y+8,colour);}
    else if(digit == 2){display_2(x,y+8,colour);}
    else if(digit == 3){display_3(x,y+8,colour);}
    else if(digit == 4){display_4(x,y+8,colour);}
    else if(digit == 5){display_5(x,y+8,colour);}
    else if(digit == 6){display_6(x,y+8,colour);}
    else if(digit == 7){display_7(x,y+8,colour);}
    else if(digit == 8){display_8(x,y+8,colour);}
    else if(digit == 9){display_9(x,y+8,colour);}
}

void displayScore(int score) {
    displayNumber(0, 20, 255, score);
}
void displayMaxScore(int maxScore) {
    displayNumber(11, 20, 202, maxScore);
}

void displayStatus(int index)
{
    //clean the old status
    for(int i = 11; i <= 15; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ledMatrix_setPixel(i,j,0);
        }
    }
    enum state status = Tetris_getGameState();
    //running is 0. OVER is 1. PAUSE is 2
    if(status == 0)
    {
        ledMatrix_setPixel(11,0,2);
        ledMatrix_setPixel(12,0,2);
        ledMatrix_setPixel(13,0,2);
        ledMatrix_setPixel(14,0,2);
        ledMatrix_setPixel(15,0,2);
        ledMatrix_setPixel(12,1,2);
        ledMatrix_setPixel(13,1,2);
        ledMatrix_setPixel(14,1,2);
        ledMatrix_setPixel(13,2,2);
        return;
    }
    if(status == 2)
    {
        for(int i = 11; i <= 15; i++)
        {
            ledMatrix_setPixel(i,0,1);
            ledMatrix_setPixel(i,2,1);
        }
        return;
    }
    if(status == 1)
    {
        for(int i = 12; i < 16; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                ledMatrix_setPixel(i,j,1);
            }
        }
        return;
    }
}


//display next element on the top-left 4*4 space
void displayNextElement(int index)
{
    //clear the old one
    if(index < 0 || index > 7)
    {
        printf("invalid element index!\n");
        return;
    }

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ledMatrix_setPixel(i,j,0);
        }
    }
    int colour = 255;

    //type : ::
    if(index == 0)
    {
        ledMatrix_setPixel(0,0,colour);
        ledMatrix_setPixel(1,0,colour);
        ledMatrix_setPixel(0,1,colour);
        ledMatrix_setPixel(1,1,colour);
        return;
    }
    // type: ....
    if(index == 1)
    {
        ledMatrix_setPixel(0,0,colour);
        ledMatrix_setPixel(0,1,colour);
        ledMatrix_setPixel(0,2,colour);
        ledMatrix_setPixel(0,3,colour);
        return;
    }

    //type: .
    //      ...
    if(index == 2)
    {
        ledMatrix_setPixel(0,0,colour);
        ledMatrix_setPixel(1,0,colour);
        ledMatrix_setPixel(1,1,colour);
        ledMatrix_setPixel(1,2,colour);
        return;
    }
    //type: .
    //    ...

    if(index == 3)
    {
        ledMatrix_setPixel(0,2,colour);
        ledMatrix_setPixel(1,0,colour);
        ledMatrix_setPixel(1,1,colour);
        ledMatrix_setPixel(1,2,colour);
        return;
    }

    //type: .
    //     ...
    if(index == 4)
    {
        ledMatrix_setPixel(1,0,colour);
        ledMatrix_setPixel(1,1,colour);
        ledMatrix_setPixel(1,2,colour);
        ledMatrix_setPixel(0,1,colour);
    }

    //type: ..
    //       ..
    if(index == 5)
    {
        ledMatrix_setPixel(0,0,colour);
        ledMatrix_setPixel(0,1,colour);
        ledMatrix_setPixel(1,1,colour);
        ledMatrix_setPixel(1,2,colour);
    }

    //type: ..
    //     ..
    if(index == 6)
    {
        ledMatrix_setPixel(0,1,colour);
        ledMatrix_setPixel(0,2,colour);
        ledMatrix_setPixel(1,0,colour);
        ledMatrix_setPixel(1,1,colour);
    }
}

//make sure the area is 18*13
void displayGameArea(int area[ROW][COL])
{
    //clear the old gameArea on screen[][]
    for(int i = 1; i < ROW -1; i++)
    {
        for(int j = 1; j < COL -1; j++)
        {
            ledMatrix_setPixel(i-1, j+4, 0);
        }
    }
    for(int i = 1; i < ROW -1; i++)
    {
        for(int j = 1; j < COL -1; j++)
        {
            if(area[i][j] != 0)
            {
                ledMatrix_setPixel(i-1, j+4, 255);
            }
        }
    }
}


void displayLevel(int level)
{
  //clean the old one
  for(int i = 4; i < 9; i++)
  {
    for(int j = 0; j< 3; j++)
    {
      ledMatrix_setPixel(i,j,0);
    }
  }

  if(level == 0){
    display_0(4,0,110);
    return;
  }
  if(level == 1){
    display_1(4,0,110);
    return;
  }
  if(level == 2){
    display_2(4,0,110);
    return;
  }
  if(level == 3){
    display_3(4,0,110);
    return;
  }
  if(level == 4){
    display_4(4,0,110);
    return;
  }
  if(level == 5){
    display_5(4,0,110);
    return;
  }
  if(level == 6){
    display_6(4,0,110);
    return;
  }
  if(level == 7){
    display_7(4,0,110);
    return;
  }
  if(level == 8){
    display_8(4,0,110);
    return;
  }
  if(level == 9){
    display_9(4,0,110);
    return;
  }
}
