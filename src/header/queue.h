#ifndef QUEUE_H
#define QUEUE_H

#define CLRSCRN          printf("\e[1;1H\e[2J");

#include <stdio.h>
#include <stdlib.h>

typedef struct queue_node
{
    unsigned int direction;
    int times;
    struct queue_node *next;

} queue_el;

typedef struct queue_info
{
    int dim;
    queue_el *head, *tail;

} iqueue;

iqueue create_queue(void);
void   delete_queue(iqueue*);
void   add_el(iqueue*, int, int);
void   rem_el(iqueue*);

#endif
