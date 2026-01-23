#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include "sorts.h"
#include "visual.h"

int main(int argc, char *args[]) {
  srand(time(NULL));
  int array[NUM_BARS];
  initialize_array(array, NUM_BARS);

  int choice;
  printf("Visualize algorithm:\n");
  printf("#1 Bubble Sort\n");
  printf("#2 Quick Sort\n");
  printf("Choose the algorithm: ");
  scanf("%d", &choice);

  // the window we'll be rendering to
  SDL_Window *window = NULL;

  // the surface contained by the window
  SDL_Surface *screenSurface = NULL;

  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL coult not initialize! SDL Error: %s\n", SDL_GetError());
    return 1;
  }

  if (TTF_Init() == -1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    SDL_Quit();
    return 1;
  }

  // create window
  window = SDL_CreateWindow("SDL First Window", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // get window surface
  screenSurface = SDL_GetWindowSurface(window);

  TTF_Font *font =
      TTF_OpenFont("fonts/PixelLetters/Pixellettersfull-BnJ5.ttf", 20);
  if (!font) {
    printf("Failed to load font: %s\n", TTF_GetError());
  }

  SDL_Color white = (SDL_Color){255, 255, 255, 255};
  draw_bars(screenSurface, array, NUM_BARS, -1, -1);
  render_algorithm_info(screenSurface, font, choice, white);
  SDL_UpdateWindowSurface(window);
  SDL_Delay(300);

  switch (choice) {
  case 1:
    bubble_sort_visual(window, screenSurface, array, NUM_BARS, font, choice);
    break;
  case 2:
    quick_sort_visual(window, screenSurface, array, NUM_BARS, font, choice);
    break;
  default:
    printf("The algorithm that you chose doesn't exist in our menu.");
    return 1;
  }

  draw_bars(screenSurface, array, NUM_BARS, -1, -1);
  SDL_UpdateWindowSurface(window);

  if (font) {
    TTF_CloseFont(font);
  }

  // hack to get the window to stay up
  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
    }
  }
  SDL_Delay(10);

  // distroy window
  SDL_DestroyWindow(window);

  TTF_Quit();

  // quit SDL subsystems
  SDL_Quit();

  return 0;
}
