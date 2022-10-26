/**
 * Starting point of the program.
 * Takes in one command line string and searches for this string in other files under the current directory, and converts them to upper case. 
**/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("%d", argc);
    // First argument of argv is current path
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
    }
    return 0;
}
