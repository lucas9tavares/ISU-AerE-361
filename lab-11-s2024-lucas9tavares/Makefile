all: gauss_jordan gauss_seidel

gauss_seidel: gauss_seidel.c
	gcc gauss_seidel.c -std=c99 -Wall -Werror -o gauss-seidel -lm

gauss_jordan: gauss_jordan.c
	gcc gauss_jordan.c -std=c99 -Wall -Werror -o gauss-jordan

clean:
	rm -rf gauss-jordan
	rm -rf gauss-seidel
	rm -rf ans.csv
