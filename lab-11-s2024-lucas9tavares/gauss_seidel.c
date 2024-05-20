/*

  Lucas Tavares
  04/22/2024

  Implement a Gauss-Seidel solver.

*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


/*Declare a struct to pass around a matrix*/

typedef struct coo_matrix_ {
  int nnz;

  /*unsigned rows[nnz]; row index for each non-zero value */
  unsigned int *rows;

  /*unsigned columns[nnz];  column index for each non-zero value */
  unsigned int *columns;

  /*double values[nnz]; each non-zero value */
  double *values;

} coo_matrix_;
  

/*****************************
initialize_COO_matrix function
*****************************/

void initialize_COO_matrix(int M, int N, int nnz, double **denseMatrix, struct coo_matrix_ *cooMatrix) {

  int m = 0;
  int n = 0;
  int running_nnz = 0;

  for (m = 0; m < M; m++) {
    for (n = 0; n < N; n++) {      
      if (denseMatrix[m][n] == 0) { continue; }
      
      /*Otherwise, we need to store the non-zero value*/
      cooMatrix->rows[running_nnz] = m;
      cooMatrix->columns[running_nnz] = n;
      cooMatrix->values[running_nnz] = denseMatrix[m][n];
      
      running_nnz++; /*make sure to increment!*/
    } /*end for*/
  } /*end for*/
  
  return;
  
} /*end initialize_COO_matrix*/


/************
main function
************/

int main (int argc, char *argv[]) {

  //Declare variables
  int i, j, k, num; //Iterators
  int M, N;
  int NNZ = 0;
  double **Matrix;
  
  //No argument: Prompt user for number of equations and their coefficient values
  if (argc == 1) {

    /* Request System Order (Number of Equations) */
    printf("\nHow many equations: ");
    scanf("%d", &num);

    M = num;
    N = num + 1;

    /* Allocate Dynamic Variables */
    Matrix = (double **)malloc(M * sizeof(double *));
    for (i = 0; i < M; i++) {
      Matrix[i] = (double *)malloc(N * sizeof(double));
    } /*end for*/

    /* Request Augmented Matrix Values. */
    printf("\nEnter the elements of augmented matrix row-wise:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf(" A[%d][%d]:", i+1, j+1);
            scanf("%lf", &Matrix[i][j]);

	    //Count number of non-zero elements
	    if (Matrix[i][j] != 0) {
	      NNZ++;
	    } //end if
        } /*end for*/
    } /*end for*/

  } //end if

  //Single argument: Collect the augmented matrix from the csv file specified
  if (argc == 2) {

    //Open csv file
    FILE * file = fopen(argv[1], "r");
    if (file == NULL) {
      fprintf(stderr, "Error opening file \n");
      return 1;
      exit(1);
    } //end if

    //Count the number of rows and columns in the CSV file
    M = 0;
    N = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
      char *token = strtok(line, ",");
      int colCount = 0;
      while (token != NULL) {
	colCount++;
	token = strtok(NULL, ",");
      } //end while
      N = (N < colCount) ? colCount : N;
      M++;
    } //end while

    //Reset file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    //Dynamically allocate memory for the Matrix
    Matrix = (double **)malloc(M * sizeof(double *));
    for (int i = 0; i < M; i++) {
        Matrix[i] = (double *)malloc(N * sizeof(double));
    } //end for

    //Read values from the csv file and store them in the Matrix
    i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        j = 0;
        while (token != NULL) {
            Matrix[i][j] = atof(token); //Convert string to double
            token = strtok(NULL, ",");

	    //Count number of non-zero elements
	    if (Matrix[i][j] != 0) {
	      NNZ++;
	    } //end if

	    j++;
	    
        } //end while
        i++;
    } //end while

    //Close file
    fclose(file);
    
  } //end if

  //More than one argument: Error
  if (argc > 2) {
    fprintf(stderr, "Incorrect use of command line arguments \n");
    fprintf(stderr, "Usage: %s <filename>  or no arguments \n", argv[0]);
    return 1;
    exit(1);
  } //end if

  /*Make a struct to pass the COO matrix*/
  struct coo_matrix_ coo_matrix;
  coo_matrix.nnz = NNZ;
  coo_matrix.rows = (unsigned int *)malloc(NNZ * sizeof(unsigned int));
  coo_matrix.columns = (unsigned int *)malloc(NNZ * sizeof(unsigned int));
  coo_matrix.values = (double *)malloc(NNZ * sizeof(double));

  /*Store the matrix in COO format*/
  initialize_COO_matrix(M, N, NNZ, Matrix, &coo_matrix);

  //Report the space savings
  float NNZf = NNZ;
  float Mf = M;
  float Nf = N;
  float spaceSavings = 100.0 * (1.0 - (NNZf / (Mf * Nf)));
  fprintf(stderr, "\nCompressed matrix contains %d elements, compressed by %.1f%% \n\n", NNZ, spaceSavings);

  //Maximum iterations and tolerance
  int maxIt = 1000;
  double tol = 0.0001;
  if (argc == 1) {
    int ans = 1;
    printf("\nDefault max iterations = 1000 and tolerance = 0.0001. Do you want to override these values (Yes = 0, No = else)? ");
    scanf("%d", &ans);
    if (ans == 0) {
      printf("\nInsert new max iterations value: ");
      scanf("%d", &maxIt);
      printf("\nInsert new tolerance value: ");
      scanf("%lf", &tol);
    } //end if
  }//end if

  //Compute Gauss-Seidel Method
  
  double *x = malloc(M * sizeof(double));
  for (i = 0; i < M; i++) {
    x[i] = 0.0;
  } //end for
  double sum1, sum2, newX, error, mainError;
  k = 1;

  while (k <= maxIt) {

    mainError = 0;

    for (i = 0; i < M; i++) {
      
      sum1 = 0;
      sum2 = 0;
      for (j = 0; j < i - 1; j++) {
	if (j != i) {
	  sum1 += Matrix[i][j] * x[j];
	} //end if
      } //end for
      for (j = i + 1; j < M; j++) {
	  sum2 += Matrix[i][j] * x[j];
      } //end for

      newX = (Matrix[i][M] - sum1 - sum2) / Matrix[i][i];

      error = fabs(newX - x[i]);
      if (error > mainError) {
	mainError = error;
      } //end if

      x[i] = newX;
      
    } //end for

    if (mainError < tol) {
      break;
    } //end if

    k++;

  } //end while

  //Print the results if system was entered by an user
  if (argc == 1) {
    printf("\nThe solution is:\n");
    for (i = 0; i < M; i++) {
      printf("\n x%d=%f\n", i+1, x[i]);
    } /*end for*/
  } //end if

  //Save the output to ans.csv if system was itiniated with a csv file
  if (argc == 2) {

    //Open ans.csv file
    FILE *fp;
    fp = fopen("ans.csv", "w");

    if (fp == NULL) {
      fprintf(stderr, "Error opening file \n");
      return 1;
      exit(1);
    } //end if

    //Write values to the csv file
    for (i = 0; i < M; i++) {
      fprintf(fp, "%lf", x[i]);
      if (i < M - 1) {
	fprintf(fp, ",");
      } //end if
    } //end for

    fclose(fp);

    printf("Answers successfully saved to ans.csv \n\n");

  } //end if
  
  /* Free allocated memory */
  for (i = 0; i < M; i++) {
    free(Matrix[i]);
  } /*end for*/
  free(Matrix);
  free(coo_matrix.rows);
  free(coo_matrix.columns);
  free(coo_matrix.values);
  free(x);

  return 0;
  
} //end main
