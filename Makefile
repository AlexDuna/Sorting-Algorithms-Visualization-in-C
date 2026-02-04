CC = gcc
CFLAGS = -Wall -Wextra -std=c17
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LIBS = $(shell sdl2-config --libs) -lSDL2_ttf

SRC_DIR = src
HEAD_DIR = headers
BUILD_DIR = build

#files for SDL program
VISUAL_SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/visual.c $(SRC_DIR)/sorts.c
VISUAL_OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/visual.o $(BUILD_DIR)/sorts.o

#files for tests program
TEST_SRCS = $(SRC_DIR)/tests.c $(SRC_DIR)/sorts_pure.c
TEST_OBJS = $(BUILD_DIR)/tests.o $(BUILD_DIR)/sorts_pure.o

.PHONY: all clean

all: $(BUILD_DIR) sorting_visualizer tests

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

sorting_visualizer: $(VISUAL_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(SDL_LIBS)

tests:  $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -I$(HEAD_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) sorting_visualizer tests
