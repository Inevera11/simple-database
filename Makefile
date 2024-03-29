CC=gcc
CFLAGS=-I.

db: main.c \
	includedFiles/bufferInput/input.c \
	includedFiles/create/create.c \
	includedFiles/fileGetters/fileGetters.c \
	includedFiles/select/select.c \
	includedFiles/selectHelpers/selectHelpers.c \
	includedFiles/insert/insert.c
	
	$(CC) $(CFLAGS) -o compiled_db main.c \
	includedFiles/bufferInput/input.c \
	includedFiles/create/create.c \
	includedFiles/selectHelpers/selectHelpers.c \
	includedFiles/select/select.c \
	includedFiles/fileGetters/fileGetters.c \
	includedFiles/insert/insert.c

clean: 
	rm -rf *.db
