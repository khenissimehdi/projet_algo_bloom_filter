#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

#define MAX_WORD_LENGTH 80
table *tab;

link *add_occurrence(link *lnk)
{
  lnk->occurrences++;
  return lnk;
}

unsigned
hash2(char *elt)
{
  int i;
  unsigned h;
  h = 0;
  for (i = 0; elt[i] != '\0'; i++)
  {
    h = 31 * h + elt[i];
  }
  return h;
}

unsigned hashFunc(char *elt, int M)
{
  int i;
  unsigned h;

  h = 0;

  for (i = 0; elt[i] != '\0'; i++)
  {
    h += ((i + 1) * elt[i]);
  }
  unsigned a = h % M;

  return a;
}

int find(table *tab, char word[])
{
  unsigned hash_index = hashFunc(word, tab->M);
  return find_list(tab->bucket[hash_index], word) != NULL;
}

void add_occ_table(table *tab, char word[])
{
  link *lst;
  unsigned hash_index = hashFunc(word, tab->M);
  lst = find_list(tab->bucket[hash_index], word);
  if (lst == NULL)
    tab->bucket[hash_index] = insert_first_list(tab->bucket[hash_index], word);
  else
    add_occurrence(lst);
  tab->size++;
}

/**
 * Create a link representing 1 occurence of the string 'word'.
 * The string is copied and must be freed when the link is freed.
 */
link *create_link(char word[])
{
  link *lnk = malloc(sizeof(link));
  lnk->word = malloc(strlen(word) + 1);
  strcpy(lnk->word, word);
  lnk->occurrences = NULL;
  lnk->next = NULL;
  return lnk;
}
olink *create_olink(int pos)
{
  olink *occurence = malloc(sizeof(olink));
  occurence->next = NULL;
  occurence->pos = pos;
  return occurence;
}

void free_link(link *lnk)
{
  free(lnk->word);
  free(lnk);
}

void display_list(link *lst)
{
  while (lst)
  {

    if (lst->occurrences != NULL)
    {

      olink *current = lst->occurrences;
      printf("%s : ", lst->word);

      while (current != NULL)
      {
        if (current->next != NULL)
        {
          printf("%d ,", current->pos);
        }
        else
        {
          printf("%d ", current->pos);
        }

        current = current->next;
      }
      putchar('\n');
    }
    else
    {
      printf("%s : %d\n", lst->word, 0);
    }

    lst = lst->next;
  }
}
table *create_table(int M)
{
  table *newTable = malloc(sizeof(table));
  newTable->bucket = malloc(sizeof(link *) * M);
  newTable->M = M;
  newTable->size = 0;
  int i;
  for (i = 0; i <= M; i++)
  {
    newTable->bucket[i] = NULL;
  }
  return newTable;
}
void free_list(link *lst)
{
  while (lst)
  {
    link *tmp = lst;
    lst = lst->next;
    free_link(tmp);
  }
}

int equal(char *w1, char *w2)
{
  return strcmp(w1, w2) == 0;
}

link *find_list(link *lst, char word[])
{
  link *ptr = lst;
  while (ptr != NULL && !equal(ptr->word, word))
    ptr = ptr->next;
  return ptr;
}
/* Old*/
link *insert_first_listOld(link *lst, char word[], int pos)
{
  link *tmp = create_link(word);
  tmp->occurrences = create_olink(pos);
  tmp->next = lst;

  return tmp;
}

/*New*/

link *insert_first_list(link *lst, char word[])
{
  link *tmp = create_link(word);
  tmp->next = lst;
  return tmp;
}
