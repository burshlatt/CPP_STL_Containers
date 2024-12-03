#include <vector>

#include "include/test_forward_list.h"

/*
     ----------------------------------------------------------
    |                                                          |
    |                                                          |
    |                  FUNDAMENTAL TYPE TESTS                  |
    |                                                          |
    |                                                          |
     ----------------------------------------------------------
*/

void ForwardListTestInt::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->empty(), _orig->empty());

        if (!_my->empty() && !_orig->empty()) {
            EXPECT_EQ(*_my->begin(), *_orig->begin());
            EXPECT_EQ(_my->front(), _orig->front());

            *_my->begin() = 111;
            *_orig->begin() = 111;

            auto my_it{_my->begin()};
            auto orig_it{_orig->begin()};

            while (orig_it != _orig->end()) {
                EXPECT_EQ(*(my_it++), *(orig_it++));
            }
        } else {
            EXPECT_EQ(_my->begin(), _my->end());
        }
    }

    delete _my;
    delete _orig;

    _my = nullptr;
    _orig = nullptr;
}

TEST_F(ForwardListTestInt, TEST_1) {
    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();
}

TEST_F(ForwardListTestInt, TEST_2) {
    _my = new s21::forward_list<int>(0, 9);
    _orig = new std::forward_list<int>(0, 9);
}

TEST_F(ForwardListTestInt, TEST_3) {
    _my = new s21::forward_list<int>(5, 9);
    _orig = new std::forward_list<int>(5, 9);
}

TEST_F(ForwardListTestInt, TEST_4) {
    _my = new s21::forward_list<int>({});
    _orig = new std::forward_list<int>({});
}

TEST_F(ForwardListTestInt, TEST_5) {
    _my = new s21::forward_list<int>({1, 2, 3, 4, 5});
    _orig = new std::forward_list<int>({1, 2, 3, 4, 5});
}

TEST_F(ForwardListTestInt, TEST_6) {
    s21::forward_list<int> my_tmp;
    std::forward_list<int> orig_tmp;

    _my = new s21::forward_list<int>(my_tmp.begin(), my_tmp.end());
    _orig = new std::forward_list<int>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ForwardListTestInt, TEST_7) {
    s21::forward_list<int> my_tmp({1, 2, 3, 4, 5});
    std::forward_list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>(++my_tmp.begin(), my_tmp.end());
    _orig = new std::forward_list<int>(++orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ForwardListTestInt, TEST_8) {
    s21::forward_list<int> my_tmp({1, 2, 3, 4, 5});
    std::forward_list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>(++my_tmp.begin(), ++my_tmp.begin());
    _orig = new std::forward_list<int>(++orig_tmp.begin(), ++orig_tmp.begin());
}

TEST_F(ForwardListTestInt, TEST_9) {
    s21::forward_list<int> my_tmp({1, 2, 3, 4, 5});
    std::forward_list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>(my_tmp.end(), my_tmp.end());
    _orig = new std::forward_list<int>(orig_tmp.end(), orig_tmp.end());
}

TEST_F(ForwardListTestInt, TEST_10) {
    s21::forward_list<int> my_tmp({1, 2, 3, 4, 5});
    std::forward_list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>(my_tmp.begin(), my_tmp.end());
    _orig = new std::forward_list<int>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ForwardListTestInt, TEST_12) {
    std::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>(my_tmp.begin(), my_tmp.end());
    _orig = new std::forward_list<int>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ForwardListTestInt, TEST_13) {
    std::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>(++my_tmp.begin(), --my_tmp.end());
    _orig = new std::forward_list<int>(++orig_tmp.begin(), --orig_tmp.end());
}

TEST_F(ForwardListTestInt, TEST_14) {
    s21::forward_list<int> my_tmp;
    std::forward_list<int> orig_tmp;

    _my = new s21::forward_list<int>(my_tmp);
    _orig = new std::forward_list<int>(orig_tmp);
}

TEST_F(ForwardListTestInt, TEST_15) {
    s21::forward_list<int> my_tmp({1, 2, 3, 4, 5});
    std::forward_list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>(my_tmp);
    _orig = new std::forward_list<int>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (int elem : orig_tmp) {
        EXPECT_EQ(*my_it, elem);
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ForwardListTestInt, TEST_16) {
    s21::forward_list<int> my_tmp;
    std::forward_list<int> orig_tmp;

    _my = new s21::forward_list<int>(std::move(my_tmp));
    _orig = new std::forward_list<int>(std::move(orig_tmp));
}

TEST_F(ForwardListTestInt, TEST_17) {
    s21::forward_list<int> my_tmp({1, 2, 3, 4, 5});
    std::forward_list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>(std::move(my_tmp));
    _orig = new std::forward_list<int>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_front(999);
    orig_tmp.push_front(999);

    my_tmp.push_front(777);
    orig_tmp.push_front(777);

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};

    for (int elem : orig_tmp) {
        EXPECT_EQ(*(my_it++), elem);
    }
}

TEST_F(ForwardListTestInt, TEST_18) {
    s21::forward_list<int> my_tmp;
    std::forward_list<int> orig_tmp;

    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    *_my = my_tmp;
    *_orig = orig_tmp;
}

TEST_F(ForwardListTestInt, TEST_19) {
    s21::forward_list<int> my_tmp({1, 2, 3, 4, 5});
    std::forward_list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (int elem : orig_tmp) {
        EXPECT_EQ(*my_it, elem);
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ForwardListTestInt, TEST_20) {
    s21::forward_list<int> my_tmp;
    std::forward_list<int> orig_tmp;

    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(ForwardListTestInt, TEST_21) {
    s21::forward_list<int> my_tmp({1, 2, 3, 4, 5});
    std::forward_list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_front(999);
    orig_tmp.push_front(999);

    my_tmp.push_front(777);
    orig_tmp.push_front(777);

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};

    for (int elem : orig_tmp) {
        EXPECT_EQ(*(my_it++), elem);
    }
}

TEST_F(ForwardListTestInt, TEST_22) {
    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    *_my = {};
    *_orig = {};
}

TEST_F(ForwardListTestInt, TEST_23) {
    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    *_my = {1, 2, 3, 4, 5};
    *_orig = {1, 2, 3, 4, 5};
}

TEST_F(ForwardListTestInt, TEST_24) {
    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    *_my = {1, 2, 3, 4, 5};
    *_orig = {1, 2, 3, 4, 5};

    _my->clear();
    _orig->clear();
}

TEST_F(ForwardListTestInt, TEST_25) {
    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    int num{123};
    int num_move{321};

    _my->push_front(num);
    _orig->push_front(num);

    EXPECT_EQ(_my->front(), _orig->front());

    _my->push_front(std::move(num_move));
    _orig->push_front(std::move(num_move));

    EXPECT_EQ(_my->front(), _orig->front());
    EXPECT_EQ(_my->front(), num_move);
}

TEST_F(ForwardListTestInt, TEST_26) {
    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    int num{123};
    int num_move{321};

    auto my_it{_my->insert_after(_my->before_begin(), num)};
    auto orig_it{_orig->insert_after(_orig->before_begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(my_it, _my->begin());
    EXPECT_EQ(_my->front(), _orig->front());

    my_it = _my->insert_after(_my->before_begin(), std::move(num_move));
    orig_it = _orig->insert_after(_orig->before_begin(), std::move(num_move));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(my_it, _my->begin());
    EXPECT_EQ(_my->front(), _orig->front());
    EXPECT_EQ(_my->front(), num_move);
}

TEST_F(ForwardListTestInt, TEST_27) {
    _my = new s21::forward_list<int>({1, 2, 3, 4, 5});
    _orig = new std::forward_list<int>({1, 2, 3, 4, 5});

    int num{123};
    int num_move{321};

    auto my_it{_my->insert_after(++_my->begin(), num)};
    auto orig_it{_orig->insert_after(++_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(my_it, _my->begin() + 2);

    my_it = _my->insert_after(_my->begin(), std::move(num_move));
    orig_it = _orig->insert_after(_orig->begin(), std::move(num_move));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(my_it, _my->begin() + 1);
}

TEST_F(ForwardListTestInt, TEST_28) {
    _my = new s21::forward_list<int>({1, 2, 3, 4, 5});
    _orig = new std::forward_list<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert_after(++_my->begin(), 10, num)};
    auto orig_it{_orig->insert_after(++_orig->begin(), 10, num)};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestInt, TEST_29) {
    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    int num{123};

    auto my_it{_my->insert_after(_my->before_begin(), 10, num)};
    auto orig_it{_orig->insert_after(_orig->before_begin(), 10, num)};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestInt, TEST_30) {
    std::vector<int> vec({1, 2, 3, 4, 5});

    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    auto my_it{_my->insert_after(_my->before_begin(), vec.begin(), vec.end())};
    auto orig_it{_orig->insert_after(_orig->before_begin(), vec.begin(), vec.end())};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestInt, TEST_31) {
    _my = new s21::forward_list<int>();
    _orig = new std::forward_list<int>();

    auto my_it{_my->insert_after(_my->before_begin(), {1, 2, 3, 4, 5})};
    auto orig_it{_orig->insert_after(_orig->before_begin(), {1, 2, 3, 4, 5})};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestInt, TEST_32) {
    _my = new s21::forward_list<int>({1, 2, 3, 4, 5});
    _orig = new std::forward_list<int>({1, 2, 3, 4, 5});

    auto my_it{_my->insert_after(++_my->begin(), {1, 2, 3, 4, 5})};
    auto orig_it{_orig->insert_after(++_orig->begin(), {1, 2, 3, 4, 5})};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestInt, TEST_33) {
    _my = new s21::forward_list<int>({1, 2, 3, 4, 5});
    _orig = new std::forward_list<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase_after(_my->before_begin())};
    auto orig_it{_orig->erase_after(_orig->before_begin())};

    EXPECT_EQ(*my_it, *orig_it);

    my_it = _my->erase_after(++_my->begin());
    orig_it = _orig->erase_after(++_orig->begin());

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestInt, TEST_34) {
    _my = new s21::forward_list<int>({1, 2, 3, 4, 5});
    _orig = new std::forward_list<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase_after(++_my->begin(), _my->begin() + 3)};
    auto orig_it{_orig->erase_after(++_orig->begin(), ++++++_orig->begin())};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestInt, TEST_35) {
    _my = new s21::forward_list<int>({1, 2, 3, 4, 5});
    _orig = new std::forward_list<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase_after(++_my->begin(), _my->end())};
    auto orig_it{_orig->erase_after(++_orig->begin(), _orig->end())};
}

TEST_F(ForwardListTestInt, TEST_37) {
    _my = new s21::forward_list<int>({1, 2, 3, 4, 5});
    _orig = new std::forward_list<int>({1, 2, 3, 4, 5});

    _my->pop_front();
    _orig->pop_front();

    _my->pop_front();
    _orig->pop_front();
}

/*
     ----------------------------------------------------------
    |                                                          |
    |                                                          |
    |                    COMPOUND TYPE TESTS                   |
    |                                                          |
    |                                                          |
     ----------------------------------------------------------
*/

void ForwardListTestString::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->empty(), _orig->empty());

        if (!_my->empty() && !_orig->empty()) {
            EXPECT_EQ(*_my->begin(), *_orig->begin());
            EXPECT_EQ(_my->front(), _orig->front());

            *_my->begin() = "111";
            *_orig->begin() = "111";

            auto my_it{_my->begin()};
            auto orig_it{_orig->begin()};

            while (orig_it != _orig->end()) {
                EXPECT_EQ(*(my_it++), *(orig_it++));
            }
        } else {
            EXPECT_EQ(_my->begin(), _my->end());
        }
    }

    delete _my;
    delete _orig;

    _my = nullptr;
    _orig = nullptr;
}

TEST_F(ForwardListTestString, TEST_1) {
    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();
}

TEST_F(ForwardListTestString, TEST_2) {
    _my = new s21::forward_list<std::string>(0, "9");
    _orig = new std::forward_list<std::string>(0, "9");
}

TEST_F(ForwardListTestString, TEST_3) {
    _my = new s21::forward_list<std::string>(5, "9");
    _orig = new std::forward_list<std::string>(5, "9");
}

TEST_F(ForwardListTestString, TEST_4) {
    _my = new s21::forward_list<std::string>({});
    _orig = new std::forward_list<std::string>({});
}

TEST_F(ForwardListTestString, TEST_5) {
    _my = new s21::forward_list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::forward_list<std::string>({"1", "2", "3", "4", "5"});
}

TEST_F(ForwardListTestString, TEST_6) {
    s21::forward_list<std::string> my_tmp;
    std::forward_list<std::string> orig_tmp;

    _my = new s21::forward_list<std::string>(my_tmp.begin(), my_tmp.end());
    _orig = new std::forward_list<std::string>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ForwardListTestString, TEST_7) {
    s21::forward_list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::forward_list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>(++my_tmp.begin(), my_tmp.end());
    _orig = new std::forward_list<std::string>(++orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ForwardListTestString, TEST_8) {
    s21::forward_list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::forward_list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>(++my_tmp.begin(), ++my_tmp.begin());
    _orig = new std::forward_list<std::string>(++orig_tmp.begin(), ++orig_tmp.begin());
}

TEST_F(ForwardListTestString, TEST_9) {
    s21::forward_list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::forward_list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>(my_tmp.end(), my_tmp.end());
    _orig = new std::forward_list<std::string>(orig_tmp.end(), orig_tmp.end());
}

TEST_F(ForwardListTestString, TEST_10) {
    s21::forward_list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::forward_list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>(my_tmp.begin(), my_tmp.end());
    _orig = new std::forward_list<std::string>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ForwardListTestString, TEST_12) {
    std::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>(my_tmp.begin(), my_tmp.end());
    _orig = new std::forward_list<std::string>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ForwardListTestString, TEST_13) {
    std::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>(++my_tmp.begin(), --my_tmp.end());
    _orig = new std::forward_list<std::string>(++orig_tmp.begin(), --orig_tmp.end());
}

TEST_F(ForwardListTestString, TEST_14) {
    s21::forward_list<std::string> my_tmp;
    std::forward_list<std::string> orig_tmp;

    _my = new s21::forward_list<std::string>(my_tmp);
    _orig = new std::forward_list<std::string>(orig_tmp);
}

TEST_F(ForwardListTestString, TEST_15) {
    s21::forward_list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::forward_list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>(my_tmp);
    _orig = new std::forward_list<std::string>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (const auto& elem : orig_tmp) {
        EXPECT_EQ(*my_it, elem);
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ForwardListTestString, TEST_16) {
    s21::forward_list<std::string> my_tmp;
    std::forward_list<std::string> orig_tmp;

    _my = new s21::forward_list<std::string>(std::move(my_tmp));
    _orig = new std::forward_list<std::string>(std::move(orig_tmp));
}

TEST_F(ForwardListTestString, TEST_17) {
    s21::forward_list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::forward_list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>(std::move(my_tmp));
    _orig = new std::forward_list<std::string>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_front("999");
    orig_tmp.push_front("999");

    my_tmp.push_front("777");
    orig_tmp.push_front("777");

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};

    for (const auto& elem : orig_tmp) {
        EXPECT_EQ(*(my_it++), elem);
    }
}

TEST_F(ForwardListTestString, TEST_18) {
    s21::forward_list<std::string> my_tmp;
    std::forward_list<std::string> orig_tmp;

    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    *_my = my_tmp;
    *_orig = orig_tmp;
}

TEST_F(ForwardListTestString, TEST_19) {
    s21::forward_list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::forward_list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (const auto& elem : orig_tmp) {
        EXPECT_EQ(*my_it, elem);
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ForwardListTestString, TEST_20) {
    s21::forward_list<std::string> my_tmp;
    std::forward_list<std::string> orig_tmp;

    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(ForwardListTestString, TEST_21) {
    s21::forward_list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::forward_list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_front("999");
    orig_tmp.push_front("999");

    my_tmp.push_front("777");
    orig_tmp.push_front("777");

    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};

    for (const auto& elem : orig_tmp) {
        EXPECT_EQ(*(my_it++), elem);
    }
}

TEST_F(ForwardListTestString, TEST_22) {
    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    *_my = {};
    *_orig = {};
}

TEST_F(ForwardListTestString, TEST_23) {
    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    *_my = {"1", "2", "3", "4", "5"};
    *_orig = {"1", "2", "3", "4", "5"};
}

TEST_F(ForwardListTestString, TEST_24) {
    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    *_my = {"1", "2", "3", "4", "5"};
    *_orig = {"1", "2", "3", "4", "5"};

    _my->clear();
    _orig->clear();
}

TEST_F(ForwardListTestString, TEST_25) {
    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    std::string num{"123"};

    _my->push_front(num);
    _orig->push_front(num);

    EXPECT_EQ(_my->front(), _orig->front());

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    _my->push_front(std::move(num_move_my));
    _orig->push_front(std::move(num_move_orig));

    EXPECT_EQ(_my->front(), _orig->front());
    EXPECT_NE(_my->front(), num_move_my);
}

TEST_F(ForwardListTestString, TEST_26) {
    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert_after(_my->before_begin(), num)};
    auto orig_it{_orig->insert_after(_orig->before_begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(my_it, _my->begin());
    EXPECT_EQ(_my->front(), _orig->front());

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert_after(_my->before_begin(), std::move(num_move_my));
    orig_it = _orig->insert_after(_orig->before_begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(my_it, _my->begin());
    EXPECT_EQ(_my->front(), _orig->front());
    EXPECT_NE(_my->front(), num_move_my);
}

TEST_F(ForwardListTestString, TEST_27) {
    _my = new s21::forward_list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::forward_list<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert_after(++_my->begin(), num)};
    auto orig_it{_orig->insert_after(++_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(my_it, _my->begin() + 2);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert_after(_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert_after(_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(my_it, _my->begin() + 1);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(ForwardListTestString, TEST_28) {
    _my = new s21::forward_list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::forward_list<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert_after(++_my->begin(), 10, num)};
    auto orig_it{_orig->insert_after(++_orig->begin(), 10, num)};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestString, TEST_29) {
    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert_after(_my->before_begin(), 10, num)};
    auto orig_it{_orig->insert_after(_orig->before_begin(), 10, num)};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestString, TEST_30) {
    std::vector<std::string> vec({"1", "2", "3", "4", "5"});

    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    auto my_it{_my->insert_after(_my->before_begin(), vec.begin(), vec.end())};
    auto orig_it{_orig->insert_after(_orig->before_begin(), vec.begin(), vec.end())};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestString, TEST_31) {
    _my = new s21::forward_list<std::string>();
    _orig = new std::forward_list<std::string>();

    auto my_it{_my->insert_after(_my->before_begin(), {"1", "2", "3", "4", "5"})};
    auto orig_it{_orig->insert_after(_orig->before_begin(), {"1", "2", "3", "4", "5"})};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestString, TEST_32) {
    _my = new s21::forward_list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::forward_list<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->insert_after(++_my->begin(), {"1", "2", "3", "4", "5"})};
    auto orig_it{_orig->insert_after(++_orig->begin(), {"1", "2", "3", "4", "5"})};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestString, TEST_33) {
    _my = new s21::forward_list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::forward_list<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase_after(_my->before_begin())};
    auto orig_it{_orig->erase_after(_orig->before_begin())};

    EXPECT_EQ(*my_it, *orig_it);

    my_it = _my->erase_after(++_my->begin());
    orig_it = _orig->erase_after(++_orig->begin());

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestString, TEST_34) {
    _my = new s21::forward_list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::forward_list<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase_after(++_my->begin(), _my->begin() + 3)};
    auto orig_it{_orig->erase_after(++_orig->begin(), ++++++_orig->begin())};

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(ForwardListTestString, TEST_35) {
    _my = new s21::forward_list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::forward_list<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase_after(++_my->begin(), _my->end())};
    auto orig_it{_orig->erase_after(++_orig->begin(), _orig->end())};
}

TEST_F(ForwardListTestString, TEST_37) {
    _my = new s21::forward_list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::forward_list<std::string>({"1", "2", "3", "4", "5"});

    _my->pop_front();
    _orig->pop_front();

    _my->pop_front();
    _orig->pop_front();
}
