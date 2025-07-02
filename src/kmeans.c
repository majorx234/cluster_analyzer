#include <float.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "stb_ds.h"

#include "kmeans.h"
#include "data.h"
#include "extra_math.h"

void kmeans_step_wrapper(ClusterStuff* cluster_stuff, size_t data_idx) {
  // TODO: need extra index parameter for state of algo
  kmeans_step((State*)cluster_stuff->state[data_idx], (Data*)cluster_stuff->data[data_idx]);
  kmeans_update_centroids((State*)cluster_stuff->state[data_idx], (Data*)cluster_stuff->data[data_idx]);
}

void kmeans_init(State** state, size_t num_clusters, Limits limits){
  *state = malloc(sizeof(State));
  (*state)->clusters = NULL;
  (*state)->centroids = NULL;
  (*state)->num_clusters = num_clusters;
  for (size_t i = 0; i< num_clusters; i++) {
    arrput((*state)->clusters, NULL);
    arrsetlen((*state)->clusters[i], 0);
    Vector2 new_centroid = {
      .x = Lerp(limits.min_x,
                limits.max_x,
                rand_float()),
      .y = Lerp(limits.min_y,
                limits.max_y,
                rand_float())
    };
    arrput((*state)->centroids, new_centroid);
  }
}

void kmeans_free(State** state) {
  for (size_t i = 0; i< (*state)->num_clusters; i++) {
    arrfree((*state)->clusters[i]);
  }
  arrfree((*state)->clusters);
  free(*state);
  *state = NULL;
}

void kmeans_step(State* state, Data* data)
{
    for (size_t j = 0; j < state->num_clusters; ++j) {
        arrsetlen(state->clusters[j], 0);
    }

    for (size_t i = 0; i < arrlen(data->samples); ++i) {
        Vector2 p = data->samples[i];
        int k = -1;
        float s = FLT_MAX;
        for (size_t j = 0; j < state->num_clusters; ++j) {
            Vector2 m = state->centroids[j];
            float sm = Vector2LengthSqr(Vector2Subtract(p, m));
            if (sm < s) {
                s = sm;
                k = j;
            }
        }
        if(k != -1) arrput(state->clusters[k], p);
    }
}

void kmeans_update_centroids(State* state, Data* data)
{
    for (size_t i = 0; i < state->num_clusters; ++i) {
        if (arrlen(state->clusters[i]) > 0) {
            state->centroids[i] = Vector2Zero();
            for (size_t j = 0; j < arrlen(state->clusters[i]); ++j) {
                state->centroids[i] = Vector2Add(state->centroids[i], state->clusters[i][j]);
            }
            state->centroids[i].x /= arrlen(state->clusters[i]);
            state->centroids[i].y /= arrlen(state->clusters[i]);
        } else {
            // if cluster is empty just regenerate mean
            state->centroids[i].x = Lerp(data->limits.min_x, data->limits.max_x, rand_float());
            state->centroids[i].y = Lerp(data->limits.min_y, data->limits.max_y, rand_float());
        }
    }
}
