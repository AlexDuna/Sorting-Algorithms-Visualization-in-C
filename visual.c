#include "visual.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

const int SCREEN_HEIGHT = 700;
const int SCREEN_WIDTH = 1200;
const int MAX_VALUE = 50;

void draw_bars(SDL_Surface *surface, int *array, int n, int highlight1,
               int highlight2) {
  int background_color = SDL_MapRGB(surface->format, 36, 36, 36);
  SDL_FillRect(surface, NULL, background_color);

  int bar_width = SCREEN_WIDTH / n;

  for (int i = 0; i < n; i++) {
    int value = array[i];
    int bar_height = (value / (float)MAX_VALUE) * (SCREEN_HEIGHT - 40);

    int x = i * bar_width;
    int y = SCREEN_HEIGHT - bar_height;

    SDL_Rect bar = {x, y, bar_width - 1, bar_height};

    int r, g, b;
    if (i == highlight1) {
      r = 204;
      g = 0;
      b = 0;
    } else if (i == highlight2) {
      r = 0;
      g = 102;
      b = 204;
    } else {
      r = 24;
      g = 251;
      b = 169;
    }
    int bar_color = SDL_MapRGB(surface->format, r, g, b);
    SDL_FillRect(surface, &bar, bar_color);
  }
}

void draw_text(SDL_Surface *surface, TTF_Font *font, const char *text, int x,
               int y, SDL_Color color) {
  SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, color);
  SDL_Rect dest = {x, y, textSurface->w, textSurface->h};
  SDL_BlitSurface(textSurface, NULL, surface, &dest);
  SDL_FreeSurface(textSurface);
}

void render_algorithm_info(SDL_Surface *surface, TTF_Font *font, int choice,
                           SDL_Color color) {
  const char *name = NULL;
  const char *complexity = NULL;

  switch (choice) {
  case 1:
    name = "Bubble Sort";
    complexity = "Time: O(n^2) Space: O(1)";
    break;
  case 2:
    name = "Quick Sort";
    complexity = "Time: O(n log n) Space: O(log n)";
    break;
  case 3:
    name = "Insertion Sort";
    complexity = "Time: O(n^2) Space: O(1)";
    break;
  case 4:
    name = "Merge Sort";
    complexity = "Time: O(n log n) Space: O(n)";
    break;
  case 5:
    name = "Heap Sort";
    complexity = "Time: O(n log n) Space: O(1)";
    break;
  default:
    name = "Unknown Algorithm";
    complexity = "";
    break;
  }

  if (name) {
    draw_text(surface, font, name, 20, 20, color);
  }
  if (complexity && complexity[0] != '\0') {
    draw_text(surface, font, complexity, 20, 50, color);
  }
}

void render_frame(SDL_Window *window, SDL_Surface *surface, int *array, int n,
                  int highlight1, int highlight2, TTF_Font *font, int choice) {
  SDL_Color white = {255, 255, 255, 255};

  draw_bars(surface, array, n, highlight1, highlight2);
  render_algorithm_info(surface, font, choice, white);
  SDL_UpdateWindowSurface(window);
}
