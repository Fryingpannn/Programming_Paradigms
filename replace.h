

//char *inputWord;

typedef struct ChangedFile {
    char *filename;
    int changes;
} ChangedFile;

ChangedFile* createChangedFile(char *filename, int changed);

int main(int argc, char *argv[]);

typedef struct {
    ChangedFile *array;
    size_t used;
    size_t size;
} FilesList;

void initFilesList(FilesList *a, size_t initialSize);
void insertFilesList(FilesList *a, ChangedFile element);
void freeFilesList(FilesList *a);
void printFilesList(FilesList *a);