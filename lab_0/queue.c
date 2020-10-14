/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) return NULL;
    q->head = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q->head == NULL) return;
    /* How about freeing the list elements and the strings? */
    list_ele_t *temp = q->head;
    while (temp->next != NULL) {
        free(temp->value);
        list_ele_t *previous = temp;
        temp = temp->next;
        free(previous);
    }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) return false;
    
    /* Make a new node */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) return false;
    
    /* Point node value to new char array, and copy over input char array. */
    newh->value = malloc(strlen(s) * sizeof(char));
    if (newh->value == NULL) return false;
    strcpy(newh->value, s);
    
    /* If q has head, put it after the new node */
    if (q->head != NULL) {
        newh->next = q->head;
    }
    
    /* Set new node to head of q */
    q->head = newh;
    
    q->size++;
    
    list_ele_t *temp = q->head;
    for (int i = 0; i < q->size; i++) {
        temp = temp->next;
    }
    q->tail = temp;
    
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || s == NULL) return false;
    
    /* Make a new node */
    list_ele_t *newNode = malloc(sizeof(list_ele_t));
    if (newNode == NULL) return false;
    
    /* Point node value to new char array, and copy over input char array. */
    newNode->value = malloc(strlen(s) * sizeof(char));
    if (newNode->value == NULL) return false;
    strcpy(newNode->value, s);
    
    if (q->tail == NULL) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL) return false;
    
    if (sp != NULL) {
        strncpy(sp, q->head->value, (bufsize-2));
        sp[(bufsize-1)] = '\0';
    }
    
    free(q->head->value);
    list_ele_t *temp = q->head;
    q->head = q->head->next;
    free(temp);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL) return;
    q->tail = q->head;
    
    list_ele_t *previous = NULL;
    list_ele_t *current = q->head;
    list_ele_t *next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    q->head = previous;
    
    
}

