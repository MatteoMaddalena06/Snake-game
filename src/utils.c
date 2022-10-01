#include "header/utils.h"

void set_screen(void)
{
    struct termios terminal;

    tcgetattr(STDIN_FILENO, &terminal);
    terminal.c_lflag &= ENABLE_RAWMODE;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal);
}

void reset_screen(void)
{
    struct termios terminal;

    tcgetattr(STDIN_FILENO, &terminal);
    terminal.c_lflag |= DISABLE_RAWMODE;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal);
}

int char2int(char* string)
{
    int result = 0;

    for(int i = 0; string[i]; i++)
    {
      if(string[i] < 0x30 || string[i] > 0x39)
        return -1;

      result = (result * 10) + (string[i] - 0x30);
    }

    return result;
}
