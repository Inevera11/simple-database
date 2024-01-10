CC=gcc
CFLAGS=-I.

db: main.c \
	includedFiles/bufferInput/input.c
	
	$(CC) $(CFLAGS) -o compiled_db main.c \
	includedFiles/bufferInput/input.c
