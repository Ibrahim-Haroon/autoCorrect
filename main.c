//
//  main.c
//  autoCorrect
//
//  Created by Ibrahim Haroon on 2/16/23.

/*
input is take as the following :
4 <----num of words
this
is
an
example
4 <----num of words in sentence
this is an exmple
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "stdmap.h"
#include "stdstring.h"

#define TABLE_SIZE (470000)

int Levenshtein_Algo(char* incorrectSpelling, char* correctSpelling);
String* autoCorrect(String* sentence, Map* dictionary);
char* getClosestWord(Map* dictionary, String* incorrectSpelledWord);
void print_res_in_unnecessary_way(String* res);

int main(int argc, const char * argv[]) {
    
    Map* dictionary= init_map();
    //fill_map(dictionary);

    String* sentence = init_string();
    my_string_extraction(sentence, stdin);
    
    String* res = autoCorrect(sentence, dictionary);
    printf("%s\n", res ->data);
    destroy_map(&dictionary);
    destroy_string(&res);
    
    return 0;
}

String* autoCorrect(String* sentence, Map* dictionary) {
    String* errorFreeSentence = init_string();
    
    for (int i = 0; i < sentence ->size; i++) {
        String* currWord = init_string();
        int tempIndex = i;
        while (!isspace(sentence ->data[tempIndex])) {
            appendChar(sentence ->data[tempIndex], currWord);
            tempIndex++;
            i = tempIndex;
            if (sentence ->data[tempIndex] == '\0') break;
        }
        if (contains(dictionary, currWord)) {
            appendWord(currWord ->data, errorFreeSentence);
        }
        else {
            appendWord(getClosestWord(dictionary, currWord), errorFreeSentence);
        }
        destroy_string(&currWord);
    }

    return errorFreeSentence;
}

char* getClosestWord(Map* dictionary, String* incorrectSpelledWord) {
    String* closestWord = init_string();
    int global_numOfEdits = INT_MAX;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (dictionary ->entries[i] == NULL) continue;
        if (dictionary ->entries[i] ->value >= incorrectSpelledWord ->size - 2 &&
            dictionary ->entries[i] ->value <= incorrectSpelledWord ->size + 2) {
            int numOfEdits = Levenshtein_Algo(incorrectSpelledWord ->data, dictionary ->entries[i] ->key);
            if (numOfEdits < global_numOfEdits) {
                strCopy(closestWord, dictionary ->entries[i] ->key);
                global_numOfEdits = numOfEdits;
            }
            //check for collisions
            Pair* temp = dictionary ->entries[i];
            if (temp ->next != NULL) { //if a collision has occured
                temp = temp ->next;
                while (temp != NULL) {
                    numOfEdits = Levenshtein_Algo(incorrectSpelledWord ->data, temp ->key);
                    if (numOfEdits < global_numOfEdits) {
                        strCopy(closestWord, temp ->key);
                        global_numOfEdits = numOfEdits;
                    }
                    temp = temp ->next;
                }
            }
        }
        else if (dictionary ->entries[i] ->next != NULL) {
            Pair* temp = dictionary ->entries[i] ->next;
            while (temp != NULL) {
                if (temp ->value >= incorrectSpelledWord ->size - 2 &&
                    temp ->value <= incorrectSpelledWord ->size + 2) {
                    int numOfEdits = Levenshtein_Algo(incorrectSpelledWord ->data, temp ->key);
                    if (numOfEdits < global_numOfEdits) {
                        strCopy(closestWord, temp ->key);
                        global_numOfEdits = numOfEdits;
                    }
                }
            }
        }
    }
    
    return closestWord ->data;
}

int min(int num1, int num2, int num3) {
    int minimum = num1;
    if (num2 < minimum) {
        minimum = num2;
    }
    if (num3 < minimum) {
        minimum = num3;
    }
    
    return minimum;
}

int Levenshtein_Algo(char* incorrectSpelling, char* correctSpelling) {
    int incorrectLen = (int)strlen(incorrectSpelling), correctLen = (int)strlen(correctSpelling);
    int numOfRows = incorrectLen, numOfColumns = correctLen;
    int matrix[incorrectLen + 1][correctLen + 1];
    
    for (int row = 0; row <= numOfRows; row++) {
        matrix[row][0] = row;
    }
    for (int column = 0; column <= numOfColumns; column++) {
        matrix[0][column] = column;
    }
    
    for (int i = 1; i <= numOfRows; i++) {
        for (int j = 1; j <= numOfColumns; j++) {
            int diagonal = matrix[i - 1][j - 1], above = matrix[i][j - 1], left = matrix[i - 1][j];
            if (incorrectSpelling[i - 1] == correctSpelling[j - 1]) {
                matrix[i][j] = diagonal;
            }
            else {
                matrix[i][j] = min(diagonal, above, left) + 1;
            }
        }
    }
    
    return matrix[numOfRows][numOfColumns];
}
