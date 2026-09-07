CC := gcc
CFLAGS := -Wall -Wextra -std=c11
LIBS := -L. -ltetris -lm -lsubunit
INC_DIRS := -Ibrick_game -Ibrick_game/tetris -Igui/cli

CLI_SRC := main/cli_main.c gui/cli/*.c

GCOV_CFLAGS := --coverage

#TETRIS LIB
TETRIS_LIB := libtetris.so
TETRIS_SRC := $(wildcard brick_game/tetris/*.c)
TETRIS_TEST := tetris_test
TETRIS_TEST_SRC := $(wildcard brick_game/tetris/tests/*.c)
TETRIS_CLI := tetris_cli

.PHONY: all, install, uninstall, clean, dvi, dist, test, gcov_report

all: build

build: $(TETRIS_CLI)

run: build
	./$(TETRIS_CLI)

dist:
	@mkdir -p $(TETRIS_CLI)_dist
	@cp --parents -r gui/cli $(TETRIS_CLI)_dist
	@cp --parents -r brick_game/tetris $(TETRIS_CLI)_dist
	@cp --parents brick_game/common.h $(TETRIS_CLI)_dist
	@cp --parents main/cli_main.c $(TETRIS_CLI)_dist
	@cp -r assets $(TETRIS_CLI)_dist
	@cp Makefile $(TETRIS_CLI)_dist
	@tar cf $(TETRIS_CLI).tar $(TETRIS_CLI)_dist
	@rm -rf $(TETRIS_CLI)_dist
	@gzip $(TETRIS_CLI).tar
	@echo "Compiling ltetris with coverage..."

dvi: 
	doxygen Doxyfile

test: $(TETRIS_TEST)

gcov_report:
	@echo "Compiling ltetris with coverage..."
	@$(CC) $(CFLAGS) $(GCOV_CFLAGS) -fPIC -shared -o $(TETRIS_LIB) $(TETRIS_SRC) $(INC_DIRS)
	@echo "Compiling tests with coverage..."
	@$(CC) $(CFLAGS) $(GCOV_CFLAGS) -o $(TETRIS_TEST) $(TETRIS_TEST_SRC) $(INC_DIRS) -L. -ltetris -lcheck -lm -lsubunit
	@LD_LIBRARY_PATH=. ./$(TETRIS_TEST)
	@echo "Generating coverage data..."
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory coverage
	@echo "Report generated in ./coverage/index.html"

INSTALL_DIR := ~/brick_game

install: $(TETRIS_CLI)
	@mkdir -p $(INSTALL_DIR)
	@cp $(TETRIS_CLI) $(INSTALL_DIR)
	@cp $(TETRIS_LIB) $(INSTALL_DIR)
	@cp -r assets $(INSTALL_DIR)
	@rm -f $(TETRIS_LIB) $(TETRIS_CLI) *.o tetris_scores.txt
	@echo "Tetris installation complete"

uninstall:
	@rm -rf $(INSTALL_DIR)
	@echo "Tetris is uninstalled"

clean:
	rm -f $(TETRIS_LIB) $(TETRIS_TEST) $(TETRIS_CLI) *.o *.gcno *.gcda *.gcov coverage.info
	rm -rf coverage
	rm -rf latex
	rm -rf html

rebuild: clean build

#TETRIS LIB
$(TETRIS_LIB): $(TETRIS_SRC)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ $(INC_DIRS) $(LIBS)

$(TETRIS_CLI): $(TETRIS_LIB)
	$(CC) $(CFLAGS) -o $@ $(CLI_SRC) $(INC_DIRS) $(LIBS) -lncurses -Wl,-rpath,'$$ORIGIN'

$(TETRIS_TEST): cf $(TETRIS_TEST_SRC) $(TETRIS_LIB)
	@$(CC) $(CFLAGS) -o $@  $(TETRIS_TEST_SRC) $(INC_DIRS) -L. -ltetris -lcheck -lm -lsubunit -Wl,-rpath,'$$ORIGIN'
	@echo "Running tests..."
	@LD_LIBRARY_PATH=. ./$(TETRIS_TEST)

# TESTS
clang:
	@clang-format -n main/*.c
	@clang-format -n brick_game/*.h brick_game/tetris/*.h brick_game/tetris/*.c
	@clang-format -n brick_game/tetris/tests/*.h brick_game/tetris/tests/*.c
	@clang-format -n gui/cli/*.c gui/cli/*.h

cpp:
	@cppcheck --enable=all --suppress=missingInclude main/*.c
	@cppcheck --enable=all --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unusedFunction brick_game/tetris/*.c
	@cppcheck --enable=all --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unusedFunction gui/cli/*.c

valgrind_test: $(TETRIS_TEST)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./tetris_test


valgrind_tetris_cli: $(TETRIS_CLI)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=valgrind/ncurses.supp ./tetris_cli


# Clang format
cf:
	@clang-format -i main/*.c
	@clang-format -i brick_game/*.h brick_game/tetris/*.h brick_game/tetris/*.c
	@clang-format -i brick_game/tetris/tests/*.h brick_game/tetris/tests/*.c
	@clang-format -i gui/cli/*.c gui/cli/*.h