all:
	gcc -c main.c Stack/*.c Calculation/*.c
	gcc `pkg-config --cflags gtk4` -o test *.o `pkg-config --libs gtk4`
	./test
