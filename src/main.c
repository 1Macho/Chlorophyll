// Example program:
// Using SDL2 to create an application window

#include "SDL2/SDL.h"
#include "colors.h"
#include <stdio.h>
#include "board.h"

int main(int argc, char* argv[]) {

    SDL_Window* window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    SDL_Renderer* renderer;

    Color background;
    Color unknown_tiles;
    Color mined_tiles;
    Board testBoard;

    int running;

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Chlorophyll",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        520,                               // width, in pixels
        520,                               // height, in pixels
        SDL_WINDOW_SHOWN                  // flags - see below
    );

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    running = 1;

    background = ColorFromHSV(0x00,0x00,0x22);
    unknown_tiles = ColorFromHSV(0x3F,0xA8,0xB0);
    mined_tiles = ColorFromHSV(0x00,0xA8,0xB0);
    testBoard = Board_Create(16, 16, 0xFF/4);

    while(running) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          running = 0;
          puts("Quit event sent.");
        }
      }
      SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, 255);
      SDL_RenderClear(renderer);
      Board_Draw(renderer, &testBoard, unknown_tiles, mined_tiles);
      SDL_RenderPresent(renderer);
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();


    return 0;
}
