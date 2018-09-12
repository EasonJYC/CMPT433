// module to handle zen-cape joystick inputs

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "joystick_control.h"
// #include "drum_modes.h"
#include "audioMixer.h"
#include "display_Word.h"
#include "test_ledMatrix.h"
#include "tetrisSound.h"


#include "Tetris.h"
#include "general.h"

#define EXPORT_GPIO "/sys/class/gpio/export"
#define JOY_IN_GPIO 61
#define JOY_UP_GPIO 60
#define JOY_RIGHT_GPIO 31
#define JOY_DOWN_GPIO 49
#define JOY_LEFT_GPIO 115
#define MUSIC_OFF_GPIO 51

#define Joystick_IN_Value "/sys/class/gpio/gpio61/value"
#define Joystick_UP_Value "/sys/class/gpio/gpio60/value"
#define Joystick_RIGHT_Value "/sys/class/gpio/gpio31/value"
#define Joystick_DOWN_Value "/sys/class/gpio/gpio49/value"
#define Joystick_LEFT_Value "/sys/class/gpio/gpio115/value"
#define BUTTON_SHUTDOWN_MUSIC "/sys/class/gpio/gpio51/value"

#define MAX_LENGTH 1024
#define ASLII_FOR_0 48
#define FIRST_BUFF_INDEX 0

#define DIRECTION_SELECTED 1
#define NANOSECOND_FOR_10MS 10000000
#define DELAY_BETWEEN_VOL_BPM_CHANGES_IN_NANOSEC 300000000

#define BGM_FILE_1 "wave-files/part1.wav"
#define BGM_FILE_2 "wave-files/part2.wav"
#define BGM_FILE_3 "wave-files/part3.wav"

#define BGM_PART_DURATION_ms 12833


void* joystickControlThread(void* arg);
static _Bool joystickControlStopping = false;
static pthread_t joystickControlThreadId;

void JoystickControl_init(void) {
    pthread_create(&joystickControlThreadId, NULL, &joystickControlThread, NULL);
}

void JoystickControl_cleanup(void) {
    printf("Stopping joystick control thread...\n");

    joystickControlStopping = true;

    pthread_join(joystickControlThreadId, NULL);
    printf("Done stopping joystick control...\n");
}

void exportGpio(int gpio) {
    // Use fopen() to open the file for write access.
    FILE *pfile = fopen(EXPORT_GPIO, "w");
    if (pfile == NULL) {
          printf("ERROR: Unable to open export file.\n");
          exit(1);
    }
    // Write to data to the file using fprintf():
    int exported = fprintf(pfile, "%d", gpio);
    if (exported <= 0) {
        printf("ERROR WRITING DATA.\n");
        exit(-1);
    }
    // Close the file using fclose():
    fclose(pfile);
}

void loadJoystickGpios(void) {
    exportGpio(JOY_IN_GPIO);
    exportGpio(JOY_UP_GPIO);
    exportGpio(JOY_RIGHT_GPIO);
    exportGpio(JOY_DOWN_GPIO);
    exportGpio(JOY_LEFT_GPIO);
    exportGpio(MUSIC_OFF_GPIO);
}

int readFromFile(char *fileName) {
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		printf("ERROR: Unable to open file (%s) for read\n", fileName);
		exit(-1);
	}
	// Read string (line)
	const int max_length = MAX_LENGTH;
	char buff[max_length];
	fgets(buff, max_length, file);

	// Close
	fclose(file);
	int result = buff[FIRST_BUFF_INDEX] - ASLII_FOR_0;
	return result;
}

enum direction checkJoystickDirection(void) {
	enum direction dir;
	dir = NO_DIRECTION;

	if (readFromFile(Joystick_UP_Value) == DIRECTION_SELECTED) {
		dir = UP;
	} else if (readFromFile(Joystick_RIGHT_Value) == DIRECTION_SELECTED){
		dir = RIGHT;
	} else if (readFromFile(Joystick_DOWN_Value) == DIRECTION_SELECTED) {
		dir = DOWN;
	} else if (readFromFile(Joystick_LEFT_Value) == DIRECTION_SELECTED) {
		dir = LEFT;
	} else if (readFromFile(Joystick_IN_Value) == DIRECTION_SELECTED) {
        dir = PRESS_IN;
    }
	return dir;
}

void* joystickControlThread(void* arg) {
    loadJoystickGpios();
    // AudioMixer_init();

    // wavedata_t bgmFile1, bgmFile2, bgmFile3;
    // AudioMixer_readWaveFileIntoMemory(BGM_FILE_1, &bgmFile1);
    // AudioMixer_readWaveFileIntoMemory(BGM_FILE_2, &bgmFile2);
    // AudioMixer_readWaveFileIntoMemory(BGM_FILE_3, &bgmFile3);
    // int part = 1;
    //
    // time_t systime = time(0);
    // AudioMixer_queueSound(&bgmFile1);
    while (!joystickControlStopping) {
        // time_t tmp = time(0);
        // if (tmp >= (systime + 13)) {
        //     switch (part) {
        //         case 0: AudioMixer_queueSound(&bgmFile1); break;
        //         case 1: AudioMixer_queueSound(&bgmFile2); break;
        //         case 2: AudioMixer_queueSound(&bgmFile3); break;
        //         default: break;
        //     }
        //     systime = tmp;
        //     part = (part + 1) % 3;
        // }
        enum direction dir = checkJoystickDirection();
        enum state cstate = Tetris_getGameState();
        if (cstate == PAUSE) {
            if (dir == PRESS_IN) {
                Tetris_setGameState(ON);
                displayStatus();
                while (checkJoystickDirection() != NO_DIRECTION) {
                    sleep_msec(100);
                };
            } else {
                sleep_msec(50);
                continue;
            }
        } else if (cstate == ON) {
            if (dir == PRESS_IN) {
                Tetris_setGameState(PAUSE);
                displayStatus();
                while (checkJoystickDirection() != NO_DIRECTION){
                    sleep_msec(100);
                };
            } else if (dir == UP) {
                Tetris_rotateBlockDir();
                Tetris_refresh();
                while (checkJoystickDirection() != NO_DIRECTION) {
                    sleep_msec(100);
                };
            } else if (dir == LEFT) {
                Tetris_moveLeft();
                Tetris_refresh();
                sleep_msec(100);
            } else if (dir == RIGHT) {
                Tetris_moveRight();
                Tetris_refresh();
                sleep_msec(100);
            } else if (dir == DOWN) {
                Tetris_speedup();
                Tetris_refresh();
                sleep_msec(100);
            } else {
                sleep_msec(100);
                continue;
            }
        } else if (cstate == OVER) {
            if (dir == PRESS_IN) {
                Tetris_init();
            } else {
                sleep_msec(100);
                continue;
            }
        } else if (readFromFile(BUTTON_SHUTDOWN_MUSIC) == 0) {

        }
    }

    // AudioMixer_freeWaveFileData(&bgmFile1);
    // AudioMixer_freeWaveFileData(&bgmFile2);
    // AudioMixer_freeWaveFileData(&bgmFile3);
    // AudioMixer_cleanup();
    return NULL;
}
