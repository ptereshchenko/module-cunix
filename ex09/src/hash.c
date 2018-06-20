#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../include/hash.h"
#include "linked_list.h"


hashtable_t *hash_create(unsigned int size)
{
  hashtable_t *new_table;
  if (size < 1)
    return NULL;
  new_table = malloc(sizeof(hashtable_t));
  new_table->table = malloc(size*sizeof(node_t*));
  for(unsigned int i = 0; i < size; i++)
     new_table->table[i] = NULL;
  new_table->size = size;
  return new_table;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data))
{
  for(unsigned int i = 0; i < ht->size;i++) {
    if( ht->table[i] != NULL) {
      node_t  *ptr = ht->table[i];
      list_destroy(&(ptr),fp);
    }
  }
  free(ht->table);
  free(ht);
}

unsigned int  hash_func(char *key)
{
    if (key == NULL)
    return 0;
    unsigned int res = 0;
    while(*key != '\0')
    {  res += *key;
       key++;
    }
    return res;
}

void    hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data))
{
  unsigned int i;
  i = hash_func(key) % ht->size;
  if (!ht->table[i])
    ht->table[i] = list_create(ptr);
  else
    list_push(ht->table[i], ptr);
  fp(key);
}

void   *hash_get(hashtable_t *ht, char *key)
{
  unsigned int i;
  i = hash_func(key) % ht->size;

  node_t *node = ht->table[i];
  if (node)
    return (node->data);
  else
    return (NULL);
}


