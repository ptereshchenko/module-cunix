#include "../include/binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

node_t *allocnode()
{
    node_t *tree;
    tree = (node_t*)malloc(sizeof(node_t));
    tree->data = NULL;
    tree->key = NULL;
    tree->left = NULL;
    tree->right = NULL;
    return (tree);
}

node_t *insert(node_t *root, char *key, void *data)
{
    if (root == NULL)
    {
       root = allocnode();
       root->key = key;
       root->data = data;
    }
    else if (root->key < key)
       root->left = insert(root->left, key, data);
    else
       root->right = insert(root->right, key, data);
    return (root);
}

void print_node(node_t *node)
{
    if (node == NULL)
    return;
    printf("%s:  %s ", node->data,(char*)node->key);
}

void    visit_tree(node_t *node, void (*fp)(node_t *root))
{
    if (node)
      fp(node);
    if (node->left)
      visit_tree(node->left, fp);
    if (node->right)
      visit_tree(node->right, fp);
}

void destroy_tree(node_t *node, void (*fdestroy)(node_t *root))
{
    if(node == NULL)
    return;
    destroy_tree(node->left,fdestroy);
    destroy_tree(node->right,fdestroy);
    fdestroy(node);
    free(node);
}
