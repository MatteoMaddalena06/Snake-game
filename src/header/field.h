#ifndef FIELD_H
#define FIELD_H

#define BODY_CELL  0x4F
#define APPLE_CELL 0x23
#define EMPTY_CELL 0x20
#define CLRSCRN          printf("\e[1;1H\e[2J");

#include <stdio.h>
#include <stdlib.h>

typedef struct field_info
{
    int row, col;
    char** field;

} ifield;

ifield alloc_field(int, int);
void   dealloc_field(ifield);
void   init_field(ifield);
void   print_field(ifield);

#endif
