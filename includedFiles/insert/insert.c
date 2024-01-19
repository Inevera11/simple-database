#include "insert.h"
#define COMMAND_LENGHT 12
#define MAX_COLUMN_NAMES_LENGHT 1024

int checkIfUserEnteredCorrectly(char *line, int quantity)
{
    char temp[MAX_COLUMN_NAMES_LENGHT];
    strcpy(temp, line);
    char *delimiter = " ";
    char *token;
    int i = 0;
    token = strtok(temp, delimiter);
    while (token != NULL)
    {
        i++;
        token = strtok(NULL, delimiter);
    };
    // column quantity - id column
    if (i == quantity - 1)
    {
        return 1;
    };
    printf("The expected words quantity do not match provided one.\n");
    return 0;
};

void insertValues(FILE *file)
{
    int columnsQuantity = 0;
    char **columns = getColumnHeaders(file, &columnsQuantity);
    printf("Provide values to insert (separated by spaces):");
    int i = 1;
    while (i < columnsQuantity)
    {
        printf(" %s", columns[i]);
        i++;
    }
    char newValues[MAX_COLUMN_NAMES_LENGHT];

    if (fgets(newValues, sizeof(newValues), stdin) == NULL || checkIfUserEnteredCorrectly(newValues, columnsQuantity) == 0)
    {
        printf("Error reading input\n");
        fclose(file);
        for (int i = 0; i < columnsQuantity; i++)
        {
            free(columns[i]);
        }
        free(columns);
        exit(EXIT_FAILURE);
    }

    char *lastRowId = getLastRowId(file);

    // add unique id automatically
    char currRowId[MAX_COLUMN_NAMES_LENGHT];
    if (strncmp(lastRowId, "id", 2) == 0)
    {
        strcpy(currRowId, "0 ");
    }
    else
    {
        sprintf(currRowId, "%d ", atoi(lastRowId) + 1);
    }
    // add id to provided values
    strcat(currRowId, newValues);
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s", currRowId);

    for (int i = 0; i < columnsQuantity; i++)
    {
        free(columns[i]);
    }
    free(columns);
};

void insertInto(InputBuffer *input_buffer)
{
    char *tableName = discardFrontCommand(input_buffer->buffer, input_buffer->input_length, COMMAND_LENGHT);
    if (tableName == NULL)
    {
        printf("Table name not provided\n");
        return;
    }
    char *fileName = appendDB(tableName, input_buffer->input_length - COMMAND_LENGHT);
    if (fileName == NULL)
    {
        printf("Memory allocation for fileName failed\n");
        return;
    }
    if (dbExists(fileName) == 0)
    {
        printf("No database %s created.\n", fileName);
        return;
    };

    FILE *file = fopen(fileName, "r+");
    if (file == NULL)
    {
        printf("Couldn't open a %s file\n", fileName);
        free(fileName);
        free(tableName);
        return;
    };
    insertValues(file);
    fclose(file);
    free(fileName);
    free(tableName);
};
