#ifndef CLUSTER_STUFF_H_
#define CLUSTER_STUFF_H_

#include "data.h"

typedef struct ClusterStuff {
  int num_algos;
  int num_distributions;
  void (*algostep_cb[4])(struct ClusterStuff* cluster_stuff, size_t data_idx); // vector of cb functions
  void* state[4]; // TODO -> vector of states
  // TODO *data_gen()
  Data** data;
} ClusterStuff;

ClusterStuff *create_cluster_stuff();
void free_cluster_stuff(ClusterStuff** cluster_stuff);

#endif // CLUSTER_STUFF_H_
