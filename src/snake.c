#include "header/snake.h"

void* keyboard_reader(void* snake)
{
    char input;

    while(1)
    {
        sem_wait(&sync_var);

        if(end_game)
        {
           pthread_join(thread[1], NULL);
           pthread_exit(0);
        }

        sem_post(&sync_var);

        scanf("%c", &input);

        sem_wait(&sync_var);

        switch(input)
        {
            case 0x77: ((isnake*)snake)->curr_move = MOVE_UP;    break;
            case 0x61: ((isnake*)snake)->curr_move = MOVE_LEFT;  break;
            case 0x73: ((isnake*)snake)->curr_move = MOVE_DOWN;  break;
            case 0x64: ((isnake*)snake)->curr_move = MOVE_RIGHT; break;
            case 0x7A:
              ((isnake*)snake)->curr_move = END_GAME;
              sem_post(&sync_var);
              pthread_join(thread[1], NULL);
              pthread_exit(0);
        }

        sem_post(&sync_var);
    }
}

void* screen_updater(void* snake)
{
    char input;

    while(1)
    {
        sem_wait(&sync_var);

        if(((isnake*)snake)->curr_move == END_GAME)
          pthread_exit(0);

        if(end_game = move_snake((isnake*)snake))
        {
           sem_post(&sync_var);
           pthread_exit(0);
        }

        print_field(((isnake*)snake)->field);

        sem_post(&sync_var);
        usleep(75500);
    }
}

int move_snake(isnake* snake)
{
    int sum_times = 0;
    queue_el* ptr;

    if(snake->prev_move != snake->curr_move)
    {
        if(~(snake->prev_move) != snake->curr_move)
        {
            ptr = snake->move_queue.head;

            while(ptr != NULL)
            {
                sum_times += ptr->times;
                ptr = ptr->next;
            }

           add_el(&snake->move_queue, snake->prev_move, snake->dim - sum_times - 1);
        }
        else
          snake->curr_move = snake->prev_move;
    }

    if(snake->move_queue.dim)
    {
       snake->prev_move = snake->move_queue.head->direction;
       snake->move_queue.head->times--;
    }

    if(update_position(snake))
      return 1;

    if(snake->move_queue.dim && !snake->move_queue.head->times)
      rem_el(&snake->move_queue);

    snake->prev_move = snake->curr_move;

    return 0;
}

int update_position(isnake* snake)
{
    switch(snake->curr_move)
    {
        case MOVE_RIGHT: snake->headx++; break;
        case MOVE_LEFT:  snake->headx--; break;
        case MOVE_DOWN:  snake->heady++; break;
        case MOVE_UP:    snake->heady--; break;
    }

    if(snake->headx >= snake->field.col - 1|| snake->headx <= 0)
      return 1;

    if(snake->heady >= snake->field.row - 1|| snake->heady <= 0)
      return 1;

    if(snake->field.field[snake->heady][snake->headx] == BODY_CELL)
      return 1;

    if(snake->headx != snake->applex || snake->heady != snake->appley)
    {
        snake->field.field[snake->taily][snake->tailx] = EMPTY_CELL;

        switch(snake->prev_move)
        {
            case MOVE_RIGHT: snake->tailx++; break;
            case MOVE_LEFT:  snake->tailx--; break;
            case MOVE_DOWN:  snake->taily++; break;
            case MOVE_UP:    snake->taily--; break;
        }
    }
    else
    {
       if(snake->move_queue.dim)
         snake->move_queue.head->times++;

       snake->dim++;
       generate(snake);
       snake->field.field[snake->appley][snake->applex] = APPLE_CELL;
    }

    snake->field.field[snake->heady][snake->headx] = BODY_CELL;

    return 0;
}

void generate(isnake* snake)
{
    do
    {
        snake->applex = rand()%(snake->field.col - 2) + 1;
        snake->appley = rand()%(snake->field.row - 2) + 1;
    }
    while(snake->field.field[snake->appley][snake->applex] == BODY_CELL);
}

isnake init_game(int row, int col)
{
    isnake snake;

    snake.dim = 2;
    snake.tailx = snake.taily = snake.heady = snake.appley = 1;
    snake.headx = 2;
    snake.applex = 4;
    snake.prev_move = snake.curr_move = MOVE_RIGHT;
    snake.field = alloc_field(row, col);
    snake.move_queue = create_queue();
    init_field(snake.field);
    set_screen();
    sem_init(&sync_var, 0, 1);

    return snake;
}

void exit_game(isnake snake)
{
    delete_queue(&snake.move_queue);
    dealloc_field(snake.field);
    reset_screen();
    sem_close(&sync_var);
}
