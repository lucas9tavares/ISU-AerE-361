all: kirchhoff_solve

kirchhoff_solve: kirchhoff_solve.c
	gcc -Wall -std=c99 kirchhoff_solve.c -lgsl -lgslcblas -o kirchhoff_solve

clean:
	rm -rf kirchhoff_solve
	rm -rf ans.csv
