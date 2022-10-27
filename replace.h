
char *inputWord;

typedef struct ChangedFile {
    char *filename;
    int changes;
} ChangedFile;

ChangedFile* createChangedFile(char *filename, int changed);

int main(int argc, char *argv[]);