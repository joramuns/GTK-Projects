CC=gcc -g
GCOV=gcc --coverage
CFLAGS=-std=c11 -pedantic -Wall -Werror -Wextra -c
OFLAGS=-std=c11 -pedantic -Wall -Werror -Wextra -o

all: install

install:
	@mkdir -p s21_smart_calc_1_0
	glib-compile-resources Style/gresource.xml --generate-source --target=resources.c
	$(CC) $(CFLAGS) main-gtk.c GUI/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	$(CC) -c resources.c `pkg-config --cflags --libs gtk4`
	$(CC) $(OFLAGS) s21_smart_calc_1_0/s21_smart_calc *.o `pkg-config --libs gtk4`
	@$(MAKE) clean

uninstall:
	@rm -rf s21_smart_calc_1_0
	@echo "S21 Smart Calc uninstalled!"

dvi:
	# goxygen dox_config
	# @texi2dvi latex/index.texi
	open html/index.html

dist: install
	tar -cvzf s21_smart_calc_1_0/s21_smart_calc_1_0.tar.gz s21_smart_calc_1_0/s21_smart_calc 
	@rm s21_smart_calc_1_0/s21_smart_calc

tests:
	$(CC) $(CFLAGS) Testcases/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs check`
	$(CC) $(OFLAGS) test *.o `pkg-config --cflags --libs check`
	./test
	# @$(MAKE) fclean

gcov_report:
	$(GCOV) $(CFLAGS) Testcases/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs check`
	$(GCOV) $(OFLAGS) test *.o `pkg-config --cflags --libs check`
	./test
	lcov -t "test" -o test.info -c -d . --rc lcov_branch_coverage=0
	genhtml -o report test.info --rc lcov_branch_coverage=0
	$(MAKE) clean
	open report/index.html

gtk:
	glib-compile-resources Style/gresource.xml --generate-source --target=resources.c
	@mkdir -p build
	$(CC) $(CFLAGS) -fsanitize=address main-gtk.c GUI/*.c Validation/*.c Calculation/*.c `pkg-config --cflags --libs gtk4`
	$(CC) -c resources.c `pkg-config --cflags --libs gtk4`
	$(CC) -fsanitize=address $(OFLAGS) build/test *.o `pkg-config --libs gtk4 glib-2.0`
	@$(MAKE) clean
	@build/test

clean:
	@rm -rf *.o *.gcda *.gcno *.info resources.c 

fclean:
	@rm -rf *.o *.so *.gcda *.a *.gcno *.info test report build s21_smart_calc_1_0 resources.c
