#!/bin/bash

FileName=$1
FileNameWithoutPrefix=${FileName/.c}

gcc -Wall -Wextra -Werror -g -c $FileName -lcurses 
