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
  }
  return new_filter;
}

void free_filter(filter *f)
{
  free_bitarray(f->bitarray);
  free(f);
}

void hash(filter *f, char *str, unsigned hashes[])
{
  int rands[f->k], n, i, j, hash;
  int len = strlen(str);
  srand(time(NULL));

  for (n = 0; n < f->k; n++)
  {
    int r = rand() % 254 + 2;
    rands[n] = r;
  }

  for (i = 0; i < f->k; i++)
  {
    hash = 0;
    for (j = 0; str[j] != '\0'; j++)
    {
      hash += str[j] * pow((rands[i]), len - (j + 1));
    }
    hashes[i] = hash;
  }
}

void add_filter(filter *f, char *str)
{
  unsigned hashes[f->k];
  hash(f, str, hashes);

  for (int i = 0; i < f->k; i++)
  {
    set_bitarray(f->bitarray, hashes[i] % f->bitarray->size);
  }
}
