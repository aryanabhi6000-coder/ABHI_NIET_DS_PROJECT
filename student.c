#include "student.h"

Student* create_student(const char* name) {
    Student* s = (Student*)malloc(sizeof(Student));
    if (s) {
        strcpy(s->name, name);
        s->num_subjects = 0;
        s->current_sem = 1;
        s->num_docs = 0;
        memset(s->marks, 0, sizeof(s->marks));
        memset(s->subjects, 0, sizeof(s->subjects));
        memset(s->documents, 0, sizeof(s->documents));
        s->remark[0] = '\0';
    }
    return s;
}

void free_student(Student* s) {
    free(s);
}

void add_subject(Student* s, const char* subj) {
    if (s->num_subjects < MAX_SUBJECTS) {
        strcpy(s->subjects[s->num_subjects++], subj);
    }
}

void set_mark(Student* s, int sem, int subj_index, int mark) {
    if (sem >= 1 && sem <= MAX_SEM && subj_index >= 0 && subj_index < s->num_subjects) {
        s->marks[sem-1][subj_index] = mark;
    }
}

void add_document(Student* s, const char* doc) {
    if (s->num_docs < MAX_DOCS) {
        strcpy(s->documents[s->num_docs++], doc);
    }
}

void set_remark(Student* s, const char* remark) {
    strcpy(s->remark, remark);
}