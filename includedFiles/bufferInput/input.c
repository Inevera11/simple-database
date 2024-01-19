#include <string.h>
#include "input.h"

InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void read_input(InputBuffer *input_buffer)
{
    ssize_t bytes_read =
        getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void printHelpCommand()
{
    printf("Enter:\n"
           ".exit - terminate program\n"
           ".help - get command list\n"
           "create table <table_name> - create table\n"
           "insert into <table_name> - insert\n"
           "select * from <table_name> - show all table in a console\n"
           "select column1,column2 from <table_name> - show specific columns from table in a console\n");
}

void close_input_buffer(InputBuffer *input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

void print_prompt()
{
    printf("db > ");
};

char *appendDB(char *tableName, int tableNameLength)
{
    // Allocate memory for the filename (tableName + ".db" + null terminator)
    char *fileName = malloc(tableNameLength + 3 + 1);
    if (fileName == NULL)
    {
        return NULL;
    }
    // Copy the table name
    strcpy(fileName, tableName);
    // Append the file extension
    strcat(fileName, ".db");

    return fileName;
}

char *discardFrontCommand(char *input, int inputLength, int commandLenght)
{
    int tableNameLenght = inputLength - commandLenght;
    char *tableName = malloc(tableNameLenght);
    if (tableName == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < tableNameLenght; i++)
    {
        tableName[i] = input[commandLenght + i];
    };

    return tableName;
}