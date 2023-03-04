//
//  stdmap.h
//  autoCorrect
//
//  Created by Ibrahim Haroon on 3/3/23.
//

#ifndef stdmap_h
#define stdmap_h
#include "stdstring.h"

#define TABLE_SIZE (470000)

typedef struct pair {
    char* key; //word
    int value; //str len
    struct pair* next;
}Pair;

typedef struct map{
    Pair* entries[TABLE_SIZE];
}Map;

Map* init_map(void);
bool contains(Map* hashMap, String* str);
unsigned int ASCII_value(String* str);
unsigned int hash(String* str);
void fill_map(Map* hashMap);
void insert_in_map(Map* hashMap, String* str);
void printMap(Map* hashMap);
void destroy_map(Map** hashMap);

#endif /* stdmap_h */

