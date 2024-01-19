#include "selectHelpers.h"

// create table [1,0,0,1...] which determines columns to show
void getColumnsToDisplayIndexes(char **columnsToSelect, int columnsQuantity,
                                char **headers, int headersQuantity, int (*indexes)[headersQuantity])
{
    int i = 0;
    while (i < headersQuantity)
    {
        int j = 0;
        if (columnsQuantity == 0)
        {
            (*indexes)[i] = 1;
        }
        else
        {
            (*indexes)[i] = 0;
        };
        while (j < columnsQuantity)
        { // last column name has new line at the end
            int len = strlen(headers[i]);
            char temp[len + 1];
            strcpy(temp, headers[i]);
            if (temp[len - 1] == '\n')
            {
                temp[len - 1] = '\0';
            };
            if (strcmp(temp, columnsToSelect[j]) == 0)
            {
                (*indexes)[i] = 1;
            };
            j++;
        };
        i++;
    };
};

void determineColumnsToSelect(InputBuffer *input_buffer, char **columnsToSelect, int *columnsQuantity)
{
    const char *delimiter = " ";
    char *originalBuffer = strdup(input_buffer->buffer);
    char *token = strtok(originalBuffer, delimiter);

    token = strtok(NULL, delimiter);
    if (token == NULL)
    { // handled in select function
        input_buffer->buffer = NULL;
        return;
    };
    if (strcmp(token, "*") == 0)
    {
        // remove "from"
        token = strtok(NULL, delimiter);
        // leave only table name in input buffer
        input_buffer->buffer = strtok(NULL, delimiter);
        return;
    };
    char *currColumn = strdup(token);
    // remove "from"
    token = strtok(NULL, delimiter);
    // remove "leave only table name in input buffer"
    input_buffer->buffer = strtok(NULL, delimiter);

    // create requested columns list
    char *temp = strtok(currColumn, ",");
    while (temp != NULL)
    {
        columnsToSelect[*columnsQuantity] = strdup(temp);
        *columnsQuantity += 1;
        temp = strtok(NULL, ",");
    };
};

void freeMemory(char **columnsToSelect, int columsQuantity,
                char *fileName, int shouldFreeFile)
{
    for (int i = 0; i < columsQuantity; i++)
    {
        free(columnsToSelect[i]);
    }
    free(columnsToSelect);
    if (shouldFreeFile)
    {
        free(fileName);
    };
}