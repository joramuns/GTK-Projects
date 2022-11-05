include config.mk

.PHONY: all test gcov_report static_check dvi lint

all: test gcov_report build

build: $(G_RESOURCES) $(CORE_SRCS) $(GUI_SRCS) $(CORE_H) $(GUI_H)
	glib-compile-resources $(GRESOURCES) --target=$(GRESOURCES_SRC) --generate-source
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(GL_CFLAGS) -I. \
		$(CORE_SRCS) $(LIB_SRCS) $(GRESOURCES_SRC) $(GUI_SRCS) \
		$(MAIN) $(GTK_LIBS) $(GL_LIBS) -o $(APP)

test: $(CORE_SRCS) $(TEST_SRCS) $(CORE_H) $(TEST_H)
	-$(CC) $(CFLAGS) $(CHECK_CFLAGS) $(GLIB_CFLAGS) -I. \
		$(CORE_SRCS) $(TEST_SRCS) $(CHECK_LIBS) $(GLIB_LIBS) -o $(TEST_RUNNER)
	-$(MEM_CHECK) ./$(TEST_RUNNER)

gcov_report: test
	@mkdir -p $(COV_DIR)
	gcovr -b -p -d --html-details $(COV_REPORT) -e tests -e gui -e *.c . 
	open $(COV_REPORT)

static_check:
	-$(CPPC) $(CORE_SRCS) $(TEST_SRCS) $(GUI_SRCS) $(CORE_H) $(GUI_H) $(TEST_H)

dvi:
	@doxygen $(DOXYFILE)
	@make -C docs/latex

lint:
	$(LINTER) --style=Google $(CORE_SRCS) $(TEST_SRCS) $(CORE_H) $(TEST_H)
	$(LINTER) --style=GNU $(GUI_C) $(GUI_H)

clean:
	@rm -rf $(ALL_GCDA) $(ALL_GCNO) $(APP) $(TEST_RUNNER) \
		docs coverage $(GRESOURCES_SRC)
