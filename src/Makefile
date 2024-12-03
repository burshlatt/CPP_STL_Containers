CXX = g++
FLAGS = -Wall -Wextra -Werror
TEST_FLAGS = -lgtest -lgtest_main -pthread

.PHONY: test_list leaks_list test_vector leaks_vector clean

main:
	rm -rf a.out && $(CXX) -std=c++17 $(FLAGS) forward_list/main.cc && clear && ./a.out

test_list:
	@echo --------------------- START ---------------------
	$(CXX) -std=c++17 $(FLAGS) tests/test_list.cc $(TEST_FLAGS) -o utest_list
	./utest_list
	@echo -------------------- SUCCESS --------------------

leaks_list:
	@echo --------------------- START ---------------------
	$(CXX) -g -std=c++17 $(FLAGS) tests/test_list.cc $(TEST_FLAGS) -o utest_list_leaks
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./utest_list_leaks
	@echo ---------------------- END ----------------------

test_vector:
	@echo --------------------- START ---------------------
	$(CXX) -std=c++17 $(FLAGS) tests/test_vector.cc $(TEST_FLAGS) -o utest_vector
	./utest_vector
	@echo -------------------- SUCCESS --------------------

leaks_vector:
	@echo --------------------- START ---------------------
	$(CXX) -g -std=c++17 $(FLAGS) tests/test_vector.cc $(TEST_FLAGS) -o utest_vector_leaks
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./utest_vector_leaks
	@echo ---------------------- END ----------------------

test_deque:
	@echo --------------------- START ---------------------
	$(CXX) -std=c++17 $(FLAGS) tests/test_deque.cc $(TEST_FLAGS) -o utest_deque
	./utest_deque
	@echo -------------------- SUCCESS --------------------

leaks_deque:
	@echo --------------------- START ---------------------
	$(CXX) -g -std=c++17 $(FLAGS) tests/test_deque.cc $(TEST_FLAGS) -o utest_deque_leaks
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./utest_deque_leaks
	@echo ---------------------- END ----------------------

test_flist:
	@echo --------------------- START ---------------------
	$(CXX) -std=c++17 $(FLAGS) tests/test_forward_list.cc $(TEST_FLAGS) -o utest_forward_list
	./utest_forward_list
	@echo -------------------- SUCCESS --------------------

leaks_flist:
	@echo --------------------- START ---------------------
	$(CXX) -g -std=c++17 $(FLAGS) tests/test_forward_list.cc $(TEST_FLAGS) -o utest_forward_list_leaks
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./utest_forward_list_leaks
	@echo ---------------------- END ----------------------

clean:
	@echo --------------------- CLEAN ---------------------
	rm -rf utest_* a.out ../.vscode
	@echo -------------------- SUCCESS --------------------
