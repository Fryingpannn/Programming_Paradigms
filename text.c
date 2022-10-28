#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>

#include "text.h"
#include "replace.h"

// Opens a file and finds and replaces the substring
int findAndReplace(char *path, char *targetWord){
    FILE *fp;
    int c;
    // Temp buffer for file text
    Array buffer;
    initArray(&buffer, 30);

    // First read all from file and copy it to a buffer
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Failed to open file %s\n", path);
    }
    while(1) {
        c = fgetc(fp);

        if (feof(fp)) {
            break;
        }
        // Insert character in buffer
        insertArray(&buffer, c);
        //printf("%c", c);
    }
    fclose(fp);

    // Find and replace substring then replace text in original file
    // Use 2 pointers approach: modify buffer
    int changesCount = 0;
    int totalCount = 0;
    int i = 0;
    int k;
    while (i < buffer.used) {
        // skip this char if not a letter
        if (!isalpha(buffer.array[i])){
            i++;
            continue;
        }

        if (tolower(buffer.array[i]) == tolower(targetWord[0])) {
            int changeNeeded = 0;
            int temp = i;
            int intervalMax = temp + strlen(targetWord);
            for (k = 0; k <= strlen(targetWord); k++) {
                // If target word letter matches | Debugging: printf("\nMatch: Current targetWord[k]: %c", targetWord[k]);
                // Full word match: replace
                if (k == strlen(targetWord)) {
                    // Modify buffer to upper case | Debugging: //printf("\nFound equal"); //printf("\nInterval Max: %i", intervalMax);
                    while (temp < intervalMax) {
                        buffer.array[temp] = toupper(buffer.array[temp]);
                        temp++;
                        // To debug: printf("-temp: %i-", temp); // printf("[%c]", buffer.array[temp]);
                    }
                    k = 0;
                    if (changeNeeded == 1) {
                        changesCount++;
                    }
                    totalCount++;
                    break;
                }

                // If target word letter doesn't matches
                if (tolower(buffer.array[i]) != tolower(targetWord[k])) {
                    break;
                }

                // Keep track of if change is needed (e.g.: if already 'APPLE' all caps = no change)
                if (buffer.array[i] != toupper(targetWord[k])) {
                    changeNeeded = 1;
                }

                // If not full word, keep iterating
                i++;
            }
        }
        else {
            i++;
        }
    }

    fp = fopen(path, "w");
    int result = fputs(buffer.array, fp);
    if (result == EOF) {
        printf("Failed to write to file %s\n", path);
    }
    fclose(fp);

    freeArray(&buffer);
    // Uncomment for debugging
    //printf("\nTotal changes: %d.", changesCount);
    //printf("\nTotal occurence: %d.", totalCount);
    if (changesCount > 0) {
        ChangedFile newFile = createChangedFile(path, changesCount);
        insertFilesList(&changedFilesList, newFile);
    }
    return 0;
}

// Functions for the Array struct below

void initArray(Array *a, size_t initialSize) {
    a->array = malloc(initialSize * sizeof(char));
    a->used = 0;
    a->size = initialSize;
}
void insertArray(Array *a, char element) {
  // 'used' increments after being put, so use equality here
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(char));
  }
  a->array[a->used++] = element;
}
void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
void printArray(Array *a) {
    printf("[Printing array]:\n");
for (int i = 0; i < a->used; i++) {
        printf("%c", a->array[i]);
    }
}