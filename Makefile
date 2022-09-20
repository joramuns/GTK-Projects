test:
	gcc -fsanitize=address -g -c Tests/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs check`
	gcc -fsanitize=address -g -o test *.o `pkg-config --cflags --libs check`
	./test
	$(MAKE) fclean

test-noasan:
	gcc -g -c main.c Validation/*.c Calculation/*.c
	gcc -g -o test *.o
	./test

gtk:
	gcc -fsanitize=address -g -c main-gtk.c GUI/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -fsanitize=address -g -o test *.o `pkg-config --libs gtk4`
	$(MAKE) clean
	./test

gtk-lasan:
	gcc -fsanitize=leak -g -c main-gtk.c GUI/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -fsanitize=leak -g -o test *.o `pkg-config --libs gtk4`
	./test

gtk-noasan:
	gcc -g -c main-gtk.c GUI/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -g -o test *.o `pkg-config --libs gtk4`
	./test

clean:
	rm -rf *.o 

fclean:
	$(MAKE) clean
	rm -rf test
