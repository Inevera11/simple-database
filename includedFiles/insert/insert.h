#ifndef INSRT_H_
#define INSRT_H_
#include "../bufferInput/input.h"
#include <fnmatch.h>
#include <string.h>

int dbExists(char *tableName);
void insert(InputBuffer *input_buffer, char *tableName);

#endif