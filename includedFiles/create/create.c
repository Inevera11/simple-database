#include "create.h"
#define COMMAND_LENGHT 13
#define MAX_COLUMN_NAMES_LENGHT 1024

int dbExists(char *fileName)
{
    if (fileName == NULL)
    {
        return 0;
    };
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL)
    {
        perror("Error opening directory");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (fnmatch(fileName, entry->d_name, 0) == 0)
        {
            closedir(dir);
            return 1;
        }
    }
    closedir(dir);
    return 0;
}

void createTable(InputBuffer *input_buffer)
{
    char *tableName = discardFrontCommand(input_buffer->buffer, input_buffer->input_length, COMMAND_LENGHT);
    if (tableName == NULL)
    {
        printf("You forgot to provide table name.\n");
        return;
    }
    char *fileName = appendDB(tableName, input_buffer->input_length - COMMAND_LENGHT);
    if (fileName == NULL)
    {
        printf("Memory allocation failed");
        return;
    }
    if (dbExists(fileName) != 0)
    {
        printf("Database %s already exists.\n", fileName);
        return;
    };

    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Couldn't create a file\n");
        close_input_buffer(input_buffer);
        exit(EXIT_FAILURE);
    }
    printf("Provide column names (separated by spaces):\n");
    char columnNames[MAX_COLUMN_NAMES_LENGHT];

    if (fgets(columnNames, sizeof(columnNames), stdin) == NULL)
    {
        printf("Error reading input\n");
        fclose(file);
        close_input_buffer(input_buffer);
        free(tableName);
        free(fileName);
        exit(EXIT_FAILURE);
    }
    char tableHeader[MAX_COLUMN_NAMES_LENGHT] = "id ";
    strcat(tableHeader, columnNames);
    fprintf(file, "%s", tableHeader);

    fclose(file);
    free(tableName);
    free(fileName);
}