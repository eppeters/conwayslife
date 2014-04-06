conwayslife
===========

A C++ implementation of Conway’s Life for Oregon State University’s Computer Science program.

Design Notes
------------

Detailed design information is available in the initialDesign.odt or initialDesign.pdf files on github, but here’s a brief summary of the design anyway:

> Built with five classes, one for cells (called Cell), one for collections of cells (Board), one for games (Game), one for an individual starting configuration (Config) and one for sets of starting configurations (ConfigSet). The classes and all their functions are defined in an interface/implementation file pair called life (life.h and life.cpp). Some configurations are provided in the life library. The user will be able to define more as he/she wants.

More on the design
------------------

I can’t say the implementation follows the design perfectly, so if something looks odd in the design, it probably is, and I probably changed it in the implementation. If you find something off about the program, let me know.

Game Configurations
-------------------

This implementation has only two initial configurations out of the box (Gosper Glider Gun and a single pulsar), but others can be added by adding to the libs/configs.h file.

Compilation Information
-----------------------

This program should compile without problems on Linux, as long as you have the library unistd.h for the usleep() function, which makes the output of generations very nice.

Be sure to run this in a terminal emulator 80 cols wide and 22 rows high.
