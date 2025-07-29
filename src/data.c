#include "data.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <float.h>
#include "extra_math.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

// function to return float number between 0 and 1
inline float rand_float(void)
{
    // random value between 0 and 1
    return (float)rand()/RAND_MAX;
}

void rotate_points_inplace(
        double* x,     //X coords to rotate - replaced on return
        double* y,     //Y coords to rotate - replaced on return
        double dx,     // dx coords to translate
        double dy,     // dy coords to translate
        double angle)   //Angle of rotation (radians, counterclockwise)
{
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    double y_new = (*x)*sin_angle + (*y)*cos_angle + dx;
    double x_new = (*x)*cos_angle - (*y)*sin_angle + dy;
    *x = x_new;
    *y = y_new;
    return;
}

void generate_cluster(Vector2 center, float radius, size_t count, Vector2 **samples)
{
    for (size_t i = 0; i < count; ++i) {
        float angle = rand_float()*2*PI;
        // float mag = pow(1.0 - rand_float(),4);
        float mag = pow(1.0 - rand_float(), 0.5);
        Vector2 sample = {
            .x = center.x + cosf(angle)*mag*radius,
            .y = center.y + sinf(angle)*mag*radius,
        };
        arrput(*samples, sample);
    }
}

void generate_circle_cluster(Vector2 center, float radius, size_t count, float width, Vector2 **samples) {
    for (size_t i = 0; i < count; ++i) {
        float angle = rand_float()*2.0f*PI;
        float mag = radius + width*(rand_float() - 0.5f);
        Vector2 sample = {
            .x = center.x + cosf(angle)*mag*radius,
            .y = center.y + sinf(angle)*mag*radius,
        };
        arrput(*samples, sample);
    }
}

void generate_half_circle_cluster(Vector2 center, float radius, float direction_angle, size_t count, float width, Vector2 **samples) {
    for (size_t i = 0; i < count; ++i) {
      float angle = fmod((rand_float()-0.5f)*PI + direction_angle, 2.0f*PI);
        float mag = radius + width*(rand_float() - 0.5f);
        Vector2 sample = {
            .x = center.x + cosf(angle)*mag*radius,
            .y = center.y + sinf(angle)*mag*radius,
        };
        arrput(*samples, sample);
    }
}

double sampleNormal2(double mean, double sigma) {
    const double two_pi = 2.0 * M_PI;
    double u1, u2;
    do
    {
        u1 = ((double) rand() / (RAND_MAX));
    }
    while (u1 == 0);
    u2 = ((double) rand() / (RAND_MAX));

    //compute z0 and z1
    double mag = sigma * sqrt(-2.0 * log(u1));
    double z0  = mag * cos(two_pi * u2) + mean;
    double z1  = mag * sin(two_pi * u2) + mean;

    return z0; // z1 is rand too
}

void generate_gaussian_distribution(Vector2 center,
                                    float sigma_x,
                                    float sigma_y,
                                    float normal_angle,
                                    size_t count,
                                    Vector2 **samples){
  float mean_x = 0.0f;
  float mean_y = 0.0f;
  for (int i = 0; i < count; ++i) {
    double x = sampleNormal2(mean_x, sigma_x);
    double y = sampleNormal2(mean_y, sigma_y);
    rotate_points_inplace(&x, &y, center.x, center.y, normal_angle);
    Vector2 sample = {
      .x = x,
      .y = y,
    };
    arrput(*samples, sample);
  }
}

void gen_data_gaussian(Data **data, size_t num_samples, Vector2* centroids,
                       Vector2* sigmas, size_t num_centroids, float* normal_angles) {
  *data = malloc(sizeof(Data));
  (*data)->samples = NULL;
  size_t count = num_samples/num_centroids;
  for (size_t i = 0; i < num_centroids; ++i) {
    generate_gaussian_distribution(centroids[i],
                                   sigmas[i].x,
                                   sigmas[i].y,
                                   normal_angles[i],
                                   count,
                                   &(*data)->samples);
  }
}


void gen_data(Data** data, size_t num_samples, size_t num_centroids, Limits limits){
  // TODO check if data == NULL

  *data = malloc(sizeof(Data));
  (*data)->samples = NULL;

  for (size_t i = 0; i < num_centroids; ++i) {
    Vector2 new_centroid = {
      .x = lerp(limits.min_x, limits.max_x, rand_float()),
      .y = lerp(limits.min_y, limits.max_y, rand_float())
    };

    float dist_min_x = new_centroid.x - limits.min_x;
    float dist_max_x = limits.max_x - new_centroid.x;
    float dist_min_y = new_centroid.y - limits.min_y;
    float dist_max_y = limits.max_y - new_centroid.y;
    float max_bound = MIN(dist_min_x, (MIN(dist_max_x, (MIN(dist_min_y, dist_max_y)))));

    float radius = lerp(0, max_bound, rand_float());
    generate_cluster(CLITERAL(Vector2){new_centroid.x, new_centroid.y}, radius, num_samples,
                     &(*data)->samples);
    (*data)->limits = limits;
  }
}

void gen_data_circles(Data** data, size_t num_samples, Vector2* centroids, size_t num_centroids, float* radius, float* widths) {
  *data = malloc(sizeof(Data));
  (*data)->samples = NULL;
  size_t count = num_samples/num_centroids;
  for (size_t i = 0; i < num_centroids; ++i) {
    generate_circle_cluster(centroids[i], radius[i], count, widths[i], &(*data)->samples);
  }
}

void gen_data_half_circles(Data** data, size_t num_samples, Vector2* centroids, size_t num_centroids, float* radius, float* direction_angle, float* widths) {
  *data = malloc(sizeof(Data));
  (*data)->samples = NULL;
  size_t count = num_samples/num_centroids;
  for (size_t i = 0; i < num_centroids; ++i) {
    generate_half_circle_cluster(centroids[i], radius[i], direction_angle[i], count, widths[i], &((*data)->samples));
  }
}

void gen_data_mouse(Data** data, size_t num_samples, Limits limits) {
  *data = malloc(sizeof(Data));
  (*data)->samples = NULL;

  generate_cluster(CLITERAL(Vector2){0}, 10, 100, &(*data)->samples);
  generate_cluster(CLITERAL(Vector2){limits.min_x*0.5f, limits.max_y*0.5f}, 5, 50, &(*data)->samples);
  generate_cluster(CLITERAL(Vector2){limits.max_x*0.5f, limits.max_y*0.5f}, 5, 50, &(*data)->samples);
}

void free_data(Data** data)
{
  arrfree((*data)->samples);
  free(*data);
  *data = NULL;
}

void print_data(Data* data) {
  for(size_t i = 0; i<arrlen(data->samples); i++) {
    printf("(%f, %f) ", data->samples[i].x, data->samples[i].y);
    if (i != arrlen(data->samples)-1){
      printf(",");
    }
  }
  printf("\n");
}
