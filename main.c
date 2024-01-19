#include <stdbool.h>
#include <string.h>
#include "includedFiles/create/create.h"
#include "includedFiles/insert/insert.h"
#include "includedFiles/select/select.h"

int main(int argc, char *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();
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
        else if (strncmp(input_buffer->buffer, "create table", 12) == 0)
        {
            createTable(input_buffer);
        }
        else if (strncmp(input_buffer->buffer, "insert into", 11) == 0)
        {
            insertInto(input_buffer);
        }
        else if (strncmp(input_buffer->buffer, "select", 6) == 0)
        {
            select(input_buffer);
        }
        else
        {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}