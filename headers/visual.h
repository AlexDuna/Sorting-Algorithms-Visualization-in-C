#ifndef VISUAL_H
#define VISUAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int MAX_VALUE;

void draw_bars(SDL_Surface *surface, int *array, int n, int highlight1, int highlight2);
void draw_text(SDL_Surface *surface, TTF_Font *font, const char *text, int x, int y, SDL_Color color);
void render_algorithm_info(SDL_Surface *surface, TTF_Font *font, int choice, SDL_Color color);
void render_frame(SDL_Window *window, SDL_Surface *surface, int *array, int n, int highlight1, int highlight2, TTF_Font *font, int choice);

#endif
