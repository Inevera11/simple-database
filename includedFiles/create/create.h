#ifndef CRT_H_
#define CRT_H_
#include "../bufferInput/input.h"
#include <fnmatch.h>
#include <string.h>
#include <dirent.h>

void createTable(InputBuffer *input_buffer);
int dbExists(char *fileName);

#endif