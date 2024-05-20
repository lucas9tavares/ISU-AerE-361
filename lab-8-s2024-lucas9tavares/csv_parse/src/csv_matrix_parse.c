/*

  Lucas Tavares
  03/18/2024

  Take the name of a CSV file on the command line, read and validate the file, and construct a 2D matrix of doubles with the values if valid. If a valid matrix is constructed, print the matrix.

*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "csv.h"


/****************
CheckNum function
****************/

int CheckNum(const char userInput[]) {

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
    } //end for
  } //end else

  return CheckNumReturn;
  
} /*end CheckNum */


/************
main function
************/

int main(int argc, char *argv[]) {

  //Check number of arguments
  if (argc != 2) {
    fprintf(stderr, "Incorrect use of command line arguments \n");
    fprintf(stderr, "Usage: %s <filename> \n", argv[0]);
  } //end if

  FILE *file;
  file = fopen(argv[1], "r");
  
  //Check file can be opened
  if (file == NULL) {
    fprintf(stderr, "Error: File cannot be opened \n");
    return 1;
    exit(1);
  } //end if 1

  //Create CsvParser
  CsvParser *csvparser = CsvParser_new(argv[1], ",", 0);

  if (csvparser == NULL) {
    printf("Error: CSV Parser Error \n");
    return 2;
    exit(2);
  } //end if 2

  CsvRow *row;

  //Check size of first row
  row = CsvParser_getRow(csvparser);
  int row1NumFields = CsvParser_getNumFields(row);
  CsvParser_destroy_row(row);

  int rowNumFields;
  int i = 1;
      
  //Check size of each row
  while ((row = CsvParser_getRow(csvparser))) {
    rowNumFields = CsvParser_getNumFields(row);
    if (rowNumFields != row1NumFields) {
      fprintf(stderr, "Error: Dimension Error \n");
      return 3;
      exit(3);
    } //end if 3
    CsvParser_destroy_row(row);
    ++i;
  } //end while 1
      
  CsvParser_destroy(csvparser);

  //Dynamically allocate the matrix i by row1NumFields in size
  double ** matrix;
  matrix = (double **)malloc(sizeof(double *) * i);
  for ( int j = 0; j < i; ++j ) {
    matrix[j] = (double *)malloc(sizeof(double) * row1NumFields);
  } //end for 1

  csvparser = CsvParser_new(argv[1], ",", 0);

  int maxLength = 0;
  int l = 0;
  double value;

  while ((row = CsvParser_getRow(csvparser))) {
	  
    const char **rowFields = CsvParser_getFields(row);
	  
    for (int k = 0; k < CsvParser_getNumFields(row); k++) {
	    
      if (CheckNum(rowFields[k]) == 1) {
	fprintf(stderr, "Error: Value Error \n");
	return 4;
	exit(4);
      } //end if 5

      //Store max length of value string
      int length = strlen(rowFields[k]);
      if (length > maxLength) {
	maxLength = length;
      } //end if 6

      value = atof(rowFields[k]);
	      
      //Fill in the matrix
      matrix[l][k] = value;

    } //end for 2
	  
    CsvParser_destroy_row(row);

    l++;
	  
  } //end while 2

  for ( int o = 0; o < i; o++ ) {

    for (int p = 0; p < row1NumFields; p++ ) {
      printf("%*f ", maxLength, matrix[o][p]);
    } /*end inner for*/

    printf("\n");

  } /*end outer for*/

  //CsvParser_destroy(csvparser);

  fclose(file);
  
  return 0;

} //end main
