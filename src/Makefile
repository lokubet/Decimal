CC=gcc
CC_FLAGS=-Wall -Werror -Wextra -std=c11
CC_test=-fprofile-arcs -ftest-coverage
TESTS_FOLDER=tests/
OS=$(shell uname -s)

ifeq ($(OS),Linux)
	libs=-lcheck -lm -lsubunit
	open=xdg-open
else
	libs=-lcheck
	open=open
endif

all: s21_decimal.a gcov_report

s21_decimal.a: 
	$(CC) $(CC_FLAGS) -c *.c
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
	rm -f *.o

gcov_report: test
	lcov -t "test" -o $(TESTS_FOLDER)test.info -c -d .
	genhtml -o report $(TESTS_FOLDER)test.info
	$(open) report/index.html

test: clean
	$(CC) $(CC_FLAGS) $(CC_test) $(TESTS_FOLDER)*.c *.c -o test $(libs)
	./test
	mv *.gcda *.gcno $(TESTS_FOLDER)

valgrind: clean
	$(CC) -g $(CC_FLAGS) $(CC_test) -DVALGRIND_TEST $(TESTS_FOLDER)*.c *.c -o test $(libs)
	valgrind --tool=memcheck --leak-check=yes ./test
	mv *.gcda *.gcno $(TESTS_FOLDER)

clean:
	rm -f s21_decimal.a
	rm -f $(TESTS_FOLDER)*.gcda $(TESTS_FOLDER)*.gcno $(TESTS_FOLDER)test.info
	rm -f test
	rm -f *.o
	rm -rf report

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h */*.c */*.h
	rm -f .clang-format
