#include <stdio.h>
#include "cluster_stuff.h"
#include "data.h"
#include "kmeans.h"
#include "analyzer_gui.h"

int main(int argc,char** argv){
  printf("starting cluster alanlyzer\n");

  Limits limits = {-10.0f, 10.0f, -10.0f, 10.0f};

  // init kmeans
  State* state;
  kmeans_init(&state, 3, limits);

  ClusterStuff cluster_stuff;
  cluster_stuff.algostep_cb = kmeans_step_wrapper;
  cluster_stuff.state = (void*)state;
  gen_data(&cluster_stuff.data, 10, 3, limits);
  print_data(cluster_stuff.data);

  start_render_loop(&cluster_stuff);
  return 0;
}
