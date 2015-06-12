#include "Utils.h"

void* mallocAndVerify(size_t size) {
	void* ptr = malloc(size);
	if(ptr == NULL) {
		printf("Error allocating memory. Terminating program..\n");
		exit(EXIT_FAILURE);
	}
	return ptr;
}

char* readString()
{
	size_t size = 10;
	char *str;
	int ch;
	size_t len = 0;
    str = malloc(sizeof(char)*size);//size is start size
    while(EOF!=(ch=fgetc(stdin)) && ch != '\n'){
    	str[len++]=ch;
    	if(len==size){
    		str = realloc(str, sizeof(char)*(size+=16));
    	}
    }
    str[len++]='\0';
    return realloc(str, sizeof(char)*len);
}

bool startsWith(const char *str, const char *pre) {
	size_t lenpre = strlen(pre);
	size_t lenstr = strlen(str);
	return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}