CXX = g++
FLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -lgtest -lgmock -pthread

.PHONY: test leaks clean

test:
	@echo --------------------- START ---------------------
	$(CXX) $(FLAGS) unit_tests.cc -o unit_tests $(TEST_FLAGS)
	./unit_tests
	@echo -------------------- SUCCESS --------------------

leaks: test
	leaks -atExit -- ./unit_tests
	@echo ---------------------- END ----------------------

clean:
	@echo --------------------- CLEAN ---------------------
	rm -rf unit_tests
	@echo -------------------- SUCCESS --------------------
