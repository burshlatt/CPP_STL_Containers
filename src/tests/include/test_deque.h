#ifndef TEST_DEQUE_H
#define TEST_DEQUE_H

#include <gtest/gtest.h>
#include <deque>
#include <memory>

#include "../../deque/deque.h"

class DequeTestInt : public ::testing::Test {
public:
    DequeTestInt() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::deque<int>* _my;
    std::deque<int>* _orig;
};

class DequeTestString : public ::testing::Test {
public:
    DequeTestString() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::deque<std::string>* _my;
    std::deque<std::string>* _orig;
};

class DequeTestUniquePtr : public ::testing::Test {
public:
    DequeTestUniquePtr() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::deque<std::unique_ptr<std::string>>* _my;
    std::deque<std::unique_ptr<std::string>>* _orig;
};

#endif  // TEST_DEQUE_H
