#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "block_rotation.h"
#include "Tetris.h"
#include "general.h"
#include "display_Word.h"
#include "joystick_control.h"
#include "tetrisSound.h"

#define DEFAULT_BLOCK_ROTATION 0
#define DEFAULT_START_X 5
#define DEFAULT_START_Y 0

#define MAX_MOVE_DELAY_ms 1000

#define SCORE_ADDED_PER_ELIMINATION 10
#define SCORE_PER_LEVEL 20
#define MAX_LEVEL 9
#define DELAY_REDUCTION_PER_LEVEL_ms 100

// Function declarations
void* tetrisThread(void* arg);
static _Bool tetrisThreadStopping = false;
static pthread_t tetrisThreadId;
static pthread_mutex_t gameAreaMutex = PTHREAD_MUTEX_INITIALIZER;


// Global variables
static int gameArea[ROW][COL] = {};
static int startY = DEFAULT_START_Y, startX = DEFAULT_START_X;
static int type = 0;
static int nextType = 0;
static int block_dir = 0;
enum state cur_state = ON;
static unsigned int score = 0;
static unsigned int maxScore = 0;
static _Bool maxScoreWowPlayed = false;


void loadMaxScore(void);
void initalizeGameArea(void);
_Bool stickBlockInGame(int block[ARRAY_SIZE][ARRAY_SIZE]);
void cleanBlock(int block[ARRAY_SIZE][ARRAY_SIZE]);
void rotateBlock(int block[ARRAY_SIZE][ARRAY_SIZE]);
_Bool moveBlock(int block[ARRAY_SIZE][ARRAY_SIZE], int flag);
_Bool checkGameOver(void);
void recordMaxScore(void);
void checkElimination(void);
void printGameArea();
void gameOver(void);



void* tetrisThread(void* arg) {
    // load max score from file
    loadMaxScore();

    displayScore(score);
    displayMaxScore(maxScore);

    initalizeGameArea();
    srand(time(NULL));

    type = rand() % BLOCK_TYPE;
    nextType = rand() % BLOCK_TYPE;

    displayNextElement(nextType);

    displayStatus();
    displayLevel(score/SCORE_PER_LEVEL);


    while (!tetrisThreadStopping) {
        if (cur_state != ON) {
            sleep_msec(100);
            continue;
        }
        _Bool isFirstStick = stickBlockInGame(blocks[type][block_dir]);
        printGameArea();
        displayGameArea(gameArea);
        if (!isFirstStick) {
            int level = score / SCORE_PER_LEVEL;
            if (level >= MAX_LEVEL) level = MAX_LEVEL;
            sleep_msec(MAX_MOVE_DELAY_ms - level*DELAY_REDUCTION_PER_LEVEL_ms);
        }
        cleanBlock(blocks[type][block_dir]);


        if (!moveBlock(blocks[type][block_dir], DOWN)) {
            stickBlockInGame(blocks[type][block_dir]);
            // printGameArea();
            checkElimination();

            startX = DEFAULT_START_X;
            startY = DEFAULT_START_Y;
            block_dir = 0;
            type = nextType;
            nextType = rand() % BLOCK_TYPE;
            displayNextElement(nextType);
        }
    }
    return NULL;
}

void loadMaxScore(void) {
    FILE *pfile = fopen("./record", "r+");
    if (pfile == NULL) {
        pfile = fopen("./record","w");
    }
    fscanf(pfile,"%u",&maxScore);
    fclose(pfile);
}

void initalizeGameArea(void) {
    printf("\033[2J");

    pthread_mutex_lock(&gameAreaMutex);
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i == 0 || j == 0 || i == ROW-1 || j == COL-1) {
                gameArea[i][j] = -1;
            } else {
                gameArea[i][j] = 0;
            }
        }
    }
    pthread_mutex_unlock(&gameAreaMutex);
}

_Bool stickBlockInGame(int block[ARRAY_SIZE][ARRAY_SIZE]) {
    pthread_mutex_lock(&gameAreaMutex);
    _Bool isFirstStick = false;
    for (int y = 0; y < ARRAY_SIZE; y++) {
        for (int x = 0; x < ARRAY_SIZE; x++) {
            if (block[y][x] != 0 ) {
                if (!gameArea[startY+y][startX+x]) {
                    gameArea[startY+y][startX+x] = block[y][x];
                } else if (gameArea[startY+y][startX+x] == -1) {
                    isFirstStick = true;
                    continue;
                } else {
                    gameOver();
                }
            }
        }
    }
    pthread_mutex_unlock(&gameAreaMutex);

    return isFirstStick;
}

void cleanBlock(int block[ARRAY_SIZE][ARRAY_SIZE]) {
    pthread_mutex_lock(&gameAreaMutex);
    for (int y = 0; y < ARRAY_SIZE; y++) {
        for (int x = 0; x < ARRAY_SIZE; x++) {
            if (block[y][x]) {
                if (gameArea[startY+y][startX+x] != -1)
                    gameArea[startY+y][startX+x] = 0;
            }
        }
    }
    pthread_mutex_unlock(&gameAreaMutex);

}

void rotateBlock(int block[ARRAY_SIZE][ARRAY_SIZE]) {
    for (int y = 0; y < ARRAY_SIZE; y++) {
        for (int x = 0; x < ARRAY_SIZE; x++) {
            if (block[y][x] != 0 && gameArea[startY+y][startX+x] != 0) {
                return;
            }
        }
    }

    // pthread_mutex_lock(&blockMutex);
    block_dir = (block_dir + 1) % NUM_ROTATIONS;
    // pthread_mutex_unlock(&blockMutex);
}

_Bool moveBlock(int block[ARRAY_SIZE][ARRAY_SIZE], int flag){
    int xx = 0, yy = 0;

    switch (flag) {
        case RIGHT : yy = 0; xx = 1;  break;
        case LEFT  : yy = 0; xx = -1; break;
        case DOWN  : yy = 1; xx = 0;  break;
    }

    // pthread_mutex_lock(&gameAreaMutex);
    for (int y = 0; y < ARRAY_SIZE; y++) {
        for (int x = 0; x < ARRAY_SIZE; x++) {
            if (block[y][x] != 0 && gameArea[startY+y+yy][startX+x+xx] != 0) {
                return false;
            }
        }
    }
    // pthread_mutex_unlock(&gameAreaMutex);

    startY += yy;
    startX += xx;

    return true;
}

_Bool checkGameOver(void) {
    for (int i = 0; i < COL; i++) {
        if (gameArea[1][i] != 0) {
            return true;
        }
    }
    return false;
}

void recordMaxScore(void) {
    // Use fopen() to open the file for write access.
    FILE *pfile = fopen("./record", "w");
    if (pfile == NULL) {
          printf("ERROR: Unable to open export file.\n");
          exit(1);
    }
    // Write to data to the file using fprintf():
    int recorded = fprintf(pfile, "%d", maxScore);
    if (recorded <= 0) {
        printf("ERROR WRITING DATA.\n");
        exit(-1);
    }
    // Close the file using fclose():
    fclose(pfile);
}

void checkElimination(void) {
    // check four lines of gameArea
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        int j = 1;
        for (j = 1; j < COL - 1; j++) {
            // if empty slot
            if (gameArea[startY+i][j] == 0) {
                break;
            } else if (gameArea[startY+i][j] == -1) { // check edge
                break;
            }
        }
        // if finished entire loop (no break)
        // elimination happens
        if (j == COL - 1) {
            for (j = 1; j < COL-1; j++){
                gameArea[startY+i][j] = 0;
            }

            // add on score
            score += SCORE_ADDED_PER_ELIMINATION;

            displayLevel(score/SCORE_PER_LEVEL);

            displayScore(score);
            // check if new score beyond maxScore
            if (score > maxScore) {
                maxScore = score;
                displayMaxScore(maxScore);
                if (!maxScoreWowPlayed) {
                    TetrisSound_newRecord();
                    maxScoreWowPlayed = true;
                }
                // save the maxScore
                recordMaxScore();
            }

            // move the rest (upper) down
            for (int x = 1; x < COL-1; x++) {
                for (int y = startY+i; y >= 7; y--) {
                    gameArea[y][x] = gameArea[y-1][x];
                }
            }

            // check the same line again because of the move down
            i++;
        }
    }
}

void printGameArea(void) {
    fprintf(stdout,"\033[1;1H");
    fflush(stdout);

    fprintf(stdout,"\033[2;1H\033[33mNext Block:\033[0m\n");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < ARRAY_SIZE; j++) {
            if (blocks[nextType][DEFAULT_BLOCK_ROTATION][i][j]) {
                fprintf(stdout,"▇▇");
            } else {
                fprintf(stdout,"  ");
            }
        }
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"\033[3;15HScore:\033[32m%u\033[0m",score);
    fprintf(stdout,"\033[4;15HMaxScore:\033[32m%u\033[0m\n",maxScore);


    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (gameArea[i][j] == -1) {
                fprintf(stdout,"[]");
            } else if (gameArea[i][j] != 0) {
                fprintf(stdout,"▇▇");
            } else {
                fprintf(stdout,"▏▏");
            }
        }
        fprintf(stdout,"\n");
    }
}


void gameOver(void) {
    cur_state = OVER;
    displayStatus(cur_state);
    Tetris_cleanup();
}












// public functions
void Tetris_init(void) {
    cur_state = ON;
    score = 0;
    maxScoreWowPlayed = false;
    tetrisThreadStopping = false;
    pthread_create(&tetrisThreadId, NULL, &tetrisThread, NULL);
}
void Tetris_cleanup(void) {
    tetrisThreadStopping = true;
    printf("stopping Tetris thread\n");
    pthread_join(tetrisThreadId, NULL);
    printf("Down stopping Tetris thread\n");
}

int Tetris_getNextBlockType(void) {
    return nextType;
};

enum state Tetris_getGameState(void) {
    return cur_state;
}

int Tetris_getCurScore(void) {
    return score;
}

int Tetris_getMaxScore(void) {
    return maxScore;
}


// For control:
void Tetris_moveLeft(void) {
    cleanBlock(blocks[type][block_dir]);
    moveBlock(blocks[type][block_dir], LEFT);
}
void Tetris_moveRight(void) {
    cleanBlock(blocks[type][block_dir]);

    moveBlock(blocks[type][block_dir], RIGHT);
}
void Tetris_speedup(void) {
    cleanBlock(blocks[type][block_dir]);
    moveBlock(blocks[type][block_dir], DOWN);
}
void Tetris_rotateBlockDir(void) {
    cleanBlock(blocks[type][block_dir]);
    rotateBlock(blocks[type][(block_dir + 1) % NUM_ROTATIONS]);
}

void Tetris_setGameState(enum state newState) {
    cur_state = newState;
}

void Tetris_refresh(void) {
    stickBlockInGame(blocks[type][block_dir]);
    printGameArea();
    displayGameArea(gameArea);
    cleanBlock(blocks[type][block_dir]);
}
