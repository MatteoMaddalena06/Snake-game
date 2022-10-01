#include "header/field.h"

ifield alloc_field(int row, int col)
{
    ifield new_field;

    new_field.row = row;
    new_field.col = col;

    new_field.field = (char**)malloc(row * sizeof(char*));

    for(int i = 0; i < new_field.row; i++)
      new_field.field[i] = (char*)malloc(col * sizeof(char));

    return new_field;
}

void dealloc_field(ifield field)
{
    for(int i = 0; i < field.row; i++)
      free(field.field[i]);

    free(field.field);
    field.row = field.col = 0;
}

void init_field(ifield field)
{
    for(int i = 0; i < field.row; i++)
    {
        for(int j = 0; j < field.col; j++)
        {
           if(!i && !j || !i && j == field.col-1 || !j && i == field.row-1 \
              || i == field.row-1 && j == field.col-1)
              field.field[i][j] = 0x2B;

           else if(!i || i == field.row - 1)
              field.field[i][j] = 0x2D;

           else if(!j || j == field.col - 1)
              field.field[i][j] = 0x7C;

           else
             field.field[i][j] = EMPTY_CELL;
        }
    }

    field.field[1][1] = field.field[1][2] = BODY_CELL;
    field.field[1][4] = APPLE_CELL;
}

void print_field(ifield field)
{
    CLRSCRN

    for(int i = 0; i < field.row; i++)
    {
        for(int j = 0; j < field.col; j++)
          printf("%c", field.field[i][j]);

        printf("\n");
    }
}
