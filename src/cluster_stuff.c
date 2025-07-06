#include "cluster_stuff.h"

#include <stdlib.h>
#include "stb_ds.h"
#include "kmeans.h"

ClusterStuff *create_cluster_stuff() {
  Limits limits = {-10.0f, 10.0f, -10.0f, 10.0f};
  ClusterStuff* cluster_stuff = malloc(sizeof(ClusterStuff));
  cluster_stuff->algostep_cb[0] = kmeans_step_wrapper;
  cluster_stuff->algostep_cb[1] = kmeans_step_wrapper;
  cluster_stuff->algostep_cb[2] = kmeans_step_wrapper;
  cluster_stuff->algostep_cb[3] = kmeans_step_wrapper;

  // init kmeans
  State* state[4] = {NULL,NULL,NULL,NULL};
  for(int i=0;i<4;i++) {
    kmeans_init(&state[i], 3, limits);
    cluster_stuff->state[i] = (void*)state[i];
    cluster_stuff->data = NULL;
  }
  Data* new_data0 = NULL;
  gen_data(&new_data0, 10, 3, limits);
  arrput(cluster_stuff->data, new_data0);
  Vector2 centroids1[2] = {
    {
      .x=0.0f,
      .y=0.0f
    },
    {
      .x=0.0f,
      .y=0.0f
    }
  };
  float radiuses1[2] = {
    0.5f,
    0.7f
  };
  float widths1[2] = {
    0.1f,
    0.1f
  };
  Data* new_data1 = NULL;
  gen_data_circles(&new_data1, 40, centroids1, 2, radiuses1, widths1);

  Data* new_data2 = NULL;
  Vector2 center2[2] = {
    {
      .x=-0.2f,
      .y=-0.2f
    },{
      .x=0.2f,
      .y=0.2f
    }
  };
  float radius2[2] = {0.5f, 05f};
  float widths2[2] = {0.1f, 0.1f};
  float direction_angle2[2] = {3.14f/2.0f,3.14f*1.5f};
  gen_data_half_circles(&new_data2, 50, center2, 2, radius2, direction_angle2, widths2);

  arrput(cluster_stuff->data, new_data1);

  return cluster_stuff;
}
void free_cluster_stuff(ClusterStuff** cluster_stuff){}
