/*

  Lucas Tavares
  05/05/2024

  Takes in a CSV file defining a resistor network and outputs a CSV file detailing the currents in that network.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>


/**********
Comp struct
**********/

typedef struct {
    int node1;
    int node2;
    double val;
    char type;
} Comp; //end struct


/****************
readFile function
****************/

int readFile(const char *filename, Comp comps[]) {

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file \n");
    return -1;
  } //end if
  
  char line[256];
  int counter = 0;
  while (fgets(line, sizeof(line), file) && counter < 1000) {
    Comp circuitComp;
    if (sscanf(line, "%c,%d,%d,%lf", &circuitComp.type, &circuitComp.node1, &circuitComp.node2, &circuitComp.val) == 4) {
	  comps[counter++] = circuitComp;
	} //end if
  }//end while

  fclose(file);
  
  return counter;

} //end readFile


/*********************
circuitSolver function
*********************/

void circuitSolver(Comp comps[], int count, int numNodes, double *voltages, double *currents) {

  int numVoltageSources = 0;
  for (int i = 0; i < count; i++) {
    if (comps[i].type == 'V') {
	  numVoltageSources++;
    } //end if
  } //end for

  int numEquations = numNodes + numVoltageSources;
  gsl_matrix *Matrix = gsl_matrix_calloc(numEquations, numEquations);
  gsl_vector *Vec_1 = gsl_vector_calloc(numEquations);
  gsl_vector *Vec_2 = gsl_vector_calloc(numEquations);
  gsl_permutation *n = gsl_permutation_alloc(numEquations);
  int s;

  int voltageSourceIndex = numNodes;
  for (int i = 0; i < count; i++) {
    int n1 = comps[i].node1 - 1;
    int n2 = comps[i].node2 - 1;
    
    if (comps[i].type == 'R') {

	  double g = 1.0 / comps[i].val;
	  gsl_matrix_set(Matrix, n1, n1, gsl_matrix_get(Matrix, n1, n1) + g);
	  gsl_matrix_set(Matrix, n2, n2, gsl_matrix_get(Matrix, n2, n2) + g);
	  gsl_matrix_set(Matrix, n1, n2, gsl_matrix_get(Matrix, n1, n2) - g);
	  gsl_matrix_set(Matrix, n2, n1, gsl_matrix_get(Matrix, n2, n1) - g);
    
    } //end if

    else if (comps[i].type == 'V') {

	  gsl_matrix_set(Matrix, n1, voltageSourceIndex, 1);
	  gsl_matrix_set(Matrix, n2, voltageSourceIndex, -1);
	  gsl_matrix_set(Matrix, voltageSourceIndex, n1, 1);
	  gsl_matrix_set(Matrix, voltageSourceIndex, n2, -1);
	  gsl_vector_set(Vec_1, voltageSourceIndex, comps[i].val);
	  voltageSourceIndex++;

    } //end else if
    
  } //end for

  gsl_matrix_set(Matrix, numNodes - 1, numNodes - 1, 1);

  if (gsl_linalg_LU_decomp(Matrix, n, &s) == GSL_SUCCESS && gsl_linalg_LU_solve(Matrix, n, Vec_1, Vec_2) == GSL_SUCCESS) {

    gsl_vector_memcpy(Vec_2, Vec_2);
    for (int i = 0; i < numNodes; i++) {
	  voltages[i] = gsl_vector_get(Vec_2, i);
    }//end for

  } //end if
  
  else {
      fprintf(stderr, "Error solving the system of equations \n");
  } //end else

  voltageSourceIndex = numNodes;
  for (int i = 0; i < count; i++) {
    int n1 = comps[i].node1 - 1;
    int n2 = comps[i].node2 - 1;
    
    if (comps[i].type == 'R') {
	  currents[i] = (gsl_vector_get(Vec_2, n2) - gsl_vector_get(Vec_2, n1)) / comps[i].val;
    } //end if

    else if (comps[i].type == 'V') {
	  currents[i] = gsl_vector_get(Vec_2, voltageSourceIndex++);
    } //end else if

  } //end for

  gsl_permutation_free(n);
  gsl_vector_free(Vec_2);
  gsl_vector_free(Vec_1);
  gsl_matrix_free(Matrix);

} //end circuitSolver


/********************
outputAnswer function
********************/

void outputAnswer(const char *filename, Comp comps[], double *nodeVoltages, double *componentCurrents, int count) {

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
      fprintf(stderr, "Error opening file \n");
      return;
  } //end if

  for (int i = 0; i < count; i++) {

    if (comps[i].type == 'V') {
	  fprintf(file, "V,%d,%d,%.0f\n", comps[i].node1, comps[i].node2,
      nodeVoltages[comps[i].node1 - 1] - nodeVoltages[comps[i].node2 - 1]);
    } //end if
    else if (comps[i].type == 'R') {
	  fprintf(file, "I,%d,%d,%.4f\n", comps[i].node1, comps[i].node2, componentCurrents[i]);
    } //end else if
  
  } //end for

  fclose(file);

} //end outputAnswer


/************
main function
************/

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Incorrect use of command line arguments \n");
    fprintf(stderr, "Usage: %s <filename.csv> \n", argv[0]);
    return 1;
    exit(1);
  } //end if

  Comp comps[1000];
  double nodeVoltages[1000];
  double componentCurrents[1000];

  int count = readFile(argv[1], comps);
  if (count == -1) {
    return 1;
    exit(1);
  } //end if
   
  int numNodes = 0;
  for (int i = 0; i < count; i++) {
    int maxNode = comps[i].node1 > comps[i].node2 ? comps[i].node1 : comps[i].node2;
    if (maxNode > numNodes) numNodes = maxNode;
  } //end if

  circuitSolver(comps, count, numNodes, nodeVoltages, componentCurrents);
  outputAnswer("ans.csv", comps, nodeVoltages, componentCurrents, count);

  return 0;

} //end main
