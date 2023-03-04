//
//  stdstring.c
//  autoCorrect
//
//  Created by Ibrahim Haroon on 3/3/23.
//

#include "stdstring.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

String* init_string(void) {
    String* newString = (String*) malloc(sizeof(String));
    if (newString == NULL) exit(EXIT_FAILURE);
    newString ->size = 0;
    newString ->capacity = 7;
    newString ->data = (char*) malloc(sizeof(char) * newString ->capacity);
    if (newString ->data == NULL) {
        free(newString);
        newString = NULL;
        exit(EXIT_FAILURE);
    }
    newString ->data[newString ->size] = '\0';
    return newString;
}

bool isFull(String* string) {
    if (string ->size >= string ->capacity) return true;
    return false;
}

#define LOAD_FACTOR (2)
void increaseSize(String* string) {
    char* biggerData = (char*) malloc(sizeof(char) * ((string ->capacity) * LOAD_FACTOR));
    if (biggerData == NULL) {
        printf("Unable to make a bigger string, heap FULL\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < string ->size; i++) {
        biggerData[i] = string ->data[i];
    }
    free(string ->data);
    string ->data = biggerData;
    string ->capacity *= LOAD_FACTOR;
    return;
}

void my_string_extraction(String* pString, FILE* fp) {
    if (fp == NULL) return;
    int c, noc;
    char c1;
    pString ->size = 0;
    noc = fscanf(fp, "%c", &c1);
    while (noc == 1 && isspace(c1)) {
        noc = fscanf(fp, "%c", &c1);
    }
    if (noc != 1) return;
    pString ->data[pString ->size] = c1;
    pString ->size++;

    c = fgetc(fp);
    while (c != EOF && c != '\n') {
        if (isFull(pString)) increaseSize(pString);
        pString ->data[pString ->size] = c;
        pString ->size++;
        c = fgetc(fp);
    }
    if (c != EOF) ungetc(c, fp);
    pString ->data[pString ->size] = '\0';
    return;
}

#define check if (isFull(string)) increaseSize(string);
#define sizeIncrement string ->size++;
void appendWord(char* word, String* string) {
    if (string ->size > 0) {
        string ->data[string ->size] = ' ';
        string ->size++;
    }
    for (int i = 0; i < (int)strlen(word); i++) {
        check
        string ->data[string ->size] = word[i];
        sizeIncrement
    }
    string ->data[string ->size] = '\0';
    return;
}

void appendChar(char letter, String* string) {
    if (isFull(string)) increaseSize(string);
    string ->data[string ->size] = letter;
    string ->size++;
    return;
}

void strCopy(String* destination, char* source) {
    char* temp = (char*) malloc(sizeof(strlen(source) + 1));
    int i;
    for (i = 0; i < (strlen(source) + 1); i++) {
        temp[i] = source[i];
    }
    temp[i] = '\0';
    free(destination ->data);
    destination ->data = temp;
    destination ->size = (int)strlen(source);
    destination ->capacity = (destination ->size) + 1;
    return;
}

void removeLastChar(String* string) {
    string ->size -= 1;
    return;
}

String* convert(char* word) {
    String* newString = init_string();
    free(newString ->data);
    newString ->data = word;
    newString ->size = (int)strlen(word);
    newString ->capacity = (int)(strlen(word) + 1); //+1 for '\0'
    
    return newString;
}

void destroy_string(String** string) {
    free((*string) ->data);
    free(*string);
    *string = NULL;
    return;
}


