# Generality
Snake developed completely in C language without the use of any graphic library or non-blocking function.
The program consists of two threads synchronized with each other through the use of semaphores: one for updating the screen, the other for acquiring characters from the keyboard.
# Study of the source
The program consists of 5 modules and 4 header files:
    
• main.c = is the main module for initializing the game and restoring the terminal via the functions defined in the   snake.c module and declared in the header file snake.h.
• snake.c = is the module containing the definition of the functions for the two threads and the functions for updating the screen and initializing the terminal.
• field.c = is the module containing the definitions of the functions to allocate, deallocate, view and initialize the field.
• queue.c = is the module containing the implementation of the tail used for the algorithm for the movement of the snake. It then contains the functions to allocate, deallocate, add and remove items from the queue.
• utils.c = is the module containing general utility functions, such as the one for setting up the terminal.

The remaining header files contain the declarations of the functions and structures used by the modules.

# Execution
To run the program type in the directory where the sources are located:

    make

and then:

    ./snake <row> <col>

Where row and col are the size of the field. The minimum size that the field can assume is 5x5;
In case of error, use this command and then try again:

    sudo apt-get install build-essential

