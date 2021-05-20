#ifndef FILTER_H
#define FILTER_H

#include "bitarray.h"

typedef struct _filter
{
  bitarray *bitarray;
  int k; /* number of hash functions */
} filter;
/* Return a pointer to an empty filter with parameters m and k */
filter *create_filter(int m, int k);

/* Free the memory associated with the filter */
void free_filter(filter *f);

/* Compute k hash values for the string str and place them in thearray hashes. */
void hash(filter *f, char *str, unsigned hashes[]);

/* Add the key str to the filter */
void add_filter(filter *f, char *str);
/*Print full filter */

void print_filter(filter *f);

/* Check if the key str is in the filter, 0 means no, 1 means maybe */
int is_member_filter(filter *f, char *str);

#endif /* FILTER */
