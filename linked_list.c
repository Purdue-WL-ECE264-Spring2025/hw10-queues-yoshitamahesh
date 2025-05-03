#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node * newNode = calloc(1, sizeof(struct list_node));
   newNode -> value = value;

   return newNode;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *newNode = new_node(value);
  newNode -> next = list -> head;
  list -> head = newNode;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *last = list -> head;
  if(last == NULL) {
    last = new_node(value);
    return;
  }

  while (last -> next != NULL) {
    last = last -> next;
  }

  last -> next = new_node(value);
}

size_t remove_from_head(struct linked_list *list) { 
  struct list_node * toDelete = list -> head;
  if (list -> head == NULL) {
    return 0;
  }
  
  
  size_t val = list -> head -> value;
  list -> head = list-> head -> next;
  free(toDelete);

  return val; 
}

size_t remove_from_tail(struct linked_list *list) {
struct list_node * toDelete = list -> head;
struct list_node * prev = NULL;

if (list -> head == NULL) {
  return 0;
}

if (toDelete -> next == NULL) {
  return remove_from_head(list);
}

while (toDelete -> next != NULL) {
  prev = toDelete;
  toDelete = toDelete -> next;
}

size_t val = toDelete -> value;
prev -> next = NULL;
free(toDelete);

return val;
}

void free_list(struct linked_list list) {

  while (list.head != NULL) {
    remove_from_head(&list);
  }

}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
