
build:
	xxd -i "Bad Apple.bin" | gcc -o badapple -x c - main.c
