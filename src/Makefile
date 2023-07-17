CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17
TEST_FLAGS = -lgtest -lgmock -pthread

#	=== Выполнить все ===
all: leaks

#	=== Запуск unit-тестов ===
test:
	@echo --------------------- START ---------------------
	$(CC) $(FLAGS) unit_tests.cc -o unit_tests $(TEST_FLAGS)
	./unit_tests
	@echo -------------------- SUCCESS --------------------

#	=== Проверка на утечки памяти ===
leaks: test
	leaks -atExit -- ./unit_tests
	@echo ---------------------- END ----------------------

#	=== Очистка ===
clean:
	@echo --------------------- CLEAN ---------------------
	rm -rf unit_tests
	@echo -------------------- SUCCESS --------------------
