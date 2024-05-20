#!/bin/bash

#Compiling the C code
gcc bindec.c -lm -o bindec

#Correct testing arguments
echo " "
echo "CORRECT TESTING ARGUMENTS:"
echo " "
./bindec -d 123.456
./bindec -d 1234567
./bindec -d 0.123456
./bindec -b 1001.001
./bindec -b 1001001
./bindec -b 0.1001001
echo " "

#Wrong testing arguments
echo "INCORRECT TESTING ARGUMENTS:"
echo " "
./bindec -b 123.456
./bindec -e 1001.001
./bindec -de 1001.001
./bindec 1001.001
./bindec -b
./bindec -b 100a.001
echo " "
