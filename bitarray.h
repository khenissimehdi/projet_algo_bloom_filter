#ifndef BITARRAY_H
#define BITARRAY_H

typedef struct _bitarray{
  /* TODO */
    unsigned char* array;
    int size;
} bitarray;

/* Return a pointer to an emptyu bitarray that can store m bits */
bitarray *create_bitarray(int m);

/* Free the memory associated with the bitarray */
void free_bitarray(bitarray *a);

/* Set position pos in the bitarray to 1 */
void set_bitarray(bitarray *a, int pos);

/* set position pos in the bitarray to 0 */
void reset_bitarray(bitarray *a, int pos);

/* Get the value at position pos in the bitarray */
int get_bitarray(bitarray* a, int pos);

/* Set all position*/
void clear_bitarray(bitarray *a);


#endif /* BITARRAY*/
