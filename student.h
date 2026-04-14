#ifndef STUDENT_H
#define STUDENT_H

#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_SUBJECTS 10
#define MAX_DOCS 5
#define MAX_REMARK 500
#define MAX_SEM 8
#define MAX_YEAR 4

typedef struct {
    char name[MAX_NAME];
    char subjects[MAX_SUBJECTS][MAX_NAME];
    int marks[MAX_SEM][MAX_SUBJECTS]; // marks[sem][subject]
    int num_subjects;
    int current_sem;
    char documents[MAX_DOCS][MAX_NAME]; // file paths or names
    int num_docs;
    char remark[MAX_REMARK];
} Student;

Student* create_student(const char* name);
void free_student(Student* s);
void add_subject(Student* s, const char* subj);
void set_mark(Student* s, int sem, int subj_index, int mark);
void add_document(Student* s, const char* doc);
void set_remark(Student* s, const char* remark);

#endif