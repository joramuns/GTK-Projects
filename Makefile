test:
	gcc -fsanitize=address -g -c main.c calculator.c credit_calculator.c Validation/*.c Calculation/*.c
	gcc -fsanitize=address -g -o test *.o
	./test

test-noasan:
	gcc -g -c main.c calculator.c credit_calculator.c Validation/*.c Calculation/*.c
	gcc -g -o test *.o
	./test

gtk:
	gcc -fsanitize=address -g -c GUI/*.c calculator.c credit_calculator.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -fsanitize=address -g -o test *.o `pkg-config --libs gtk4`
	./test

gtk-lasan:
	gcc -fsanitize=leak -g -c GUI/*.c calculator.c credit_calculator.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -fsanitize=leak -g -o test *.o `pkg-config --libs gtk4`
	./test

gtk-noasan:
	gcc -g -c GUI/*.c calculator.c credit_calculator.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -g -o test *.o `pkg-config --libs gtk4`
	./test

clean:
	rm -rf *.o test
