#ifndef DATA_H_
#define DATA_H_

#include "raylib.h"
#include <stddef.h>

typedef struct Limits {
  float min_x;
  float max_x;
  float min_y;
  float max_y;
} Limits;

typedef struct Data {
  Vector2* samples;
  Limits limits;
} Data;

float rand_float(void);
void gen_data(Data** data, size_t num_samples, size_t num_centroids, Limits limits);
void gen_data_mouse(Data** data, size_t num_samples, Limits limits);
void gen_data_circles(Data **data, size_t num_samples, Vector2 *centroids,
                      size_t num_centroids, float *radius, float *widths);
void gen_data_half_circles(Data** data, size_t num_samples, Vector2* centroids,
                           size_t num_centroids, float* radius, float* direction_angle, float* widths);
void generate_half_circle_cluster(Vector2 center, float radius, float direction_angle, size_t count, float width, Vector2 **samples);
void free_data(Data** data);
void print_data(Data *data);

#endif // DATA_H_
