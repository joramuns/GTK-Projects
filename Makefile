all:
	gcc -fsanitize=address -g -c main.c calculator.c Validation/*.c Calculation/*.c
	gcc -fsanitize=address -g -o test *.o
	./test

gtk:
	gcc -fsanitize=address -g -c main-gtk.c calculator.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -fsanitize=address -g -o test *.o `pkg-config --libs gtk4`
	./test

clean:
	rm -rf *.o test
