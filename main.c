#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

// Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int NUM_BARS = 100;
const int MAX_VALUE = 100;

void initialize_array(int *array, int n) {
  for (int i = 0; i < n; i++) {
    array[i] = rand() % MAX_VALUE + 1;
  }
}

void draw_bars(SDL_Surface *surface, int *array, int n) {
  int background_color = SDL_MapRGB(surface->format, 36, 36, 36);
  SDL_FillRect(surface, NULL, background_color);

  int bar_width = SCREEN_WIDTH / n;

  for (int i = 0; i < n; i++) {
    int value = array[i];
    int bar_height = (value / (float)MAX_VALUE) * (SCREEN_HEIGHT - 40);

    int x = i * bar_width;
    int y = SCREEN_HEIGHT - bar_height;

    SDL_Rect bar = {x, y, bar_width - 1, bar_height};
    int bar_color = SDL_MapRGB(surface->format, 24, 251, 169);
    SDL_FillRect(surface, &bar, bar_color);
  }
}

int main(int argc, char *args[]) {
  // the window we'll be rendering to
  SDL_Window *window = NULL;

  // the surface contained by the window
  SDL_Surface *screenSurface = NULL;

  srand(time(NULL));
  int array[NUM_BARS];
  initialize_array(array, NUM_BARS);

  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL coult not initialize! SDL Error: %s\n", SDL_GetError());
  } else {

    // create window
    window = SDL_CreateWindow("SDL First Window", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {

      // get window surface
      screenSurface = SDL_GetWindowSurface(window);

      draw_bars(screenSurface, array, NUM_BARS);
      SDL_UpdateWindowSurface(window);

      // hack to get the window to stay up
      SDL_Event e;
      bool quit = false;
      while (quit == false) {
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT)
            quit = true;
        }
      }
    }
  }
  // distroy window
  SDL_DestroyWindow(window);

  // quit SDL subsystems
  SDL_Quit();

  return 0;
}
