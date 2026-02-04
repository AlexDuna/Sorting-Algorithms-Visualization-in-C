#include "sorts.h"
#include "visual.h"

#include <SDL2/SDL_events.h>
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
      SDL_Delay(20);
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
    SDL_Delay(20);
  }

  swap(&array[i + 1], &array[high]);
  int pivotIndex = i + 1;
  render_frame(window, surface, array, n, pivotIndex, -1, font, choice);
  SDL_Delay(20);

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

void insertion_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array,
                           int n, TTF_Font *font, int choice) {
  bool quit = false;

  for (int i = 1; i < n && !quit; i++) {
    int key = array[i];
    int j = i - 1;

    render_frame(window, surface, array, n, i, -1, font, choice);
    SDL_Delay(20);

    while (j >= 0 && array[j] > key && !quit) {
      SDL_Event e;
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
          quit = true;
      }

      array[j + 1] = array[j];

      render_frame(window, surface, array, n, j, j + 1, font, choice);
      SDL_Delay(20);

      j--;
    }

    array[j + 1] = key;
    render_frame(window, surface, array, n, j + 1, -1, font, choice);
    SDL_Delay(20);
  }
}

static void merge_segments(SDL_Window *window, SDL_Surface *surface, int *array,
                           int left, int mid, int right, int *temp, int n,
                           TTF_Font *font, int choice, bool *quit) {
  int i = left;
  int j = mid + 1;
  int k = left;

  while (i <= mid && j <= right && !*quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        *quit = true;
    }

    if (*quit)
      return;

    if (array[i] <= array[j]) {
      temp[k] = array[i];
      render_frame(window, surface, array, n, i, -1, font, choice);
      SDL_Delay(20);

      i++;
    } else {
      temp[k] = array[j];

      render_frame(window, surface, array, n, j, -1, font, choice);
      SDL_Delay(20);

      j++;
    }
    k++;
  }

  while (i <= mid && !*quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        *quit = true;
      }
    }
    if (*quit)
      return;

    temp[k] = array[i];

    render_frame(window, surface, array, n, i, -1, font, choice);
    SDL_Delay(20);

    i++;
    k++;
  }

  while (j <= right && !*quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        *quit = true;
      }
    }
    if (*quit)
      return;

    temp[k] = array[j];

    render_frame(window, surface, array, n, j, -1, font, choice);
    SDL_Delay(20);

    j++;
    k++;
  }

  for (int idx = left; idx <= right && !*quit; idx++) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        *quit = true;
      }
    }
    if (*quit)
      return;

    array[idx] = temp[idx];

    render_frame(window, surface, array, n, idx, -1, font, choice);
    SDL_Delay(20);
  }
}

static void merge_sort_rec(SDL_Window *window, SDL_Surface *surface, int *array,
                           int left, int right, int *temp, int n,
                           TTF_Font *font, int choice, bool *quit) {
  if (*quit || left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort_rec(window, surface, array, left, mid, temp, n, font, choice,
                 quit);
  merge_sort_rec(window, surface, array, mid + 1, right, temp, n, font, choice,
                 quit);

  merge_segments(window, surface, array, left, mid, right, temp, n, font,
                 choice, quit);
}

void merge_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array,
                       int n, TTF_Font *font, int choice) {
  bool quit = false;

  int *temp = malloc(n * sizeof(int));
  if (!temp) {
    return;
  }

  merge_sort_rec(window, surface, array, 0, n - 1, temp, n, font, choice,
                 &quit);

  free(temp);
}

static void heapify(SDL_Window *window, SDL_Surface *surface, int *array, int n,
                    int i, TTF_Font *font, int choice, bool *quit) {
  while (!*quit) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        *quit = true;
      }
    }
    if (*quit)
      return;

    if (left < n && array[left] > array[largest]) {
      largest = left;
    }

    if (right < n && array[right] > array[largest]) {
      largest = right;
    }

    if (largest == i) {
      render_frame(window, surface, array, n, i, -1, font, choice);
      SDL_Delay(20);
      break;
    }

    render_frame(window, surface, array, n, i, largest, font, choice);
    SDL_Delay(20);

    int tmp = array[i];
    array[i] = array[largest];
    array[largest] = tmp;

    i = largest;

    render_frame(window, surface, array, n, i, largest, font, choice);
    SDL_Delay(20);
  }
}

void heap_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array,
                      int n, TTF_Font *font, int choice) {
  bool quit = false;

  for (int i = n / 2 - 1; i >= 0 && !quit; i--) {
    heapify(window, surface, array, n, i, font, choice, &quit);
  }

  for (int end = n - 1; end > 0 && !quit; end--) {
    render_frame(window, surface, array, n, 0, end, font, choice);
    SDL_Delay(20);

    int tmp = array[0];
    array[0] = array[end];
    array[end] = tmp;

    render_frame(window, surface, array, n, 0, end, font, choice);
    SDL_Delay(20);

    heapify(window, surface, array, end, 0, font, choice, &quit);
  }
}
