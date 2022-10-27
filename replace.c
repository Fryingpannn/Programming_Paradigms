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

// Creates a struct representing a changed file. Must be freed after.
ChangedFile* createChangedFile(char *filename, int changes) {
    // Allocate memory for the filename pointer and elements in struct
    ChangedFile *changedFile = malloc(sizeof(ChangedFile));
    // Must allocate memory for contents of pointers.  Here, strdup()
    // creates a new copy of name (str pointed by *filename).  Another option:
    // changedFile->filename = malloc(strlen(name)+1);
    // strcpy(changedFile->filename, filename);
    changedFile->filename = strdup(filename);
    changedFile->changes = changes;
    return changedFile;
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
    // First argument of argv is the execution's first argument.
    printf("The current directory is: %s.\n", argv[0]);
    printf("The input string is: %s (length: %lu).", argv[1], strlen(argv[1]));

    printf("\n\nPrinting files:\n");
    listFilesRecursively(cwd);

    // TODO: Clean allocated memory (structs, vars).
    printf("\n[END]\n");
    return 0;
}
