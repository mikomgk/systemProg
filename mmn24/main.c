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
    char extractedLine[MAX_WORD_LENGTH + 1] = {0}, *startWord = extractedLine, *endWord;
    /*Set the histogram by the given string*/
    char *pnt = wordPermutation;
    for (; *pnt; pnt++) {
        histogram[*pnt]++;
        isLetterExist[*pnt] = 1;
    }
    for (i = permutationLength; (c = getc(inFile)) != EOF; i++) { /*insert the next char into the string*/
        extractedLine[i % MAX_WORD_LENGTH] = c;
        /*move the right end of the frame one step forward*/
        endWord = extractedLine + i % MAX_WORD_LENGTH;

        /*updates the count of the histogram*/
        letterCount -= isLetterExist[*endWord];
        histogram[*endWord] -= isLetterExist[*endWord];
        letterCount += isLetterExist[*startWord];
        histogram[*startWord] += isLetterExist[*startWord];

        /*move the left end of the frame one step forward*/
        startWord = (extractedLine + (((startWord - extractedLine) % MAX_WORD_LENGTH + 1) % MAX_WORD_LENGTH));

        if (letterCount == 0) {
            for (j = 0; !histogram[j] && j < ASCII_ENTRIES; j++) /*checks number of occurrences of each letter*/
                ;
            if (j == ASCII_ENTRIES) { /*there is a permutation*/
                extractedLine[(j + 1) % MAX_WORD_LENGTH] = '\0';
                printf("%s", startWord);
                if (startWord > extractedLine + MAX_WORD_LENGTH - permutationLength)
                    printf("%s", extractedLine);
                printf("\n");
                wordCount++;
            }
        }
    }
    if (wordCount == 0)
        puts("There are no permutations in the file");
}

