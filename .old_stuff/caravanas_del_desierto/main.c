#include <raylib/raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_NAME "window_test"

int main(void) {
  int exit_code = EXIT_FAILURE;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);

  while (!WindowShouldClose()) {
    BeginDrawing();

    EndDrawing();
  }

  CloseWindow();

  exit_code = EXIT_SUCCESS;

  return exit_code;
}
