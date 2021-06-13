#include "bitarray.h"
#include "time.h"
#include "filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_WORD_LENGTH 80
char *fileInName;
char *fileOutName;
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
  /*char *mdp = "abc";
  int len = strlen(mdp);
  filter *f = create_filter(5, len);
  unsigned hashes[len];
  hash(f, "abc", hashes);
  printf("%d \n", hashes[0]);
  add_filter(f, "abc");
  add_filter(f, "dce");
  print_filter(f);
  printf("is_member_filter : %d\n", is_member_filter(f, "abc"));
  printf("is_member_filter : %d\n", is_member_filter(f, "dce"));*/
  char *line;
  FILE *fin = NULL;
  FILE *fileIn = NULL;
  FILE *fileOut = NULL;
  int m = 7000;
  int k = 3;
  int launched = 0;
  /* readline = ? = fgets ou bien ??? */
  printf("Bloom filter : choose between the following options :\n\n");
  while (!launched || fin == NULL)
  {
    if (fin == NULL)
      printf(" - Load a password file up : 		     	     enter 'f' then '<password file path>' (mandatory)\n");
    else
    {
      printf(" - Load a password file up : 		     	     enter 'f' then '<password file path>' (file loaded)\n");
    }
    printf(" - Define m the number of bits in the bitarray 	     enter 'm' then '<number of bits>' (default value: %d)\n", m);
    printf(" - Run stats using s \n");
    printf(" - Define stats files using g \n");
    printf(" - Define k the number of different hash functions   enter 'k' then '<number of hash f>' (default value: %d)\n", k);
    printf(" - Run the bloom filter program                      enter 'r', must have a password file loaded up first !\n");
    line = readline(">>>");
    if (line[0] == 'f')
    {
      char *filename = readline("file name :");
      if (filename != NULL)
      {
        filename[strlen(filename) - 1] = '\0';
      }
      putchar('\n');
      fin = fopen(filename, "r");
      if (fin == NULL)
      {
        /*fprintf(stderr, "Error opening file for reading: %s\n", argv[1]);
        return 1;*/
        printf("No file specified or incorrect format, please enter a valid txt password file.\n");
      }
    }
    else if (line[0] == 'm')
    {
      m = atoi(readline("m value : "));
    }
    else if (line[0] == 'k')
    {
      k = atoi(readline("k value : "));
    }
    else if (line[0] == 'r')
    {
      if (fin == NULL)
      {
        printf("Please load up a password file before running the program");
      }
      else
      {
        launched = 1;
      }
    }
    else if (line[0] == 's')
    {

      fileInName = readline("file input name :");
      fileOutName = readline("file ouput name :");
      if (fileInName != NULL)
      {
        fileInName[strlen(fileInName) - 1] = '\0';
      }
      if (fileOutName != NULL)
      {
        fileOutName[strlen(fileOutName) - 1] = '\0';
      }

      fileIn = fopen(fileInName, "r");
      fileOut = fopen(fileOutName, "w+");
      size_t word_length;
      char *mdp = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
      table *hash_table;
      filter *f = create_filter(m, k);
      hash_table = create_table(m);

      while (fscanf(fileIn, "%s ", mdp) != -1)
      {

        word_length = strlen(mdp);
        if (word_length == 4 || word_length == 5)
        {
          add_filter(f, mdp);
          add_occ_table(hash_table, mdp);
        }
      }

      int yes = 0, maybe = 0, falseP = 0, no = 0;
      float n = 0.0;
      fclose(fileIn);
      fileInName = readline("file input name :");
      if (fileInName != NULL)
      {
        fileInName[strlen(fileInName) - 1] = '\0';
      }
      fileIn = fopen(fileInName, "r");

      fileOut = fopen(fileOutName, "w+");

      int i;

      free(mdp);

      while (fscanf(fileIn, "%s ", mdp) != -1)
      {
        n++;

        if (is_member_filter(f, mdp))
        {

          if (find(hash_table, mdp))
          {
            fprintf(fileOut, "%s:  yes\n", mdp);
            yes++;
          }
          else
          {
            fprintf(fileOut, "%s:  False positive\n", mdp);
            falseP++;
          }

          maybe++;
        }
        else
        {
          fprintf(fileOut, "%s:  non\n", mdp);
          no++;
        }
      }

      printf(" maybes : %d   no : %d,   false positives :  %d ,  percentage of false positive : %f \n",
             maybe, no, falseP, (float)(falseP * 100.0) / n);

      free(line);
      free_filter(f);
    }
    putchar('\n');
  }
  if (launched)
  {
    char *mdp = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
    filter *f = create_filter(m, k);
    while (fscanf(fin, "%s ", mdp) != -1)
    {
      add_filter(f, mdp);
    }

    free(mdp);
    printf("Filter display: \n");
    print_filter(f);
    putchar('\n');
    fclose(fin);

    printf(" -If you want to check if a password might be in the database or not, type it below :\n");
    printf(" -To quit the program , type 'q'.\n");

    while (line[0] != 'q')
    {
      line = readline(">>>");
      if (is_member_filter(f, line))
      {
        printf("%s is maybe in the database   (MAYBE).\n", line);
      }
      else
      {
        printf("%s is not in the database     (NO)\n", line);
      }

      free(line);
    }

    free_filter(f);
  }

  /*
  while((line = readline (">>>"))){
    add_history(line);
    printf("%s\n", line);
    if (strcmp("quit", line) == 0)
      break;
    free(line);
  }
  clear_history();*/

  return 0;
}
