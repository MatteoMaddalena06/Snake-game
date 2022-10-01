#ifndef SNAKE_H
#define SNAKE_H

#define MOVE_LEFT    0x0
#define MOVE_RIGHT   0xFFFFFFFF
#define MOVE_DOWN    0x1
#define MOVE_UP      0xFFFFFFFE
#define TAIL         0x0
#define HEAD         0x1
#define END_GAME     0x2

#include "field.h"
#include "queue.h"
#include "utils.h"
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

extern int end_game;
extern sem_t sync_var;
extern pthread_t thread[2];

typedef struct snake_info
{
    int              headx, heady;
    int              tailx, taily;
    int              applex, appley;
    unsigned int     curr_move, prev_move;
    int              dim;
    iqueue           move_queue;
    ifield           field;

} isnake;

isnake init_game(int, int);
void   exit_game(isnake);
void*  keyboard_reader(void*);
void*  screen_updater(void*);
int    move_snake(isnake*);
int    update_position(isnake*);
void   generate(isnake*);

#endif
