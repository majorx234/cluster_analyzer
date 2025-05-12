#include <stdio.h>
#include "cluster_stuff.h"
#include "data.h"
#include "kmeans.h"

int main(int argc,char** argv){
  printf("starting cluster alanlyzer\n");
  ClusterStuff cluster_stuff;
  cluster_stuff.algostep_cb = kmeans_step_wrapper;
  Limits limits = {-10.0f, 10.0f, -10.0f, 10.0f};
  gen_data(&cluster_stuff.data, 10, 3, limits);
  print_data(cluster_stuff.data);
  return 0;
}
