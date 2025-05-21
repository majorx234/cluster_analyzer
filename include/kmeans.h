#ifndef KMEANS_H_
#define KMEANS_H_

#include "raylib.h"
#include <stddef.h>
#include "data.h"
#include "cluster_stuff.h"

typedef struct State {
  Vector2** clusters;
  Vector2* centroids;
  size_t num_clusters;
} State;

void kmeans_step_wrapper(ClusterStuff* cluster_stuff, size_t data_idx);
void kmeans_init(State** state, size_t num_clusters, Limits limits);
void kmeans_step(State *state, Data *data);
void kmeans_update_centroids(State* state, Data* data);
void kmeans_free(State** state);

#endif // KMEANS_H_

