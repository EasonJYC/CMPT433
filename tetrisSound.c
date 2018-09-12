#include <alsa/asoundlib.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include "audioMixer.h"
#include "tetrisSound.h"
#include "general.h"

#define BGM_FILE_1 "wave-files/part1.wav"
#define BGM_FILE_2 "wave-files/part2.wav"
#define BGM_FILE_3 "wave-files/part3.wav"
#define WOW_FILE "wave-files/wow_2.wav"
// #define

#define BGM_PART_DURATION_ms 12833


#define SAMPLE_RATE   44100
#define NUM_CHANNELS  1
#define SAMPLE_SIZE   (sizeof(short)) 	// bytes per sample

void* tetrisSoundThread(void* arg);
static _Bool tetrisSoundStopping = false;
static pthread_t tetrisSoundThreadId;


void TetrisSound_init(void) {
	tetrisSoundStopping = false;
	pthread_create(&tetrisSoundThreadId, NULL, &tetrisSoundThread, NULL);
}

void TetrisSound_cleanup(void) {
	printf("Stopping tetris sound thread...\n");
	tetrisSoundStopping = true;
	pthread_join(tetrisSoundThreadId, NULL);
	printf("Done stopping soundThread...\n");
}

void TetrisSound_newRecord(void) {
	wavedata_t wowFile;
	AudioMixer_readWaveFileIntoMemory(WOW_FILE, &wowFile);
	AudioMixer_queueSound(&wowFile);
	sleep_msec(1000);
	AudioMixer_freeWaveFileData(&wowFile);
}

void* tetrisSoundThread(void* arg) {
    AudioMixer_init();
    wavedata_t bgmFile1, bgmFile2, bgmFile3;
    AudioMixer_readWaveFileIntoMemory(BGM_FILE_1, &bgmFile1);
    AudioMixer_readWaveFileIntoMemory(BGM_FILE_2, &bgmFile2);
    AudioMixer_readWaveFileIntoMemory(BGM_FILE_3, &bgmFile3);
    int part = 0;
    while (!tetrisSoundStopping)  {
        switch (part) {
            case 0: {
                AudioMixer_queueSound(&bgmFile1);
                break;
            }
            case 1: {
                AudioMixer_queueSound(&bgmFile2);
                break;
            }
            case 2: {
                AudioMixer_queueSound(&bgmFile3);
                break;
            }
            default: break;
        }
        part = (part + 1) % 3;
        sleep_msec(BGM_PART_DURATION_ms);
    }
    AudioMixer_freeWaveFileData(&bgmFile1);
    AudioMixer_freeWaveFileData(&bgmFile2);
    AudioMixer_freeWaveFileData(&bgmFile3);
    AudioMixer_cleanup();
    return NULL;
}
