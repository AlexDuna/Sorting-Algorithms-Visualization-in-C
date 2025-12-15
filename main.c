#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

int main(int argc, char *args[]) {
  // the window we'll be rendering to
  SDL_Window *window = NULL;

  // the surface contained by the window
  SDL_Surface *screenSurface = NULL;

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

      // fill the surface white
      SDL_FillRect(screenSurface, NULL,
                   SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      // update the surface
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
