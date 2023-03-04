//
//  stdmap.c
//  autoCorrect
//
//  Created by Ibrahim Haroon on 3/3/23.
//

#include "stdmap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE (470000)

Map* init_map(void) {
    Map* newMap = (Map*) malloc(sizeof(Map));
    if (newMap == NULL) exit(EXIT_FAILURE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        newMap ->entries[i] = NULL;
    }
    return newMap;
}

bool contains(Map* hashMap, String* str) {
    int index = hash(str);
    if (hashMap ->entries[index] == NULL) return false;
    if (strcmp(hashMap ->entries[index] ->key, str ->data) == 0) return true;
    Pair* temp = hashMap ->entries[index];
    temp = temp ->next;
    while (temp != NULL && strcmp(temp ->key, str ->data) != 0) {
        temp = temp ->next;
    }
    if (temp == NULL) return false;

    return true;
}

unsigned int ASCII_value(String* str) {
    unsigned int ascii = 0;
    for (int i = 0; i < str ->size; i++) {
        ascii += (int)(str ->data[i]);
    }
    return ascii;
}

unsigned int hash(String* str) {
    return (31 * ASCII_value(str) + 34) % TABLE_SIZE;
}

Pair* createPair(String* str) {
    Pair* newPair = (Pair*) malloc(sizeof(Pair));
    char* temp = (char*) malloc(sizeof(char) * str ->size);
    strcpy(temp, str ->data);
    newPair ->key = temp;
    newPair ->value = str ->size;
    newPair ->next = NULL;
    return newPair;
}

void insert_in_map(Map* hashMap, String* str) {
    Pair* pair = createPair(str);
    int index = hash(str);
    if (hashMap ->entries[index] == NULL) {
        hashMap ->entries[index] = pair;
        return;
    }
    Pair* temp = hashMap ->entries[index];
    temp = temp ->next;
    while (temp != NULL) {
        temp = temp ->next;
    }
    pair ->next = hashMap ->entries[index];
    hashMap ->entries[index] = pair;
    return;
}

void printMap(Map* hashMap) {
    if (hashMap == NULL) return;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashMap ->entries[i] == NULL) {
            printf("\t%d\t--<EMPTY>--\n", i);
            continue;
        }
        printf("\t%d\t{%s:%d}", i, hashMap ->entries[i] ->key, hashMap ->entries[i] ->value);
        if (hashMap ->entries[i] ->next != NULL) {
            Pair* temp = hashMap ->entries[i];
            temp = temp ->next;
            while (temp != NULL) {
                if (temp ->next == NULL) printf("NULL\n");
                else printf(" - {%s:%d}", temp ->key, temp ->value);
                temp = temp ->next;
            }
            continue;
        }
        printf("\n");
    }
    return;
}

void destroy_map(Map** hashMap) {
    if (*hashMap == NULL) {
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        Pair* current = (*hashMap)->entries[i];
        while (current != NULL) {
            Pair* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free((*hashMap) ->entries);
    *hashMap = NULL;
    return;
}


