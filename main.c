#include "test_ledMatrix.h"
#include "display_Word.h"
#include "joystick_control.h"
#include "tetrisSound.h"

int main() {
    ledMatrix_setupPins();
    init_display();

    TetrisSound_init();

    Tetris_init();
    JoystickControl_init();

    while (1) {
        ledMatrix_refresh();
    }

    // system("stty icanon");
    // system("stty echo");
    // fprintf(stdout,"\033[?25h");
    return 0;
}
