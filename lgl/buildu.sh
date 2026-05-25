#!/bin/bash

FileName=$1
FileNameWithoutPrefix=${FileName/.c}

gcc -Wall -g -c $FileName -lcurses 
