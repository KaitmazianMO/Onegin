#ifndef STDLIB_ADDITION_H_INCLUDED
#define STDLIB_ADDITION_H_INCLUDED

#include <stdio.h>

char *read_buff (FILE *file, size_t *size);
long file_size (FILE *file);
bool allocation_error (int _errno);

#endif