#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void print_table(float** table) {
  for(size_t i = 0; i<arrlen(table); i++) {
    for(size_t j = 0; j<arrlen(table[i]); j++) {
      if(j>0){
        printf(",");
      }
      printf(" %f",table[i][j]);
    }
    printf("\n");
  }
}

float** read_csv_from_file(const char* file_path) {
  FILE* file_handle = fopen(file_path, "r");

  float** float_table = NULL;
  char* line_array = NULL;

  while(true) {
    // read file step by step
    char buff[2] = {0};
    fgets(buff, 2, file_handle);
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
        arrput(float_table, float_array);
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
  return float_table;
}
