#include "csv.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
  if (argc < 5)
        fprintf(stderr, "usage: %s <csv file> \n", argv[0]), exit(1);
  char *file_path = argv[1];
  float **table = read_csv_from_file(file_path);
  return 0;
}
