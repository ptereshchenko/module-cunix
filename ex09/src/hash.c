#include "../include/hash.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../ex07/include/linked_list.h"
/*
typedef struct  node {
    void        *data;
    struct node *next;
}              node_t;

node_t  *list_create(void *data)
 {
   node_t *head = (node_t *) malloc(sizeof(node_t));
   head->data = data;
   head->next = NULL;
   return head;
 }

void    list_destroy(node_t **head, void (*fp)(void *data))
 {
  if(*head == NULL)
         return;
     fp((*head)->data);
     list_destroy(&(*head)->next, fp);
     free(*head);
 }
 void list_push(node_t *head, void *data)
{
   if (!head) {
      head = list_create(data);
      return;
   }
 node_t *tmp = head;
   while (tmp->next) tmp = tmp->next;
   tmp->next = list_create(data);
 }
*/
hashtable_t *hash_create(unsigned int size)
{
  hashtable_t *new_table;
  if (size < 1)
    return NULL;
  new_table = malloc(sizeof(hashtable_t));
  new_table->table = malloc(size*sizeof(node_t*));
  for(int i = 0; i < size; i++)
     new_table->table[i] = NULL;
  new_table->size = size;
  return new_table;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data))
{
  for(int i = 0; i < ht->size;i++) {
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
  int i;
  i = hash_func(key) % ht->size;

  node_t *node = ht->table[i];
  if (node)
    return (node->data);
  else
    return (NULL);
}
