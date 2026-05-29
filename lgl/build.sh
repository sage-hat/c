#!/bin/bash
#file assembly

FileName=$1
FileNameWithoutPrefix=${FileName/.c}


gcc -Wall -Wextra -Werror -g -c move.c -lcurses 
gcc -Wall -Wextra -Werror -g -c parse.c -lcurses 
gcc -Wall -Wextra -Werror -g -c error.c -lcurses 

gcc -Wall -Wextra -Werror -g main.c move.o parse.o error.o -lcurses -o main

#gcc -Wall -Wextra -Werror -g $FileName move.o parse.o error.o -lcurses -o $FileNameWithoutPrefix
