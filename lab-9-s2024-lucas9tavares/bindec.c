/*

  Lucas Tavares
  03/26/2024

  Take a number as an input and a flag to indicate if the number is decimal or binary. Output the equivalent number in the other system.

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


/*******************
binaryCheck function
*******************/
int binaryCheck(int n) {

  int j = 0;
  int bCheckReturn = 0;
  
  while (n != 0) {
    
    j = n % 10;
    
    if ((j == 0) || (j == 1)) {
      
      n = n / 10;
      
      if (n == 0) {
	break;
      } //end inner if
      
    } //end outer if
    
    else {
      bCheckReturn = 1;
      break;
    } //end else
    
  } //end while

  return bCheckReturn;

} //end binaryCheck


/**********************
binary2Decimal function
**********************/

double binary2Decimal(char * integerPart, char * decimalPart) {

  //Convert integer part from binary to decimal
  int integer = strtol(integerPart, NULL, 2);

  //Convert decimal part from binary to decimal
  double decimal = 0.0;
  int length = 0;
  while (*decimalPart != '\0') {
    decimal += (*decimalPart++ - '0') * pow(2, -++length);
  } //end while

  //Combine integer and decimal parts to get the final decimal number
  double result = integer + decimal;

  //Round up to 10 decimal places
  //result = round(result * 1e10) / 1e10;

  return result;
  
} //end binary2decimal


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


/************
main function
************/

int main(int argc, char *argv[]) {

  //Check if command line argunts are inserted correctly 
  if (argc != 3) {
    fprintf(stderr, "Invalid arguments structure \n");
    fprintf(stderr, "Usage: %s -<flag> <number> \n", argv[0]);
    return 1;
    exit(1);
  } //end if

  //Check if number is a real number
  if (isReal(argv[2]) == 1) {
    fprintf(stderr, "Invalid number argument \n");
    fprintf(stderr, "Usage: %s -<flag> <number> \n", argv[0]);
    return 1;
    exit(1);
  } //end if

  //Check if flag is a valid input
  const char * flag = &argv[1][1];
  int flagTest = 1;
  if (strcmp(flag, "b") == 0 || strcmp(flag, "d") == 0) {
    flagTest = 0;
  } //end if
  if (flagTest == 1 || strlen(argv[1]) > 2) {
    fprintf(stderr, "Invalid flag argument: Flag must be '-d' for decimal or '-b' for binary \n");
    fprintf(stderr, "Usage: %s -<flag> <number> \n", argv[0]);
    return 1;
    exit(1);
  } //end if

  char * number = argv[2];
  char beforePoint[250];
  char afterPoint[250];

  //Parse the number before and after the point
  sscanf(number, "%[^.].%s", beforePoint, afterPoint);

  int beforePointInt = atoi(beforePoint);
  int afterPointInt = atoi(afterPoint);

  //Convert from binary to decimal
  if (strcmp(flag, "b") == 0) {

    //Check if binary is valid
    if (binaryCheck(beforePointInt) == 1 || binaryCheck(afterPointInt) == 1) {
    fprintf(stderr, "Invalid binary number. Binaries should only contain 0 or 1 digits. \n");
    return 1;
    exit(1);
    } //end if

    double decimalAnswer = binary2Decimal(beforePoint, afterPoint);

    //Output results
    printf("Binary number: %s \n", number);
    printf("Decimal equivalent: %.10lf \n", decimalAnswer);
    
  } //end if

  //Convert from decimal to decimalbinary
  if (strcmp(flag, "d") == 0) {

    double numberDouble = atof(number);
    char * binaryAnswer = decimal2Binary(numberDouble);

    //Output results
    printf("Decimal number: %s \n", number);
    printf("Binary equivalent: %s \n", binaryAnswer);

    free(binaryAnswer);

  } //end if

  return 0;

} //end main
