#!/bin/bash
#file assembly

FileName=$1
FileNameWithoutPrefix=${FileName/.c}

gcc -Wall -g $FileName move.o -lcurses -o $FileNameWithoutPrefix
