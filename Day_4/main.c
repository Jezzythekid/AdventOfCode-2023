#include <stdio.h>
#include "string.h"
#include "stdlib.h"

const int LINE_LENGTH = 120;
const int NO_OF_LINES = 201;
const int NO_OF_CARDS = 200;

/// function that compares the winning numbers to the personal numbers
/// @param array the string to parse
/// @return the amount of point won
int parseCard(char string[LINE_LENGTH]);

int main() {

    FILE *filePtr;
    char string[LINE_LENGTH];
    int noOfCards[NO_OF_CARDS] = {};
    int count = 0;
    int sum = 0;

    int matches = 0;

    filePtr = fopen("ScratchCards.txt", "r");

    for (int i = 0; i < NO_OF_CARDS; i++) {
        noOfCards[i] = 1;
    }


    while (fgets(string, LINE_LENGTH, filePtr)) {


        matches = parseCard(string + 10);

        for (int i = count; i < (count + matches); i++){
            noOfCards[i + 1] += noOfCards[i] * matches; ///@todo uitzoeken
        }



        count++;

    }

    printf("\n");

    for (int i = 0; i < NO_OF_CARDS; i++) {
        printf("\ncard[%d] = %d", i + 1, noOfCards[i]);
        sum += noOfCards[i];
    }

    fclose(filePtr);

    printf("\n\nsum = %d", sum);


    return 0;
}

int parseCard(char string[LINE_LENGTH]) {

    char *splitNbrs;
    int winningNbrs[10];
    int personalNbrs[25];
    int points;

    // split all numbers

    splitNbrs = strtok(string, " ");

    printf("w:");

    // write the first 10 numbers in winning array
    for (int i = 0; i < 10; i++){

        winningNbrs[i] = atoi(splitNbrs);

        printf("%d ", winningNbrs[i]);

        splitNbrs = strtok(NULL, " ");
    }

    printf("\np:");

    splitNbrs = strtok(NULL, " ");


    // write the other 25 numbers in the personal array
    for (int i = 0; i < 25; i++){

        personalNbrs[i] = atoi(splitNbrs);

        printf("%d ", personalNbrs[i]);

        splitNbrs = strtok(NULL, " ");
    }

    // compare the numbers

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 25; j++) {
            if (winningNbrs[i] == personalNbrs[j]){
                points++;
            }
        }

    }

    printf(" points: %d\n", points);
    return points;
}
