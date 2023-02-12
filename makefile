
build: BadApple.o main.o
	gcc -o badapple BadApple.o main.o

main.o:
	gcc -c main.c

BadApple.o:
	xxd -i "Bad Apple.bin" | gcc -c -o BadApple.o -x c -

clean:
	rm badapple
	rm *.o
