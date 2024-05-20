/*
  Lucas Tavares
  04/06/2024

  Run a filename of a data file as a command line argument, count the number of data collections in the file, store the max and min X and Y positions, story the velocity X and Y components in separate matrices, save these two matrices to text files named Xvel.txt and Yvel.txt.

*/


#include <stdio.h>
#include <stdlib.h>


/************
main function
************/

int main(int argc, char *argv[]) {
  //Check command-line arguments
  if (argc != 2) {
    fprintf(stderr, "Incorrect use of command line arguments \n");
    fprintf(stderr, "Usage: %s <filename> \n", argv[0]);
    return 1;
    exit(1);
  } //end if

  //Open datafile
  FILE * file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file \n");
    return 1;
    exit(1);
  } //end if

  int numDataCollections = 0;
  double minX = __DBL_MAX__;
  double minY = __DBL_MAX__;
  double maxX = -__DBL_MAX__;
  double maxY = -__DBL_MAX__;

  //Skip the header
  char header[256];
  fgets(header, sizeof(header), file);

  //Read through the datafile
  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {

    //Extract the X and Y positions
    double x;
    double y;
    sscanf(line, "%lf\t%lf", &x, &y);

    //Convert positions from mm to m
    x = x / 1000;
    y = y / 1000;

    //Check if new X and Y are a new max or min value
    if (x < minX) {
      minX = x;
    } //end if
    if (x > maxX) {
      maxX = x;
    } //end if
    if (y < minY) {
      minY = y;
    } //end if
    if (y > maxY) {
      maxY = y;
    } //end if

    numDataCollections++;

  } //end while

  /*
  //Output max and min X and Y
  printf("Max X position: %lf m \n", maxX);
  printf("Min X position: %lf m \n", minX);
  printf("Max Y position: %lf m \n", maxY);
  printf("Min Y position: %lf m \n", minX);
  printf("Number of points: %d \n", numDataCollections);
  */

  int numOfX = 172;
  int numOfY = numDataCollections / numOfX;

  printf("\nNumber of X positions: %d \n", numOfX);
  printf("Number of Y positions: %d \n\n", numOfY);

  //Compute X and Y spacing
  double deltaX = (maxX - minX) / (numOfX - 1);
  double deltaY = (maxY - minY) / (numOfY - 1);

  printf("\nDelta X value: %.10lf \n", deltaX);
  printf("Delta Y value: %.10lf \n\n", deltaY);

  //Allocate memory for the velocity matrices
  double ** xVelocityMatrix = malloc(numOfY * sizeof(double *));
  double ** yVelocityMatrix = malloc(numOfY * sizeof(double *));
  for (int i = 0; i < numOfY; i++) {
    xVelocityMatrix[i] = malloc(numOfX * sizeof(double));
    yVelocityMatrix[i] = malloc(numOfX * sizeof(double));
  } //end for

  //Reset file reading and skip header
  fseek(file, 0, SEEK_SET);
  fgets(header, sizeof(header), file);

  double maxXvelocity = -__DBL_MAX__;
  double maxYvelocity = -__DBL_MAX__;

  //Read through the datafile again to store velocity components
  int j = 0;
  int k = 0;
  while (fgets(line, sizeof(line), file) != NULL) {

    double x, y, xVelocity, yVelocity;
    sscanf(line, "%lf\t%lf\t%lf\t%lf", &x, &y, &xVelocity, &yVelocity);

    //Store velocity X and Y components in corresponding matrices
    xVelocityMatrix[j][k] = xVelocity;
    yVelocityMatrix[j][k] = yVelocity;

    //Check if new velocity components are a new max value
    if (xVelocity > maxXvelocity) {
      maxXvelocity = xVelocity;
    } //end if
    if (yVelocity > maxYvelocity) {
      maxYvelocity = yVelocity;
    } //end if

    k++;

    if (k == numOfX) {
      k = 0;
      j++;
    } //end if

  } //end while

  /*
  //Output max velocity components
  printf("Max X velocity: %lf m/s \n", maxXvelocity);
  printf("Max Y velocity: %lf m/s \n", maxYvelocity);
  */

  //Close file
  fclose(file);

  //Write velocity matrices to text files
  FILE * xVelocityFile = fopen("Xvel.txt", "w");
  FILE * yVelocityFile = fopen("Yvel.txt", "w");

  for (int l = 0; l < numOfY; l++) {
    for (int m = 0; m < numOfX; m++) {
      fprintf(xVelocityFile, "%lf\t", xVelocityMatrix[l][m]);
      fprintf(yVelocityFile, "%lf\t", yVelocityMatrix[l][m]);
    } //end for
    fprintf(xVelocityFile, "\n");
    fprintf(yVelocityFile, "\n");
  } //end for

  //Close velocity files
  fclose(xVelocityFile);
  fclose(yVelocityFile);

  //Allocate memory for the vortex matrix
  double ** vortexMatrix = malloc((numOfY - 4) * sizeof(double *));
  for (int o = 0; o < (numOfY - 4); o++) {
    vortexMatrix[o] = malloc((numOfX - 4) * sizeof(double));
  } //end for

  double vortexValue = 0;
  double maxVortex = -__DBL_MAX__;
  
  for (int i = 2; i < (numOfY - 2); i++) {
    for (int j = 2; j < (numOfX - 2); j++) {

      //Calculate the vortex value and assign it to the matrix
      vortexValue = (-(-xVelocityMatrix[i+2][j] + (8.0*xVelocityMatrix[i+1][j]) - (8.0*xVelocityMatrix[i-1][j]) + xVelocityMatrix[i-2][j]) / (12.0 * deltaX)) + ((-yVelocityMatrix[i][j+2] + (8.0*yVelocityMatrix[i][j+1]) - (8.0*yVelocityMatrix[i][j-1]) + yVelocityMatrix[i][j-2]) / (12.0 * deltaY));
      vortexMatrix[i-2][j-2] = vortexValue;

      //Check if new vortex value is a new max
      if (vortexValue > maxVortex) {
	maxVortex = vortexValue;
      } //end if

    } //end for
  } //end for

  /*
  //Output max vortex value
  printf("Max vortex value: %lf rad/s \n", maxVortex);
  */

  FILE * vortexFile = fopen("Vort.txt", "w");

  for (int p = 0; p < (numOfY - 4); p++) {
    for (int q = 0; q < (numOfX - 4); q++) {
      fprintf(vortexFile, "%lf\t", vortexMatrix[p][q]);
    } //end for
    fprintf(vortexFile, "\n");
  } //end for

  //Close velocity files
  fclose(vortexFile);

  //Free allocated memory
  for (int n = 0; n < numOfY; n++) {
    free(xVelocityMatrix[n]);
    free(yVelocityMatrix[n]);
  } //end for
  free(xVelocityMatrix);
  free(yVelocityMatrix);
  for (int r = 0; r < (numOfY - 4); r++) {
    free(vortexMatrix[r]);
  } //end for
  free(vortexMatrix);
  
  return 0;

} //end main
