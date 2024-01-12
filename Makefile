CC=gcc
CFLAGS=-I.

db: main.c \
	includedFiles/bufferInput/input.c \
	includedFiles/create/create.c
	
	$(CC) $(CFLAGS) -o compiled_db main.c \
	includedFiles/bufferInput/input.c \
	includedFiles/create/create.c
