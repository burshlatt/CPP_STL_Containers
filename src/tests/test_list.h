#ifndef TEST_LIST_H
#define TEST_LIST_H

#include <gtest/gtest.h>
#include <list>

#include "../list/list.h"

class ListTestInt : public ::testing::Test {
public:
    ListTestInt() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::list<int>* _my;
    std::list<int>* _orig;
};

class ListTestString : public ::testing::Test {
public:
    ListTestString() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::list<std::string>* _my;
    std::list<std::string>* _orig;
};

#endif  // TEST_LIST_H
