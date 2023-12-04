#include <stdio.h>
#include "stdbool.h"
#include "ctype.h"

const int STRING_SIZE = 140;
const char DEF_CHAR = '.';
const int ASCII_OFFSET = 48;

int sizeOfNumber(char string[STRING_SIZE], int idxStartNo);

bool numTouchingChar(char string[STRING_SIZE][STRING_SIZE], int line, int startNbr, int sizeNbr);

int valueOfNumber(char string[STRING_SIZE][STRING_SIZE], int line, int startNbr, int sizeNbr);

int main() {
    FILE *filePTR;

    char string[STRING_SIZE];
    char engineScematics[140][140];
    int sizeNumber = 0;
    int idxNumber;
    int lineNumber;

    long int sum = 0;

    filePTR = fopen("EngineScematics.txt", "r");

    // put string in array
    for (int y = 0; y < STRING_SIZE; y++) {
        fgets(string, 150, filePTR);

        for (int x = 0; x < STRING_SIZE; x++) {
            engineScematics[y][x] = string[x];
        }

    }

    // Print array
    for (int y = 0; y < STRING_SIZE; y++){

        for (int x = 0; x < STRING_SIZE; x++){
            printf("%c", engineScematics[y][x]);

            // find number and its size
            if (isdigit(engineScematics[y][x])){

                sizeNumber = sizeOfNumber(engineScematics[y], x);

                if (numTouchingChar(engineScematics, y, x, sizeNumber)) {

                    int num = valueOfNumber(engineScematics, y, x, sizeNumber);

                    printf("(%d)",sizeNumber);
                    printf("%d + ", sum);

                    sum += num;

                    printf("%d ", num);
                }

                x = x + sizeNumber;


                // check if character is touching
            }




        }

        printf("\n%d %d: ", sum, y + 2);
    }

    printf("\n\n\n sum = %d", sum);

}

int sizeOfNumber(char string[STRING_SIZE], int idxStartNo) {

    int sizeNumber = 0;

    while (isdigit(string[idxStartNo + sizeNumber])) {
        sizeNumber++;
    }

    return sizeNumber;
}

bool numTouchingChar(char string[STRING_SIZE][STRING_SIZE], int line, int startNbr, int sizeNbr) {

    int endNbr = startNbr + (sizeNbr - 1);

    // check top
    if (line > 0) {

        // diagonal left
        if (startNbr > 0 && string[line - 1][startNbr - 1] != DEF_CHAR) return true;

        //top middle
        for (int i = 0; i < sizeNbr; i++) {

            if (string[line - 1][startNbr + i] != DEF_CHAR) return true;
        }

        // diagonal right
        if (endNbr < (STRING_SIZE - 1) && string[line - 1][endNbr + 1] != DEF_CHAR) return true;
    }

    // check bottom
    if (line < STRING_SIZE - 1) {

        // diagonal left
        if (startNbr > 0 && string[line + 1][startNbr - 1] != DEF_CHAR) return true;

        //bottom middle
        for (int i = 0; i < sizeNbr; i++) {

            if (string[line + 1][startNbr + i] != DEF_CHAR) return true;
        }

        // diagonal right
        if (endNbr < (STRING_SIZE - 1) && string[line + 1][endNbr + 1] != DEF_CHAR) return true;
    }


    // check left
    if (startNbr > 0 && string[line][startNbr - 1] != DEF_CHAR) return true;

    // check right
    if (endNbr < (STRING_SIZE - 1) && string[line][endNbr + 1] != DEF_CHAR) return true;

    return false;
}

int valueOfNumber(char string[STRING_SIZE][STRING_SIZE], int line, int startNbr, int sizeNbr) {

    switch (sizeNbr) {
        case 1:
            return string[line][startNbr] - ASCII_OFFSET;
            break;
        case 2:
            return (((string[line][startNbr]) - ASCII_OFFSET) * 10) + (string[line][startNbr + 1] - ASCII_OFFSET);
            break;
        case 3:
            return (((string[line][startNbr]) - ASCII_OFFSET) * 100) + (((string[line][startNbr + 1]) - ASCII_OFFSET) * 10) + (string[line][startNbr + 2] - ASCII_OFFSET);
            break;
        default:
            return 99999; //make it stand out in all those numbers
    }
}