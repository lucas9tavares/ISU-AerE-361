/*

  Lucas Tavares
  02/26/2024

  Prompt the user for a value x and a relative error, correctly reject invalid values of x, evaluate e^x using the Maclaurin series, print the correct output format as provided in the lab manual.

*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


/****************
CheckNum function
****************/

/* First get the length of the userInput, then loop and check each char is a digit or a point */

int CheckNum(char userInput[]) {

  int StringLen = strlen( userInput );
  int CheckNumReturn = 0;

  if ( userInput[0] != '-' && !isdigit(userInput[0]) ) {
    CheckNumReturn = 1;
  } //end if

  else {
    for (int i = 1; i < StringLen; ++i) {

      if (!isdigit(userInput[i]) && userInput[i] != '.') {
        CheckNumReturn = 1;
        break;
      }
    } /*end for*/
  } //end else

  return CheckNumReturn;
  
} /*end CheckNum */


/************
main function
************/

int main(void) {

  //Prompt the user for a value of x
  char userInput1[256];
  printf("Enter a value for x: ");
  scanf("%s", userInput1);

  int myReturn = 0;

  //Check if x is a real number
  if (CheckNum(userInput1) == 0) {

    double x = atof(userInput1); //Transform the user input for x from a string to a double

    //Prompt the user for a relative error value
    double err;
    printf("Enter a value for relative error: ");
    scanf("%lf", &err);

    double newTerm = 1000.0;
    int ittr = 0;
    int n;
    double fact = 1.0;
    double ans = 0.0;

    //Compute the Maclaurin series until newTerm is smaller than err 
    while (fabs(newTerm) > err) {

      if (ittr == 0) {
	n = 1;
      } //end if
      else {
	n = ittr;
      } //end else

      fact = fact * n; //Compute the factorial

      newTerm = pow(x,ittr) / fact; //Compute the new term that will be added to the sum
      ans = ans + newTerm; //Sum of terms

      ++ittr;

    } //end while

    printf("After %d terms in the series, exp(%lf) is approx. %lf with an error of %lf \n", ittr+1, x, ans, err);

  } //end if

  //Return error if x is an invalid input
  else {
    printf("Invalid value for x \n");
    myReturn = 1;
  } //end else

  return myReturn;

} //end main
