//
//  stdstring.h
//  autoCorrect
//
//  Created by Ibrahim Haroon on 3/3/23.
//

#ifndef stdstring_h
#define stdstring_h

#include <stdbool.h>
#include <stdio.h>

typedef struct string {
    int size;
    int capacity;
    char* data;
}String;

String* init_string(void);
bool isFull(String* string);
void increaseSize(String* string);
void my_string_extraction(String* pString, FILE* fp);
void appendWord(char* word, String* string);
void appendChar(char letter, String* string);
void strCopy(String* destination, char* source);
void removeLastChar(String* string);
String* convert(char* word);
void destroy_string(String** string);

#endif /* stdstring_h */
