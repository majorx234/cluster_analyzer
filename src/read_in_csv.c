#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

int main(int argc, char** argv){
  if (argc < 5)
        fprintf(stderr, "usage: %s <csv file> \n", argv[0]), exit(1);
  char *file_path = argv[1];
  FILE* file_handle = fopen(file_path, "r");

  float** float_table = NULL;
  char* line_array = NULL;
  char buff[2];
  while(true) {
    // read file step by step
    fgets(buff, 1, file_handle);
    if( !( (buff[0] == '\n' || buff[0] == '\0')) ){
      arrput(line_array, buff[0]);
    } else {
      float* float_array = NULL;
      char* float_string = NULL;
      for (size_t i = 0; i < arrlen(line_array);i++) {
        if(line_array[i] != ','){
          arrput(float_string, line_array[i]);
        } else {
          arrput(float_string, 0);
          float value = atof (float_string);
          arrput(float_array, value);
          arrfree(float_string);
        }
      }
      // end of line
      arrput(float_string, 0);
      float value = atof (float_string);
      arrput(float_array, value);
      arrfree(float_string);
      // add float_array to float table
      if (arrlen(float_array) > 1){
        arrput(float_table,float_array);
      }
      arrfree(line_array);
      line_array = NULL;
      float_array = NULL; // pointer is in float table, and still needed so ne free
      // check for end of file
      if( buff[0] == '\0') {
        break;
      }
    }
  }
  return 0;
}
