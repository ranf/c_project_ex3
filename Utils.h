#ifndef UTILS_
#define UTILS_

#include <stdio.h>

#define printErrorMessage(func_name) (fprintf(stderr, "Error: standard function %s has failed\n", func_name))
#define printMessage(message) (printf("%s", message))

void* mallocAndVerify(size_t size);
char* readString();

#endif