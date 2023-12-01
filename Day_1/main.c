#include <stdio.h>
#include "ctype.h"
#include "string.h"

/// function that filters out all other characters except int
/// @param array the string to filter
/// @return the number hidden in the string.
int FilterString(char array[128]);


/// function that checks if a string contains written out int's
/// @param array the string to check for.
/// @return the number that is written or -1 if none
void StringIntToCharInt(char array[128]);

const int ASCII_OFFSET = 48;

int main() {
    FILE *filePtr;
    char string[128];
    int no;
    long int output = 0;

    filePtr = fopen("CalibrationValues.txt", "r");

    //fgets(string, 64,filePtr);

    while (fgets(string, 128, filePtr)) {

        //printf("\n%s ", string);

        StringIntToCharInt(string);

        no = FilterString(string);

        output += no;

        printf("%d ", output);
        printf("%d ", no);
        printf("%s", string);
    }

    printf("\nSum of all the numbers is: %d", output);

    fclose(filePtr);

    // codeblock to test the StringIntToCharIn

//    char test[] = "eighthreeightwosevenineoneightafiveightonetwothreefourfivesixseveneightnine";
//
//    printf("%s", test);
//
//    StringIntToCharInt(test);
//
//    printf("\n\n%s", test);

    return 0;
}

const int NO_OF_NOs = 15;
const int MAX_SIZE = 10;

// somehow constants give me error, dont want to fix it
char numbers[15][10] = {"zero","one","two","three","four","five","six","seven","eight","nine", "oneight", "threeight","sevenine", "eighthree", "fiveight"};

void StringIntToCharInt(char array[128]) {


    int index;
    char *ptr;

    // for loop that cycles though the array
    for (int i = NO_OF_NOs - 1; i >= 0; i--) {
        ptr = strstr(array, numbers[i]);

        // while loop loops till a NULL pointer aka substring not found
        while (ptr > 0) {
            index = ptr - array;

            if (i > 9) {
                switch (i) {
                    case 10:
                        array[index] = 1 + ASCII_OFFSET;
                        array[index + 2] = 8 + ASCII_OFFSET;
                        break;
                    case 11:
                        array[index] = 3 + ASCII_OFFSET;
                        array[index + 4] = 8 + ASCII_OFFSET;
                        break;
                    case 12:
                        array[index] = 7 + ASCII_OFFSET;
                        array[index + 4] = 9 + ASCII_OFFSET;
                        break;
                    case 13:
                        array[index] = 8 + ASCII_OFFSET;
                        array[index + 4] = 3 + ASCII_OFFSET;
                        break;
                    case 14:
                        array[index] = 5 + ASCII_OFFSET;
                        array[index + 3] = 8 + ASCII_OFFSET;
                }

            } else array[index] = i + ASCII_OFFSET;



            ptr = strstr(array, numbers[i]);
        }
    }

}

int FilterString(char array[128]) {

    int first_number = -1;
    int last_number = -1;

    // check chars in array if it is a number, if it's the case make the first one
    // first_number and the ones after that last_number (with more than 2 numbers
    // last_number gets overwritten)
    for (int i = 0; array[i] != '\0'; i++) {

        if (isdigit(array[i])) {
            if (first_number == -1) first_number = (int) array[i];
            else last_number = (int) array[i];
        }
    }

    // edge case if string has 1 number
    if (last_number == -1) last_number = first_number;

    // ascii to int
    first_number = first_number - ASCII_OFFSET;
    last_number = last_number - ASCII_OFFSET;

    return (first_number * 10) + last_number;
}
