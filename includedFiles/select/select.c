#include "select.h"
#define COMMAND_LENGHT 5
#define MAX_COLUMN_NAMES_LENGHT 1024
#define MAX_TOKEN_LENGTH 18
#define GUESSED_COL 4

void select(InputBuffer *input_buffer)
{

    const char *delimiter = " ";
    char **columnsToSelect = malloc(GUESSED_COL * sizeof(char *));
    int columsToSelectQuantity = 0;
    // fill in columns to select and their quantity with user input. Leave onlu table name in buffer
    determineColumnsToSelect(input_buffer, columnsToSelect, &columsToSelectQuantity);

    char *tableName = input_buffer->buffer;
    char *fileName;
    if (tableName == NULL)
    {
        printf("You forgot to provide table name.\n");
        freeMemory(columnsToSelect, columsToSelectQuantity, fileName, 0);
        return;
    }
    fileName = appendDB(tableName, input_buffer->input_length - COMMAND_LENGHT);
    if (fileName == NULL)
    {
        printf("Memory allocation failed");
        freeMemory(columnsToSelect, columsToSelectQuantity, fileName, 0);
        return;
    }
    if (dbExists(fileName) == 0)
    {
        printf("No database %s created.\n", fileName);
        freeMemory(columnsToSelect, columsToSelectQuantity, fileName, 1);
        return;
    };

    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Couldn't open a %s file\n", fileName);
        freeMemory(columnsToSelect, columsToSelectQuantity, fileName, 1);
    };

    int columnsHeadersQuantity = 0;
    char **columnsHeader = getColumnHeaders(file, &columnsHeadersQuantity);
    int columnsToShowIndexes[columnsHeadersQuantity];
    // fill in columnsToShowIndexes with 0 (don't show) and 1 (show)
    getColumnsToDisplayIndexes(columnsToSelect, columsToSelectQuantity, columnsHeader,
                               columnsHeadersQuantity, &columnsToShowIndexes);

    char currLine[MAX_COLUMN_NAMES_LENGHT];
    char truncatedToken[MAX_TOKEN_LENGTH + 1];
    fseek(file, 0, SEEK_SET);
    while (fgets(currLine, sizeof(currLine), file))
    {
        int i = 0;
        // Split the currLine into tokens
        char *token = strtok(currLine, delimiter);
        while (token != NULL)
        {
            if (i == 0 || columnsToShowIndexes[i] == 1)
            {
                // Print each token with a fixed width for alignment
                if (strlen(token) > MAX_TOKEN_LENGTH)
                {
                    strncpy(truncatedToken, token, MAX_TOKEN_LENGTH - 3);
                    truncatedToken[MAX_TOKEN_LENGTH - 3] = '\0'; // Null-terminate before appending
                    strcat(truncatedToken, "...");
                    printf("%-20s", truncatedToken);
                }
                else
                {
                    printf("%-20s", token);
                }
            }
            token = strtok(NULL, delimiter);
            i++;
        }
        printf("\n");
    }
    fclose(file);
    freeMemory(columnsToSelect, columsToSelectQuantity, fileName, 1);
}