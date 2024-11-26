#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

#include <gtest/gtest.h>
#include <vector>
#include <memory>

#include "../../vector/vector.h"

class VectorTestInt : public ::testing::Test {
public:
    VectorTestInt() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::vector<int>* _my;
    std::vector<int>* _orig;
};

class VectorTestString : public ::testing::Test {
public:
    VectorTestString() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::vector<std::string>* _my;
    std::vector<std::string>* _orig;
};

class VectorTestUniquePtr : public ::testing::Test {
public:
    VectorTestUniquePtr() :
        _my(nullptr),
        _orig(nullptr)
    {}

protected:
    void SetUp() override { }

    void TearDown() override;

public:
    s21::vector<std::unique_ptr<std::string>>* _my;
    std::vector<std::unique_ptr<std::string>>* _orig;
};

#endif  // TEST_VECTOR_H
