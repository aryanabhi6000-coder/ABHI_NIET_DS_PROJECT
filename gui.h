#ifndef GUI_H
#define GUI_H

#include <windows.h>

#define ID_ADD 1
#define ID_DELETE 2
#define ID_VIEW 3
#define ID_LIST 4

void create_gui_elements(HWND hwnd);
void handle_commands(HWND hwnd, WPARAM wParam);

#endif