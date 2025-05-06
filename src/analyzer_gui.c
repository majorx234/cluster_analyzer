#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <time.h>
#include <float.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include "analyzer_gui.h"

Color get_color(size_t idx){
  Color colors[] = {
    PINK,
    YELLOW,
    RED,
    BLUE,
    MAROON,
    GREEN,
    LIME,
    SKYBLUE,
    GOLD,
    PURPLE,
    VIOLET,
    BEIGE,
    BROWN,
  };
  return colors[idx];
}

int start_render_loop() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "k-means");

  // generate_new_state();

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_R)) {
      // generate_new_state();
      //  recluster_state();
    }
    if (IsKeyPressed(KEY_SPACE)) {
      // update_means();
      //  recluster_state();
    }
    BeginDrawing();
    ClearBackground(GetColor(0x181818AA));
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
