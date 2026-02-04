#ifndef SORTS_H
#define SORTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

extern const int NUM_BARS;

void initialize_array(int *array, int n);

void bubble_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array, int n, TTF_Font *font, int choice);

void quick_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array, int n, TTF_Font *font, int choice);

void insertion_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array, int n, TTF_Font *font, int choice);

void merge_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array, int n, TTF_Font *font, int choice);

void heap_sort_visual(SDL_Window *window, SDL_Surface *surface, int *array, int n, TTF_Font *font, int choice);

#endif
