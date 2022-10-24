PROJECT_NAME := 3DViewer
VERSION := 0.1


KERN := $(shell uname -s)

CC         := gcc
CFLAGS     := -Wall -Wextra -g3 --coverage
GTK_FLAGS  := -g3
ifdef ASAN
	CFLAGS += -fsanitize=address
endif

# GTK dependencies
GTK_CFLAGS := $(shell pkg-config --cflags gtk4)
GTK_LIBS := $(shell pkg-config --libs gtk4)

#GLib dependencies
GLIB_CFLAGS := $(shell pkg-config --cflags glib-2.0)
GLIB_LIBS := $(shell pkg-config --libs glib-2.0)

# Check dependencies
CHECK_CFLAGS := $(shell pkg-config --cflags check)
CHECK_LIBS := $(shell pkg-config --libs check)

# Opengl dependencies
GL_CFLAGS := $(shell pkg-config --cflags epoxy)
GL_LIBS := $(shell pkg-config --libs epoxy)

# Static check flags
CPPC       := cppcheck --enable=all --suppress=missingIncludeSystem
LINTER     := clang-format -i

# Dynamic memory check tool
ifeq ($(KERN),Darwin)
	MEM_TOOL := leaks -atExit --
else
	VGDUMP   := vgdump.txt
	MEM_TOOL := valgrind --leak-check=full \
                         --show-leak-kinds=definite \
                         --leak-resolution=high \
                         --num-callers=20 \
                         --log-file=$(VGDUMP) \
                         --suppressions=smartcalc.supp \
                         -q --gen-suppressions=all
endif

ifdef LEAKS
	MEM_CHECK := $(MEM_TOOL)
endif

# Sources
CORE_SRCS := $(shell find core -name "*.c")
CORE_H := $(shell find core -name "*.h")
GUI_SRCS := $(shell find gui -name "*.c")
GUI_H := $(shell find gui -name "*.h")
MAIN := main.c
TEST_SRCS :=$(shell find tests -name "*.c") 
TEST_H :=$(shell find tests -name "*.h") 
GRESOURCES := 3dviewer.gresource.xml
GRESOURCES_SRC := resources.c

# Executables and objects
APP := 3DViewer
TEST_RUNNER := test_runner

COV_DIR := coverage
COV_REPORT := $(COV_DIR)/index.html
ALL_GCDA := $(shell find . -name "*.gcda")
ALL_GCNO := $(shell find . -name "*.gcno")

DOXYFILE := Doxyfile
