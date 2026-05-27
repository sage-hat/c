#!/bin/bash
#file assembly

FileName=$1
FileNameWithoutPrefix=${FileName/.c}

gcc -Wall -g -DDEB $FileName move.o -lcurses -o $FileNameWithoutPrefix
