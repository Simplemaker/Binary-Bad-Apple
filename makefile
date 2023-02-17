build: compressed.o main.o decompress.o
	gcc -o badapple compressed.o main.o decompress.o

main.o: main.c
	gcc -c main.c

decompress.o:
	gcc -c decompress.c

compressed.o: BadApple.lz4
	xxd -i "BadApple.lz4" | gcc -c -o compressed.o -x c -

BadApple.lz4: BadApple.bin
	lz4 -9 BadApple.bin BadApple.lz4

BadApple.bin:
	python extract.py

clean:
	rm -f badapple
	rm -f *.o

