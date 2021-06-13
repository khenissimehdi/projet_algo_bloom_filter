#include "bitarray.h"
#include "time.h"
#include "filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "tree.h"
#define MAX_WORD_LENGTH 80
char *fileInName;
char *fileOutName;
int main(int argc, char *argv[])
{

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
    printf(" - Run stats bloom using b \n");
    printf(" - Run stats tree using  t \n");
    printf(" - Run stats hash table using  h \n");
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

    else if (line[0] == 't')
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
      node *node = NULL;
      clock_t treeT;
      treeT = clock();

      while (fscanf(fileIn, "%s ", mdp) != -1)
      {

        word_length = strlen(mdp);
        if (word_length == 4 || word_length == 5)
        {
          node = insert_bst(node, mdp);
        }
      }

      int yes = 0, no = 0;

      fclose(fileIn);
      fileInName = readline("file input name :");
      if (fileInName != NULL)
      {
        fileInName[strlen(fileInName) - 1] = '\0';
      }

      free(mdp);
      fileIn = fopen(fileInName, "r");
      fileOut = fopen(fileOutName, "w+");

      while (fscanf(fileIn, "%s ", mdp) != -1)
      {

        if (find_bst(node, mdp))
        {
          fprintf(fileOut, "%s:  yes\n", mdp);
          yes++;
        }
        else
        {
          fprintf(fileOut, "%s:  non\n", mdp);
          no++;
        }
      }
      treeT = clock() - treeT;
      double time_takenTree = ((double)treeT) / CLOCKS_PER_SEC;

      printf(" yes : %d   no : %d,  time : %f\n", yes, no, time_takenTree);

      free(line);
      free_tree(node);
    }

    else if (line[0] == 'h')
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

      hash_table = create_table(m);
      clock_t hashT;
      hashT = clock();

      while (fscanf(fileIn, "%s ", mdp) != -1)
      {

        word_length = strlen(mdp);
        if (word_length == 4 || word_length == 5)
        {
          add_occ_table(hash_table, mdp);
        }
      }

      int yes = 0, no = 0;

      fclose(fileIn);
      fileInName = readline("file input name :");
      if (fileInName != NULL)
      {
        fileInName[strlen(fileInName) - 1] = '\0';
      }
      fileIn = fopen(fileInName, "r");

      fileOut = fopen(fileOutName, "w+");

      free(mdp);

      while (fscanf(fileIn, "%s ", mdp) != -1)
      {

        if (find(hash_table, mdp))
        {
          fprintf(fileOut, "%s:  yes\n", mdp);
          yes++;
        }
        else
        {
          fprintf(fileOut, "%s:  no\n", mdp);
          no++;
        }
      }
      hashT = clock() - hashT;
      double time_takenHash = ((double)hashT) / CLOCKS_PER_SEC;
      printf(" yes : %d   no : %d  tile : %f \n", yes, no, time_takenHash);
      int i;
      for (i = 0; i < hash_table->M; i++)
      {
        if (hash_table->bucket[i] != NULL)
        {
          free_list(hash_table->bucket[i]);
        }
      }

      free(line);
    }
    else if (line[0] == 'b')
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
      clock_t Bloom;
      Bloom = clock();

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
      Bloom = clock() - Bloom;
      double time_takenBloom = ((double)Bloom) / CLOCKS_PER_SEC;

      printf(" maybes : %d   no : %d,   false positives :  %d ,  percentage of false positive : %f  time : %f\n",
             maybe, no, falseP, (float)(falseP * 100.0) / n, time_takenBloom);

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
