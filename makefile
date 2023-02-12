build: BadAppleZip.o main.o
	gcc -o badapple BadAppleZip.o main.o -lzip

main.o: main.c
	gcc -c main.c

BadAppleZip.o: BadApple.zip
	xxd -i "BadApple.zip" | gcc -c -o BadAppleZip.o -x c -

BadApple.zip: Bad\ Apple.bin
	zip -9 -r BadApple.zip Bad\ Apple.bin

Bad\ Apple.bin:
	python extract.py

clean:
	rm -f badapple
	rm -f *.o
	rm -f BadApple.zip

BadApple.o: Bad\ Apple.bin
	xxd -i "Bad Apple.bin" | gcc -c -o BadApple.o -x c -