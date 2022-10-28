#include <stdio.h>
#include <stdlib.h>

#include "replace.h"

// Comparator function to sort change files based on changes count
int cmpfunc (const void * a, const void * b) {
    return ( (*(ChangedFile*)b).changes - (*(ChangedFile*)a).changes);
}

// Prints the report
void printReport() {
    // Sort list of files for highest changes first
    qsort(changedFilesList.array, changedFilesList.used, sizeof(ChangedFile), cmpfunc);

    printFilesList(&changedFilesList);
}