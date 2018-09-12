# Makefile for building multi-file application
# by Brian Fraser

PUBDIR = $(HOME)/cmpt433/public/myApps/Tetris
# final executable to build:
TARGET= tetris

CFILES = main.c Tetris.c general.c display_Word.c test_ledMatrix.c joystick_control.c audioMixer.c tetrisSound.c

# Add support for pthread and real-time clock here:
CFLAGS = -Wall -g -std=c99 -D_POSIX_C_SOURCE=200809L -Werror

# You should not need to change any of this:
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB

all: wav clean $(TARGET)
	cp $(TARGET) $(PUBDIR)
	rm $(TARGET)


$(TARGET): $(CFILES)
	$(CC_C) $(CFLAGS) $(CFILES) -lm -o $@ $(LFLAGS) -lpthread -lasound

wav:
	mkdir -p $(PUBDIR)/wave-files/
	cp sounds/* $(PUBDIR)/wave-files/

clean:
	rm -f $(TARGET)

host:
	gcc -Wall -g -std=c99 -D_POSIX_C_SOURCE=200809L -Werror -pthread -lrt $(CFILES) -o x
