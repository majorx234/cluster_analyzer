#include "stddef.h"
#include "math.h"
#include "raylib.h"
#include "raymath.h"
#include "stb_ds.h"

#include "kmeans.h"
#include "data.h"
#include <float.h>

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
