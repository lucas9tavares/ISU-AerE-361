all: seq quad MyFloat bindec

seq: seq.c
	gcc seq.c -std=c99 -Wall -Werror -o seq -lm

quad: quad.c
	gcc quad.c -std=c99 -Wall -Werror -o quad -lm

MyFloat: MyFloat.c
	gcc MyFloat.c -std=c99 -Wall -Werror -o MyFloat -lm

bindec: bindec.c
	gcc bindec.c -std=c99 -Wall -Werror -o bindec -lm

clean:
	rm -rf bindec
	rm -rf MyFloat
	rm -rf quad
	rm -rf seq
