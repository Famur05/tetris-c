#===========================================================================
CC = gcc
FLAGS = -std=c11 -Wall -Werror -Wextra
#===========================================================================
TARGET = tetris.a
#===========================================================================
OS := $(shell uname -s)
#===========================================================================
ifeq ($(OS), Linux)
    TEST_FLAGS = -lcheck -lrt -lpthread -lsubunit -lm
else
    TEST_FLAGS = -lcheck -lm
endif
#===========================================================================
tetris_c = brick_game/tetris/*.c gui/cli/*.c
tetris_h = brick_game/tetris/*.h gui/cli/*.h
#===========================================================================
all: install

install:
	$(CC) $(FLAGS) $(tetris_c) -lncurses -o tetris

uninstall:
	rm -rf tetris

$(TARGET):
	$(CC) $(FLAGS) -c brick_game/tetris/*.c
	ar rcs $(TARGET) *.o
	ranlib $(TARGET)
	rm -rf *.o

test: $(TARGET)
	$(CC) $(FLAGS) tests/tests.c $(TARGET) $(TEST_FLAGS) -o test.out
	./test.out

gcov_report: clean
	$(CC) $(FLAGS) tests/tests.c brick_game/tetris/*.c $(TEST_FLAGS) --coverage -o coverage.out
	./coverage.out
	lcov -c -d ./ -o coverage.info
	genhtml -o coverage_html coverage.info 
	open coverage_html/index.html

dvi:
	open images/dvi.png

dist: clean
	mkdir archived_tetris
	cp -r $(shell ls | grep -v archived_tetris) archived_tetris
	tar -czvf archived_tetris.tar.gz archived_tetris
	rm -rf archived_tetris

clang_i:
	clang-format -i -style=Google $(tetris_c) $(tetris_h) tests/*.c

clang_n:
	clang-format -n -style=Google $(tetris_c) $(tetris_h) tests/*.c

clean:
	rm -rf coverage_html *.gcno *.gcda *.out *.info *.a *.o tetris archived_tetris.tar.gz

rebuild: clean all
#===========================================================================
