#ifndef ANALYZE_GUI_H_
#define ANALYZE_GUI_H_

#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <time.h>
#include <float.h>
#include "data.h"
#include "cluster_stuff.h"

typedef struct UiRect {
  float x;
  float y;
  float w;
  float h;
} UiRect;

Color get_color(size_t idx);
int start_render_loop(ClusterStuff* cluster_stuff);
void cluster_widget(UiRect r, Vector2 *samples, Vector2 **clusters, Vector2* centroids, size_t num_cluster, Limits limits);

#endif // ANALYZE_GUI_H_
