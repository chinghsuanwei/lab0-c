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

    if (q == NULL)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}
/*
void q_dump(queue_t *q)
{
    if (q == NULL)
        return;

    list_ele_t *cur = q->head;
    printf("[");
    while (cur != NULL) {
        printf("%s, ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}
*/

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;

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
    if (q == NULL)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL)
        return false;

    unsigned int size = strlen(s) + 1;
    char *value = malloc(size * sizeof(char));

    if (value == NULL) {
        free(newh);
        return false;
    }

    memset(value, '\0', size);
    strncpy(value, s, size);
    newh->value = value;
    newh->next = q->head;

    q->head = newh;
    if (q->size == 0) {
        q->tail = newh;
    }

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
    if (q == NULL)
        return false;

    list_ele_t *newh = malloc(sizeof(list_ele_t));

    if (newh == NULL)
        return false;

    unsigned int size = strlen(s) + 1;
    char *value = malloc(size * sizeof(char));

    if (value == NULL) {
        free(newh);
        return false;
    }

    memset(value, '\0', size);
    strncpy(value, s, size);
    newh->value = value;
    newh->next = NULL;

    if (q->size == 0) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
    }

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
    if (q == NULL || q->size == 0)
        return false;

    list_ele_t *node = q->head;

    if (sp != NULL) {
        unsigned int size = strlen(node->value);
        unsigned int min = size < bufsize - 1 ? size : bufsize - 1;
        strncpy(sp, node->value, min);
        sp[min] = '\0';
    }

    free(node->value);
    q->head = node->next;
    free(node);

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
    pre->next = NULL;

    do {
        list_ele_t *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    } while (cur);
}

/*
void q_insertion_sort(queue_t *q)
{
    // insertion sort
    list_ele_t **cur_head = &q->head;

    // For q->head
    list_ele_t *min_pre_node = q->head;
    list_ele_t *min_node = min_pre_node->next;

    for (int i = 1; i < q->size; i++) {
        list_ele_t *pre = *(cur_head);
        list_ele_t *cur = pre->next;
        list_ele_t *min_pre_node = pre;
        list_ele_t *min_node = min_pre_node->next;
        bool changed = false;
        char *value = pre->value;
        do {
            if (strcmp(value, min_node->value) > 0) {
                min_node = cur;
                min_pre_node = pre;
                changed = true;
            }
            pre = cur;
            cur = cur->next;
        } while (cur);

        printf("%s\n", min_node->value);
        if (changed) {
            min_pre_node->next = min_node->next;
            min_node->next = (*cur_head)->next;
            (*cur_head)->next = min_node;
            cur_head = &min_node;
        } else {
            cur_head = &min_node;
        }
    }
}
*/

void q_bubble_sort(queue_t *q)
{
    for (int i = 1; i < q->size; i++) {
        list_ele_t **pre_next = &q->head;
        list_ele_t *cur = q->head;
        list_ele_t *next = cur->next;
        for (int j = i; j < q->size; j++) {
            if (strcmp(cur->value, next->value) > 0) {
                (*pre_next) = next;
                cur->next = next->next;
                next->next = cur;
                pre_next = &next->next;

                next = cur->next;
            } else {
                pre_next = &cur->next;
                cur = next;
                next = cur->next;
            }
        }
    }

    list_ele_t *cur = q->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    q->tail = cur;
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
    // q_insertion_sort(q);
    q_bubble_sort(q);
}
