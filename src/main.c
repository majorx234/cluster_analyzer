#include <stdio.h>
#include "cluster_stuff.h"
#include "data.h"
#include "kmeans.h"
#include "analyzer_gui.h"
#include "stb_ds.h"

int main(int argc,char** argv){
  printf("starting cluster alanlyzer\n");

  Limits limits = {-10.0f, 10.0f, -10.0f, 10.0f};

  // init kmeans
  State* state;
  kmeans_init(&state, 3, limits);

  ClusterStuff cluster_stuff;
  cluster_stuff.algostep_cb = kmeans_step_wrapper;
  cluster_stuff.state = (void*)state;
  Data* new_data;
  gen_data(&new_data, 10, 3, limits);
  arrput(cluster_stuff.data, new_data);
  print_data(cluster_stuff.data[0]);

  start_render_loop(&cluster_stuff);
  return 0;
}
