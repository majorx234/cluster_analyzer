#ifndef CLUSTER_STUFF_H_
#define CLUSTER_STUFF_H_

#include "data.h"

typedef struct ClusterStuff {
  void (*algostep_cb)(struct ClusterStuff* cluster_stuff);
  void* state;
  // TODO *data_gen()
  Data* data;
} ClusterStuff;

#endif // CLUSTER_STUFF_H_
