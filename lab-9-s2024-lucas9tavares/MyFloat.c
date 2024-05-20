/*

  Lucas Tavares
  04/01/2024

  Accept the number of bits the exponent and the mantissa shall have, prompt the user for a signed decimal number, which is converted to the internal bit representation of MyFloat.

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


// Structure for MyFloat
typedef struct {
    int sign; // Sign bit
    int *exponent; // Array for exponent bits
    int *significand; // Array for significand bits
    int exp_bits; // Number of bits for exponent
    int sig_bits; // Number of bits for significand
} MyFloat;

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

// Function to convert decimal to binary
int *decimal_to_binary(int num, int bits) {
    int *binary = (int *)malloc(bits * sizeof(int));
    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int index = bits - 1;
    while (num > 0 && index >= 0) {
        binary[index--] = num % 2;
        num /= 2;
    }

    while (index >= 0) {
        binary[index--] = 0;
    }

    return binary;
}

// Function to free memory allocated for MyFloat
void free_myfloat(MyFloat *mf) {
    free(mf->exponent);
    free(mf->significand);
    free(mf);
}

// Function to convert decimal number to MyFloat representation
MyFloat *decimal_to_myfloat(double decimal, int exp_bits, int sig_bits) {
    MyFloat *mf = (MyFloat *)malloc(sizeof(MyFloat));
    if (mf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    mf->sign = (decimal < 0) ? 1 : 0;

    // Extract integer part and fractional part
    int integer_part = abs((int)decimal);
    double fractional_part = fabs(decimal) - integer_part;

    // Convert integer part to binary
    int exp = exp_bits - 1;
    mf->exponent = decimal_to_binary(exp + 127, 8);

    // Convert fractional part to binary
    mf->significand = decimal_to_binary((int)(fractional_part * pow(2, sig_bits)), sig_bits);

    mf->exp_bits = exp_bits;
    mf->sig_bits = sig_bits;

    return mf;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <exponentBits> <mantissaBits>\n", argv[0]);
        return 1;
    }

    int CheckNumReturn = 0;
    for (int j = 1; j <= 2; j ++) {
      for (int i = 0; i < strlen(argv[1]); ++i) {
	if (!isdigit(argv[j][i])) {
	  CheckNumReturn = 1;
	  break;
	} //end if
      } /*end for*/
    } //end for
	
    if (CheckNumReturn != 0) {
      fprintf(stderr, "Invalid exponent and/or mantissa values! \n");
      return 1;
      exit(1);
    } //end if

    int exp_bits = atoi(argv[1]);
    int sig_bits = atoi(argv[2]);

    char *decimalChar = (char *)malloc(256 * sizeof(char));;
    printf("Enter a signed decimal number: ");
    scanf("%s", decimalChar);

    if (isReal(decimalChar) != 0) {
      fprintf(stderr, "Invalid signed decimal number! \n");
      return 1;
      exit(1);
    } //end if

    double decimal = atof(decimalChar);

    //printf("%f\n", decimal);

    MyFloat *myfloat = decimal_to_myfloat(decimal, exp_bits, sig_bits);

    printf("MyFloat representation of %f: %d ", decimal, myfloat->sign);
    for (int i = 0; i < exp_bits; i++) {
        printf("%d", myfloat->exponent[i]);
    }
    printf(" ");
    for (int i = 0; i < sig_bits; i++) {
        printf("%d", myfloat->significand[i]);
    }
    printf("\n");

    // Free memory allocated for MyFloat
    free_myfloat(myfloat);
    free(decimalChar);

    return 0;
}
