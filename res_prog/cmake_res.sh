#!/bin/sh

gcc -Wall -g res.c my_string.o const.o error.o valid.o parse.o decode.o run.o -o res
