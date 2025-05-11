#include "csv.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
  if (argc < 2)
        fprintf(stderr, "usage: %s <csv file> \n", argv[0]), exit(1);
  char *file_path = argv[1];
  float **table = read_csv_from_file(file_path);
  printf("print table:\n");
  print_table(table);

  return 0;
}
