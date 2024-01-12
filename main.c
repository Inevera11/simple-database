#include <stdbool.h>
#include <string.h>
#include "includedFiles/create/create.h"
#include "includedFiles/insert/insert.h"

int main(int argc, char *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();
    char *lastUsedTableName = NULL;
    while (true)
    {
        print_prompt();
        read_input(input_buffer);
        if (input_buffer->buffer[0] == '.')
        {
            if (strcmp(input_buffer->buffer, ".help") == 0)
            {
                printHelpCommand();
            }
            else if (strcmp(input_buffer->buffer, ".exit") == 0)
            {
                close_input_buffer(input_buffer);
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("Unrecognized command '%s'.\n", input_buffer->buffer);
            }
        }
        else if (strncmp(input_buffer->buffer, "createTable", 11) == 0)
        {
            createTable(input_buffer, &lastUsedTableName);
        }
        else if (strncmp(input_buffer->buffer, "insert", 6) == 0)
        {
            if (dbExists(lastUsedTableName) == 0)
            {
                printf("No database %s created.\n", lastUsedTableName);
            }
            else
            {
                printf("Found.");
            };
        }
        else
        {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}