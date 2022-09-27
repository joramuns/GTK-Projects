install:

uninstall:

dvi:

dist:

tests:
	gcc -g -c Testcases/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs check`
	gcc -g -o test *.o `pkg-config --cflags --libs check`
	./test
	$(MAKE) fclean

test-asan:
	gcc -fsanitize=address -g -c Testcases/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs check`
	gcc -fsanitize=address -g -o test *.o `pkg-config --cflags --libs check`
	./test
	$(MAKE) fclean

gcov_report:
	gcc --coverage -c Testcases/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs check`
	gcc --coverage -o test *.o `pkg-config --cflags --libs check`
	./test
	lcov -t "test" -o test.info -c -d . --rc lcov_branch_coverage=0
	genhtml -o report test.info --rc lcov_branch_coverage=0
	$(MAKE) clean
	open report/index.html

gtk:
	gcc -fsanitize=address -DNDEBUG -g -c main-gtk.c GUI/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -fsanitize=address -DNDEBUG -g -o test *.o `pkg-config --libs gtk4`
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
	rm -rf *.o *.gcda *.gcno *.info

fclean:
	rm -rf *.o *.so *.gcda *.a *.gcno *.info test report
