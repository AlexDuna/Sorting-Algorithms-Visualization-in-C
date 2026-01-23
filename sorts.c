#include "sorts.h"
#include "visual.h"

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdlib.h>

const int NUM_BARS = 50;

void initialize_array(int *array, int n) {
  for (int i = 0; i < n; i++) {
    array[i] = rand() % MAX_VALUE + 1;
  }
}

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void bubble_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array,
                        int n, TTF_Font *font, int choice) {
  int i, j;
  bool swapped;
  int quit = false;
  for (i = 0; i < n - 1 && !quit; i++) {
    swapped = false;
    for (j = 0; j < n - i - 1 && !quit; j++) {
      if (array[j] > array[j + 1]) {
        swap(&array[j], &array[j + 1]);
        swapped = true;
      }
      SDL_Event e;
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
          quit = true;
      }
      render_frame(window, surface, array, n, j, j + 1, font, choice);
      SDL_Delay(10);
    }
    if (!swapped)
      break;
  }
  if (quit)
    return;
}

int partition(SDL_Window *window, SDL_Surface *surface, int *array, int low,
              int high, int n, bool *quit, TTF_Font *font, int choice) {
  if (*quit)
    return low;

  int pivot = array[high];
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (array[j] < pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        *quit = true;
    }
    render_frame(window, surface, array, n, j, high, font, choice);
    SDL_Delay(10);
  }

  swap(&array[i + 1], &array[high]);
  int pivotIndex = i + 1;
  render_frame(window, surface, array, n, pivotIndex, -1, font, choice);
  SDL_Delay(10);

  return pivotIndex;
}

static void quick_sort_rec(SDL_Window *window, SDL_Surface *surface, int *array,
                           int low, int high, int n, bool *quit, TTF_Font *font,
                           int choice) {
  if (*quit || low >= high)
    return;

  int pivotIndex =
      partition(window, surface, array, low, high, n, quit, font, choice);
  if (*quit)
    return;

  quick_sort_rec(window, surface, array, low, pivotIndex - 1, n, quit, font,
                 choice);
  quick_sort_rec(window, surface, array, pivotIndex + 1, high, n, quit, font,
                 choice);
}

void quick_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array,
                       int n, TTF_Font *font, int choice) {
  bool quit = false;
  quick_sort_rec(window, surface, array, 0, n - 1, n, &quit, font, choice);
}
