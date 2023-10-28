PROJECT = s21_3DViewer_v1.0
RELEASE =$(PROJECT).a

PLATFORM = $(shell uname -s)
CC = gcc
CFLAGS = -Wall  -Wextra -Werror -std=c11  -pedantic

ifeq ($(PLATFORM), Linux)
FLAGS_TST = -lcheck -lm -lsubunit
else
FLAGS_TST = -lcheck
endif

########################################################################################################################

# directories of project
BACK_DIR = backend/
DEBUG_DIR = debug/
FRONT_DIR = frontend/
TEST_DIR = tests/

BUILD_DIR = build/

# sourcecode files
BACK_C = $(BACK_DIR)*.c
DEBUG_C = $(DEBUG_DIR)*.c
FRONT_C = $(shell find $(FRONT_DIR) -name "*.c")
TEST_C = $(TEST_DIR)*.c
ALL_C = $(BACK_C) $(DEBUG_C) $(FRONT_C) $(TESTS_C)

########################################################################################################################

# Flags for linking and compilation
FLAGS_FTEST = -fprofile-arcs -ftest-coverage
FLAGS_COV = --coverage -g
FLAGS_GCONV = -r . --html --html-details -d
FLAGS_SANITIZE = -fsanitize=address -fsanitize=undefined

# Targets
.PHONY: all build rebuild install run uninstall gui dvi dvi_pdf dist test gcov_report style_check style_apply clean debug

all: clean build

build: gui

rebuild: clean build

install: build
	@mkdir -vp install
	@mkdir -vp install/materials
	@mkdir -vp install/samples
	@mkdir -vp install/shaders
	@cp -v build/frontend/viewer.app install
	@cp -rv build/frontend/materials/* install/materials/
	@cp -rv build/frontend/samples/* install/samples/
	@cp -rv build/frontend/shaders/* install/shaders/
	@rm -rf build/frontend

run:
	cd install && ./viewer.app || exit

uninstall:
	@rm -rvf install

gui:
	cmake -S frontend -B build/frontend -DCMAKE_BUILD_TYPE=RELEASE
	cd build/frontend && make || exit

dvi:
	@mkdir -vp doc/html
	@mkdir -vp doc/latex
	doxygen
	open doc/html/index.html

dvi_pdf:
	@mkdir -vp doc/html
	@mkdir -vp doc/latex
	doxygen
	cd doc/latex && make || exit
	open doc/latex/refman.pdf

dist: install
	@mkdir -vp Viewer-1.0
	@mkdir -vp Viewer-1.0/materials
	@mkdir -vp Viewer-1.0/samples
	@mkdir -vp Viewer-1.0/shaders
	@mkdir -vp dist
	@cp -rv install/* Viewer-1.0
	@tar -czvf dist/Viewer-1.0.tar.gz Viewer-1.0
	@rm -rf Viewer-1.0

test:
	rm -rf build/tests
	cmake -S tests -B build/tests -DCMAKE_BUILD_TYPE=DEBUG
	cd build/tests && make unit_tests && ./unit_tests || exit

gcov_report:
	rm -rf build/tests_coverage
	cmake -S tests -B build/tests_coverage -DCMAKE_BUILD_TYPE=DEBUG
	cd build/tests_coverage && \
	make unit_tests_coverage && \
	./unit_tests_coverage || exit
	cd build/tests_coverage/CMakeFiles/unit_tests_coverage.dir
	gcovr -r . --html --html-details -o build/tests_coverage/CMakeFiles/unit_tests_coverage.dir/coverage_report.html && \
#    rm -rf *.gcda *.gcno && \
    open build/tests_coverage/CMakeFiles/unit_tests_coverage.dir/coverage_report.html

debug:
	cmake -S debug -B build/debug -DCMAKE_BUILD_TYPE=DEBUG
	cd build/debug && make || exit
	./build/debug/back_debug.app

style_check:
	@mkdir -vp logs
	clang-format -n -style=Google $(ALL_C) 2>&1 | tee "logs/test_clang_$$(date +"%d_%m_%y__%H_%M_%S").log"

style_apply:
	@mkdir -vp logs
	clang-format -i -style=Google $(ALL_C) 2>&1 | tee "logs/test_clang_$$(date +"%d_%m_%y__%H_%M_%S").log"

clean:
	rm -rf build/*
	rm -rf logs/*
	rm -rf doc/*



########################################################################################################################

## compiled object files
#BACK_OBJS = $(BACK_DIR)*.o
#DEBUG_OBJS = $(DEBUG_DIR)*.o
#FRONT_OBJS = $(FRONT_DIR)*.o
#TEST_OBJS = $(TEST_DIR)*.o
#ALL_OBJS = $(BACK_OBJS) $(DEBUG_OBJS) $(FRONT_OBJS) $(TEST_OBJS)
#
## header files
#BACK_HDRS = $(BACK_DIR)*.h
#DEBUG_HDRS = $(DEBUG_DIR)*.h
#FRONT_HDRS = $(FRONT_DIR)*.h $(FRONT_DIR)common/*.h
#TEST_HDRS = $(TEST_DIR)*.h
#ALL_HDRS = $(BACK_HDRS) $(DEBUG_HDRS) $(FRONT_HDRS) $(TEST_HDRS)
#
## compiled object files
#BACK_OBJS = $(BACK_DIR)*.o
#DEBUG_OBJS = $(DEBUG_DIR)*.o
#FRONT_OBJS = $(FRONT_DIR)*.o
#TEST_OBJS = $(TEST_DIR)*.o
#ALL_OBJS = $(BACK_OBJS) $(DEBUG_OBJS) $(FRONT_OBJS) $(TEST_OBJS)
#
## compiled object files with coverage
#BACK_OBJS_COV = $(BACK_DIR)*.co
#DEBUG_OBJS_COV = $(DEBUG_DIR)*.co
#FRONT_OBJS_COV = $(FRONT_DIR)*.co
#TEST_OBJS_COV = $(TEST_DIR)*.co
#ALL_OBJS_COV = $(BACK_OBJS_COV) $(DEBUG_OBJS_COV) $(FRONT_OBJS_COV) $(TEST_OBJS_COV)