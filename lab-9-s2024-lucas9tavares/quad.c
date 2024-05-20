/*

  Lucas Tavares
  04/01/2024

  Solve the quadratic equation a*x^2 + b*x + c = 0.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


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


/************
main function
************/

int main(int argc, char *argv[]) {

  //Check if command line argunts are inserted correctly 
  if (argc != 4) {
    fprintf(stderr, "Invalid arguments structure \n");
    fprintf(stderr, "Usage: %s <a> <b> <c> \n", argv[0]);
    return 1;
    exit(1);
  } //end if

  //Check if number is a real number
  if (isReal(argv[1]) == 1 || isReal(argv[2]) == 1 || isReal(argv[3]) == 1) {
    fprintf(stderr, "Invalid value for argument(s) \n");
    fprintf(stderr, "Usage: %s <a> <b> <c> \n", argv[0]);
    return 1;
    exit(1);
  } //end if

  //Assign a, b, and c to variables
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  double c = atof(argv[3]);

  //Rescailling the coefficients
  if (a > b && a > c) {
    b = b / a;
    c = c / a;
    a = 1;
  } //end if

  if (b > a && b > c) {
    a = a / b;
    c = c / b;
    b = 1;
  } //end if

  if (c > a && c > b) {
    a = a / c;
    b = b / c;
    c = 1;
  } //end if
  

  //Calculate the root if a = 0
  if (a == 0 || fabs(a / b) < 0.00000000001 || fabs(a / c) < 0.0000000001) {
    
    double x1 = - c / b;
    printf("Root: %f \n", x1);

    return 0;
    exit(0);
      
  } //end if

  //Calculate the determinant
  double det = b * b - 4 * a * c;

  //Calculate the roots
  if (det > 0) {
    
    double x1 = (-b + sqrt(det)) / (2 * a);
    double x2 = (-b - sqrt(det)) / (2 * a);

    printf("Roots: %f , %f \n", x1, x2);

  } //end if

  if (det == 0) {

    double x1 = (-b + sqrt(det)) / (2 * a);

    printf("Roots: %f , %f \n", x1, x1);

  } //end if

  if (det < 0) {

    printf("The roots are imaginary \n");

    double realPart = -b / (2 * a);
    double imaginaryPart = sqrt(-det) / (2 * a);

    printf("Roots: %f +-i%f \n", realPart, imaginaryPart);

  } //end if

  /*
  double x3 = 2 * c / (-b - sqrt(b * b - 4 * a * c));
  double x4 = 2 * c / (-b + sqrt(b * b - 4 * a * c));
  */

  return 0;
  
} //end main
