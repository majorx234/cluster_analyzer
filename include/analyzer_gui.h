#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <time.h>
#include <float.h>
#include "data.h"

typedef struct UiRect {
  float x;
  float y;
  float w;
  float h;
} UiRect;

Color get_color(size_t idx);
int start_render_loop();
void cluster_widget(UiRect r, Vector2 *set, Vector2 *clusters[], Vector2 means[], Limits limits);
