#include "bitarray.h"
#include <stdio.h>
#include <stdlib.h>

bitarray *create_bitarray(int m){
  bitarray *new_bitarray = (bitarray*)malloc(m*sizeof(bitarray));

  if(new_bitarray == NULL){
    fprintf(stderr, "Not enough memory\n");
    exit(1);
  }
  else{
    new_bitarray->size = m;
    new_bitarray->array = (unsigned char*)calloc(m, sizeof(unsigned char));
    if(new_bitarray->array == NULL){
      fprintf(stderr, "Not enough memory\n");
      exit(1);
    }
  }
  return new_bitarray;
}

void free_bitarray(bitarray *a){
  free(a->array);
  free(a);
}

void set_bitarray(bitarray *a, int pos){
  if(a != NULL){
    a->array[pos] = 1;
  }
}

void reset_bitarray(bitarray *a, int pos){
  if(a != NULL){
    a->array[pos] = 0;
  }
}

int get_bitarray(bitarray *a, int pos){
  return a->array[pos];
}

void clear_bitarray(bitarray *a){
  a->array = (unsigned char*)calloc(a->size, sizeof(unsigned char));
  if(a->array == NULL){
    fprintf(stderr, "Not enough memory\n");
    exit(1);
  }
}
