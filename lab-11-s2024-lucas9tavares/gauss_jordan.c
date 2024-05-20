/*This is an example template for the Gauss-Jordan exercise. You are not required to use it. 
It simply provides an example structure to get you started.

This code does not compile and run on its own. That task falls to you. In order to get this
program working, you need to add in lines of code where we have placed comments. Keep in mind,
one comment != one line of code. The comment discussing "where the magic happens" will have
several lines in order to perform its function*/

/*The functionality of the program is up to you, and you can use whichever method you're most
comfortable with to write it. You may need more packages, or there may be other various things
you'll need in each of the steps. It depends on how you structure the program.*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Declare Variables */
    int i,j,k,n; /*iterators*/
    double a;

    /* Request System Order (Number of Equations) */
    printf("\nHow many equations: ");
    scanf("%d", &n);

    /* Allocate Dynamic Variables */
    double **Matrix = malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
      Matrix[i] = malloc((n + 1) * sizeof(double));
    } /*end for*/

    /* Request Augmented Matrix Values. */
    printf("\nEnter the elements of augmented matrix row-wise:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) {
            printf(" A[%d][%d]:", i+1, j+1);
            scanf("%lf", &Matrix[i][j]);
        } /*end for*/
    } /*end for*/

    /* Diagonalize the matrix. */
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            if (i != j) {
                a = Matrix[i][j] / Matrix[j][j];
                for (k = 0; k <= n; k++) {
                    Matrix[i][k] = Matrix[i][k] - a * Matrix[j][k];
                }  /*end for*/
            } /*end if*/
        } /*end for*/
    } /*end for*/

    double solution[n];
    
    printf("\nThe solution is:\n");
    for (i = 0; i < n; i++) {
        solution[i] = Matrix[i][n] / Matrix[i][i];
        printf("\n x%d=%f\n", i+1, solution[i]);
    } /*end for*/

    /* Free allocated memory */
    for (i = 0; i < n; i++) {
      free(Matrix[i]);
    } /*end for*/
    free(Matrix);

    return 0; /*exit normally*/
    
} /*end main*/
