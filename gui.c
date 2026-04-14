#include "gui.h"
#include "student.h"
#include "hashmap.h"
#include <stdio.h>
#include <commdlg.h>

HWND hList, hNameEdit, hRemarkEdit, hSubjectEdit, hMarkEdit, hSemEdit;

void create_gui_elements(HWND hwnd) {
    CreateWindow("BUTTON", "Add Student", WS_VISIBLE | WS_CHILD, 10, 10, 100, 30, hwnd, (HMENU)ID_ADD, NULL, NULL);
    CreateWindow("BUTTON", "Delete Student", WS_VISIBLE | WS_CHILD, 120, 10, 100, 30, hwnd, (HMENU)ID_DELETE, NULL, NULL);
    CreateWindow("BUTTON", "View Student", WS_VISIBLE | WS_CHILD, 230, 10, 100, 30, hwnd, (HMENU)ID_VIEW, NULL, NULL);
    CreateWindow("BUTTON", "Add Subject", WS_VISIBLE | WS_CHILD, 340, 10, 100, 30, hwnd, (HMENU)5, NULL, NULL);
    CreateWindow("BUTTON", "Set Mark", WS_VISIBLE | WS_CHILD, 450, 10, 100, 30, hwnd, (HMENU)6, NULL, NULL);
    CreateWindow("BUTTON", "Add Document", WS_VISIBLE | WS_CHILD, 560, 10, 100, 30, hwnd, (HMENU)7, NULL, NULL);

    CreateWindow("STATIC", "Name:", WS_VISIBLE | WS_CHILD, 10, 50, 50, 20, hwnd, NULL, NULL, NULL);
    hNameEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 50, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Remark:", WS_VISIBLE | WS_CHILD, 10, 80, 50, 20, hwnd, NULL, NULL, NULL);
    hRemarkEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 70, 80, 200, 60, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Subject:", WS_VISIBLE | WS_CHILD, 10, 150, 50, 20, hwnd, NULL, NULL, NULL);
    hSubjectEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 150, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Sem:", WS_VISIBLE | WS_CHILD, 10, 180, 30, 20, hwnd, NULL, NULL, NULL);
    hSemEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 180, 50, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Mark:", WS_VISIBLE | WS_CHILD, 120, 180, 30, 20, hwnd, NULL, NULL, NULL);
    hMarkEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 160, 180, 50, 20, hwnd, NULL, NULL, NULL);

    hList = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | LBS_NOTIFY, 10, 210, 760, 350, hwnd, (HMENU)ID_LIST, NULL, NULL);
}

void handle_commands(HWND hwnd, WPARAM wParam) {
    switch (LOWORD(wParam)) {
        case ID_ADD:
            {
                char name[100];
                char remark[500];
                GetWindowText(hNameEdit, name, 100);
                GetWindowText(hRemarkEdit, remark, 500);
                if (strlen(name) > 0) {
                    Student* s = create_student(name);
                    set_remark(s, remark);
                    int id = insert_student(s);
                    char buf[200];
                    sprintf(buf, "ID: %d, Name: %s", id, name);
                    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buf);
                    SetWindowText(hNameEdit, "");
                    SetWindowText(hRemarkEdit, "");
                }
            }
            break;
        case ID_DELETE:
            {
                int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
                if (index != LB_ERR) {
                    char buf[200];
                    SendMessage(hList, LB_GETTEXT, index, (LPARAM)buf);
                    int id;
                    sscanf(buf, "ID: %d", &id);
                    if (delete_student(id)) {
                        SendMessage(hList, LB_DELETESTRING, index, 0);
                    }
                }
            }
            break;
        case ID_VIEW:
            {
                int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
                if (index != LB_ERR) {
                    char buf[200];
                    SendMessage(hList, LB_GETTEXT, index, (LPARAM)buf);
                    int id;
                    sscanf(buf, "ID: %d", &id);
                    Student* s = get_student(id);
                    if (s) {
                        char info[2000] = "Name: ";
                        strcat(info, s->name);
                        strcat(info, "\nRemark: ");
                        strcat(info, s->remark);
                        strcat(info, "\nSubjects and Marks:\n");
                        for (int sem = 0; sem < MAX_SEM; sem++) {
                            for (int subj = 0; subj < s->num_subjects; subj++) {
                                if (s->marks[sem][subj] > 0) {
                                    char temp[100];
                                    sprintf(temp, "Sem %d %s: %d\n", sem+1, s->subjects[subj], s->marks[sem][subj]);
                                    strcat(info, temp);
                                }
                            }
                        }
                        MessageBox(hwnd, info, "Student Info", MB_OK);
                    }
                }
            }
            break;
        case 5: // Add Subject
            {
                int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
                if (index != LB_ERR) {
                    char buf[200];
                    SendMessage(hList, LB_GETTEXT, index, (LPARAM)buf);
                    int id;
                    sscanf(buf, "ID: %d", &id);
                    Student* s = get_student(id);
                    if (s) {
                        char subj[100];
                        GetWindowText(hSubjectEdit, subj, 100);
                        add_subject(s, subj);
                        SetWindowText(hSubjectEdit, "");
                    }
                }
            }
            break;
        case 6: // Set Mark
            {
                int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
                if (index != LB_ERR) {
                    char buf[200];
                    SendMessage(hList, LB_GETTEXT, index, (LPARAM)buf);
                    int id;
                    sscanf(buf, "ID: %d", &id);
                    Student* s = get_student(id);
                    if (s) {
                        char sem_str[10], mark_str[10];
                        GetWindowText(hSemEdit, sem_str, 10);
                        GetWindowText(hMarkEdit, mark_str, 10);
                        int sem = atoi(sem_str);
                        int mark = atoi(mark_str);
                        // Assume subj_index is 0 for simplicity, or find by name
                        if (s->num_subjects > 0) {
                            set_mark(s, sem, 0, mark); // for first subject
                        }
                        SetWindowText(hSemEdit, "");
                        SetWindowText(hMarkEdit, "");
                    }
                }
            }
            break;
        case 7: // Add Document
            {
                int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
                if (index != LB_ERR) {
                    char buf[200];
                    SendMessage(hList, LB_GETTEXT, index, (LPARAM)buf);
                    int id;
                    sscanf(buf, "ID: %d", &id);
                    Student* s = get_student(id);
                    if (s) {
                        OPENFILENAME ofn;
                        char szFile[260];
                        ZeroMemory(&ofn, sizeof(ofn));
                        ofn.lStructSize = sizeof(ofn);
                        ofn.hwndOwner = hwnd;
                        ofn.lpstrFile = szFile;
                        ofn.lpstrFile[0] = '\0';
                        ofn.nMaxFile = sizeof(szFile);
                        ofn.lpstrFilter = "All Files\0*.*\0";
                        ofn.nFilterIndex = 1;
                        ofn.lpstrFileTitle = NULL;
                        ofn.nMaxFileTitle = 0;
                        ofn.lpstrInitialDir = NULL;
                        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                        if (GetOpenFileName(&ofn) == TRUE) {
                            add_document(s, szFile);
                        }
                    }
                }
            }
            break;
    }
}