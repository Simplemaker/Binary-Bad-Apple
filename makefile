build: BadApple.o main.o
	gcc -o badapple BadApple.o main.o

main.o: main.c
	gcc -c main.c

BadApple.o: Bad\ Apple.bin
	xxd -i "Bad Apple.bin" | gcc -c -o BadApple.o -x c -

Bad\ Apple.bin:
	python extract.py

clean:
	rm -f badapple
	rm -f *.o

