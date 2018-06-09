#include <stdio.h>
#include <string.h>

#define ASCII_ENTRIES 256
#define MAX_WORD_LENGTH 80

void checkPermuntation(FILE *inFile, char *wordPermuntation);

int main(int argc, char *argv[]) {
    FILE *fp;
    if (argc != 3)
        printf("ERROR: The number of arguments is wrong");
    else if (!(fp = fopen(argv[1], "r")))
        printf("ERROR: Can't open the file");
    else
        checkPermuntation(fp, argv[2]);
}

void checkPermuntation(FILE *inFile, char *wordPermuntation) {
    int histogram[ASCII_ENTRIES] = {0}, isLetterExist[ASCII_ENTRIES] = {0},
            permuntationLength = strlen(wordPermuntation), letterCount = permuntationLength, wordCount = 0, c, i;
    char extractedLine[MAX_WORD_LENGTH], *startWord = extractedLine, *endWord = extractedLine + permuntationLength;
    /*Set the histogram by the given string*/
    for (char *pnt = wordPermuntation; *pnt; pnt++) {
        histogram[*pnt]++;
        isLetterExist[*pnt] = 1;
    }
    for (int i = permuntationLength; (c = getc(inFile)); i++) { /*insert the next char into the string*/
        extractedLine[i % MAX_WORD_LENGTH]=c;
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
            for (i = 0; !histogram[i] && i < ASCII_ENTRIES; i++) /*checks number of occurrences of each letter*/
                ;
            if (i == ASCII_ENTRIES) { /*there is a permutation*/
                extractedLine[(i + 1) % MAX_WORD_LENGTH] = '\0';
                puts(startWord);
                wordCount++;
            }
        }
    }

}

