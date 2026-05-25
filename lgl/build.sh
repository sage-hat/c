#!/bin/bash
#file assembly

FileName=$1
FileNameWithoutPrefix=${FileName/.c}

gcc -Wall -g $FileName move.o my_string.o -lcurses -o $FileNameWithoutPrefix
