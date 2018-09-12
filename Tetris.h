#ifndef  _TETRIS_H_
#define  _TETRIS_H_


#define ROW 18
#define COL 13
enum state {
    ON,
    OVER,
    PAUSE
};

void Tetris_init(void);
void Tetris_cleanup(void);

// For display
// int Tetris_getNextBlockType(void);
//
enum state Tetris_getGameState(void);
//
// int Tetris_getCurScore(void);
// int Tetris_getMaxScore(void);
//
// int** Tetris_getGameArea(void);

// For control
void Tetris_moveLeft(void);
void Tetris_moveRight(void);
void Tetris_speedup(void);
void Tetris_rotateBlockDir(void);

void Tetris_setGameState(enum state newState);

void Tetris_refresh(void);
#endif
