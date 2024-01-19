#include "fileGetters.h"
#define COL_CONST 8

char **getColumnHeaders(FILE *file, int *numColumns)
{
    int guessedNumberOfColumns = COL_CONST;
    char **columns = malloc(guessedNumberOfColumns * sizeof(char *));
    fseek(file, 0, SEEK_SET);
    char firstLine[1024];
    if (fgets(firstLine, sizeof(firstLine), file) == NULL)
    {
        printf("Could not read the first line or the file is empty\n");
        return NULL;
    };
    char *delimiter = " ";
    char *token;
    int columnsQuantity = 0;
    // extract column headers from first line
    token = strtok(firstLine, delimiter);
    while (token != NULL)
    {
        if (columnsQuantity >= guessedNumberOfColumns)
        {
            guessedNumberOfColumns += COL_CONST;
            columns = realloc(columns, guessedNumberOfColumns * sizeof(char *));
        }
        columns[columnsQuantity] = strdup(token);
        columnsQuantity++;
        token = strtok(NULL, delimiter);
    };
    columns = realloc(columns, columnsQuantity * sizeof(char *));
    *numColumns = columnsQuantity;
    return columns;
};

char *getLastRowId(FILE *file)
{
    char line[1024];
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0)
    {
        printf("incorect file");
        return NULL;
    }

    long position = fileSize - 1;
    int foundNewline = 0;
    // Iterate backwards to find the newline character
    while (position >= 0)
    {
        fseek(file, position, SEEK_SET);
        if (fgetc(file) == '\n')
        {
            if (position != fileSize - 1)
            {
                foundNewline = 1;
                break;
            }
        }
        position--;
    }

    if (!foundNewline && position <= 0)
    {
        // File does not have a newline or only one line
        fseek(file, 0, SEEK_SET);
    }
    else
    {
        // go to the beggining of last line
        fseek(file, position + 1, SEEK_SET);
    }
    if (fgets(line, sizeof(line), file) == NULL)
    {
        printf("Could not read the line or the file is empty\n");
        return NULL;
    };
    return strtok(line, " ");
};