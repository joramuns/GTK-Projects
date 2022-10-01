install:
	@mkdir -p s21_smart_calc_1_0
	glib-compile-resources Style/gresource.xml --generate-source --target=resources.c
	gcc -g -c main-gtk.c resources.c GUI/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -g -o s21_smart_calc_1_0/s21_smart_calc *.o `pkg-config --libs gtk4`
	@$(MAKE) clean

uninstall:

dvi:
	@texi2dvi some.texi

dist: install
	tar -cvzf s21_smart_calc_1_0/s21_smart_calc_1_0.tar.gz s21_smart_calc_1_0/s21_smart_calc 
	@rm s21_smart_calc_1_0/s21_smart_calc

tests:
	gcc -g -c Testcases/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs check`
	gcc -g -o test *.o `pkg-config --cflags --libs check`
	./test
	@$(MAKE) fclean

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
	glib-compile-resources Style/gresource.xml --generate-source --target=resources.c
	@mkdir -p build
	gcc -fsanitize=address -g -c main-gtk.c resources.c GUI/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	gcc -fsanitize=address -g -o build/test *.o `pkg-config --libs gtk4`
	@$(MAKE) clean
	@build/test

clean:
	@rm -rf *.o *.gcda *.gcno *.info

fclean:
	@rm -rf *.o *.so *.gcda *.a *.gcno *.info test report build s21_smart_calc_1_0 resources.c
