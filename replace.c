/**
 * Starting point of the program.
 * Takes in one command line string and searches for this string in other files under the current directory, and converts them to upper case. 
**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define _POSIX_C_SOURCE 1
#include <limits.h>

#include "replace.h"
#include "traversal.h"
#include "text.h"

// Creates a struct representing a changed file. Must be freed after.
ChangedFile createChangedFile(char *filename, int changes) {
    ChangedFile changedFile = {strdup(filename), changes};
    return changedFile;
}

// Comparator function to sort change files based on changes count
int cmpfunc (const void * a, const void * b) {
    return ( (*(ChangedFile*)a).changes - (*(ChangedFile*)b).changes );
}

int main(int argc, char *argv[]) {
    printf("\n");
    // Stop program if user did not input anything
    if (argc != 2) {
        printf("Please input a single string to the program.\n");
        return 0;
    }

    // TODO: full path vs relative
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s (length: %lu).\n", cwd, strlen(cwd));
    } else { 
        perror("Error getting current working directory.");
        return 1; 
    }
    printf("The input string is: %s (length: %lu).", argv[1], strlen(argv[1]));

    printf("\n\nPrinting all files:");
    // List to append all changed files to
    initFilesList(&changedFilesList, 10);
    // Recursively find all txt files and perform search and replace
    findFiles(argv[1], cwd);
    // Sort list of files for highest changes first
    //qsort(&changedFilesList, changedFilesList.used, sizeof(ChangedFile), cmpfunc);


    // Test array
    // Array arr; 
    // initArray(&arr, 20);
    // insertArray(&arr, 'h');
    // insertArray(&arr, 'e');
    // insertArray(&arr, 'l');
    // insertArray(&arr, 'l');
    // insertArray(&arr, 'o');
    // printArray(&arr);
    // freeArray(&arr);

    // TODO: Clean allocated memory (structs, vars, anything malloc'd).
    printf("\n");
    printFilesList(&changedFilesList);
    freeFilesList(&changedFilesList);
    printf("\n[END]\n");
    return 0;
}

// Functions for the FilesList struct below

void initFilesList(FilesList *a, size_t initialSize) {
    a->array = malloc(initialSize * sizeof(FilesList));
    a->used = 0;
    a->size = initialSize;
}
void insertFilesList(FilesList *a, ChangedFile element) {
  // 'used' increments after being put, so use equality here
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(FilesList));
  }
  a->array[a->used++] = element;
}
void freeFilesList(FilesList *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
void printFilesList(FilesList *a) {
    printf("[Printing changed files]:\n");
    for (int i = 0; i < a->used; i++) {
        printf("   %i. %s ", i, a->array[i].filename);
        printf("\n");
    }
}