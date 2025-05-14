#include <stdio.h>
#include "data.h"
#include "kmeans.h"
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

int start_render_loop(ClusterStuff* cluster_stuff) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "k-means");

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_R)) {
      Limits limits = cluster_stuff->data->limits;
      free_data(&cluster_stuff->data);
      gen_data_mouse(&cluster_stuff->data, 10, limits);
      kmeans_free((State**)&cluster_stuff->state);
      kmeans_init((State**)&cluster_stuff->state, 3, limits);
      //  recluster_state();
    }
    if (IsKeyPressed(KEY_SPACE)) {
      cluster_stuff->algostep_cb(cluster_stuff);
      cluster_stuff->algostep_cb(cluster_stuff->state);
      //  recluster_state();
    }
    BeginDrawing();
    ClearBackground(GetColor(0x181818AA));
    UiRect rect = {
      .h = 600,
      .w = 800,
      .x = 0,
      .y = 0
    };
    State* kmeans_state = (State*)cluster_stuff->state;
    cluster_widget(rect,
                   cluster_stuff->data->samples,
                   kmeans_state->clusters,
                   kmeans_state->centroids,
                   arrlen(kmeans_state->centroids),
                   ((Data*)(cluster_stuff->data))->limits);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

void cluster_widget(UiRect r, Vector2 *samples, Vector2 **clusters, Vector2* centroids, size_t num_cluster, Limits limits)
{
  // draw samples
  for (size_t i = 0; i < arrlen(samples); ++i) {
    Vector2 it = samples[i];
    DrawCircleV(project_sample_to_screen(r, it, limits), SAMPLE_RADIUS, LIGHTGRAY);
  }

  // draw cluster items and centroids
  for (size_t i = 0; i < num_cluster; ++i) {
    Color color = get_color(i);

    for (size_t j = 0; j < arrlen(clusters[i]); ++j) {
      Vector2 it = clusters[i][j];
      DrawCircleV(project_sample_to_screen(r, it, limits), SAMPLE_RADIUS, color);
    }

    DrawCircleV(project_sample_to_screen(r, centroids[i], limits), CENTROID_RADIUS, color);
  }
}
