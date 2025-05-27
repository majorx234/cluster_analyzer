#ifndef CLUSTER_STUFF_H_
#define CLUSTER_STUFF_H_

#include "data.h"

typedef struct ClusterStuff {
  void (*algostep_cb[4])(struct ClusterStuff* cluster_stuff, size_t data_idx); // vector of cb functions
  void* state[4]; // TODO -> vector of states
  // TODO *data_gen()
  Data** data;
} ClusterStuff;

#endif // CLUSTER_STUFF_H_
