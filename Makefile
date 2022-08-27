all:
	gcc -fsanitize=address -g -c main.c calculator.c Validation/*.c Calculation/*.c
	gcc -fsanitize=address -g -o test *.o
	./test

gtk:
	gcc -g -c main.c calculator.c Validation/*.c Calculation/*.c
	gcc -g -o test *.o `pkg-config --libs gtk4`
	./test
