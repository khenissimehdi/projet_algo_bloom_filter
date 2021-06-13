#ifndef TREE_H
#define TREE_H

typedef struct _node
{
    char *data;          /* data stored : an integer    */
    struct _node *left;  /* pointer to the left child   */
    struct _node *right; /* pointer to the right child  */
} node;

/*
 * Allocate memory for a new node.
 */
node *create_node(char *data);

void parcours_prefixe(node *t);
int count_nodes(node *t);
int count_leaves(node *t);
int count_only_children(node *t);
void parcours_infixe(node *t);
void parcours_suffixe(node *t);
int height(node *t);
node *scan_tree(void);
void free_tree(node *t);
node *find_bst(node *t, char *elt);
node *insert_bst(node *t, char *elt);
node *treeGen(node *t, int number);
node *remove_bst(node *t, int elt);
int equal(char *s1, char *s2);
int less(char *s1, char *s2);

#endif /* TREE_H */
