include config.mk

.PHONY: all test gcov_report static_check dvi lint

all: test gcov_report build

build: $(GRESOURCES_CMP) $(GSCHEMA_CMP) $(CORE_SRCS) $(GUI_SRCS) $(MAIN) $(CORE_H) $(GUI_H)
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(GL_CFLAGS) -I. \
		$(CORE_SRCS) $(GRESOURCES_CMP) $(GUI_SRCS) \
		$(MAIN) $(GTK_LIBS) $(GL_LIBS) -o $(APP)

$(GRESOURCES_CMP): $(GRESOURCES)
	glib-compile-resources $^ --target=$@ --generate-source

$(GSCHEMA_CMP): $(GSCHEMA)
	glib-compile-schemas .

test: $(CORE_SRCS) $(TEST_SRCS) $(CORE_H) $(TEST_H)
	-$(CC) $(CFLAGS) $(CHECK_CFLAGS) $(GLIB_CFLAGS) $(GL_CFLAGS) -I. \
		$(CORE_SRCS) $(TEST_SRCS) $(CHECK_LIBS) $(GLIB_LIBS) $(GL_LIBS) -o $(TEST_RUNNER)
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
		docs coverage $(GRESOURCES_CMP) $(GSCHEMA_CMP) $(ALL_GSYM)
