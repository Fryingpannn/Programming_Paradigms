#include <stdlib.h>

typedef struct {
    char *array;
    size_t used;
    size_t size;
} Array;
void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, char element);
void freeArray(Array *a);
void printArray(Array *a);

int findAndReplace(char *path, char *targetWord);