#ifndef KMEANS_H_
#define KMEANS_H_

#include "raylib.h"
#include <stddef.h>
#include "data.h"

typedef struct State {
  Vector2** clusters;
  Vector2* centroids;
  size_t num_clusters;
} State;

void kmeans_init(State** state, size_t num_clusters);
void kmeans_step(Data *data, State *state);
void kmeans_free(State** state);

#endif // KMEANS_H_

