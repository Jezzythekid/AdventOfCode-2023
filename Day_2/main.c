#include <stdio.h>
#include "ctype.h"
#include "string.h"
#include "stdbool.h"

const int ASCII_OFFSET = 48;
//const int MAX_RED = 12;
//const int MAX_GREEN = 13;
//const int MAX_BLUE = 14;


int checkString(char string[255], char keyWord[10]);

int checkIfValid(char string[255]);

int main() {
    FILE *filePtr;

    char string[255];
    long int sum = 0;

    filePtr = fopen("Games.txt", "r");

    while (fgets(string, 255, filePtr)) {

        printf("\n");
        sum += checkIfValid(string);

    }

    printf("\n\nThe sum of the valid games is: %d.", sum);
}

int checkString(char string[255], char keyWord[10]) {
    // check for keyword

    char *ptr;
    int Value;
    int MinValue = -1;

    ptr = strstr(string, keyWord);

    printf("%s: ", keyWord);

    while (ptr > 0) {

        *ptr = 'x';

        // check if two digits
        if (isdigit(*(ptr - 3))) {

            Value = ((*(ptr - 3) - ASCII_OFFSET) * 10) + *(ptr - 2) - ASCII_OFFSET;
            if (Value > MinValue) MinValue = Value;
            printf("v=%d min=%d ",Value, MinValue);
        } else {

            Value = *(ptr - 2) - ASCII_OFFSET;
            if (Value > MinValue) MinValue = Value;
            printf("v=%d min=%d ",Value, MinValue);
        }

        ptr = strstr(string, keyWord);
    }

    return MinValue;
}

int checkIfValid(char string[255]) {

    int gameNo = -1;
    int minRed;
    int minGreen;
    int minBlue;

    for (int i = 0; string[i] != '\0'; i++) {

        // Set game no
        if (isdigit(string[i]) && gameNo == -1) {

            // if 2 digits calculate gameNo
            if (isdigit(string[i + 1])) {

                // if 3 digits gameNo = 100
                if (isdigit(string[i + 2])) gameNo = 100;
                else {
                    gameNo = (string[i] - ASCII_OFFSET) * 10;
                    gameNo += (string[i + 1] - ASCII_OFFSET);
                }

            } else {
                gameNo = (string[i] - ASCII_OFFSET);
            }

        printf("Game no %d: ", gameNo);
        }

        if (gameNo != -1) {

            minRed = checkString(string, "red");
            minGreen = checkString(string, "green");
            minBlue = checkString(string, "blue");

            int pwr = minRed * minGreen * minBlue;

            printf(" || PWr = %d * %d * %d = %d",minRed, minGreen, minBlue, pwr);

            return pwr;

        }
    }
}