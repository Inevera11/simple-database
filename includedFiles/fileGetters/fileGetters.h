#ifndef FILEG_H_
#define FILEG_H_
#include "../bufferInput/input.h"
#include <string.h>

char **getColumnHeaders(FILE *file, int *numColumns);
char *getLastRowId(FILE *file);

#endif