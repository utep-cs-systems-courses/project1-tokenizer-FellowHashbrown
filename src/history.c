#include <stdio.h>
#include <stdlib.h>
#include "history.h"

/* Initialize the linked list to keep the history */
List *init_history()
{
  List *history = malloc(sizeof(List));
  history->root = malloc(sizeof(Item));
  return history;
}

/* Add a history item to the end of the list.
   List *list - the linked list
   char *str - the string to store
*/
void add_history(List *list, char *str)
{

  // Find the next empty node to insert the string into
  Item *temp = list->root;
  int id = 1;
  while(temp->next != NULL) {
    temp = temp->next;
    id++;
  }

  // Call malloc to create memory for the next empty node
  temp->next = malloc(sizeof(Item));
  temp->next->str = str;
  temp->next->id = id;
}

/* Retrieve the string stored in the node where Item->id == id.
   List *list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id)
{
  Item *temp = list->root;

  while(temp != NULL) {
    if (temp->id == id) { return temp->str; }
    temp = temp->next;
  }
  
  return "Not Found";
}

/* Print the entire contents of the list. */
void print_history(List *list)
{
  Item *temp = list->root;
  while(temp != NULL) {
    printf("#%d = %s\n", temp->id, temp->str);
    temp = temp->next;
  }
}

/* A recursive helper method to back track through the linked list
 */
void free_root_recursive(Item *root) {
  if (root == NULL) {
    return;
  } else {
    free_root_recursive(root->next);
    free(root->next); free(root->str);
  }
}

/* Free the history list and the strings it references. */
void free_history(List *list)
{
  free_root_recursive(list->root);
  free(list);
}
