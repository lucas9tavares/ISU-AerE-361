#include <math.h>
#include <stdio.h>

// Thanks to Dr. Jeff Donahoo at Baylor University

int ComputeFactorial(int number) {
  int facto = 1;

  for (int j = 1; j <= number; j++) {
    facto = facto * j;
  }

  return facto;
}

double ComputeSeriesValue(double x, int n) {
  double seriesValue = 0.0;

  for (int k = 0; k <= n; k++) {
    seriesValue += x / ComputeFactorial(k);
  }

  return seriesValue;
}

void StringTest() {
  char temp[] = "HelLo";

  int i;

  temp[3] = 'l';

  for (i = 0 ; i < 5 ; i++ )
    printf("%c\n", temp[i]);
}

int main() {
  printf("This program is used to compute the value of the following series :\n");
  printf("x/0! + x/1! + x/2! + x/3! + x/4! + ........ + x/n! \n");

  double x;
  printf("Please enter the value of x : ");
  scanf("%lf", &x);

  int n;
  printf("Please enter an integer value for n : ");
  scanf("%d", &n);

  double seriesValue = ComputeSeriesValue(x, n);
  printf("The value of the series for the values entered is %lf\n", seriesValue);

  printf("String testing...\n");
  StringTest();

  return 0;
}
