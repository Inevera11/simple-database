#ifndef SLCTH_H_
#define SLCTH_H_
#include "../fileGetters/fileGetters.h"
#include "../create/create.h"
#include <string.h>

void determineColumnsToSelect(InputBuffer *input_buffer, char **columnsToSelect, int *columnsQuantity);
void freeMemory(char **columnsToSelect, int columsQuantity, char *fileName, int shouldFreeFile);
void getColumnsToDisplayIndexes(char **columnsToSelect, int columnsQuantity,
                                char **headers, int headersQuantity, int (*indexes)[headersQuantity]);
#endif