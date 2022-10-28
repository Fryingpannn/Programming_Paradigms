/**
 * C program to list contents of a directory recursively.
 */
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#define _POSIX_C_SOURCE 1
#include <limits.h>
#include <sys/stat.h>

#include "traversal.h"
#include "text.h"

// Check if file is .txt
int isTxt(char const *name)
{
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;
}

// Checks if path is a directory
int isDirectory(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

/**
 * Find all text files recursively in the current directory.
 * Changes the targetWord found into all upper case.
 * Considers basePath as curernt directory.
*/
void findFiles(char *targetWord, char *basePath)
{
    char path[PATH_MAX];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir) {
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, "test-write-pan.txt"))
        {
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            // Open text only if text file
            if (isTxt(dp->d_name)){
                // Uncomment for debugging
                //printf("\n========");
                //printf("\nFilename: %s\n", dp->d_name);
                findAndReplace(path, targetWord);
            }

            // Recurse only if it's a directory
            if (isDirectory(path)) {
                findFiles(targetWord, path);
            }
        }
    }

    closedir(dir);
}