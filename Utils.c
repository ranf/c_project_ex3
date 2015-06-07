#include "Utils.h"

void* mallocAndVerify(size_t size) {
	void* ptr = malloc(size);
	if(ptr == NULL) {
		printf("Error allocating memory. Terminating program..\n");
		exit(EXIT_FAILURE);
	}
	return ptr;
}