#include "stddef.h"
#include "math.h"
#include "raylib.h"
#include "raymath.h"
#include "stb_ds.h"

#include "kmeans.h"
#include "data.h"
#include <float.h>
#include <stdlib.h>

void kmeans_init(State** state, size_t num_clusters){
  *state = malloc(sizeof(State));
  (*state)->clusters = malloc(num_clusters*sizeof(Vector2*));
  for (size_t i = 0; i< num_clusters; i++) {
    arrsetlen((*state)->clusters[i], 1);
  }
}

void kmeans_free(State** state) {
  for (size_t i = 0; i< (*state)->num_clusters; i++) {
    arrfree((*state)->clusters[i]);
  }
  free((*state)->clusters);
  free(*state);
  *state = NULL;
}

void kmeans_step(Data* data, State* state)
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
        arrput(state->clusters[k], p);
    }
}
