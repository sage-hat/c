#!/bin/bash
#file assembly

FileName=$1
FileNameWithoutPrefix=${FileName/.c}

gcc -Wall -g -DDEB $FileName move.o my_string.o -lcurses -o $FileNameWithoutPrefix
