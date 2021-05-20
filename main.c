#include <stdio.h>
#include <stdlib.h>
#include "bitarray.h"
#include "time.h"
#include "filter.h"

int main(int argc, char *argv[])
{

  /*int SIZE = 10000;

  bitarray *barray = create_bitarray(SIZE);

  clock_t start, end;
  double cpu_time_used;

  start = clock();
  clear_bitarray(barray);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("clear_bitarray with new allocation, time taken: %f\n\n", cpu_time_used);

  start = clock();
  clear_bitarray_for(barray);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("clear_bitarray with loop through bitarray->array, time taken: %f\n", cpu_time_used);
*/
  filter *f = create_filter(5, 1);
  unsigned hashes[1];
  hash(f, "a", hashes);
  printf("%d ", hashes[0]);

  return 0;
}
