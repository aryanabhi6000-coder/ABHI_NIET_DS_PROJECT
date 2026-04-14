#ifndef HASHMAP_H
#define HASHMAP_H

#include "student.h"

#define HASH_SIZE 100

typedef struct HashNode {
    int id;
    Student* student;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode* table[HASH_SIZE];
} HashMap;

void init_hashmap();
int generate_id();
int insert_student(Student* s);
Student* get_student(int id);
int delete_student(int id);
void free_hashmap();

#endif