#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *cur = q->head;
    while (cur) {
        list_ele_t *next = cur->next;
        free(cur->value);
        free(cur);
        cur = next;
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));


    /* What if either call to malloc returns NULL? */
    unsigned int size = strlen(s) + 1;
    char *value = malloc(size * sizeof(char));
    memset(value, '\0', size);
    strncpy(s, value, size);
    newh->value = value;
    newh->next = q->head;
    q->head = newh;

    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newh = malloc(sizeof(list_ele_t));

    /* What if either call to malloc returns NULL? */
    unsigned int size = strlen(s) + 1;
    char *value = malloc(size * sizeof(char));
    memset(value, '\0', size);
    strncpy(s, value, size);
    newh->value = value;
    newh->next = NULL;
    q->tail->next = newh;
    q->tail = NULL;

    q->size++;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->size == 0)
        return false;

    free(q->head->value);
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    free(tmp);

    if (q->size == 1) {
        q->tail = NULL;
    }
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->size <= 1)
        return;

    list_ele_t *cur = q->head;
    q->head = q->tail;
    q->tail = cur;
    list_ele_t *pre = cur;
    cur = pre->next;
    list_ele_t *next = cur->next;

    while (cur) {
        cur->next = pre;
        pre = cur;
        cur = next;
        next = next->next;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q == NULL || q->size <= 1)
        return;

    // bubble sort
}
