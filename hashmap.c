#include "hashmap.h"
#include <stdlib.h>

HashMap hashmap;
static int next_id = 1;

unsigned int hash(int id) {
    return id % HASH_SIZE;
}

void init_hashmap() {
    memset(hashmap.table, 0, sizeof(hashmap.table));
}

int generate_id() {
    return next_id++;
}

int insert_student(Student* s) {
    int id = generate_id();
    unsigned int index = hash(id);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    if (!node) return -1;
    node->id = id;
    node->student = s;
    node->next = hashmap.table[index];
    hashmap.table[index] = node;
    return id;
}

Student* get_student(int id) {
    unsigned int index = hash(id);
    HashNode* node = hashmap.table[index];
    while (node) {
        if (node->id == id) return node->student;
        node = node->next;
    }
    return NULL;
}

int delete_student(int id) {
    unsigned int index = hash(id);
    HashNode* node = hashmap.table[index];
    HashNode* prev = NULL;
    while (node) {
        if (node->id == id) {
            if (prev) prev->next = node->next;
            else hashmap.table[index] = node->next;
            free_student(node->student);
            free(node);
            return 1;
        }
        prev = node;
        node = node->next;
    }
    return 0;
}

void free_hashmap() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = hashmap.table[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free_student(temp->student);
            free(temp);
        }
    }
}