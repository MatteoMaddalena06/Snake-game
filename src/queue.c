#include "header/queue.h"

iqueue create_queue(void)
{
    iqueue new_queue;

    new_queue.dim = 0;
    new_queue.head = new_queue.tail = NULL;

    return new_queue;
}

void delete_queue(iqueue* queue)
{
    if(!queue->dim)
      return;

    queue->tail = queue->head->next;

    while(queue->head != NULL)
    {
        free(queue->head);
        queue->head = queue->tail;

        if(queue->tail != NULL)
          queue->tail = queue->tail->next;
    }

    queue->dim = 0;
}

void add_el(iqueue* queue, int val1, int val2)
{
    queue->dim++;

    if(queue->dim != 1)
    {
        queue->tail->next = (queue_el*)malloc(sizeof(queue_el));
        queue->tail = queue->tail->next;
    }
    else
      queue->tail = queue->head = (queue_el*)malloc(sizeof(queue_el));

    queue->tail->direction = val1;
    queue->tail->next = NULL;
    queue->tail->times = val2;
}

void rem_el(iqueue* queue)
{
    queue_el* tmp_ptr = queue->head;

    if(!queue->dim)
      return;

    if(queue->dim == 1)
      queue->tail = NULL;

    queue->head = queue->head->next;
    free(tmp_ptr);
    queue->dim--;
}
