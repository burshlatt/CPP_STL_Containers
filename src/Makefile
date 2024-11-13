CXX = g++
FLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -lgtest -lgtest_main -pthread

.PHONY: test_list leaks_list clean

test_list:
	@echo --------------------- START ---------------------
	$(CXX) -std=c++17 $(FLAGS) tests/test_list.cc $(TEST_FLAGS) -o utest_list
	./utest_list
	@echo -------------------- SUCCESS --------------------

leaks_list:
	$(CXX) -g -std=c++17 $(FLAGS) tests/test_list.cc $(TEST_FLAGS) -o utest_list_leaks
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./utest_list_leaks
	@echo ---------------------- END ----------------------

clean:
	@echo --------------------- CLEAN ---------------------
	rm -rf utest_*
	@echo -------------------- SUCCESS --------------------
