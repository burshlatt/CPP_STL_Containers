#include <array>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "gtest/gtest.h"
#include "s21_containers.h"

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА VECTOR (START) ==========
*/

TEST(test_class_vector, default_constructor) {
  s21::vector<int> vector_;
  EXPECT_EQ((int)vector_.size(), 0);
  EXPECT_EQ((int)vector_.capacity(), 0);
  EXPECT_EQ(vector_.data(), nullptr);
}

TEST(test_class_vector, copy_constructor) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};
  s21::vector<int> vector_2(vector_1);
  EXPECT_EQ(vector_2.size(), vector_1.size());
  EXPECT_EQ(vector_2.capacity(), vector_1.capacity());
  EXPECT_EQ(vector_2[0], 1);
  EXPECT_EQ(vector_2[1], 2);
  EXPECT_EQ(vector_2[2], 3);
  EXPECT_EQ(vector_2[3], 4);
  EXPECT_EQ(vector_2[4], 5);
}

TEST(test_class_vector, move_constructor) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};
  int size = vector_1.size();
  int capacity = vector_1.capacity();
  s21::vector<int> vector_2(std::move(vector_1));
  EXPECT_EQ((int)vector_2.size(), size);
  EXPECT_EQ((int)vector_2.capacity(), capacity);
  EXPECT_EQ(vector_2[0], 1);
  EXPECT_EQ(vector_2[1], 2);
  EXPECT_EQ(vector_2[2], 3);
  EXPECT_EQ(vector_2[3], 4);
  EXPECT_EQ(vector_2[4], 5);
  EXPECT_EQ((int)vector_1.size(), 0);
  EXPECT_EQ((int)vector_1.capacity(), 0);
  EXPECT_EQ(vector_1.data(), nullptr);
}

TEST(test_class_vector, parameterized_constructor_1) {
  s21::vector<int> vector_(5);
  EXPECT_EQ((int)vector_.size(), 5);
  EXPECT_EQ((int)vector_.capacity(), 5);
  EXPECT_EQ(vector_[0], 0);
  EXPECT_EQ(vector_[1], 0);
  EXPECT_EQ(vector_[2], 0);
  EXPECT_EQ(vector_[3], 0);
  EXPECT_EQ(vector_[4], 0);
}

TEST(test_class_vector, parameterized_constructor_2) {
  EXPECT_ANY_THROW(s21::vector<int> vector_(-5));
}

TEST(test_class_vector, initializer_list_constructor_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)vector_.size(), 5);
  EXPECT_EQ((int)vector_.capacity(), 5);
  EXPECT_EQ(vector_[0], 1);
  EXPECT_EQ(vector_[1], 2);
  EXPECT_EQ(vector_[2], 3);
  EXPECT_EQ(vector_[3], 4);
  EXPECT_EQ(vector_[4], 5);
}

TEST(test_class_vector, initializer_list_constructor_2) {
  s21::vector<int> vector_ = {};
  EXPECT_EQ((int)vector_.size(), 0);
  EXPECT_EQ((int)vector_.capacity(), 0);
  EXPECT_EQ(vector_.data(), nullptr);
}

TEST(test_class_vector, begin_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  int *pointer = vector_.data();
  EXPECT_EQ(vector_.begin(), pointer);
}

TEST(test_class_vector, begin_2) {
  s21::vector<int> vector_;
  EXPECT_ANY_THROW(vector_.begin());
}

TEST(test_class_vector, end_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  int *pointer = vector_.data();
  EXPECT_EQ(vector_.end(), pointer + vector_.size());
}

TEST(test_class_vector, end_2) {
  s21::vector<int> vector_;
  EXPECT_ANY_THROW(vector_.end());
}

TEST(test_class_vector, insert_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  s21::vector<int>::iterator it = vector_.begin();
  vector_.insert(it + 2, 10);
  EXPECT_EQ(vector_[0], 1);
  EXPECT_EQ(vector_[1], 2);
  EXPECT_EQ(vector_[2], 10);
  EXPECT_EQ(vector_[3], 3);
  EXPECT_EQ(vector_[4], 4);
  EXPECT_EQ(vector_[5], 5);
}

TEST(test_class_vector, insert_2) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  s21::vector<int>::iterator it = vector_.begin();
  EXPECT_ANY_THROW(vector_.insert(it + 12, 10));
}

TEST(test_class_vector, data_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  int *copy = vector_.data();
  EXPECT_EQ(copy[0], vector_[0]);
  EXPECT_EQ(copy[1], vector_[1]);
  EXPECT_EQ(copy[2], vector_[2]);
  EXPECT_EQ(copy[3], vector_[3]);
  EXPECT_EQ(copy[4], vector_[4]);
}

TEST(test_class_vector, data_2) {
  s21::vector<int> vector_;
  int *copy = vector_.data();
  EXPECT_EQ(copy, nullptr);
}

TEST(test_class_vector, at_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(vector_.at(0), 1);
  EXPECT_EQ(vector_.at(1), 2);
  EXPECT_EQ(vector_.at(2), 3);
  EXPECT_EQ(vector_.at(3), 4);
  EXPECT_EQ(vector_.at(4), 5);
}

TEST(test_class_vector, at_2) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(vector_.at(10));
}

TEST(test_class_vector, back_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(vector_.back(), 5);
}

TEST(test_class_vector, back_2) {
  s21::vector<int> vector_;
  EXPECT_ANY_THROW(vector_.back());
}

TEST(test_class_vector, front_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(vector_.front(), 1);
}

TEST(test_class_vector, front_2) {
  s21::vector<int> vector_;
  EXPECT_ANY_THROW(vector_.front());
}

TEST(test_class_vector, assignment_operator) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};
  s21::vector<int> vector_2 = vector_1;
  EXPECT_EQ(vector_2.size(), vector_1.size());
  EXPECT_EQ(vector_2.capacity(), vector_2.capacity());
  EXPECT_EQ(vector_2[0], 1);
  EXPECT_EQ(vector_2[1], 2);
  EXPECT_EQ(vector_2[2], 3);
  EXPECT_EQ(vector_2[3], 4);
  EXPECT_EQ(vector_2[4], 5);
}

TEST(test_class_vector, brackets_operator) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  vector_[2] = 5;
  EXPECT_EQ(vector_[0], 1);
  EXPECT_EQ(vector_[1], 2);
  EXPECT_EQ(vector_[2], 5);
  EXPECT_EQ(vector_[3], 4);
  EXPECT_EQ(vector_[4], 5);
}

TEST(test_class_vector, empty_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(vector_.empty(), false);
}

TEST(test_class_vector, empty_2) {
  s21::vector<int> vector_;
  EXPECT_EQ(vector_.empty(), true);
}

TEST(test_class_vector, size) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)vector_.size(), 5);
}

TEST(test_class_vector, max_size) {
  std::vector<int> vector_1 = {1, 2, 3, 4, 5};
  s21::vector<int> vector_2 = {1, 2, 3, 4, 5};
  printf("std::vector.max_size = %lu\n", vector_1.max_size());
  printf("s21::vector.max_size = %lu\n", vector_2.max_size());
}

TEST(test_class_vector, capacity) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  vector_.push_back(6);
  EXPECT_EQ((int)vector_.capacity(), 10);
}

TEST(test_class_vector, clear) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  vector_.clear();
  EXPECT_EQ((int)vector_.size(), 0);
}

TEST(test_class_vector, pop_back) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  vector_.pop_back();
  EXPECT_EQ((int)vector_.size(), 4);
  EXPECT_EQ(vector_[0], 1);
  EXPECT_EQ(vector_[1], 2);
  EXPECT_EQ(vector_[2], 3);
  EXPECT_EQ(vector_[3], 4);
}

TEST(test_class_vector, shrink_to_fit) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  vector_.push_back(6);
  vector_.shrink_to_fit();
  EXPECT_EQ((int)vector_.capacity(), 6);
}

TEST(test_class_vector, erase_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  s21::vector<int>::iterator it = vector_.begin();
  vector_.erase(it + 2);
  EXPECT_EQ((int)vector_.size(), 4);
  EXPECT_EQ(vector_[0], 1);
  EXPECT_EQ(vector_[1], 2);
  EXPECT_EQ(vector_[2], 4);
  EXPECT_EQ(vector_[3], 5);
}

TEST(test_class_vector, erase_2) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  s21::vector<int>::iterator it = vector_.begin();
  EXPECT_ANY_THROW(vector_.erase(it + 12));
  EXPECT_EQ((int)vector_.size(), 5);
}

TEST(test_class_vector, swap) {
  s21::vector<int> vector_1 = {1, 2, 3, 4, 5};
  s21::vector<int> vector_2 = {5, 4, 3, 2, 1};
  vector_1.swap(vector_2);
  EXPECT_EQ(vector_1[0], 5);
  EXPECT_EQ(vector_1[1], 4);
  EXPECT_EQ(vector_1[2], 3);
  EXPECT_EQ(vector_1[3], 2);
  EXPECT_EQ(vector_1[4], 1);

  EXPECT_EQ(vector_2[0], 1);
  EXPECT_EQ(vector_2[1], 2);
  EXPECT_EQ(vector_2[2], 3);
  EXPECT_EQ(vector_2[3], 4);
  EXPECT_EQ(vector_2[4], 5);
}

TEST(test_class_vector, reserve_1) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  vector_.reserve(10);
  EXPECT_EQ((int)vector_.capacity(), 10);
}

TEST(test_class_vector, reserve_2) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  vector_.reserve(3);
  EXPECT_EQ((int)vector_.capacity(), 5);
}

TEST(test_class_vector, push_back) {
  s21::vector<int> vector_ = {1, 2, 3, 4, 5};
  vector_.push_back(6);
  vector_.push_back(7);
  vector_.push_back(8);
  vector_.push_back(9);
  vector_.push_back(10);
  vector_.push_back(11);
  EXPECT_EQ((int)vector_.size(), 11);
  EXPECT_EQ((int)vector_.capacity(), 20);
  EXPECT_EQ(vector_[0], 1);
  EXPECT_EQ(vector_[1], 2);
  EXPECT_EQ(vector_[2], 3);
  EXPECT_EQ(vector_[3], 4);
  EXPECT_EQ(vector_[4], 5);
  EXPECT_EQ(vector_[5], 6);
  EXPECT_EQ(vector_[6], 7);
  EXPECT_EQ(vector_[7], 8);
  EXPECT_EQ(vector_[8], 9);
  EXPECT_EQ(vector_[9], 10);
  EXPECT_EQ(vector_[10], 11);
}

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА VECTOR (END) ==========
*/

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА STACK (START) ==========
*/

TEST(test_class_stack, default_constructor) {
  s21::stack<int> stack_;
  EXPECT_EQ((int)stack_.size(), 0);
}

TEST(test_class_stack, copy_constructor) {
  s21::stack<int> stack_1 = {1, 2, 3, 4, 5};
  s21::stack<int> stack_2(stack_1);
  EXPECT_EQ(stack_2.size(), stack_1.size());
  EXPECT_EQ((int)stack_2.top(), 5);
}

TEST(test_class_stack, move_constructor) {
  s21::stack<int> stack_1 = {1, 2, 3, 4, 5};
  s21::stack<int> stack_2(std::move(stack_1));
  EXPECT_EQ((int)stack_1.size(), 0);
  EXPECT_EQ((int)stack_2.size(), 5);
  EXPECT_EQ((int)stack_2.top(), 5);
}

TEST(test_class_stack, initializer_list_constructor_1) {
  s21::stack<int> stack_1 = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)stack_1.size(), 5);
  EXPECT_EQ((int)stack_1.top(), 5);
}

TEST(test_class_stack, initializer_list_constructor_2) {
  s21::stack<int> stack_1 = {};
  EXPECT_EQ((int)stack_1.size(), 0);
}

TEST(test_class_stack, size) {
  s21::stack<int> stack_ = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)stack_.size(), 5);
}

TEST(test_class_stack, top_1) {
  s21::stack<int> stack_ = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)stack_.top(), 5);
}

TEST(test_class_stack, top_2) {
  s21::stack<int> stack_;
  EXPECT_ANY_THROW(stack_.top());
}

TEST(test_class_stack, empty_1) {
  s21::stack<int> stack_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(stack_.empty(), false);
}

TEST(test_class_stack, empty_2) {
  s21::stack<int> stack_;
  EXPECT_EQ(stack_.empty(), true);
}

TEST(test_class_stack, pop_1) {
  s21::stack<int> stack_ = {1, 2, 3, 4, 5};
  stack_.pop();
  EXPECT_EQ((int)stack_.size(), 4);
  EXPECT_EQ((int)stack_.top(), 4);
}

TEST(test_class_stack, pop_2) {
  s21::stack<int> stack_;
  EXPECT_ANY_THROW(stack_.pop());
}

TEST(test_class_stack, swap) {
  s21::stack<int> stack_1 = {1, 2, 3, 4, 5};
  s21::stack<int> stack_2 = {5, 4, 3, 2, 1, 0};
  stack_1.swap(stack_2);
  EXPECT_EQ((int)stack_1.size(), 6);
  EXPECT_EQ((int)stack_1.top(), 0);
  EXPECT_EQ((int)stack_2.size(), 5);
  EXPECT_EQ((int)stack_2.top(), 5);
}

TEST(test_class_stack, push) {
  s21::stack<int> stack_ = {1, 2, 3, 4, 5};
  stack_.push(6);
  stack_.push(7);
  EXPECT_EQ((int)stack_.size(), 7);
  EXPECT_EQ((int)stack_.top(), 7);
}

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА STACK (END) ==========
*/

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА ARRAY (START) ==========
*/

TEST(test_class_array, default_constructor) {
  s21::array<int, 1> array_;
  EXPECT_EQ((int)array_.size(), 1);
  EXPECT_EQ(array_[0], 0);
}

TEST(test_class_array, copy_constructor) {
  s21::array<int, 5> array_1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> array_2(array_1);
  EXPECT_EQ(array_2.size(), array_1.size());
  EXPECT_EQ(array_2[0], array_1[0]);
  EXPECT_EQ(array_2[1], array_1[1]);
  EXPECT_EQ(array_2[2], array_1[2]);
  EXPECT_EQ(array_2[3], array_1[3]);
  EXPECT_EQ(array_2[4], array_1[4]);
}

TEST(test_class_array, move_constructor) {
  s21::array<int, 5> array_1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> array_2(std::move(array_1));
  EXPECT_EQ((int)array_1.size(), 0);
  EXPECT_EQ((int)array_2.size(), 5);
  EXPECT_EQ(array_2[0], 1);
  EXPECT_EQ(array_2[1], 2);
  EXPECT_EQ(array_2[2], 3);
  EXPECT_EQ(array_2[3], 4);
  EXPECT_EQ(array_2[4], 5);
}

TEST(test_class_array, operator) {
  s21::array<int, 5> array_1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> array_2;
  array_2 = std::move(array_1);
  EXPECT_EQ(array_1.empty(), true);
  EXPECT_EQ(array_2[0], 1);
  EXPECT_EQ(array_2[1], 2);
  EXPECT_EQ(array_2[2], 3);
  EXPECT_EQ(array_2[3], 4);
  EXPECT_EQ(array_2[4], 5);
}

TEST(test_class_array, initializer_list_constructor) {
  s21::array<int, 5> array_1 = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)array_1.size(), 5);
  EXPECT_EQ(array_1[0], 1);
  EXPECT_EQ(array_1[1], 2);
  EXPECT_EQ(array_1[2], 3);
  EXPECT_EQ(array_1[3], 4);
  EXPECT_EQ(array_1[4], 5);
}

TEST(test_class_array, assignment_operator) {
  s21::array<int, 5> array_1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> array_2 = array_1;
  EXPECT_EQ(array_2.size(), array_1.size());
  EXPECT_EQ(array_2[0], array_1[0]);
  EXPECT_EQ(array_2[1], array_1[1]);
  EXPECT_EQ(array_2[2], array_1[2]);
  EXPECT_EQ(array_2[3], array_1[3]);
  EXPECT_EQ(array_2[4], array_1[4]);
}

TEST(test_class_array, brackets_operator) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  array_[2] = 5;
  EXPECT_EQ(array_[0], 1);
  EXPECT_EQ(array_[1], 2);
  EXPECT_EQ(array_[2], 5);
  EXPECT_EQ(array_[3], 4);
  EXPECT_EQ(array_[4], 5);
}

TEST(test_class_array, begin_1) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(*array_.begin(), 1);
}

TEST(test_class_array, begin_2) {
  s21::array<int, 0> array_;
  EXPECT_ANY_THROW(array_.begin());
}

TEST(test_class_array, end_1) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(*array_.end(), 0);
}

TEST(test_class_array, end_2) {
  s21::array<int, 0> array_;
  EXPECT_ANY_THROW(array_.end());
}

TEST(test_class_array, data) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  int *copy = array_.data();
  copy[0] = 999;
  EXPECT_EQ(array_[0], 999);
  EXPECT_EQ(copy[0], 999);
  EXPECT_EQ(copy[1], 2);
  EXPECT_EQ(copy[2], 3);
  EXPECT_EQ(copy[3], 4);
  EXPECT_EQ(copy[4], 5);
}

TEST(test_class_array, size) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)array_.size(), 5);
}

TEST(test_class_array, max_size) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)array_.max_size(), 5);
}

TEST(test_class_array, back_1) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(array_.back(), 5);
}

TEST(test_class_array, back_2) {
  s21::array<int, 0> array_;
  EXPECT_ANY_THROW(array_.back());
}

TEST(test_class_array, front_1) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(array_.front(), 1);
}

TEST(test_class_array, front_2) {
  s21::array<int, 0> array_;
  EXPECT_ANY_THROW(array_.front());
}

TEST(test_class_array, at_1) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(array_.at(0), 1);
  EXPECT_EQ(array_.at(1), 2);
  EXPECT_EQ(array_.at(2), 3);
  EXPECT_EQ(array_.at(3), 4);
  EXPECT_EQ(array_.at(4), 5);
}

TEST(test_class_array, at_2) {
  s21::array<int, 5> array_ = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(array_.at(5));
}

TEST(test_class_array, empty) {
  s21::array<int, 0> array_1;
  s21::array<int, 5> array_2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(array_1.empty(), true);
  EXPECT_EQ(array_2.empty(), false);
}

TEST(test_class_array, swap) {
  s21::array<int, 5> array_1 = {5, 4, 3, 2, 1};
  s21::array<int, 5> array_2 = {1, 2, 3, 4, 5};
  array_1.swap(array_2);
  EXPECT_EQ(array_1[0], 1);
  EXPECT_EQ(array_1[1], 2);
  EXPECT_EQ(array_1[2], 3);
  EXPECT_EQ(array_1[3], 4);
  EXPECT_EQ(array_1[4], 5);

  EXPECT_EQ(array_2[0], 5);
  EXPECT_EQ(array_2[1], 4);
  EXPECT_EQ(array_2[2], 3);
  EXPECT_EQ(array_2[3], 2);
  EXPECT_EQ(array_2[4], 1);
}

TEST(test_class_array, fill) {
  s21::array<int, 5> array_1 = {5, 4, 3, 2, 1};
  array_1.fill(3);
  EXPECT_EQ(array_1[0], 3);
  EXPECT_EQ(array_1[1], 3);
  EXPECT_EQ(array_1[2], 3);
  EXPECT_EQ(array_1[3], 3);
  EXPECT_EQ(array_1[4], 3);
}

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА ARRAY (END) ==========
*/

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА QUEUE (START) ==========
*/

TEST(test_class_queue, default_constructor) {
  s21::queue<int> queue_;
  EXPECT_EQ(queue_.empty(), true);
  EXPECT_EQ((int)queue_.size(), 0);
}

TEST(test_class_queue, copy_constructor) {
  s21::queue<int> queue_1 = {1, 2, 3, 4, 5};
  s21::queue<int> queue_2(queue_1);
  EXPECT_EQ(queue_2.size(), queue_1.size());
  EXPECT_EQ(queue_2.back(), queue_1.back());
  EXPECT_EQ(queue_2.front(), queue_1.front());
  queue_1.pop();
  queue_2.pop();
  EXPECT_EQ(queue_2.back(), queue_1.back());
  EXPECT_EQ(queue_2.front(), queue_1.front());
}

TEST(test_class_queue, move_constructor) {
  s21::queue<int> queue_1 = {1, 2, 3, 4, 5};
  s21::queue<int> queue_2(std::move(queue_1));
  EXPECT_EQ((int)queue_2.size(), 5);
  EXPECT_EQ(queue_2.back(), 5);
  EXPECT_EQ(queue_2.front(), 1);
  queue_2.pop();
  EXPECT_EQ(queue_2.back(), 5);
  EXPECT_EQ(queue_2.front(), 2);
  EXPECT_EQ((int)queue_1.size(), 0);
  EXPECT_EQ(queue_1.empty(), true);
  EXPECT_ANY_THROW(queue_1.back());
  EXPECT_ANY_THROW(queue_1.front());
}

TEST(test_class_queue, initializer_list_constructor) {
  s21::queue<int> queue_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(queue_.back(), 5);
  EXPECT_EQ(queue_.front(), 1);
  EXPECT_EQ((int)queue_.size(), 5);
  EXPECT_EQ(queue_.empty(), false);
}

TEST(test_class_queue, operator) {
  s21::queue<int> queue_1 = {1, 2, 3, 4, 5};
  s21::queue<int> queue_2;
  queue_2 = std::move(queue_1);
  EXPECT_EQ(queue_1.empty(), true);
}

TEST(test_class_queue, assignment_operator) {
  s21::queue<int> queue_1 = {1, 2, 3, 4, 5};
  s21::queue<int> queue_2 = queue_1;
  EXPECT_EQ(queue_2.size(), queue_1.size());
  EXPECT_EQ(queue_2.back(), queue_1.back());
  EXPECT_EQ(queue_2.front(), queue_1.front());
  queue_1.pop();
  queue_2.pop();
  EXPECT_EQ(queue_2.back(), queue_1.back());
  EXPECT_EQ(queue_2.front(), queue_1.front());
}

TEST(test_class_queue, size) {
  s21::queue<int> queue_ = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)queue_.size(), 5);
}

TEST(test_class_queue, back_1) {
  s21::queue<int> queue_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(queue_.back(), 5);
}

TEST(test_class_queue, back_2) {
  s21::queue<int> queue_;
  EXPECT_ANY_THROW(queue_.back());
}

TEST(test_class_queue, front_1) {
  s21::queue<int> queue_ = {1, 2, 3, 4, 5};
  EXPECT_EQ(queue_.front(), 1);
}

TEST(test_class_queue, front_2) {
  s21::queue<int> queue_;
  EXPECT_ANY_THROW(queue_.front());
}

TEST(test_class_queue, empty) {
  s21::queue<int> queue_1;
  s21::queue<int> queue_2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(queue_1.empty(), true);
  EXPECT_EQ(queue_2.empty(), false);
}

TEST(test_class_queue, push) {
  s21::queue<int> queue_ = {1, 2, 3};
  EXPECT_EQ((int)queue_.size(), 3);
  EXPECT_EQ(queue_.back(), 3);
  EXPECT_EQ(queue_.front(), 1);
  queue_.push(4);
  queue_.push(5);
  EXPECT_EQ((int)queue_.size(), 5);
  EXPECT_EQ(queue_.back(), 5);
  EXPECT_EQ(queue_.front(), 1);
}

TEST(test_class_queue, pop_1) {
  s21::queue<int> queue_ = {1, 2, 3, 4, 5};
  EXPECT_EQ((int)queue_.size(), 5);
  EXPECT_EQ(queue_.back(), 5);
  EXPECT_EQ(queue_.front(), 1);
  queue_.pop();
  queue_.pop();
  EXPECT_EQ((int)queue_.size(), 3);
  EXPECT_EQ(queue_.back(), 5);
  EXPECT_EQ(queue_.front(), 3);
}

TEST(test_class_queue, pop_2) {
  s21::queue<int> queue_;
  EXPECT_ANY_THROW(queue_.pop());
}

TEST(test_class_queue, swap) {
  s21::queue<int> queue_1 = {1, 2, 3};
  s21::queue<int> queue_2 = {5, 4, 3, 2, 1};
  queue_1.swap(queue_2);
  EXPECT_EQ((int)queue_1.size(), 5);
  EXPECT_EQ(queue_1.back(), 1);
  EXPECT_EQ(queue_1.front(), 5);
  EXPECT_EQ((int)queue_2.size(), 3);
  EXPECT_EQ(queue_2.back(), 3);
  EXPECT_EQ(queue_2.front(), 1);
}

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА QUEUE (END) ==========
*/

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА LIST (START) ==========
*/

template <typename Type>
void AreEqualLists(std::list<Type> std_list, s21::list<Type> s21_list) {
  auto std_it = std_list.begin();
  auto s21_it = s21_list.begin();

  while (std_it != std_list.end()) {
    EXPECT_EQ(*std_it, *s21_it);
    ++std_it;
    ++s21_it;
  }
  EXPECT_EQ(std_list.size(), s21_list.size());
}

TEST(test_class_list, default_constructor) {
  std::list<int> std_list{};
  s21::list<int> s21_list{};

  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, parameterized_constructor_1) {
  std::list<int> std_list(5);
  s21::list<int> s21_list(5);

  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, parameterized_constructor_2) {
  std::list<int> std_list(0);
  s21::list<int> s21_list(0);

  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, initializer_list_constructor_1) {
  std::list<char> std_list = {'t', 'e', 's', 't'};
  s21::list<char> s21_list = {'t', 'e', 's', 't'};

  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, initializer_list_constructor_2) {
  std::list<char> std_list = {};
  s21::list<char> s21_list = {};
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, copy_constructor) {
  std::list<int> std_list_1 = {1, 2, 3, 4, 5};
  std::list<int> std_list_2(std_list_1);
  s21::list<int> s21_list_1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list_2(s21_list_1);

  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, move_constructor) {
  std::list<char> std_list_1 = {'t', 'e', 's', 't'};
  std::list<char> std_list_2(std::move(std_list_1));
  s21::list<char> s21_list_1 = {'t', 'e', 's', 't'};
  s21::list<char> s21_list_2(std::move(s21_list_1));

  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, assignment_operator) {
  std::list<int> std_list_1 = {1, 2, 3, 4, 5};
  std::list<int> std_list_2 = std_list_1;
  s21::list<int> s21_list_1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list_2 = s21_list_1;

  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, front_1) {
  std::list<char> std_list = {'t', 'e', 's', 't'};
  s21::list<char> s21_list = {'t', 'e', 's', 't'};
  EXPECT_EQ(std_list.front(), s21_list.front());
}

TEST(test_class_list, front_2) {
  std::list<char> std_list;
  s21::list<char> s21_list;
  EXPECT_EQ(std_list.front(), s21_list.front());
}

TEST(test_class_list, back_1) {
  std::list<char> std_list = {'t', 'e', 's', 't'};
  s21::list<char> s21_list = {'t', 'e', 's', 't'};
  EXPECT_EQ(std_list.back(), s21_list.back());
}

TEST(test_class_list, back_2) {
  std::list<char> std_list;
  s21::list<char> s21_list;
  EXPECT_EQ(std_list.back(), s21_list.back());
}

TEST(test_class_list, begin_and_end) {
  std::list<char> std_list;
  s21::list<int> s21_list;
  EXPECT_EQ(std_list.begin(), std_list.end());
  EXPECT_EQ(s21_list.begin(), s21_list.end());
}

TEST(test_class_list, empty_1) {
  std::list<char> std_list;
  s21::list<int> s21_list;
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(test_class_list, empty_2) {
  std::list<char> std_list = {1};
  s21::list<int> s21_list = {1};
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(test_class_list, empty_3) {
  std::list<char> std_list;
  s21::list<int> s21_list = {1};
  EXPECT_FALSE(std_list.empty() == s21_list.empty());
}

TEST(test_class_list, max_size) {
  std::list<char> std_list;
  s21::list<int> s21_list;
  EXPECT_EQ(std_list.max_size(), s21_list.max_size());
}

TEST(test_class_list, clear_1) {
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std_list.clear();
  s21_list.clear();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, clear_2) {
  std::list<int> std_list;
  s21::list<int> s21_list;
  std_list.clear();
  s21_list.clear();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, insert_1) {
  std::list<char> std_list = {'t', 'e', 's', 't'};
  s21::list<char> s21_list = {'t', 'e', 's', 't'};
  std_list.insert(std_list.begin(), 'q');
  s21_list.insert(s21_list.begin(), 'q');
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, insert_2) {
  std::list<char> std_list = {'t', 'e', 's', 't'};
  s21::list<char> s21_list = {'t', 'e', 's', 't'};
  std_list.insert(std_list.end(), 'q');
  s21_list.insert(s21_list.end(), 'q');
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, insert_3) {
  std::list<char> std_list = {'t', 'e', 's', 't'};
  s21::list<char> s21_list = {'t', 'e', 's', 't'};
  std_list.insert(++std_list.begin(), 'q');
  s21_list.insert(++s21_list.begin(), 'q');
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, insert_4) {
  std::list<char> std_list;
  s21::list<char> s21_list;
  std_list.insert(std_list.begin(), 'q');
  s21_list.insert(s21_list.begin(), 'q');
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, erase_1) {
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std_list.erase(std_list.begin());
  s21_list.erase(s21_list.begin());
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, erase_2) {
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  // std_list.erase(std_list.end());
  s21_list.erase(s21_list.end());
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, erase_3) {
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std_list.erase(++std_list.begin());
  s21_list.erase(++s21_list.begin());
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, erase_4) {
  std::list<int> std_list;
  s21::list<int> s21_list;
  // std_list.erase(std_list.begin());
  s21_list.erase(s21_list.begin());
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, erase_5) {
  std::list<int> std_list;
  s21::list<int> s21_list;
  // std_list.erase(std_list.begin());
  s21_list.erase(s21_list.begin());
  s21_list.erase(s21_list.begin());
  s21_list.erase(s21_list.begin());
  s21_list.erase(s21_list.begin());
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, push_back) {
  std::list<int> std_list;
  s21::list<int> s21_list;
  std_list.push_back(123);
  std_list.push_back(1);
  std_list.push_back(-1);
  s21_list.push_back(123);
  s21_list.push_back(1);
  s21_list.push_back(-1);
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, pop_back) {
  std::list<int> std_list = {1, 2};
  s21::list<int> s21_list = {1, 2};
  std_list.pop_back();
  s21_list.pop_back();
  AreEqualLists(std_list, s21_list);
  std_list.pop_back();
  s21_list.pop_back();
  AreEqualLists(std_list, s21_list);
  // std_list.pop_back();
  s21_list.pop_back();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, push_front) {
  std::list<int> std_list;
  s21::list<int> s21_list;
  std_list.push_front(123);
  std_list.push_front(1);
  std_list.push_front(-1);
  s21_list.push_front(123);
  s21_list.push_front(1);
  s21_list.push_front(-1);
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, pop_front) {
  std::list<int> std_list = {1, 2};
  s21::list<int> s21_list = {1, 2};
  std_list.pop_front();
  s21_list.pop_front();
  AreEqualLists(std_list, s21_list);
  std_list.pop_front();
  s21_list.pop_front();
  AreEqualLists(std_list, s21_list);
  // std_list.pop_front();
  s21_list.pop_front();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, swap_1) {
  std::list<double> std_list_1 = {5, 6, 7, 8, 9};
  std::list<double> std_list_2 = {1, 2, 3, 4};
  s21::list<double> s21_list_1 = {5, 6, 7, 8, 9};
  s21::list<double> s21_list_2 = {1, 2, 3, 4};
  std_list_1.swap(std_list_2);
  s21_list_1.swap(s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, swap_2) {
  std::list<double> std_list_1 = {};
  std::list<double> std_list_2 = {1, 2, 3, 4};
  s21::list<double> s21_list_1 = {};
  s21::list<double> s21_list_2 = {1, 2, 3, 4};
  std_list_1.swap(std_list_2);
  s21_list_1.swap(s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, swap_3) {
  std::list<double> std_list_1 = {5, 6, 7, 8, 9};
  std::list<double> std_list_2 = {};
  s21::list<double> s21_list_1 = {5, 6, 7, 8, 9};
  s21::list<double> s21_list_2 = {};
  std_list_1.swap(std_list_2);
  s21_list_1.swap(s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, swap_4) {
  std::list<double> std_list_1 = {};
  std::list<double> std_list_2 = {};
  s21::list<double> s21_list_1 = {};
  s21::list<double> s21_list_2 = {};
  std_list_1.swap(std_list_2);
  s21_list_1.swap(s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, merge_1) {
  std::list<double> std_list_1 = {5, 6, 7, 8, -9};
  std::list<double> std_list_2 = {1, 12, 3, 4};
  s21::list<double> s21_list_1 = {5, 6, 7, 8, -9};
  s21::list<double> s21_list_2 = {1, 12, 3, 4};
  std_list_1.merge(std_list_2);
  s21_list_1.merge(s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, merge_2) {
  std::list<double> std_list_1 = {};
  std::list<double> std_list_2 = {1, 12, 3, 4};
  s21::list<double> s21_list_1 = {};
  s21::list<double> s21_list_2 = {1, 12, 3, 4};
  std_list_1.merge(std_list_2);
  s21_list_1.merge(s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, merge_3) {
  std::list<double> std_list_1 = {5, 6, 7, 8, -9};
  std::list<double> std_list_2 = {};
  s21::list<double> s21_list_1 = {5, 6, 7, 8, -9};
  s21::list<double> s21_list_2 = {};
  std_list_1.merge(std_list_2);
  s21_list_1.merge(s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, splice_1) {
  std::list<char> std_list_1 = {'t', 'e', 's', 't'};
  std::list<char> std_list_2 = {'s', '2', '1', 'l', 'i', 's', 't'};
  s21::list<char> s21_list_1 = {'t', 'e', 's', 't'};
  s21::list<char> s21_list_2 = {'s', '2', '1', 'l', 'i', 's', 't'};
  std_list_1.splice(std_list_1.begin(), std_list_2);
  s21_list_1.splice(s21_list_1.begin(), s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, splice_2) {
  std::list<char> std_list_1 = {};
  std::list<char> std_list_2 = {'s', '2', '1', 'l', 'i', 's', 't'};
  s21::list<char> s21_list_1 = {};
  s21::list<char> s21_list_2 = {'s', '2', '1', 'l', 'i', 's', 't'};
  std_list_1.splice(std_list_1.begin(), std_list_2);
  s21_list_1.splice(s21_list_1.begin(), s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, splice_3) {
  std::list<char> std_list_1 = {'t', 'e', 's', 't'};
  std::list<char> std_list_2 = {};
  s21::list<char> s21_list_1 = {'t', 'e', 's', 't'};
  s21::list<char> s21_list_2 = {};
  std_list_1.splice(std_list_1.begin(), std_list_2);
  s21_list_1.splice(s21_list_1.begin(), s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, splice_4) {
  std::list<char> std_list_1 = {};
  std::list<char> std_list_2 = {};
  s21::list<char> s21_list_1 = {};
  s21::list<char> s21_list_2 = {};
  std_list_1.splice(std_list_1.begin(), std_list_2);
  s21_list_1.splice(s21_list_1.begin(), s21_list_2);
  AreEqualLists(std_list_1, s21_list_1);
  AreEqualLists(std_list_2, s21_list_2);
}

TEST(test_class_list, reverse_1) {
  std::list<double> std_list = {1, 2, 3, 4, 5};
  s21::list<double> s21_list = {1, 2, 3, 4, 5};
  std_list.reverse();
  s21_list.reverse();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, reverse_2) {
  std::list<double> std_list = {1};
  s21::list<double> s21_list = {1};
  std_list.reverse();
  s21_list.reverse();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, reverse_3) {
  std::list<double> std_list;
  s21::list<double> s21_list;
  std_list.reverse();
  s21_list.reverse();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, unique_1) {
  std::list<double> std_list = {1.1, -2.3, -2.3, -2.3, 1.1, 2.5, 2.5};
  s21::list<double> s21_list = {1.1, -2.3, -2.3, -2.3, 1.1, 2.5, 2.5};
  std_list.unique();
  s21_list.unique();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, unique_2) {
  std::list<double> std_list = {1.1, 1.1, 1.1, 1.1, 1.1};
  s21::list<double> s21_list = {1.1, 1.1, 1.1, 1.1, 1.1};
  std_list.unique();
  s21_list.unique();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, unique_3) {
  std::list<double> std_list = {1.1, 1.2, 1.1, 1.2, 1.1};
  s21::list<double> s21_list = {1.1, 1.2, 1.1, 1.2, 1.1};
  std_list.unique();
  s21_list.unique();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, unique_4) {
  std::list<double> std_list = {1.1, 1.1};
  s21::list<double> s21_list = {1.1, 1.1};
  std_list.unique();
  s21_list.unique();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, unique_5) {
  std::list<double> std_list = {1.1};
  s21::list<double> s21_list = {1.1};
  std_list.unique();
  s21_list.unique();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, sort_1) {
  std::list<double> std_list = {1.1, -2.3, -2.3, -2.3, 1.1, 2.5, 2.5};
  s21::list<double> s21_list = {1.1, -2.3, -2.3, -2.3, 1.1, 2.5, 2.5};
  std_list.sort();
  s21_list.sort();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, sort_2) {
  std::list<char> std_list = {'c', 'a', 'c', 'r'};
  s21::list<char> s21_list = {'c', 'a', 'c', 'r'};
  std_list.sort();
  s21_list.sort();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, sort_3) {
  std::list<double> std_list = {1.1, 1.1};
  s21::list<double> s21_list = {1.1, 1.1};
  std_list.sort();
  s21_list.sort();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, sort_4) {
  std::list<double> std_list = {1.1, -1.1};
  s21::list<double> s21_list = {1.1, -1.1};
  std_list.sort();
  s21_list.sort();
  AreEqualLists(std_list, s21_list);
}

TEST(test_class_list, sort_5) {
  std::list<double> std_list = {1.1};
  s21::list<double> s21_list = {1.1};
  std_list.sort();
  s21_list.sort();
  AreEqualLists(std_list, s21_list);
}

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА LIST (END) ==========
*/

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА MAP (START) ==========
*/

class TestMap {
 public:
  s21::map<int, int> s21_map_empty;
  s21::map<int, int> s21_map_four{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  s21::map<int, int> s21_map_swap{{1, 95}, {2, 94}, {3, 93}};

  std::map<int, int> std_map_empty;
  std::map<int, int> std_map_four{{
                                      1,
                                      1,
                                  },
                                  {2, 2},
                                  {3, 3},
                                  {4, 4}};
  std::map<int, int> std_map_swap{{1, 95}, {2, 95}, {3, 95}};
};

TEST(Map, construcor_default) {
  TestMap tester;
  //    EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
}

TEST(Map, construcot_initializer) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_four[1], tester.std_map_four[1]);
  EXPECT_EQ(tester.s21_map_four[4], tester.std_map_four[4]);
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.std_map_four.empty(), tester.std_map_four.empty());
}

TEST(Map, constructor_copy_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_copy(tester.s21_map_empty);
  std::map<int, int> std_map_copy(tester.std_map_empty);
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(std_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, constructor_copy_not_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_copy(tester.s21_map_four);
  std::map<int, int> std_map_copy(tester.std_map_four);
  EXPECT_EQ(s21_map_copy[1], std_map_copy[1]);
  EXPECT_EQ(s21_map_copy[4], std_map_copy[4]);
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(std_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, constructor_move_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_move = std::move(tester.s21_map_empty);
  std::map<int, int> std_map_move = std::move(tester.std_map_empty);
  EXPECT_EQ(s21_map_move.size(), std_map_move.size());
  EXPECT_EQ(s21_map_move.empty(), std_map_move.empty());
}

TEST(Map, constructor_move_not_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_move = std::move(tester.s21_map_four);
  std::map<int, int> std_map_move = std::move(tester.std_map_four);
  EXPECT_EQ(s21_map_move[1], std_map_move[1]);
  EXPECT_EQ(s21_map_move[4], std_map_move[4]);
  EXPECT_EQ(s21_map_move.size(), std_map_move.size());
  EXPECT_EQ(s21_map_move.empty(), std_map_move.empty());
}

TEST(Map, operator_copy_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_copy;
  std::map<int, int> std_map_copy;
  s21_map_copy = tester.s21_map_four;
  std_map_copy = tester.std_map_four;
  EXPECT_EQ(s21_map_copy[1], std_map_copy[1]);
  EXPECT_EQ(s21_map_copy[4], std_map_copy[4]);
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(s21_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, operator_copy_not_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_copy{{1, 1}, {2, 2}};
  std::map<int, int> std_map_copy{{1, 1}, {2, 2}};
  s21_map_copy = tester.s21_map_four;
  std_map_copy = tester.std_map_four;
  EXPECT_EQ(s21_map_copy[1], std_map_copy[1]);
  EXPECT_EQ(s21_map_copy[4], std_map_copy[4]);
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(s21_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, operator_move_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_move;
  std::map<int, int> std_map_move;
  s21_map_move = std::move(tester.s21_map_four);
  std_map_move = std::move(tester.std_map_four);
  EXPECT_EQ(s21_map_move[1], std_map_move[1]);
  EXPECT_EQ(std_map_move[4], std_map_move[4]);
  EXPECT_EQ(s21_map_move.size(), std_map_move.size());
  EXPECT_EQ(s21_map_move.empty(), std_map_move.empty());
}

TEST(Map, function_empty_not_empty) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(tester.s21_map_four[1], tester.std_map_four[1]);
}

TEST(Map, function_size_not_empty) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.std_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(tester.s21_map_four[1], tester.std_map_four[1]);
  EXPECT_EQ(tester.s21_map_four[4], tester.std_map_four[4]);
}

TEST(Map, function_swap_empty) {
  s21::map<int, int> m1({{1, 8}, {4, 2}, {2, 3}});
  s21::map<int, int> m2;
  m1.swap(m2);

  std::map<int, int> m3({{1, 8}, {4, 2}, {2, 3}});
  std::map<int, int> m4;
  m3.swap(m4);

  ASSERT_EQ(m2[1], m4[1]);
  ASSERT_EQ(m2[2], m4[2]);
  ASSERT_EQ(m2[4], m4[4]);

  ASSERT_EQ(m1.size(), m3.size());
  ASSERT_EQ(m2.size(), m4.size());
}

TEST(Map, function_swap_not_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_swap{{1, 1}, {2, 2}};
  std::map<int, int> std_map_swap{{1, 1}, {2, 2}};
  s21_map_swap.swap(tester.s21_map_four);
  std_map_swap.swap(tester.std_map_four);
  EXPECT_EQ(s21_map_swap[1], std_map_swap[1]);
  EXPECT_EQ(s21_map_swap[4], std_map_swap[4]);
  EXPECT_EQ(s21_map_swap.size(), std_map_swap.size());
  EXPECT_EQ(s21_map_swap.empty(), std_map_swap.empty());
}

TEST(Map, WithDuplicatesCase) {
  s21::map<int, int> m1({{1, 8}, {4, 2}, {2, 3}});
  s21::map<int, int> m2({{1, 3}, {2, 2}});
  m1.merge(m2);

  std::map<int, int> m3({{1, 8}, {4, 2}, {2, 3}});
  std::map<int, int> m4({{1, 3}, {2, 2}});
  m3.merge(m4);

  ASSERT_EQ(m1[1], m3[1]);
  ASSERT_EQ(m1[2], m3[2]);
  ASSERT_EQ(m1[4], m3[4]);

  ASSERT_EQ(m2[1], m4[1]);
  ASSERT_EQ(m2[2], m4[2]);

  ASSERT_EQ(m1.size(), m3.size());
  ASSERT_EQ(m2.size(), m4.size());
}

TEST(Map, WithoutDuplicatesCase) {
  s21::map<int, int> m1({{1, 2}, {3, 4}, {4, 5}});
  s21::map<int, int> m2({{5, 6}, {7, 7}});
  m1.merge(m2);

  std::map<int, int> m3({{1, 2}, {3, 4}, {4, 5}});
  std::map<int, int> m4({{5, 6}, {7, 7}});
  m3.merge(m4);

  ASSERT_EQ(m1[1], m3[1]);
  ASSERT_EQ(m1[3], m3[3]);
  ASSERT_EQ(m1[4], m3[4]);
  ASSERT_EQ(m1[5], m3[5]);
  ASSERT_EQ(m1[7], m3[7]);

  ASSERT_EQ(m1.size(), m3.size());
  ASSERT_EQ(m2.size(), m4.size());
}

TEST(Map, function_clear_empty) {
  TestMap tester;
  tester.s21_map_empty.clear();
  tester.std_map_empty.clear();
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
}

TEST(Map, function_clear_not_empty) {
  TestMap tester;
  tester.s21_map_four.clear();
  tester.std_map_four.clear();
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
}

TEST(Map, function_begin_empty) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_empty.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_empty.begin();
  EXPECT_EQ(iter_1 == tester.s21_map_empty.end(),
            iter_2 == tester.std_map_empty.end());
}

TEST(Map, function_begin_not_empty) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ(iter_1 != tester.s21_map_four.end(),
            iter_2 != tester.std_map_four.end());
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}

TEST(Map, const_begin_empty) {
  TestMap tester;
  s21::map<int, int>::const_iterator iter_1 = tester.s21_map_empty.begin();
  std::map<int, int>::const_iterator iter_2 = tester.std_map_empty.begin();
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
  EXPECT_EQ(iter_1 == tester.s21_map_empty.end(),
            iter_2 == tester.std_map_empty.end());
}

TEST(Map, const_begin_not_empty) {
  TestMap tester;
  s21::map<int, int>::const_iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::const_iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(iter_1 != tester.s21_map_four.end(),
            iter_2 != tester.std_map_four.end());
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}

TEST(Map, operator_plus) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}

TEST(Map, operator_minus) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  --iter_1;
  --iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}

TEST(Map, operator_assignment) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  s21::map<int, int>::iterator iter_3 = iter_1;
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  std::map<int, int>::iterator iter_4 = iter_2;
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ((*iter_1).second, (*iter_3).second);
  EXPECT_EQ((*iter_2).second, (*iter_4).second);
}

TEST(Map, operator_equal) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  s21::map<int, int>::iterator iter_3 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_empty.begin();
  std::map<int, int>::iterator iter_4 = tester.std_map_empty.begin();
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
  EXPECT_EQ(iter_1 == iter_3, iter_2 == iter_4);
}

TEST(Map, operatort_not_equal) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ(iter_1 != tester.s21_map_four.end(),
            iter_2 != tester.std_map_empty.end());
}

TEST(Map, const_operator_plus) {
  TestMap tester;
  s21::map<int, int>::const_iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::const_iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}

TEST(Map, const_operator_minus) {
  TestMap tester;
  s21::map<int, int>::const_iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::const_iterator iter_2 = tester.std_map_four.begin();
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  --iter_1;
  --iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}

TEST(Map, const_operator_assignment) {
  TestMap tester;
  s21::map<int, int>::const_iterator iter_1 = tester.s21_map_four.begin();
  s21::map<int, int>::const_iterator iter_3 = iter_1;
  std::map<int, int>::const_iterator iter_2 = tester.std_map_four.begin();
  std::map<int, int>::const_iterator iter_4 = iter_2;
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ((*iter_1).second, (*iter_3).second);
  EXPECT_EQ((*iter_2).second, (*iter_4).second);
}

TEST(Map, const_operator_equal) {
  TestMap tester;
  s21::map<int, int>::const_iterator iter_1 = tester.s21_map_four.begin();
  s21::map<int, int>::const_iterator iter_3 = tester.s21_map_four.begin();
  std::map<int, int>::const_iterator iter_2 = tester.std_map_empty.begin();
  std::map<int, int>::const_iterator iter_4 = tester.std_map_empty.begin();
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
  EXPECT_EQ(iter_1 == iter_3, iter_2 == iter_4);
}

TEST(Map, const_operatort_not_equal) {
  TestMap tester;
  s21::map<int, int>::const_iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ(iter_1 != tester.s21_map_four.end(),
            iter_2 != tester.std_map_empty.end());
}

TEST(Map, function_insert_without_duplicate) {
  TestMap tester;
  std::pair<s21::map<int, int>::iterator, bool> iter_1 =
      tester.s21_map_four.insert({5, 2});
  std::pair<std::map<int, int>::iterator, bool> iter_2 =
      tester.std_map_four.insert({5, 2});
  EXPECT_EQ((*(iter_1.first)).second, (*(iter_2.first)).second);
  EXPECT_TRUE(iter_1.second == iter_2.second);
}

TEST(Map, function_insert_with_duplicate) {
  TestMap tester;
  std::pair<s21::map<int, int>::iterator, bool> iter_1 =
      tester.s21_map_four.insert({1, 2});
  std::pair<std::map<int, int>::iterator, bool> iter_2 =
      tester.std_map_four.insert({1, 2});
  EXPECT_TRUE(iter_1.second == iter_2.second);
}

TEST(Map, function_insert_key_value_without_duplicate) {
  TestMap tester;
  std::pair<s21::map<int, int>::iterator, bool> iter_1 =
      tester.s21_map_four.insert(7, 7);
  std::pair<std::map<int, int>::iterator, bool> iter_2 =
      tester.std_map_four.insert({7, 7});
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ((*(iter_1.first)).second, (*(iter_2.first)).second);
  EXPECT_TRUE(iter_1.second == iter_2.second);
}

TEST(Map, function_insert_key_value_with_duplicate) {
  TestMap tester;
  std::pair<s21::map<int, int>::iterator, bool> iter_1 =
      tester.s21_map_four.insert(1, 7);
  std::pair<std::map<int, int>::iterator, bool> iter_2 =
      tester.std_map_four.insert({1, 7});
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_TRUE(iter_1.second == iter_2.second);
}

TEST(Map, function_insert_or_assign_value) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  std::map<int, int> m2({{1, 3}, {4, 2}});
  std::pair<s21::map<int, int>::iterator, bool> it1 = m1.insert_or_assign(5, 2);
  std::pair<std::map<int, int>::iterator, bool> it2 = m2.insert_or_assign(5, 2);
  ASSERT_TRUE(it1.second == it2.second);
}

TEST(Map, function_insert_or_assign) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  std::map<int, int> m2({{1, 3}, {4, 2}});
  std::pair<s21::map<int, int>::iterator, bool> it1 = m1.insert_or_assign(1, 2);
  std::pair<std::map<int, int>::iterator, bool> it2 = m2.insert_or_assign(1, 2);
  ASSERT_EQ((*(it1.first)).second, (*(it2.first)).second);
  ASSERT_TRUE(it1.second == it2.second);
}

TEST(Map, function_insert_s) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  std::pair<s21::map<int, int>::iterator, bool> it1 = m1.insert(5, 2);
  ASSERT_EQ((*(it1.first)).second, 2);
  ASSERT_TRUE(it1.second);
}

TEST(Map, function_max_sez) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  std::map<int, int> m2({{1, 3}, {4, 2}});
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(Map, function_max_sez_empty) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(Map, function_max_size_float_empty) {
  s21::map<int, int> s21_float_empty;
  std::map<int, int> std_float_empty;
  EXPECT_EQ(s21_float_empty.max_size(), std_float_empty.max_size());
}

TEST(Map, function_at) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  std::map<int, int> m2({{1, 3}, {4, 2}});
  ASSERT_EQ(m1.at(1), m2.at(1));
}

TEST(Map, function_erase) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  std::map<int, int> m2({{1, 3}, {4, 2}});
  m1.erase(m1.begin());
  m2.erase(m2.begin());
  ASSERT_EQ(m1.size(), m2.size());
}

TEST(Map, function_сontains) {
  s21::map<int, int> s1({{1, 3}, {4, 2}});
  ASSERT_TRUE(s1.contains(1));
  ASSERT_TRUE(s1.contains(4));
  ASSERT_FALSE(s1.contains(3));
}

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА MAP (END) ==========
*/

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА SET (START) ==========
*/

class TestSet {
 public:
  s21::set<int> s21_set_empty;
  s21::set<int> s21_set_ten{1, 2, 56, 76, 123, 53, 78, 43, 21, 100};
  s21::set<int> s21_set_copy;
  std::set<int> std_set_copy;
  s21::set<int> s21_move;
  std::set<int> std_move;
  s21::set<int> s21_set_swap{95, 94, 93, 92};
  std::set<int> std_set_swap{95, 94, 93, 92};
  s21::set<int> s21_set_merge{1, 2, 3, 4, 5};
  std::set<int> std_set_merge{1, 2, 3, 4, 5};

  std::set<int> std_set_empty;
  std::set<int> std_set_ten{1, 2, 56, 76, 123, 53, 78, 43, 21, 100};
};

TEST(Set, constructor_default) {
  TestSet tester;
  EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
  EXPECT_EQ(tester.s21_set_empty.empty(), tester.std_set_empty.empty());
}

TEST(Set, constructor_initialazer) {
  TestSet tester;
  EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
  EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
  EXPECT_EQ(tester.s21_set_ten.find(1) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(1) != tester.std_set_ten.end());
  EXPECT_EQ(tester.s21_set_ten.find(2) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(2) != tester.std_set_ten.end());
  EXPECT_EQ(tester.s21_set_ten.find(3) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(3) != tester.std_set_ten.end());
  EXPECT_EQ(tester.s21_set_ten.find(4) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(4) != tester.std_set_ten.end());
}

TEST(Set, constructor_copy) {
  TestSet tester;
  s21::set<int> s21_empty(tester.s21_set_ten);
  std::set<int> std_empty(tester.std_set_ten);
  EXPECT_EQ(s21_empty.find(1) != s21_empty.end(),
            std_empty.find(1) != std_empty.end());
  EXPECT_EQ(s21_empty.find(2) != s21_empty.end(),
            std_empty.find(2) != std_empty.end());
  EXPECT_EQ(s21_empty.find(3) != s21_empty.end(),
            std_empty.find(3) != std_empty.end());
  EXPECT_EQ(s21_empty.find(4) != s21_empty.end(),
            std_empty.find(4) != std_empty.end());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
}

TEST(Set, construct_move) {
  TestSet tester;
  s21::set<int> s21_move = std::move(tester.s21_set_ten);
  std::set<int> std_move = std::move(tester.std_set_ten);
  EXPECT_EQ(s21_move.find(1) != s21_move.end(),
            std_move.find(1) != std_move.end());
  EXPECT_EQ(s21_move.find(2) != s21_move.end(),
            std_move.find(2) != std_move.end());
  EXPECT_EQ(s21_move.find(3) != s21_move.end(),
            std_move.find(3) != std_move.end());
  EXPECT_EQ(s21_move.find(4) != s21_move.end(),
            std_move.find(4) != std_move.end());
  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_move.empty(), std_move.empty());
}

TEST(Set, operator_move) {
  TestSet tester;
  tester.s21_move = std::move(tester.s21_set_ten);
  tester.std_move = std::move(tester.std_set_ten);
  EXPECT_EQ(tester.s21_move.find(1) != tester.s21_move.end(),
            tester.std_move.find(1) != tester.std_move.end());
  EXPECT_EQ(tester.s21_move.find(2) != tester.s21_move.end(),
            tester.std_move.find(2) != tester.std_move.end());
  EXPECT_EQ(tester.s21_move.find(3) != tester.s21_move.end(),
            tester.std_move.find(3) != tester.std_move.end());
  EXPECT_EQ(tester.s21_move.find(4) != tester.s21_move.end(),
            tester.std_move.find(4) != tester.std_move.end());
  EXPECT_EQ(tester.s21_move.size(), tester.std_move.size());
  EXPECT_EQ(tester.s21_move.empty(), tester.std_move.empty());
}

TEST(Set, operator_copy) {
  TestSet tester;
  tester.s21_set_copy = tester.s21_set_ten;
  tester.std_set_copy = tester.std_set_ten;
  EXPECT_EQ(tester.s21_set_copy.find(1) != tester.s21_set_copy.end(),
            tester.std_set_copy.find(1) != tester.std_set_copy.end());
  EXPECT_EQ(tester.s21_set_copy.find(2) != tester.s21_set_copy.end(),
            tester.std_set_copy.find(2) != tester.std_set_copy.end());
  EXPECT_EQ(tester.s21_set_copy.find(3) != tester.s21_set_copy.end(),
            tester.std_set_copy.find(3) != tester.std_set_copy.end());
  EXPECT_EQ(tester.s21_set_copy.find(4) != tester.s21_set_copy.end(),
            tester.std_set_copy.find(4) != tester.std_set_copy.end());
  EXPECT_EQ(tester.s21_set_copy.size(), tester.std_set_copy.size());
  EXPECT_EQ(tester.s21_set_copy.empty(), tester.std_set_copy.empty());
}

TEST(Set, function_not_empty) {
  TestSet tester;
  EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
  EXPECT_EQ(tester.s21_set_ten.empty(), tester.std_set_ten.empty());
}

TEST(Set, function_empty) {
  TestSet tester;
  EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
  EXPECT_EQ(tester.s21_set_empty.empty(), tester.std_set_empty.empty());
}

TEST(Set, function_size_empty) {
  TestSet tester;
  EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
}
TEST(Set, function_size_not_empty) {
  TestSet tester;
  EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
}

TEST(Set, function_max_sez_empty) {
  TestSet tester;
  EXPECT_EQ(tester.s21_set_empty.max_size(), tester.std_set_empty.max_size());
}

TEST(Set, function_max_siez_not_empty) {
  TestSet tester;
  EXPECT_EQ(tester.s21_set_ten.max_size(), tester.std_set_ten.max_size());
}

TEST(Set, function_max_size_float_empty) {
  s21::set<float> s21_float_empty;
  std::set<float> std_float_empty;
  EXPECT_EQ(s21_float_empty.max_size(), std_float_empty.max_size());
}

TEST(Set, function_swap_not_empty) {
  TestSet tester;
  tester.s21_set_swap.swap(tester.s21_set_ten);
  tester.std_set_swap.swap(tester.std_set_ten);
  EXPECT_EQ(tester.s21_set_swap.find(1) != tester.s21_set_swap.end(),
            tester.std_set_swap.find(1) != tester.std_set_swap.end());
  EXPECT_EQ(tester.s21_set_swap.find(56) != tester.s21_set_swap.end(),
            tester.std_set_swap.find(56) != tester.std_set_swap.end());
  EXPECT_EQ(tester.s21_set_swap.find(76) != tester.s21_set_swap.end(),
            tester.std_set_swap.find(76) != tester.std_set_swap.end());
  EXPECT_EQ(tester.s21_set_ten.find(95) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(95) != tester.std_set_ten.end());
  EXPECT_EQ(tester.s21_set_ten.find(94) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(94) != tester.std_set_ten.end());
  EXPECT_EQ(tester.s21_set_ten.find(93) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(93) != tester.std_set_ten.end());
  EXPECT_EQ(tester.s21_set_swap.size(), tester.std_set_swap.size());
  EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
}

TEST(Set, function_swap_empty) {
  TestSet tester;
  tester.s21_set_empty.swap(tester.s21_set_swap);
  tester.std_set_empty.swap(tester.std_set_swap);

  EXPECT_EQ(tester.s21_set_empty.find(95) != tester.s21_set_empty.end(),
            tester.std_set_empty.find(95) != tester.std_set_empty.end());
  EXPECT_EQ(tester.s21_set_empty.find(94) != tester.s21_set_empty.end(),
            tester.std_set_empty.find(94) != tester.std_set_empty.end());
  EXPECT_EQ(tester.s21_set_empty.find(93) != tester.s21_set_empty.end(),
            tester.std_set_empty.find(93) != tester.std_set_empty.end());

  EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
  EXPECT_EQ(tester.s21_set_empty.empty(), tester.std_set_empty.empty());
  EXPECT_EQ(tester.s21_set_swap.size(), tester.std_set_swap.size());
  EXPECT_EQ(tester.s21_set_swap.empty(), tester.std_set_swap.empty());
}
TEST(Set, function_merge_with_duplicates) {
  TestSet tester;
  tester.s21_set_merge.merge(tester.s21_set_ten);
  tester.std_set_merge.merge(tester.std_set_ten);
  EXPECT_EQ(tester.s21_set_merge.find(1) != tester.s21_set_merge.end(),
            tester.std_set_merge.find(1) != tester.std_set_merge.end());
  EXPECT_EQ(tester.s21_set_merge.find(2) != tester.s21_set_merge.end(),
            tester.std_set_merge.find(2) != tester.std_set_merge.end());
  EXPECT_EQ(tester.s21_set_merge.find(76) != tester.s21_set_merge.end(),
            tester.std_set_merge.find(76) != tester.std_set_merge.end());

  EXPECT_EQ(tester.s21_set_merge.size(), tester.std_set_merge.size());
  EXPECT_EQ(tester.std_set_merge.empty(), tester.std_set_merge.empty());
}

TEST(Set, function_merge_wihout_duplicates) {
  TestSet tester;
  tester.s21_set_ten.merge(tester.s21_set_swap);
  tester.std_set_ten.merge(tester.std_set_swap);

  EXPECT_EQ(tester.s21_set_ten.find(95) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(95) != tester.std_set_ten.end());
  EXPECT_EQ(tester.s21_set_ten.find(1) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(1) != tester.std_set_ten.end());
  EXPECT_EQ(tester.s21_set_ten.find(94) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(94) != tester.std_set_ten.end());
  EXPECT_EQ(tester.s21_set_ten.find(76) != tester.s21_set_ten.end(),
            tester.std_set_ten.find(76) != tester.std_set_ten.end());

  EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
  EXPECT_EQ(tester.std_set_ten.empty(), tester.std_set_ten.empty());
  EXPECT_EQ(tester.s21_set_swap.size(), tester.std_set_swap.size());
  EXPECT_EQ(tester.s21_set_swap.empty(), tester.std_set_swap.empty());
}

TEST(Set, function_clear_not_empty) {
  TestSet tester;
  tester.s21_set_ten.clear();
  tester.std_set_ten.clear();
  EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
  EXPECT_EQ(tester.s21_set_ten.empty(), tester.std_set_ten.empty());
}

TEST(Set, function_clear_empty) {
  TestSet tester;
  tester.s21_set_empty.clear();
  tester.std_set_empty.clear();
  EXPECT_EQ(tester.s21_set_empty.size(), tester.std_set_empty.size());
  EXPECT_EQ(tester.std_set_empty.empty(), tester.std_set_empty.empty());
}

TEST(Set, function_begin_not_empty) {
  TestSet tester;
  s21::set<int>::iterator i = tester.s21_set_ten.begin();
  std::set<int>::iterator j = tester.std_set_ten.begin();
  EXPECT_EQ(*i, *j);
}

TEST(Set, function_begin_empty) {
  TestSet tester;
  s21::set<int>::iterator i = tester.s21_set_empty.begin();
  std::set<int>::iterator j = tester.std_set_empty.begin();
  EXPECT_EQ(*i, *j);
}

TEST(Set, function_const_begin_not_empty) {
  TestSet tester;
  s21::set<int>::const_iterator i = tester.s21_set_ten.begin();
  std::set<int>::const_iterator j = tester.std_set_ten.begin();
  EXPECT_EQ(*i, *j);
}

TEST(Set, function_const_begin_empty) {
  TestSet tester;
  s21::set<int>::const_iterator i = tester.s21_set_empty.begin();
  EXPECT_EQ(*i, 0);
}

TEST(Set, function_end_not_empty) {
  TestSet tester;
  s21::set<int>::iterator i = tester.s21_set_ten.end();
  --i;
  EXPECT_EQ(*i, 0);
}

TEST(Set, function_end_empty) {
  TestSet tester;
  s21::set<int>::iterator i = tester.s21_set_empty.end();
  EXPECT_EQ(*i, 0);
}

TEST(Set, function_const_end_not_empty) {
  TestSet tester;
  s21::set<int>::const_iterator i = tester.s21_set_ten.end();
  --i;
  EXPECT_EQ(*i, 0);
}

TEST(Set, function_const_end_empty) {
  TestSet tester;
  s21::set<int>::const_iterator i = tester.s21_set_empty.end();
  EXPECT_EQ(*i, 0);
}

TEST(Set, operator_plus) {
  TestSet tester;
  s21::set<int>::iterator i = tester.s21_set_ten.begin();
  std::set<int>::iterator j = tester.std_set_ten.begin();
  while (i != tester.s21_set_ten.end() && j != tester.std_set_ten.end()) {
    EXPECT_EQ(*i, *j);
    ++i;
    ++j;
  }
  EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
  EXPECT_EQ(tester.std_set_ten.empty(), tester.std_set_ten.empty());
}

TEST(Set, operator_minus) {
  TestSet tester;
  s21::set<int>::iterator i = tester.s21_set_ten.end();
  EXPECT_EQ(*i, 0);
  EXPECT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
  EXPECT_EQ(tester.s21_set_ten.empty(), tester.std_set_ten.empty());
}

TEST(Set, operation_assignment) {
  TestSet tester;
  s21::set<int>::iterator iter_1 = tester.s21_set_ten.begin();
  s21::set<int>::iterator iter_3 = iter_1;
  std::set<int>::iterator iter_2 = tester.std_set_ten.begin();
  std::set<int>::iterator iter_4 = iter_2;
  ASSERT_EQ(*iter_1, *iter_3);
  ASSERT_EQ(*iter_2, *iter_4);
}

TEST(Set, operation_equal) {
  TestSet tester;
  s21::set<int>::iterator it1 = tester.s21_set_ten.begin();
  s21::set<int>::iterator it3 = tester.s21_set_ten.begin();
  std::set<int>::iterator it2 = tester.std_set_ten.begin();
  std::set<int>::iterator it4 = tester.std_set_ten.begin();
  ASSERT_EQ(it1 == it3, it2 == it4);
}

TEST(Set, operation_not_equal) {
  TestSet tester;
  s21::set<int>::iterator iter_1 = tester.s21_set_ten.begin();
  std::set<int>::iterator iter_2 = tester.std_set_ten.begin();
  ASSERT_EQ(iter_1 != tester.s21_set_ten.end(),
            iter_2 != tester.std_set_ten.end());
}

TEST(Set, function_insert) {
  TestSet tester;
  std::pair<s21::set<int>::iterator, bool> iter_1 =
      tester.s21_set_ten.insert(45);
  std::pair<std::set<int>::iterator, bool> iter_2 =
      tester.std_set_ten.insert(45);
  EXPECT_EQ(*(iter_1.first), *(iter_2.first));
  EXPECT_EQ(iter_1.second, iter_2.second);
}

TEST(Set, function_find_have) {
  TestSet tester;
  s21::set<int>::iterator i = tester.s21_set_ten.find(1);
  std::set<int>::iterator j = tester.std_set_ten.find(1);
  EXPECT_EQ(i != tester.s21_set_ten.end(), j != tester.std_set_ten.end());
}

TEST(Set, function_find_dont_have) {
  TestSet tester;
  s21::set<int>::iterator i = tester.s21_set_ten.find(100);
  std::set<int>::iterator j = tester.std_set_ten.find(100);
  EXPECT_EQ(i == tester.s21_set_ten.end(), j == tester.std_set_ten.end());
}

TEST(Set, function_erase) {
  TestSet tester;
  tester.s21_set_ten.erase(tester.s21_set_ten.begin());
  tester.std_set_ten.erase(tester.std_set_ten.begin());
  s21::set<int>::iterator iter_1 = tester.s21_set_ten.find(1);
  std::set<int>::iterator iter_2 = tester.std_set_ten.find(1);
  ASSERT_EQ(iter_1 == tester.s21_set_ten.end(),
            iter_2 == tester.std_set_ten.end());
}

TEST(Set, functions_erase_alot) {
  TestSet tester;
  s21::set<int>::iterator it1 = tester.s21_set_ten.find(76);
  std::set<int>::iterator it2 = tester.std_set_ten.find(76);
  tester.s21_set_ten.erase(it1);
  tester.std_set_ten.erase(it2);
  it1 = tester.s21_set_ten.find(123);
  it2 = tester.std_set_ten.find(123);
  tester.s21_set_ten.erase(it1);
  tester.std_set_ten.erase(it2);
  it1 = tester.s21_set_ten.find(43);
  it2 = tester.std_set_ten.find(43);
  tester.s21_set_ten.erase(it1);
  tester.std_set_ten.erase(it2);
  ASSERT_EQ(tester.s21_set_ten.size(), tester.std_set_ten.size());
}

/*
    ========== ТЕСТЫ КОНТЕЙНЕРА SET (END) ==========
*/

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
