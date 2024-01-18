#include "insert.h"
#define COMMAND_LENGHT 12

void insertInto(InputBuffer *input_buffer)
{
    char *tableName = discardFrontCommand(input_buffer->buffer, input_buffer->input_length, COMMAND_LENGHT);
    if (tableName == NULL)
    {
        printf("Memory allocation for tableName failed");
        return;
    }
    char *fileName = appendDB(tableName, input_buffer->input_length - COMMAND_LENGHT);
    if (fileName == NULL)
    {
        printf("Memory allocation for fileName failed");
        return;
    }

    printf("table name %s\n", tableName);
    printf("file name %s\n", fileName);

    if (dbExists(fileName) == 0)
    {
        printf("No database %s created.\n", fileName);
        return;
    };

    FILE *file = fopen(fileName, "a");
    if (file == NULL)
    {
        printf("Couldn't open a %s file\n", fileName);
        close_input_buffer(input_buffer);
        exit(EXIT_FAILURE);
    };
    // fprintf(file, "%s", tableName);
    printf("File %s opened!\n", fileName);
    fclose(file);
    free(fileName);
    free(tableName);
};