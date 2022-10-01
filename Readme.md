Snake developed completely in C language without the use of any graphic library or non-blocking function.
The program consists of two threads synchronized with each other through the use of semaphores: one for updating the screen, the other for acquiring characters from the keyboard;

To run the program type in the directory where the sources are located:

    make

and then:

    ./snake <row> <col>

Where row and col are the size of the field. The minimum size that the field can assume is 5x5;

#Study of the source:




