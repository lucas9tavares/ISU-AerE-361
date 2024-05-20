/*

  Lucas Tavares
  04/01/2024

  Accept the number of bits the exponent and the mantissa shall have, prompt the user for a signed decimal number, which is converted to the internal bit representation of MyFloat.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


//itoa() imported since it is not a standard function.
/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
char* itoa(int value, char* result, int base) {
  // check that the base if valid
  if (base < 2 || base > 36) { *result = '\0'; return result; }

  char* ptr = result, *ptr1 = result, tmp_char;
  int tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
  } while ( value );

  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}


/*******************
myFloatStr structure
*******************/

struct myFloatStr {
  
  int sign;
  int * exponent;
  int * mantissa;

};


/**************
isReal function
**************/

int isReal(const char * input) {

  int length = strlen(input);
  int countPeriods = 0;
  int countDigits = 0;
  int myReturn = 0;
  
  for (int i = 0; i < length; i++) {

    //Check if is positive or negative
    if (i == 0) {
      if (input[i] == '-' || input[i] == '+') {
        continue;
      } //end if 1
    } //end if 2

    //Check if it has decimal cases
    if (input[i] == '.') {
      countPeriods++;
    } //end if 3

    else {

      //Check if other characters are digits
      if (isdigit(input[i])) {
	countDigits++;
      } //end if 4

      //Check if character is invalid
      else {
	myReturn = 1;
	break;
      } //end inner else

    } //end outer else
      
  } //end for

  //Check if there are no digits or there are more than one period
  if (countPeriods > 1 || countDigits == 0) { 
    myReturn = 1;
  } //end if

  return myReturn;

} //end isReal


/**********************
decimal2Binary function
**********************/

char * decimal2Binary(double decimal) {
  
  //Convert the integer part of the decimal number to binary
  int integerPart = (int) decimal;
  char * binaryInteger = malloc(32 * sizeof(char));
  itoa(integerPart, binaryInteger, 2);

  //Convert the decimal part of the decimal number to binary with up to 10 decimal places
  double decimalPart = decimal - integerPart;
  char *binaryDecimal = malloc(12 * sizeof(char));
  binaryDecimal[0] = '.';
  binaryDecimal[11] = '\0'; // Null terminator

  for (int i = 1; i < 11; i++) {
    decimalPart *= 2;
    int bit = (int) decimalPart;
    binaryDecimal[i] = bit + '0';
    decimalPart -= bit;
  } //end for

  // Return the combined binary number
  char *binaryNumber = malloc(44 * sizeof(char));
  sprintf(binaryNumber, "%s%s", binaryInteger, binaryDecimal);

  // Free memory allocated for binary parts
  free(binaryInteger);
  free(binaryDecimal);

  return binaryNumber;
  
} //end decimal2Binary


/***********************
decimal2MyFloat function
***********************/

struct myFloatStr * decimal2MyFloat(double decimal, int expBits, int manBits) {

  //Allocate memory for mf
  struct myFloatStr * mf = (struct myFloatStr *)malloc(sizeof(struct myFloatStr));
  if (mf == NULL) {
    fprintf(stderr, "Memory allocation failed \n");
    exit(1);
  } //end if

  mf->sign = (decimal < 0) ? 1 : 0;

  //Convert decimal to binary
  char * binary = decimal2Binary(fabs(decimal));

  //Find exponent value
  const char ch = '.';
  char * periodPos = strchr(binary, ch);
  int exp = (periodPos - binary) - 1;
  int expAdd = (pow(2, expBits) / 2) - 1;
  int expTot = exp + expAdd;

  //Check if number fits the bits
  if (expTot < 0 || expTot > pow(2, expBits)) {
    fprintf(stderr, "Number cannot be stored in quantity of bits specified for exponent \n");
    exit(1);
  } //end if

  //Calculate the binary exponent
  int expAns[expBits];
  int i = expBits - 1;
  int rem;
  while ((expTot) != 0) {
    rem = expTot % 2;
    expTot = expTot / 2;
    expAns[i] = rem;
    i = i -1;
  } //end while
    
  mf->exponent = expAns;

  int manAns[manBits];
  double binaryDou = atoi(binary);
  double newBinary = binaryDou * pow(10, -exp);

  /////////////////////////////////////////////

  mf->mantissa = 0;
  
  return mf;

} //end decimal2MyFloat


/************
main function
************/

int main(int argc, char *argv[]) {

  //Check if number of command line arguments is valid
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <exponent bits> <mantissa bits> \n", argv[0]);
    return 1;
    exit(1);
  } //end if

  //Allocate arguments
  int expBits = atoi(argv[1]);
  int manBits = atoi(argv[2]);

  //Collect the decimal number from user
  printf("Enter a signed decimal number: ");
  char * decimal;
  scanf("%s", decimal);

  //Check if decimal is a real number
  if (isReal(decimal) == 1) {
    fprintf(stderr, "Invalid number input \n");
    return 1;
    exit(1);
  } //end if

  double decimalDouble = atof(decimal);

  //Calculate decimal in MyFloat representation
  struct myFloatStr * myFloat = decimal2MyFloat(decimalDouble, expBits, manBits);

  //Output result
  printf("MyFloat representation: %d ", myFloat->sign);
  for (int i = 0; i < expBits; i++) {
    printf("%d", myFloat->exponent[i]);
  } //end for
  printf(" ");
  for (int i = 0; i < manBits; i++) {
    printf("%d", myFloat->mantissa[i]);
  } //end for
  printf("\n");

  // Free memory allocated
  free(myFloat->exponent);
  free(myFloat->mantissa);
  free(myFloat);

  return 0;
  
} //end main
