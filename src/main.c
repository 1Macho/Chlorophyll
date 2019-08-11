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
    Color selected_tile;
    Color known_tiles;
    Color flagged_tiles;
    Color selected_flagged_tile;
    Board testBoard;
    int mouse_x;
    int mouse_y;
    unsigned char last_click;
    unsigned char now_click;
    unsigned char last_rclick;
    unsigned char now_rclick;
    unsigned char selected_x;
    unsigned char selected_y;
    unsigned char tick_cell;
    unsigned char flag_cell;
    unsigned long mouse_state;
    unsigned char dead;

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
    selected_tile = ColorFromHSV(0x3F,0xA8,0x80);
    mined_tiles = ColorFromHSV(0x00,0xA8,0xB0);
    known_tiles = ColorFromHSV(0x1D,0xA8,0xB0);
    flagged_tiles = ColorFromHSV(0x76,0xA8,0xB0);
    selected_flagged_tile = ColorFromHSV(0x76,0xA8,0x80);
    testBoard = Board_Create(16, 16, 0xFF/10);
    selected_x = -1;
    selected_y = -1;
    mouse_x = -1;
    mouse_y = -1;
    tick_cell = 0;
    last_click = 0;
    last_rclick = 0;
    dead = 0;

    while(running) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          running = 0;
          puts("Quit event sent.");
        }
      }

      tick_cell = 0;
      flag_cell = 0;

      mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

      if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        now_click = 1;
      }
      else {
        now_click = 0;
      }

      if (mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        now_rclick = 1;
      }
      else {
        now_rclick = 0;
      }

      if (~(now_click) & last_click) {
        tick_cell = 1;
      }

      if (~(now_rclick) & last_rclick) {
        flag_cell = 1;
      }

      last_click = now_click;
      last_rclick = now_rclick;

      selected_x = (mouse_x-CELL_PADDING) / CELL_SIDE;
      selected_y = (mouse_y-CELL_PADDING) / CELL_SIDE;
      if (tick_cell) {
        dead = Board_TickCell(&testBoard,selected_x,selected_y);
      }

      if (flag_cell) {
        Board_FlagCell(&testBoard,selected_x,selected_y);
      }

      SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, 255);
      SDL_RenderClear(renderer);
      Board_Draw(renderer, &testBoard, unknown_tiles, mined_tiles, selected_tile, known_tiles, flagged_tiles, selected_flagged_tile, selected_x, selected_y,dead);
      SDL_RenderPresent(renderer);
      if(dead) {
        SDL_Delay(3000);
        running = 0;
      }
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();


    return 0;
}
