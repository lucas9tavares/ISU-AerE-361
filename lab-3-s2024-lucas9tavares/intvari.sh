#!/bin/bash

# Variance of a sample set is:
# Sum of the squares of the difference from the mean, divided by the number of samples
# Sum( x_i - mu )^2 / N

echo "Integer Variance Calculator"

if [ -z "$2" ]
then
    echo "Not enough samples!"
    exit
else
    echo "I recieved $# samples."
fi

sum=0
mean=0
for sampval in "$@"
do
    sum=$(($sum + $sampval))
done
mean=$(($sum/$#))

echo "The integer mean value is: $mean"

sum1=0
vari=0
for sampval in "$@"
do
    sum1=$(($sum1 + ($sampval - $mean)*($sampval - $mean) ))
done
vari=$(($sum1/$#))

echo "The integer standard deviation is: $vari"
