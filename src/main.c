#include <stdio.h>
#include "cluster_stuff.h"
#include "data.h"
#include "analyzer_gui.h"

int main(int argc,char** argv){
  printf("starting cluster alanlyzer\n");

  ClusterStuff* cluster_stuff = create_cluster_stuff();
  print_data(cluster_stuff->data[0]);

  start_render_loop(cluster_stuff);

  //cleanup
  free_cluster_stuff(&cluster_stuff);
  return 0;
}
