#include "data.h"
#include <raylib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <float.h>
#include "extra_math.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

// function to return float number between 0 and 1
static inline float rand_float(void)
{
    // random value between 0 and 1
    return (float)rand()/RAND_MAX;
}

static void generate_cluster(Vector2 center, float radius, size_t count, Vector2 **samples)
{
    for (size_t i = 0; i < count; ++i) {
        float angle = rand_float()*2*PI;
        float mag = pow(1.0 - rand_float(),4);
        Vector2 sample = {
            .x = center.x + cosf(angle)*mag*radius,
            .y = center.y + sinf(angle)*mag*radius,
        };
        arrput(*samples, sample);
    }
}

void gen_data(Data** data, size_t num_samples, size_t num_centroids, Limits limits){
  // TODO check if data == NULL

  *data = malloc(sizeof(Data));

  for (size_t i = 0; i < num_centroids; ++i) {
    Vector2 new_centroid = {
      .x = lerp(limits.min_x, limits.max_x, rand_float()),
      .y = lerp(limits.min_y, limits.max_y, rand_float())
    };
    arrput((*data)->centroids, new_centroid);
    float radius = lerp(0, 12, rand_float());
    generate_cluster(
        CLITERAL(Vector2){(*data)->centroids[i].x, (*data)->centroids[i].y}, radius, num_samples,
        &(*data)->samples);
  }
}

void gen_data_mouse(Data** data, size_t num_samples, size_t num_centroids, Limits limits) {
  *data = malloc(sizeof(Data));
  generate_cluster(CLITERAL(Vector2){0}, 10, 100, &(*data)->samples);
  generate_cluster(CLITERAL(Vector2){limits.min_x*0.5f, limits.max_y*0.5f}, 5, 50, &(*data)->samples);
  generate_cluster(CLITERAL(Vector2){limits.max_x*0.5f, limits.max_y*0.5f}, 5, 50, &(*data)->samples);

  for (size_t i = 0; i < num_centroids; ++i) {
    Vector2 new_centroid = {
      .x = lerp(limits.min_x, limits.max_x, rand_float()),
      .y = lerp(limits.min_y, limits.max_y, rand_float())
    };
    arrput((*data)->centroids, new_centroid);
  }
}
