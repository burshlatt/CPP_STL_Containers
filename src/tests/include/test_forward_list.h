#ifndef TEST_FORWARD_LIST_H
#define TEST_FORWARD_LIST_H

#include <gtest/gtest.h>
#include <forward_list>
#include <memory>

#include "../../forward_list/forward_list.h"

class ForwardListTestInt : public ::testing::Test {
public:
    ForwardListTestInt() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::forward_list<int>* _my;
    std::forward_list<int>* _orig;
};

class ForwardListTestString : public ::testing::Test {
public:
    ForwardListTestString() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::forward_list<std::string>* _my;
    std::forward_list<std::string>* _orig;
};

#endif  // TEST_FORWARD_LIST_H
