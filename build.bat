@echo off
gcc -c main.c -o main.o
gcc -c student.c -o student.o
gcc -c hashmap.c -o hashmap.o
gcc -c gui.c -o gui.o
gcc main.o student.o hashmap.o gui.o -o student_management.exe -lgdi32 -luser32 -lkernel32 -lcomdlg32