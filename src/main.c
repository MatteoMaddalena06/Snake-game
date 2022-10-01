#include "header/snake.h"
#include <stdio.h>

int end_game = 0;
sem_t sync_var;
pthread_t thread[2];

int main(int argv, char** argc)
{
    isnake snake;

    if(argv < 3 || argv > 3)
    {
        printf("Usage: ./snake <row> <col>.\n");
        return -1;
    }

    if(char2int(argc[1]) < 0 || char2int(argc[2]) < 0)
    {
        printf("Invalid format.\n");
        return -1;
    }

    if(char2int(argc[1]) < 5 || char2int(argc[2]) < 5)
    {
        printf("Invalid array size. Minimum size: 5x5.\n");
        return -1;
    }

    snake = init_game(char2int(argc[1]) + 2, char2int(argc[2]) + 2);

    pthread_create(thread, NULL, keyboard_reader, (void*)&snake);
    pthread_create(thread + 1, NULL, screen_updater, (void*)&snake);

    pthread_join(thread[1], NULL);

    exit_game(snake);

    return 0;
}
