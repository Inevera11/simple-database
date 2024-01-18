#ifndef CRT_H_
#define CRT_H_

#include "../bufferInput/input.h"
#define COLUMN_SIZE 255
#include <fnmatch.h>
#include <string.h>
#include <dirent.h>

typedef struct
{
    int id;
    char name[COLUMN_SIZE];
    char surname[COLUMN_SIZE];
} Row;

void createTable(InputBuffer *input_buffer);
int dbExists(char *fileName);

#endif