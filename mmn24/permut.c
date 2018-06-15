#include <stdio.h>
#include <string.h>

#define ASCII_ENTRIES 256
#define MAX_WORD_LENGTH 80

void checkPermutation(FILE *inFile, char *wordPermutation);

int main(int argc, char *argv[]) {
    FILE *fp;
    if (argc != 3)
        printf("ERROR: The number of arguments is wrong");
    else if (!(fp = fopen(argv[1], "r")))
        printf("ERROR: Can't open the file");
    else
        checkPermutation(fp, argv[2]);
    return 0;
}

void checkPermutation(FILE *inFile, char *wordPermutation) {
    int histogram[ASCII_ENTRIES] = {0}, isLetterExist[ASCII_ENTRIES] = {0},
            permutationLength = strlen(wordPermutation), letterCount = permutationLength, wordCount = 0, c, i, j;
    char buffer[MAX_WORD_LENGTH + 1] = {0};

    /*Set the histogram by the given string*/
    char *pnt = wordPermutation;
    for (; *pnt; pnt++) {
        histogram[(unsigned) *pnt]++;
        isLetterExist[(unsigned) *pnt] = 1;
    }
    for (i = 0; (c = getc(inFile)) != EOF; i = (i + 1) % permutationLength) {
        /*take out the last letter from the letters calculations*/
        letterCount += isLetterExist[(unsigned) buffer[i]];
        histogram[(unsigned) buffer[i]] += isLetterExist[(unsigned) buffer[i]];

        /*insert the next char into the string*/
        buffer[i] = c;

        /*insert the next letter to the letters calculations*/
        letterCount -= isLetterExist[(unsigned) buffer[i]];
        histogram[(unsigned) buffer[i]] -= isLetterExist[(unsigned) buffer[i]];

        if (letterCount == 0) {
            for (j = 0; !histogram[j] && j < ASCII_ENTRIES; j++) /*checks number of occurrences of each letter*/
                ;
            if (j == ASCII_ENTRIES) { /*there is a permutation*/
                printf("%s", buffer + (i + 1) % permutationLength);
                printf("%.*s\n", (i + 1) % permutationLength, buffer);
                wordCount++;
            }
        }
    }
    if (wordCount == 0)
        puts("There are no permutations in the file");
}