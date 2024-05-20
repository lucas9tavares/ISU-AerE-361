#!/bin/bash

#Compiling the C code
gcc quad.c -lm -o quad

#Testing arguments
echo "a = 6, b = 5, c = -4"
./quad 6 5 -4
echo " "
echo "a = 6e30, b = 5e30, c = -4e30"
./quad 6000000000000000000000000000000 500000000000000000000000000000 -400000000000000000000000000000
echo " "
echo "a = 0, b = 1, c = 1"
./quad 0 1 1
echo " "
echo "a = 1, b = -e5, c = 1"
./quad 1 -10000 1
echo " "
echo "a = 1, b = -4, c = 3.999999"
./quad 1 -4 3.999999
echo " "
echo "a = e-30, b = -e30, c = e30"
./quad 0.00000000000000000000000000000001 -1000000000000000000000000000000 1000000000000000000000000000000
echo " "
