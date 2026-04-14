CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lgdi32 -luser32 -lkernel32 -lcomdlg32

TARGET = student_management.exe
OBJS = main.o student.o hashmap.o gui.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.c student.h hashmap.h gui.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c

hashmap.o: hashmap.c hashmap.h student.h
	$(CC) $(CFLAGS) -c hashmap.c

gui.o: gui.c gui.h student.h hashmap.h
	$(CC) $(CFLAGS) -c gui.c

clean:
	del $(OBJS) $(TARGET)