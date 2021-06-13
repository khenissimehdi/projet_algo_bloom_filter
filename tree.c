#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

void parcours_prefixe(node *t)
{
  if (t == NULL)
    return;
  printf("%s ", t->data);
  parcours_prefixe(t->left);
  parcours_prefixe(t->right);
}

void parcours_infixe(node *t)
{
  if (t == NULL)
    return;

  parcours_infixe(t->left);
  printf("%s ", t->data);
  parcours_infixe(t->right);
}
void parcours_suffixe(node *t)
{
  if (t == NULL)
    return;
  parcours_suffixe(t->left);
  parcours_suffixe(t->right);
  printf("%s ", t->data);
}

node *scan_tree(void)
{
  char *input;
  node *tree = NULL;
  scanf("%s", &input);

  if (input == 0)
  {
    return NULL;
  }

  tree = create_node(input);

  tree->left = scan_tree();
  tree->right = scan_tree();
  return tree;
}
int count_nodes(node *t)
{
  if (t == NULL)
    return 0;
  return count_nodes(t->left) + count_nodes(t->right) + 1;
}

int count_leaves(node *t)
{
  if (t == NULL)
    return 0;

  if (t->left == NULL && t->right == NULL)
  {
    return 1;
  }
  return count_leaves(t->left) + count_leaves(t->right);
}
int count_only_children(node *t)
{

  if (t == NULL)
    return 0;

  if (t->left == NULL || t->right == NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      return 0;
    }
    if (t->left != NULL)
    {
      return count_only_children(t->left) + 1;
    }
    if (t->right != NULL)
    {
      return count_only_children(t->right) + 1;
    }
  }
  return count_only_children(t->left) + count_only_children(t->right);
}
int height(node *t)
{

  if (t == NULL)
    return 0;
  else
  {

    int left = height(t->left);
    int right = height(t->right);

    if (left > right)
    {
      return (left + 1);
    }

    else
    {
      return (right + 1);
    }
  }
}
void free_tree(node *t)
{
  if (t == NULL)
    return;

  free_tree(t->left);
  free_tree(t->right);
  free(t->data);
  free(t);
}
int equal(char *s1, char *s2)
{
  return strcmp(s1, s2) == 0;
}

int less(char *s1, char *s2)
{
  return strcmp(s1, s2) < 0;
}

node *create_node(char *word)
{
  node *new_node = (node *)malloc(sizeof(node));
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->data = (char *)malloc((strlen(word) + 1) * sizeof(char));
  strcpy(new_node->data, word);
  return new_node;
}

node *find_bst(node *t, char *elt)
{
  node *tmp = t;
  while (tmp != NULL && !equal(tmp->data, elt))
  {

    if (!less(tmp->data, elt))
    {
      tmp = tmp->left;
    }
    else
    {
      tmp = tmp->right;
    }
  }
  return tmp;
}

node *insert_bst(node *t, char *elt)
{
  if (t == NULL)
  {
    t = create_node(elt);
    return t;
  }
  if (equal(elt, t->data))
    return t;
  else if (!less(t->data, elt))
  {
    t->left = insert_bst(t->left, elt);
  }
  else if (less(t->data, elt))
  {
    t->right = insert_bst(t->right, elt);
  }

  return t;
}

node *treeGen(node *t, int number)
{

  int i;
  t = NULL;
  srand(time(NULL));

  for (i = 0; i < number; i++)
  {

    int r = rand() % number + 1;

    t = insert_bst(t, r);
  }

  return t;
}

node *extract_min_bst(node *t, node **min)
{
  if (t == NULL)
    *min = NULL;
  else if (t->left != NULL)
  {
    t->left = extract_min_bst(t->left, min);
  }
  else
  {
    node *to_extract = t;
    t = t->right;
    *min = to_extract;
  }
  return t;
}

node *remove_bst(node *t, int elt)
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (t->data > elt)
  {
    t->left = remove_bst(t->left, elt);
  }
  else if (t->data < elt)
  {
    t->right = remove_bst(t->right, elt);
  }
  else
  {
    node *left = t->left;
    node *right = t->right;
    free(t);
    if (right == NULL)
    {
      return left;
    }
    if (left == NULL)
    {
      return right;
    }
    node *tmp;
    right = extract_min_bst(right, &tmp);
    t = tmp;
    t->left = left;
    t->right = right;
  }
  return t;
}
