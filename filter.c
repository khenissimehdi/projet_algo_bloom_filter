#include "filter.h"
#include "bitarray.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

filter *create_filter(int m, int k)
{
  filter *new_filter = (filter *)malloc(m * sizeof(filter));
  if (new_filter == NULL)
  {
    fprintf(stderr, "Not enough memory\n");
    exit(1);
  }
  else
  {
    new_filter->bitarray = create_bitarray(m);
    new_filter->k = k;
    int i;
    for (i = 0; i < new_filter->k; i++)
    {
      int r = rand() % 254 + 2;
      new_filter->weights[i] = r;
    }
  }
  return new_filter;
}

void free_filter(filter *f)
{
  free(f->bitarray);
  free(f);
}

void hash(filter *f, char *str, unsigned hashes[])
{
  int i, j, hash;
  int len = strlen(str);
  srand(time(NULL));

  for (i = 0; i < f->k; i++)
  {
    hash = 0;
    for (j = 0; str[j] != '\0'; j++)
    {
      //hash += pow((double)(f->weights[i]), (double)(len - i)) * str[i];
      //hash += str[j] * pow(f->weights[i], len - (j + 1));
      hash = (f->weights[i] * hash + str[i]) % f->bitarray->size;
    }
    hashes[i] = hash;
  }
}

void add_filter(filter *f, char *str)
{
  unsigned hashes[f->k];
  hash(f, str, hashes);
  int i;
  for (i = 0; i < f->k; i++)
  {
    set_bitarray(f->bitarray, hashes[i] % f->bitarray->size);
  }
}

void print_filter(filter *f)
{
  int i;
  putchar('[');
  for (i = 0; i < f->bitarray->size - 1; i++)
  {
    /*  printf("%d \n", f->bitarray->array[i]);*/
    printf("%d, ", f->bitarray->array[i]);
  }
  printf("%d", f->bitarray->array[f->bitarray->size - 1]);
  printf("]\n");
}

int is_member_filter(filter *f, char *str)
{
  int i;
  int res = 1;
  unsigned hashes[f->k];
  hash(f, str, hashes);
  for (i = 0; i < f->k; i++)
  {
    if (get_bitarray(f->bitarray, hashes[i] % f->bitarray->size) != 1)
    {
      res = 0;
    }
  }
  return res;
}
