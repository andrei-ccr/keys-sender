# keys-sender
Program keys to automatically press themselves. Works on Windows.

## Usage
Execute program with argument *-s* followed by a string to be typed. 

`ksender -s This is a string`

The program will start typing each character in the string after 2 seconds from execution with a 100ms pause between each character. To change these timings use *-d* for start time and *-D* for pause between characters time. Time is specified in miliseconds.

The following command tells the program to type `This is a string` after 3 seconds from execution and wait half a second between each character.

`ksender -s This is a string -d 3000 -D 500`

Note: The program runs in the background from execution until it finishes typing, then it closes. After execution, you can switch to any window. The keys will be sent to the active window.

## Getting the executable
Compile `main.cpp` using C++ 11 flag. If you use g++ you can use the Makefile.
