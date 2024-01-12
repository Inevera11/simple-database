#ifndef INPT_H_
#define INPT_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

void read_input(InputBuffer *input_buffer);

InputBuffer *new_input_buffer();

void printHelpCommand();

void print_prompt();

void close_input_buffer(InputBuffer *input_buffer);

#endif