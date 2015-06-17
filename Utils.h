#ifndef UTILS_
#define UTILS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define printErrorMessage(func_name) (fprintf(stderr, "Error: standard function %s has failed\n", func_name))
#define printMessage(message) (printf("%s", message))

void* safeMalloc(size_t size);
void* safeRealloc(void* ptr, size_t size);
char* readString();
bool startsWith(const char *str, const char *pre);

#endif