#include <string.h>
#include "create.h"

void createTable(InputBuffer *input_buffer)
{
    strtok(input_buffer->buffer, " ");
    // clip buffer to keep the string after createTable
    char *fileName = strtok(NULL, "");
    FILE *file = fopen(strcat(fileName, ".db"), "a");
    if (file == NULL)
    {
        printf("Couldn't create a file\n");
        close_input_buffer(input_buffer);
        exit(EXIT_FAILURE);
    }
    // delete .db
    char *tableName = strtok(fileName, ".");
    fprintf(file, "%s", tableName);
    printf("Table %s created! Now you can perform insert operation\n", tableName);
    fclose(file);
}