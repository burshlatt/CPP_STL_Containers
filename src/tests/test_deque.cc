#include <list>

#include "include/test_deque.h"

/*
     ----------------------------------------------------------
    |                                                          |
    |                                                          |
    |                  FUNDAMENTAL TYPE TESTS                  |
    |                                                          |
    |                                                          |
     ----------------------------------------------------------
*/

void DequeTestInt::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->size(), _orig->size());
        EXPECT_EQ(_my->empty(), _orig->empty());

        if (!_my->empty() && !_orig->empty()) {
            EXPECT_EQ(*_my->begin(), *_orig->begin());
            EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
            EXPECT_EQ(_my->front(), _orig->front());
            EXPECT_EQ(_my->back(), _orig->back());

            *_my->begin() = 111;
            *_orig->begin() = 111;

            *(_my->end() - 1) = 222;
            *(_orig->end() - 1) = 222;

            auto my_it{_my->begin()};
            auto orig_it{_orig->begin()};

            for (std::size_t i{}; i < _orig->size(); ++i) {
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

TEST_F(DequeTestInt, TEST_0) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();
}

TEST_F(DequeTestInt, TEST_1) {
    _my = new s21::deque<int>(9);
    _orig = new std::deque<int>(9);
}

TEST_F(DequeTestInt, TEST_2) {
    _my = new s21::deque<int>(0, 9);
    _orig = new std::deque<int>(0, 9);
}

TEST_F(DequeTestInt, TEST_3) {
    _my = new s21::deque<int>(5, 9);
    _orig = new std::deque<int>(5, 9);
}

TEST_F(DequeTestInt, TEST_4) {
    _my = new s21::deque<int>({});
    _orig = new std::deque<int>({});
}

TEST_F(DequeTestInt, TEST_5) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});
}

TEST_F(DequeTestInt, TEST_6) {
    s21::deque<int> my_tmp({1, 2, 3, 4, 5});
    std::deque<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::deque<int>(my_tmp.begin() + 1, my_tmp.end() - 1);
    _orig = new std::deque<int>(orig_tmp.begin() + 1, orig_tmp.end() - 1);
}

TEST_F(DequeTestInt, TEST_7) {
    s21::deque<int> my_tmp({1, 2, 3, 4, 5});
    std::deque<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::deque<int>(my_tmp.begin() + 1, my_tmp.begin() + 1);
    _orig = new std::deque<int>(orig_tmp.begin() + 1, orig_tmp.begin() + 1);
}

TEST_F(DequeTestInt, TEST_8) {
    s21::deque<int> my_tmp({1, 2, 3, 4, 5});
    std::deque<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::deque<int>(my_tmp.end(), my_tmp.end());
    _orig = new std::deque<int>(orig_tmp.end(), orig_tmp.end());
}

TEST_F(DequeTestInt, TEST_9) {
    s21::deque<int> my_tmp({1, 2, 3, 4, 5});
    std::deque<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::deque<int>(my_tmp.begin() + 1, my_tmp.end());
    _orig = new std::deque<int>(orig_tmp.begin() + 1, orig_tmp.end());
}

TEST_F(DequeTestInt, TEST_10) {
    std::deque<int> my_tmp({1, 2, 3, 4, 5});
    std::deque<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::deque<int>(my_tmp.begin(), my_tmp.end());
    _orig = new std::deque<int>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(DequeTestInt, TEST_11) {
    s21::deque<int> my_tmp;
    std::deque<int> orig_tmp;

    _my = new s21::deque<int>(my_tmp);
    _orig = new std::deque<int>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(DequeTestInt, TEST_12) {
    s21::deque<int> my_tmp({1, 2, 3, 4, 5});
    std::deque<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::deque<int>(my_tmp);
    _orig = new std::deque<int>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(DequeTestInt, TEST_13) {
    s21::deque<int> my_tmp;
    std::deque<int> orig_tmp;

    _my = new s21::deque<int>(std::move(my_tmp));
    _orig = new std::deque<int>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(DequeTestInt, TEST_14) {
    s21::deque<int> my_tmp({1, 2, 3, 4, 5});
    std::deque<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::deque<int>(std::move(my_tmp));
    _orig = new std::deque<int>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back(999);
    orig_tmp.push_back(999);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};
    auto orig_it{orig_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(orig_it++));
    }
}

TEST_F(DequeTestInt, TEST_15) {
    s21::deque<int> my_tmp;
    std::deque<int> orig_tmp;

    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(DequeTestInt, TEST_16) {
    s21::deque<int> my_tmp({1, 2, 3, 4, 5});
    std::deque<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(DequeTestInt, TEST_17) {
    s21::deque<int> my_tmp;
    std::deque<int> orig_tmp;

    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(DequeTestInt, TEST_18) {
    s21::deque<int> my_tmp({1, 2, 3, 4, 5});
    std::deque<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back(999);
    orig_tmp.push_back(999);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};
    auto orig_it{orig_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(orig_it++));
    }
}

TEST_F(DequeTestInt, TEST_19) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    *_my = {};
    *_orig = {};
}

TEST_F(DequeTestInt, TEST_20) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    *_my = {1, 2, 3, 4, 5};
    *_orig = {1, 2, 3, 4, 5};
}

TEST_F(DequeTestInt, TEST_21) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    *_my = {1, 2, 3, 4, 5};
    *_orig = {1, 2, 3, 4, 5};

    _my->clear();
    _orig->clear();
}

TEST_F(DequeTestInt, TEST_22) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    int num{123};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_23) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    int num{123};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->begin() + 1, std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin() + 1, std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_24) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    int num{123};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_25) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    int num{123};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_26) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    int num{123};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_27) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    int num{123};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_28) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_29) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(_my->begin() + 1, num)};
    auto orig_it{_orig->insert(_orig->begin() + 1, num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->begin() + 1, std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin() + 1, std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_30) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_31) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_32) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_33) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(_my->end() - 1, num)};
    auto orig_it{_orig->insert(_orig->end() - 1, num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(_my->end() - 1, std::move(num_move_my));
    orig_it = _orig->insert(_orig->end() - 1, std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(DequeTestInt, TEST_34) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(_my->end() - 1)};
    auto orig_it{_orig->erase(_orig->end() - 1)};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
    EXPECT_EQ(*(--my_it), *(--orig_it));

    my_it = _my->erase(_my->begin());
    orig_it = _orig->erase(_orig->begin());

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(*(++my_it), *(++orig_it));

    my_it = _my->erase(_my->begin() + 1);
    orig_it = _orig->erase(_orig->begin() + 1);

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(*(--my_it), *(--orig_it));
    EXPECT_EQ(*(++my_it), *(++orig_it));
}

TEST_F(DequeTestInt, TEST_35) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(_my->begin() + 1, _my->end() - 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->end() - 1)};

    EXPECT_EQ(my_it, _my->end() - 1);
    EXPECT_EQ(orig_it, _orig->end() - 1);
    EXPECT_EQ(*(--my_it), *(--orig_it));
}

TEST_F(DequeTestInt, TEST_36) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(_my->begin(), _my->end())};
    auto orig_it{_orig->erase(_orig->begin(), _orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
}

TEST_F(DequeTestInt, TEST_37) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(_my->begin() + 1, _my->begin() + 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->begin() + 1)};

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(my_it, _my->begin() + 1);
    EXPECT_EQ(orig_it, _orig->begin() + 1);
}

TEST_F(DequeTestInt, TEST_38) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    int str{123};

    _my->push_back(str);
    _orig->push_back(str);

    EXPECT_EQ(*_my->begin(), str);
    EXPECT_EQ(*_orig->begin(), str);
    EXPECT_EQ(_my->begin(), _my->end() - 1);
    EXPECT_EQ(_orig->begin(), (_orig->end() - 1));
}

TEST_F(DequeTestInt, TEST_39) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    int str_1{123};
    int str_2{123};

    _my->push_back(std::move(str_1));
    _orig->push_back(std::move(str_2));;

    EXPECT_EQ(*_my->begin(), str_1);
    EXPECT_EQ(*_orig->begin(), str_2);
    EXPECT_EQ(_my->begin(), (_my->end() - 1));
    EXPECT_EQ(_orig->begin(), (_orig->end() - 1));
}

TEST_F(DequeTestInt, TEST_40) {
    _my = new s21::deque<int>();
    _orig = new std::deque<int>();

    _my->push_back(123);
    _orig->push_back(123);

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
}

TEST_F(DequeTestInt, TEST_41) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    _my->pop_back();
    _orig->pop_back();

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
}

TEST_F(DequeTestInt, TEST_42) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    _my->clear();
    _orig->clear();
}

TEST_F(DequeTestInt, TEST_43) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    auto it_1{_my->erase(_my->begin())};
    auto it_2{_orig->erase(_orig->begin())};

    EXPECT_EQ(*it_1, *it_2);
    EXPECT_EQ(*(it_1 + 1), *(it_2 + 1));
}

TEST_F(DequeTestInt, TEST_44) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    auto it_1{_my->erase(_my->begin() + 1)};
    auto it_2{_orig->erase(_orig->begin() + 1)};

    EXPECT_EQ(*it_1, *it_2);

    it_1 = _my->erase(_my->end() - 2);
    it_2 = _orig->erase(_orig->end() - 2);

    EXPECT_EQ(*it_1, *it_2);
}

TEST_F(DequeTestInt, TEST_45) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    auto it_1{_my->erase(_my->begin() + 1, _my->end() - 1)};
    auto it_2{_orig->erase(_orig->begin() + 1, _orig->end() - 1)};

    EXPECT_EQ(*it_1, *it_2);
}

TEST_F(DequeTestInt, TEST_46) {
    _my = new s21::deque<int>({1, 2, 3, 4, 5});
    _orig = new std::deque<int>({1, 2, 3, 4, 5});

    _my->erase(_my->begin(), _my->end());
    _orig->erase(_orig->begin(), _orig->end());
}

TEST_F(DequeTestInt, TEST_47) {
    std::list<int> list({1, 2, 3, 4, 5});

    _my = new s21::deque<int>(list.begin(), list.end());
    _orig = new std::deque<int>(list.begin(), list.end());
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

void DequeTestString::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->size(), _orig->size());
        EXPECT_EQ(_my->empty(), _orig->empty());

        if (!_my->empty() && !_orig->empty()) {
            EXPECT_EQ(*_my->begin(), *_orig->begin());
            EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
            EXPECT_EQ(_my->front(), _orig->front());
            EXPECT_EQ(_my->back(), _orig->back());

            *_my->begin() = "111";
            *_orig->begin() = "111";

            *(_my->end() - 1) = "222";
            *(_orig->end() - 1) = "222";

            auto my_it{_my->begin()};
            auto orig_it{_orig->begin()};

            for (std::size_t i{}; i < _orig->size(); ++i) {
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

TEST_F(DequeTestString, TEST_0) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();
}

TEST_F(DequeTestString, TEST_1) {
    _my = new s21::deque<std::string>(9);
    _orig = new std::deque<std::string>(9);
}

TEST_F(DequeTestString, TEST_2) {
    _my = new s21::deque<std::string>(0, "9");
    _orig = new std::deque<std::string>(0, "9");
}

TEST_F(DequeTestString, TEST_3) {
    _my = new s21::deque<std::string>(5, "9");
    _orig = new std::deque<std::string>(5, "9");
}

TEST_F(DequeTestString, TEST_4) {
    _my = new s21::deque<std::string>({});
    _orig = new std::deque<std::string>({});
}

TEST_F(DequeTestString, TEST_5) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});
}

TEST_F(DequeTestString, TEST_6) {
    s21::deque<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::deque<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>(my_tmp.begin() + 1, my_tmp.end() - 1);
    _orig = new std::deque<std::string>(orig_tmp.begin() + 1, orig_tmp.end() - 1);
}

TEST_F(DequeTestString, TEST_7) {
    s21::deque<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::deque<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>(my_tmp.begin() + 1, my_tmp.begin() + 1);
    _orig = new std::deque<std::string>(orig_tmp.begin() + 1, orig_tmp.begin() + 1);
}

TEST_F(DequeTestString, TEST_8) {
    s21::deque<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::deque<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>(my_tmp.end(), my_tmp.end());
    _orig = new std::deque<std::string>(orig_tmp.end(), orig_tmp.end());
}

TEST_F(DequeTestString, TEST_9) {
    s21::deque<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::deque<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>(my_tmp.begin() + 1, my_tmp.end());
    _orig = new std::deque<std::string>(orig_tmp.begin() + 1, orig_tmp.end());
}

TEST_F(DequeTestString, TEST_10) {
    std::deque<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::deque<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>(my_tmp.begin(), my_tmp.end());
    _orig = new std::deque<std::string>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(DequeTestString, TEST_11) {
    s21::deque<std::string> my_tmp;
    std::deque<std::string> orig_tmp;

    _my = new s21::deque<std::string>(my_tmp);
    _orig = new std::deque<std::string>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(DequeTestString, TEST_12) {
    s21::deque<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::deque<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>(my_tmp);
    _orig = new std::deque<std::string>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(DequeTestString, TEST_13) {
    s21::deque<std::string> my_tmp;
    std::deque<std::string> orig_tmp;

    _my = new s21::deque<std::string>(std::move(my_tmp));
    _orig = new std::deque<std::string>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(DequeTestString, TEST_14) {
    s21::deque<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::deque<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>(std::move(my_tmp));
    _orig = new std::deque<std::string>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back("999");
    orig_tmp.push_back("999");

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};
    auto orig_it{orig_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(orig_it++));
    }
}

TEST_F(DequeTestString, TEST_15) {
    s21::deque<std::string> my_tmp;
    std::deque<std::string> orig_tmp;

    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(DequeTestString, TEST_16) {
    s21::deque<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::deque<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(DequeTestString, TEST_17) {
    s21::deque<std::string> my_tmp;
    std::deque<std::string> orig_tmp;

    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(DequeTestString, TEST_18) {
    s21::deque<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::deque<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back("999");
    orig_tmp.push_back("999");

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};
    auto orig_it{orig_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(orig_it++));
    }
}

TEST_F(DequeTestString, TEST_19) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    *_my = {};
    *_orig = {};
}

TEST_F(DequeTestString, TEST_20) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    *_my = {"1", "2", "3", "4", "5"};
    *_orig = {"1", "2", "3", "4", "5"};
}

TEST_F(DequeTestString, TEST_21) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    *_my = {"1", "2", "3", "4", "5"};
    *_orig = {"1", "2", "3", "4", "5"};

    _my->clear();
    _orig->clear();
}

TEST_F(DequeTestString, TEST_22) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_23) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->begin() + 1, std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin() + 1, std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_24) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_25) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_26) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_27) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_28) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_29) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(_my->begin() + 1, num)};
    auto orig_it{_orig->insert(_orig->begin() + 1, num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->begin() + 1, std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin() + 1, std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_30) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(_my->begin(), num)};
    auto orig_it{_orig->insert(_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_31) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_32) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(_my->end(), num)};
    auto orig_it{_orig->insert(_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_33) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(_my->end() - 1, num)};
    auto orig_it{_orig->insert(_orig->end() - 1, num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(_my->end() - 1, std::move(num_move_my));
    orig_it = _orig->insert(_orig->end() - 1, std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(DequeTestString, TEST_34) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(_my->end() - 1)};
    auto orig_it{_orig->erase(_orig->end() - 1)};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
    EXPECT_EQ(*(--my_it), *(--orig_it));

    my_it = _my->erase(_my->begin());
    orig_it = _orig->erase(_orig->begin());

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(*(++my_it), *(++orig_it));

    my_it = _my->erase(_my->begin() + 1);
    orig_it = _orig->erase(_orig->begin() + 1);

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(*(--my_it), *(--orig_it));
    EXPECT_EQ(*(++my_it), *(++orig_it));
}

TEST_F(DequeTestString, TEST_35) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(_my->begin() + 1, _my->end() - 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->end() - 1)};

    EXPECT_EQ(my_it, _my->end() - 1);
    EXPECT_EQ(orig_it, _orig->end() - 1);
    EXPECT_EQ(*(--my_it), *(--orig_it));
}

TEST_F(DequeTestString, TEST_36) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(_my->begin(), _my->end())};
    auto orig_it{_orig->erase(_orig->begin(), _orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
}

TEST_F(DequeTestString, TEST_37) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(_my->begin() + 1, _my->begin() + 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->begin() + 1)};

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(my_it, _my->begin() + 1);
    EXPECT_EQ(orig_it, _orig->begin() + 1);
}

TEST_F(DequeTestString, TEST_38) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    std::string str{"123"};

    _my->push_back(str);
    _orig->push_back(str);

    EXPECT_EQ(*_my->begin(), str);
    EXPECT_EQ(*_orig->begin(), str);
    EXPECT_EQ(_my->begin(), _my->end() - 1);
    EXPECT_EQ(_orig->begin(), (_orig->end() - 1));
}

TEST_F(DequeTestString, TEST_39) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    std::string str_1{"123"};
    std::string str_2{"123"};

    _my->push_back(std::move(str_1));
    _orig->push_back(std::move(str_2));;

    EXPECT_NE(*_my->begin(), str_1);
    EXPECT_NE(*_orig->begin(), str_2);
    EXPECT_EQ(_my->begin(), (_my->end() - 1));
    EXPECT_EQ(_orig->begin(), (_orig->end() - 1));
}

TEST_F(DequeTestString, TEST_40) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    _my->push_back("123");
    _orig->push_back("123");

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
}

TEST_F(DequeTestString, TEST_41) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    _my->pop_back();
    _orig->pop_back();

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
}

TEST_F(DequeTestString, TEST_42) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    _my->clear();
    _orig->clear();
}

TEST_F(DequeTestString, TEST_43) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    auto it_1{_my->erase(_my->begin())};
    auto it_2{_orig->erase(_orig->begin())};

    EXPECT_EQ(*it_1, *it_2);
    EXPECT_EQ(*(it_1 + 1), *(it_2 + 1));
}

TEST_F(DequeTestString, TEST_44) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    auto it_1{_my->erase(_my->begin() + 1)};
    auto it_2{_orig->erase(_orig->begin() + 1)};

    EXPECT_EQ(*it_1, *it_2);

    it_1 = _my->erase(_my->end() - 2);
    it_2 = _orig->erase(_orig->end() - 2);

    EXPECT_EQ(*it_1, *it_2);
}

TEST_F(DequeTestString, TEST_45) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    auto it_1{_my->erase(_my->begin() + 1, _my->end() - 1)};
    auto it_2{_orig->erase(_orig->begin() + 1, _orig->end() - 1)};

    EXPECT_EQ(*it_1, *it_2);
}

TEST_F(DequeTestString, TEST_46) {
    _my = new s21::deque<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::deque<std::string>({"1", "2", "3", "4", "5"});

    _my->erase(_my->begin(), _my->end());
    _orig->erase(_orig->begin(), _orig->end());
}

TEST_F(DequeTestString, TEST_47) {
    std::list<std::string> list({"1", "2", "3", "4", "5"});

    _my = new s21::deque<std::string>(list.begin(), list.end());
    _orig = new std::deque<std::string>(list.begin(), list.end());
}

TEST_F(DequeTestString, TEST_48) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    for (int i{}; i < 2000; ++i) {
        _my->push_back(std::to_string(i));
        _orig->push_back(std::to_string(i));
    }

    for (int i{}; i < 2000; ++i) {
        _my->pop_back();
        _orig->pop_back();
    }

    for (int i{}; i < 2000; ++i) {
        _my->push_front(std::to_string(i));
        _orig->push_front(std::to_string(i));
    }

    for (int i{}; i < 2000; ++i) {
        _my->pop_front();
        _orig->pop_front();
    }
}

TEST_F(DequeTestString, TEST_49) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    for (int i{}; i < 2000; ++i) {
        _my->push_back(std::to_string(i));
        _orig->push_back(std::to_string(i));
    }

    for (int i{}; i < 2000; ++i) {
        _my->push_front(std::to_string(i));
        _orig->push_front(std::to_string(i));
    }

    for (int i{}; i < 2000; ++i) {
        _my->pop_back();
        _orig->pop_back();
    }

    for (int i{}; i < 2000; ++i) {
        _my->pop_front();
        _orig->pop_front();
    }
}

TEST_F(DequeTestString, TEST_50) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    for (int i{}; i < 2000; ++i) {
        _my->push_back(std::to_string(i));
        _orig->push_back(std::to_string(i));
    }

    for (int i{}; i < 2000; ++i) {
        _my->push_front(std::to_string(i));
        _orig->push_front(std::to_string(i));
    }

    for (int i{}; i < 4000; ++i) {
        _my->pop_back();
        _orig->pop_back();
    }
}

TEST_F(DequeTestString, TEST_51) {
    _my = new s21::deque<std::string>();
    _orig = new std::deque<std::string>();

    for (int i{}; i < 2000; ++i) {
        _my->push_back(std::to_string(i));
        _orig->push_back(std::to_string(i));
    }

    for (int i{}; i < 2000; ++i) {
        _my->push_front(std::to_string(i));
        _orig->push_front(std::to_string(i));
    }

    for (int i{}; i < 4000; ++i) {
        _my->pop_front();
        _orig->pop_front();
    }
}

/*
     ----------------------------------------------------------
    |                                                          |
    |                                                          |
    |                 NON-COPYABLE TYPE TESTS                  |
    |                                                          |
    |                                                          |
     ----------------------------------------------------------
*/

void DequeTestUniquePtr::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->size(), _orig->size());
        EXPECT_EQ(_my->empty(), _orig->empty());

        if (_my->empty() && _orig->empty()) {
            EXPECT_EQ(_my->begin(), _my->end());
        }
    }

    delete _my;
    delete _orig;

    _my = nullptr;
    _orig = nullptr;
}

TEST_F(DequeTestUniquePtr, TEST_0) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();
}

TEST_F(DequeTestUniquePtr, TEST_1) {
    _my = new s21::deque<std::unique_ptr<std::string>>(9);
    _orig = new std::deque<std::unique_ptr<std::string>>(9);
}

TEST_F(DequeTestUniquePtr, TEST_2) {
    s21::deque<std::unique_ptr<std::string>> my_tmp;
    std::deque<std::unique_ptr<std::string>> orig_tmp;

    _my = new s21::deque<std::unique_ptr<std::string>>(std::move(my_tmp));
    _orig = new std::deque<std::unique_ptr<std::string>>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(DequeTestUniquePtr, TEST_3) {
    s21::deque<std::unique_ptr<std::string>> my_tmp;
    std::deque<std::unique_ptr<std::string>> orig_tmp;

    my_tmp.push_back(std::make_unique<std::string>("123"));
    orig_tmp.push_back(std::make_unique<std::string>("123"));

    _my = new s21::deque<std::unique_ptr<std::string>>(std::move(my_tmp));
    _orig = new std::deque<std::unique_ptr<std::string>>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back(std::make_unique<std::string>());
    orig_tmp.push_back(std::make_unique<std::string>());

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    EXPECT_EQ(*(*_my->begin()), *(*_orig->begin()));
    EXPECT_EQ(*(*my_tmp.begin()), *(*orig_tmp.begin()));
}

TEST_F(DequeTestUniquePtr, TEST_4) {
    s21::deque<std::unique_ptr<std::string>> my_tmp;
    std::deque<std::unique_ptr<std::string>> orig_tmp;

    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    for (int i{}; i < 10; ++i) {
        my_tmp.push_back(std::make_unique<std::string>(std::to_string(i)));
        orig_tmp.push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    for (std::size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(*(my_tmp.begin() + i)), *(*(orig_tmp.begin() + i)));
    }
}

TEST_F(DequeTestUniquePtr, TEST_5) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    _my->clear();
    _orig->clear();
}

TEST_F(DequeTestUniquePtr, TEST_6) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    auto val_move_my{std::make_unique<std::string>("321")};
    auto val_move_orig{std::make_unique<std::string>("321")};

    auto my_it{_my->insert(_my->begin(), std::move(val_move_my))};
    auto orig_it{_orig->insert(_orig->begin(), std::move(val_move_orig))};

    EXPECT_EQ(*(*my_it), *(*orig_it));
}

TEST_F(DequeTestUniquePtr, TEST_7) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    _my->push_back(std::make_unique<std::string>("123"));
    _orig->push_back(std::make_unique<std::string>("123"));

    auto val_move_my{std::make_unique<std::string>("321")};
    auto val_move_orig{std::make_unique<std::string>("321")};

    auto my_it{_my->insert(++_my->begin(), std::move(val_move_my))};
    auto orig_it{_orig->insert(++_orig->begin(), std::move(val_move_orig))};

    EXPECT_EQ(*(*my_it), *(*orig_it));
}

TEST_F(DequeTestUniquePtr, TEST_8) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    auto val_move_my{std::make_unique<std::string>("321")};
    auto val_move_orig{std::make_unique<std::string>("321")};

    auto my_it{_my->insert(_my->end(), std::move(val_move_my))};
    auto orig_it{_orig->insert(_orig->end(), std::move(val_move_orig))};

    EXPECT_EQ(*(*my_it), *(*orig_it));
}

TEST_F(DequeTestUniquePtr, TEST_9) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    auto my_it{_my->erase(_my->end() - 1)};
    auto orig_it{_orig->erase(_orig->end() - 1)};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
    EXPECT_EQ(*(*(--my_it)), *(*(--orig_it)));

    my_it = _my->erase(_my->begin());
    orig_it = _orig->erase(_orig->begin());

    EXPECT_EQ(*(*(my_it)), *(*(orig_it)));
    EXPECT_EQ(*(*(++my_it)), *(*(++orig_it)));

    my_it = _my->erase(_my->begin() + 1);
    orig_it = _orig->erase(_orig->begin() + 1);

    EXPECT_EQ(*(*(my_it)), *(*(orig_it)));
    EXPECT_EQ(*(*(--my_it)), *(*(--orig_it)));
    EXPECT_EQ(*(*(++my_it)), *(*(++orig_it)));
}

TEST_F(DequeTestUniquePtr, TEST_10) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    auto my_it{_my->erase(_my->begin() + 1, _my->end() - 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->end() - 1)};

    EXPECT_EQ(my_it, _my->end() - 1);
    EXPECT_EQ(orig_it, _orig->end() - 1);
    EXPECT_EQ(*(*(--my_it)), *(*(--orig_it)));
}

TEST_F(DequeTestUniquePtr, TEST_11) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    auto my_it{_my->erase(_my->begin(), _my->end())};
    auto orig_it{_orig->erase(_orig->begin(), _orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
}

TEST_F(DequeTestUniquePtr, TEST_12) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    auto my_it{_my->erase(_my->begin() + 1, _my->begin() + 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->begin() + 1)};

    EXPECT_EQ(*(*(my_it)), *(*(orig_it)));
    EXPECT_EQ(my_it, _my->begin() + 1);
    EXPECT_EQ(orig_it, _orig->begin() + 1);
}

TEST_F(DequeTestUniquePtr, TEST_13) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    _my->push_back(std::make_unique<std::string>("123"));
    _orig->push_back(std::make_unique<std::string>("123"));

    EXPECT_EQ(_my->begin(), _my->end() - 1);
    EXPECT_EQ(_orig->begin(), _orig->end() - 1);
    EXPECT_EQ(**_my->begin(), **_orig->begin());
    EXPECT_EQ(**(_my->end() - 1), **(_orig->end() - 1));
}

TEST_F(DequeTestUniquePtr, TEST_14) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    _my->pop_back();
    _orig->pop_back();

    EXPECT_EQ(**_my->begin(), **_orig->begin());
    EXPECT_EQ(**(_my->end() - 1), **(_orig->end() - 1));
}

TEST_F(DequeTestUniquePtr, TEST_15) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    _my->clear();
    _orig->clear();
}

TEST_F(DequeTestUniquePtr, TEST_16) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    auto it_1{_my->erase(_my->begin())};
    auto it_2{_orig->erase(_orig->begin())};

    EXPECT_EQ(**it_1, **it_2);
    EXPECT_EQ(**(it_1 + 1), **(it_2 + 1));
}

TEST_F(DequeTestUniquePtr, TEST_17) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    auto it_1{_my->erase(_my->begin() + 1)};
    auto it_2{_orig->erase(_orig->begin() + 1)};

    EXPECT_EQ(**it_1, **it_2);

    it_1 = _my->erase(_my->end() - 2);
    it_2 = _orig->erase(_orig->end() - 2);

    EXPECT_EQ(**it_1, **it_2);
}

TEST_F(DequeTestUniquePtr, TEST_18) {
    _my = new s21::deque<std::unique_ptr<std::string>>();
    _orig = new std::deque<std::unique_ptr<std::string>>();

    _my->erase(_my->begin(), _my->end());
    _orig->erase(_orig->begin(), _orig->end());
}
