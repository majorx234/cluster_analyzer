#ifndef CLUSTER_STUFF_H_
#define CLUSTER_STUFF_H_

#include "data.h"

typedef struct ClusterStuff {
  void (*algostep_cb)(struct ClusterStuff* cluster_stuff); // vector of cb functions
  void* state; // TODO -> vector of states
  // TODO *data_gen()
  Data* data;
} ClusterStuff;

#endif // CLUSTER_STUFF_H_
