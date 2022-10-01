#ifndef UTILS_H
#define UTILS_H

#define ENABLE_RAWMODE   ~(0xA)
#define DISABLE_RAWMODE  0xA

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void   set_screen(void);
void   reset_screen(void);
int    char2int(char*);


#endif
