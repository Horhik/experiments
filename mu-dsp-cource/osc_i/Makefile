# Define the compiler
CC = gcc

# Define the compiler flags
CFLAGS = -Wall -I.

SRC = ./src
OBJ = ./obj
BIN = ./bin

# Objects location

# Define the linker flags
LDFLAGS = -ljack -lm

# Define the target executable
TARGET = sine

SINE_SRCS = $(SRC)/osc.c $(SRC)/sine.c
SINE_OBJS = $(SRCS:.c=.o)




# Default target to build the executable
all: $(TARGET)

# Rule to build the executable
sine: $(SINE_SRCS)
	$(CC) $(OBJS_SINE) -o $(BIN)/sine $(LDFLAGS)




graphics: display_freq.c
	$(CC) display_freq.c -o $(BIN)/display_freq $(LDFLAGS) -lraylib


phasor: phasor.c
	$(CC) phasor.c -o $(BIN)/phasor $(LDFLAGS)


run_sine: all
	$(BIN)/phasor &
	$(BIN)/display_freq &
	$(BIN)/sine &



# Rule to build object files for sine
osc.o: $(SRC)/osc.c $(SRC)/osc_i.h
	$(CC) $(CFLAGS) -c $(SRC)/osc.c -o $(OBJ)/osc.o

sine.o: $(SRC)/sine.c $(SRC)/osc_i.h
	$(CC) $(CFLAGS) -c $(SRC)/sine.c -o $(OBJ)/sine.o
