#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <time.h>
#include <float.h>

//#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include "analyzer_gui.h"

#define ARRAY_LEN(xs) sizeof(xs)/sizeof(xs[0])

#define SAMPLE_RADIUS 2
#define CENTROID_RADIUS 5

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
  return colors[idx%(ARRAY_LEN(colors))];
}

Vector2 project_sample_to_screen(UiRect r, Vector2 sample, Limits limits)
{
  // normalize to 0..1
  float nx = (sample.x - limits.min_x)/(limits.max_x - limits.min_x);
  float ny = (sample.y - limits.min_y)/(limits.max_y - limits.min_y);

  // project to screen
  return CLITERAL(Vector2) {
    .x = r.w*nx + r.x,
    .y = r.h - (r.h*ny) + r.y,
  };
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

void cluster_widget(UiRect r, Vector2 *set, Vector2 *clusters[], Vector2 means[], Limits limits)
{
    for (size_t i = 0; i < arrlen(set); ++i) {
        Vector2 it = set[i];
        DrawCircleV(project_sample_to_screen(r, it, limits), SAMPLE_RADIUS, LIGHTGRAY);
    }
    for (size_t i = 0; i < 3; ++i) {
      Color color = get_color(i);

        for (size_t j = 0; j < arrlen(clusters[i]); ++j) {
            Vector2 it = clusters[i][j];
            DrawCircleV(project_sample_to_screen(r, it, limits), SAMPLE_RADIUS, color);
        }

        DrawCircleV(project_sample_to_screen(r, means[i], limits), CENTROID_RADIUS, color);
    }
}
