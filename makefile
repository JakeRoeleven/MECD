CC=gcc
CFLAGS=-lm

make: main.c 
	$(CC) -Wall -ansi -o main.out main.c libs/Compression/compression.c libs/Records/records.c libs/Encryption/encryption.c