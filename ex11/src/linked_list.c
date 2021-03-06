#include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
  #include <unistd.h>
  #include <stddef.h>
  #include <fcntl.h>
  #include "../include/linked_list.h"
 
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
 
  void list_push(node_t *head, void *data) {
    if (!head) {
       head = list_create(data);
       return;
    }
  node_t *tmp = head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = list_create(data);
  }
 
  void list_unshift(node_t **head, void *data)
  {
    node_t * new_node = malloc(sizeof(node_t));
    new_node->next = *head;
    new_node->data = data;
    *head = new_node;
  }
 
  void *list_pop(node_t **head)
  {
    node_t *tmp  = *head;
    while(tmp->next->next != NULL)
    tmp = tmp->next;
    free(tmp->next->data);
    free(tmp->next);
    tmp->next = NULL;
  }
void    *list_shift(node_t **head)
  {
    node_t *tmp  = *head;
    *head = tmp->next;
    free(tmp->data);
    free(tmp);
  }
  void   *list_remove(node_t **head, int pos)
  {
      if (pos == 1)
      return list_shift(head);
      node_t *cur_elem = *head;
      int i = 0;
      while (i < pos)
      {
        cur_elem = cur_elem->next;
        i++;
      }
      node_t *tmp = cur_elem->next;
      cur_elem->next = tmp->next;
      free(tmp);
  }
  void    *list_rem(node_t *head, void *data)
  {
      node_t *cur_elem = head;
      int i = 1;
      while (strcmp(cur_elem->data,data) != 0) {
          cur_elem = cur_elem->next;
          i++;
      }
 
      list_remove(&(head), i);
 
  }
  void list_print(node_t *head) {
    for (node_t* tmp = head; tmp; tmp = tmp->next)
        printf("%s ", tmp->data);
  }
 
  void    list_visitor(node_t *head, void (*fp)(void *data))
  {
   node_t *cur_elem = head;
   while (cur_elem->next != NULL)
   {
     fp(cur_elem->data);
     cur_elem = cur_elem->next;
   }
  }

