#include <vector>

#include "include/test_list.h"

/*
     ----------------------------------------------------------
    |                                                          |
    |                                                          |
    |                  FUNDAMENTAL TYPE TESTS                  |
    |                                                          |
    |                                                          |
     ----------------------------------------------------------
*/

void ListTestInt::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->size(), _orig->size());
        EXPECT_EQ(_my->empty(), _orig->empty());

        if (!_my->empty() && !_orig->empty()) {
            EXPECT_EQ(*_my->begin(), *_orig->begin());
            EXPECT_EQ(*(--_my->end()), *(--_orig->end()));
            EXPECT_EQ(_my->front(), _orig->front());
            EXPECT_EQ(_my->back(), _orig->back());

            *_my->begin() = 111;
            *_orig->begin() = 111;

            *(--_my->end()) = 222;
            *(--_orig->end()) = 222;

            auto my_it{_my->begin()};
            auto orig_it{_orig->begin()};

            for (std::size_t i{}; i < _orig->size(); ++i) {
                EXPECT_EQ(*(my_it++), *(orig_it++));
            }
        } else {
            EXPECT_EQ(_my->begin(), _my->end());
            EXPECT_EQ(++_my->begin(), _my->end());
            EXPECT_EQ(--_my->begin(), _my->end());
            EXPECT_EQ(++_my->end(), _my->begin());
            EXPECT_EQ(--_my->end(), _my->begin());
        }
    }

    delete _my;
    delete _orig;

    _my = nullptr;
    _orig = nullptr;
}

TEST_F(ListTestInt, TEST_1) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();
}

TEST_F(ListTestInt, TEST_2) {
    _my = new s21::list<int>(0, 9);
    _orig = new std::list<int>(0, 9);
}

TEST_F(ListTestInt, TEST_3) {
    _my = new s21::list<int>(5, 9);
    _orig = new std::list<int>(5, 9);
}

TEST_F(ListTestInt, TEST_4) {
    _my = new s21::list<int>({});
    _orig = new std::list<int>({});
}

TEST_F(ListTestInt, TEST_5) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});
}

TEST_F(ListTestInt, TEST_6) {
    s21::list<int> my_tmp;
    std::list<int> orig_tmp;

    _my = new s21::list<int>(++my_tmp.begin(), --my_tmp.end());
    _orig = new std::list<int>(++orig_tmp.begin(), --orig_tmp.end());
}

TEST_F(ListTestInt, TEST_7) {
    s21::list<int> my_tmp({1, 2, 3, 4, 5});
    std::list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>(++my_tmp.begin(), --my_tmp.end());
    _orig = new std::list<int>(++orig_tmp.begin(), --orig_tmp.end());
}

TEST_F(ListTestInt, TEST_8) {
    s21::list<int> my_tmp({1, 2, 3, 4, 5});
    std::list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>(++my_tmp.begin(), ++my_tmp.begin());
    _orig = new std::list<int>(++orig_tmp.begin(), ++orig_tmp.begin());
}

TEST_F(ListTestInt, TEST_9) {
    s21::list<int> my_tmp({1, 2, 3, 4, 5});
    std::list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>(my_tmp.end(), my_tmp.end());
    _orig = new std::list<int>(orig_tmp.end(), orig_tmp.end());
}

TEST_F(ListTestInt, TEST_10) {
    s21::list<int> my_tmp({1, 2, 3, 4, 5});
    std::list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>(++my_tmp.end(), my_tmp.end());
    _orig = new std::list<int>(++orig_tmp.end(), orig_tmp.end());
}

TEST_F(ListTestInt, TEST_11) {
    s21::list<int> my_tmp({1, 2, 3, 4, 5});
    std::list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>(++my_tmp.end(), --my_tmp.end());
    _orig = new std::list<int>(++orig_tmp.end(), --orig_tmp.end());
}

TEST_F(ListTestInt, TEST_12) {
    std::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>(my_tmp.begin(), my_tmp.end());
    _orig = new std::list<int>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ListTestInt, TEST_13) {
    std::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>(++my_tmp.begin(), --my_tmp.end());
    _orig = new std::list<int>(++orig_tmp.begin(), --orig_tmp.end());
}

TEST_F(ListTestInt, TEST_14) {
    s21::list<int> my_tmp;
    std::list<int> orig_tmp;

    _my = new s21::list<int>(my_tmp);
    _orig = new std::list<int>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ListTestInt, TEST_15) {
    s21::list<int> my_tmp({1, 2, 3, 4, 5});
    std::list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>(my_tmp);
    _orig = new std::list<int>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ListTestInt, TEST_16) {
    s21::list<int> my_tmp;
    std::list<int> orig_tmp;

    _my = new s21::list<int>(std::move(my_tmp));
    _orig = new std::list<int>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(ListTestInt, TEST_17) {
    s21::list<int> my_tmp({1, 2, 3, 4, 5});
    std::list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>(std::move(my_tmp));
    _orig = new std::list<int>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back(999);
    orig_tmp.push_back(999);

    my_tmp.push_front(777);
    orig_tmp.push_front(777);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};
    auto orig_it{orig_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(orig_it++));
    }
}

TEST_F(ListTestInt, TEST_18) {
    s21::list<int> my_tmp;
    std::list<int> orig_tmp;

    _my = new s21::list<int>();
    _orig = new std::list<int>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ListTestInt, TEST_19) {
    s21::list<int> my_tmp({1, 2, 3, 4, 5});
    std::list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>();
    _orig = new std::list<int>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ListTestInt, TEST_20) {
    s21::list<int> my_tmp;
    std::list<int> orig_tmp;

    _my = new s21::list<int>();
    _orig = new std::list<int>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(ListTestInt, TEST_21) {
    s21::list<int> my_tmp({1, 2, 3, 4, 5});
    std::list<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::list<int>();
    _orig = new std::list<int>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back(999);
    orig_tmp.push_back(999);

    my_tmp.push_front(777);
    orig_tmp.push_front(777);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};
    auto orig_it{orig_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(orig_it++));
    }
}

TEST_F(ListTestInt, TEST_22) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    *_my = {};
    *_orig = {};
}

TEST_F(ListTestInt, TEST_23) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    *_my = {1, 2, 3, 4, 5};
    *_orig = {1, 2, 3, 4, 5};
}

TEST_F(ListTestInt, TEST_24) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    *_my = {1, 2, 3, 4, 5};
    *_orig = {1, 2, 3, 4, 5};

    _my->clear();
    _orig->clear();
}

TEST_F(ListTestInt, TEST_25) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

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

TEST_F(ListTestInt, TEST_26) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    int num{123};

    auto my_it{_my->insert(++_my->begin(), num)};
    auto orig_it{_orig->insert(++_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(++_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(++_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(ListTestInt, TEST_27) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    int num{123};

    auto my_it{_my->insert(--_my->begin(), num)};
    auto orig_it{_orig->insert(--_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(--_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(--_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(ListTestInt, TEST_28) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

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

TEST_F(ListTestInt, TEST_29) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    int num{123};

    auto my_it{_my->insert(++_my->end(), num)};
    auto orig_it{_orig->insert(++_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(++_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(++_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(ListTestInt, TEST_30) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    int num{123};

    auto my_it{_my->insert(--_my->end(), num)};
    auto orig_it{_orig->insert(--_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(--_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(--_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(ListTestInt, TEST_31) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

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

TEST_F(ListTestInt, TEST_32) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(++_my->begin(), num)};
    auto orig_it{_orig->insert(++_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(++_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(++_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(ListTestInt, TEST_33) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(--_my->begin(), num)};
    auto orig_it{_orig->insert(--_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(--_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(--_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(ListTestInt, TEST_34) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

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

TEST_F(ListTestInt, TEST_35) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(++_my->end(), num)};
    auto orig_it{_orig->insert(++_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(++_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(++_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(ListTestInt, TEST_36) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(--_my->end(), num)};
    auto orig_it{_orig->insert(--_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    int num_move_my{321};
    int num_move_orig{321};

    my_it = _my->insert(--_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(--_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num_move_my);
}

TEST_F(ListTestInt, TEST_37) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(--_my->end())};
    auto orig_it{_orig->erase(--_orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
    EXPECT_EQ(*(--my_it), *(--orig_it));

    my_it = _my->erase(_my->begin());
    orig_it = _orig->erase(_orig->begin());

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(*(++my_it), *(++orig_it));

    my_it = _my->erase(++_my->begin());
    orig_it = _orig->erase(++_orig->begin());

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(*(--my_it), *(--orig_it));
    EXPECT_EQ(*(++my_it), *(++orig_it));
}

TEST_F(ListTestInt, TEST_38) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(++_my->begin(), --_my->end())};
    auto orig_it{_orig->erase(++_orig->begin(), --_orig->end())};

    EXPECT_EQ(my_it, --_my->end());
    EXPECT_EQ(orig_it, --_orig->end());
    EXPECT_EQ(*(--my_it), *(--orig_it));
}

TEST_F(ListTestInt, TEST_39) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(_my->begin(), _my->end())};
    auto orig_it{_orig->erase(_orig->begin(), _orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
}

TEST_F(ListTestInt, TEST_40) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(++_my->begin(), ++_my->begin())};
    auto orig_it{_orig->erase(++_orig->begin(), ++_orig->begin())};

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(my_it, ++_my->begin());
    EXPECT_EQ(orig_it, ++_orig->begin());
}

TEST_F(ListTestInt, TEST_41) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    int str{123};

    _my->push_front(str);
    _orig->push_front(str);

    EXPECT_EQ(*_my->begin(), str);
    EXPECT_EQ(*_orig->begin(), str);
    EXPECT_EQ(_my->begin(), --_my->end());
    EXPECT_EQ(_orig->begin(), (--_orig->end()));
}

TEST_F(ListTestInt, TEST_42) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    int str_1{123};
    int str_2{123};

    _my->push_front(std::move(str_1));
    _orig->push_front(std::move(str_2));

    EXPECT_EQ(*_my->begin(), str_1);
    EXPECT_EQ(*_orig->begin(), str_2);
    EXPECT_EQ(_my->begin(), (--_my->end()));
    EXPECT_EQ(_orig->begin(), (--_orig->end()));
}

TEST_F(ListTestInt, TEST_43) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    int str{123};

    _my->push_back(str);
    _orig->push_back(str);

    EXPECT_EQ(*_my->begin(), str);
    EXPECT_EQ(*_orig->begin(), str);
    EXPECT_EQ(_my->begin(), --_my->end());
    EXPECT_EQ(_orig->begin(), (--_orig->end()));
}

TEST_F(ListTestInt, TEST_44) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    int str_1{123};
    int str_2{123};

    _my->push_back(std::move(str_1));
    _orig->push_back(std::move(str_2));;

    EXPECT_EQ(*_my->begin(), str_1);
    EXPECT_EQ(*_orig->begin(), str_2);
    EXPECT_EQ(_my->begin(), (--_my->end()));
    EXPECT_EQ(_orig->begin(), (--_orig->end()));
}

TEST_F(ListTestInt, TEST_45) {
    _my = new s21::list<int>();
    _orig = new std::list<int>();

    _my->push_back(123);
    _my->push_front(321);

    _orig->push_back(123);
    _orig->push_front(321);

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(--_my->end()), *(--_orig->end()));
}

TEST_F(ListTestInt, TEST_46) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    _my->pop_back();
    _orig->pop_back();

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(--_my->end()), *(--_orig->end()));
}

TEST_F(ListTestInt, TEST_47) {
    _my = new s21::list<int>({1, 2, 3, 4, 5});
    _orig = new std::list<int>({1, 2, 3, 4, 5});

    _my->pop_front();
    _orig->pop_front();

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(--_my->end()), *(--_orig->end()));
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

void ListTestString::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->size(), _orig->size());
        EXPECT_EQ(_my->empty(), _orig->empty());

        if (!_my->empty() && !_orig->empty()) {
            EXPECT_EQ(*_my->begin(), *_orig->begin());
            EXPECT_EQ(*(--_my->end()), *(--_orig->end()));
            EXPECT_EQ(_my->front(), _orig->front());
            EXPECT_EQ(_my->back(), _orig->back());

            *_my->begin() = "111";
            *_orig->begin() = "111";

            *(--_my->end()) = "222";
            *(--_orig->end()) = "222";

            auto my_it{_my->begin()};
            auto orig_it{_orig->begin()};

            for (std::size_t i{}; i < _orig->size(); ++i) {
                EXPECT_EQ(*(my_it++), *(orig_it++));
            }
        } else {
            EXPECT_EQ(_my->begin(), _my->end());
            EXPECT_EQ(++_my->begin(), _my->end());
            EXPECT_EQ(--_my->begin(), _my->end());
            EXPECT_EQ(++_my->end(), _my->begin());
            EXPECT_EQ(--_my->end(), _my->begin());
        }
    }

    delete _my;
    delete _orig;

    _my = nullptr;
    _orig = nullptr;
}

TEST_F(ListTestString, TEST_1) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();
}

TEST_F(ListTestString, TEST_2) {
    _my = new s21::list<std::string>(0, "9");
    _orig = new std::list<std::string>(0, "9");
}

TEST_F(ListTestString, TEST_3) {
    _my = new s21::list<std::string>(5, "9");
    _orig = new std::list<std::string>(5, "9");
}

TEST_F(ListTestString, TEST_4) {
    _my = new s21::list<std::string>({});
    _orig = new std::list<std::string>({});
}

TEST_F(ListTestString, TEST_5) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});
}

TEST_F(ListTestString, TEST_6) {
    s21::list<std::string> my_tmp;
    std::list<std::string> orig_tmp;

    _my = new s21::list<std::string>(++my_tmp.begin(), --my_tmp.end());
    _orig = new std::list<std::string>(++orig_tmp.begin(), --orig_tmp.end());
}

TEST_F(ListTestString, TEST_7) {
    s21::list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>(++my_tmp.begin(), --my_tmp.end());
    _orig = new std::list<std::string>(++orig_tmp.begin(), --orig_tmp.end());
}

TEST_F(ListTestString, TEST_8) {
    s21::list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>(++my_tmp.begin(), ++my_tmp.begin());
    _orig = new std::list<std::string>(++orig_tmp.begin(), ++orig_tmp.begin());
}

TEST_F(ListTestString, TEST_9) {
    s21::list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>(my_tmp.end(), my_tmp.end());
    _orig = new std::list<std::string>(orig_tmp.end(), orig_tmp.end());
}

TEST_F(ListTestString, TEST_10) {
    s21::list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>(++my_tmp.end(), my_tmp.end());
    _orig = new std::list<std::string>(++orig_tmp.end(), orig_tmp.end());
}

TEST_F(ListTestString, TEST_11) {
    s21::list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>(++my_tmp.end(), --my_tmp.end());
    _orig = new std::list<std::string>(++orig_tmp.end(), --orig_tmp.end());
}

TEST_F(ListTestString, TEST_12) {
    std::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>(my_tmp.begin(), my_tmp.end());
    _orig = new std::list<std::string>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(ListTestString, TEST_13) {
    std::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>(++my_tmp.begin(), --my_tmp.end());
    _orig = new std::list<std::string>(++orig_tmp.begin(), --orig_tmp.end());
}

TEST_F(ListTestString, TEST_14) {
    s21::list<std::string> my_tmp;
    std::list<std::string> orig_tmp;

    _my = new s21::list<std::string>(my_tmp);
    _orig = new std::list<std::string>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ListTestString, TEST_15) {
    s21::list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>(my_tmp);
    _orig = new std::list<std::string>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ListTestString, TEST_16) {
    s21::list<std::string> my_tmp;
    std::list<std::string> orig_tmp;

    _my = new s21::list<std::string>(std::move(my_tmp));
    _orig = new std::list<std::string>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(ListTestString, TEST_17) {
    s21::list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>(std::move(my_tmp));
    _orig = new std::list<std::string>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back("999");
    orig_tmp.push_back("999");

    my_tmp.push_front("777");
    orig_tmp.push_front("777");

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};
    auto orig_it{orig_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(orig_it++));
    }
}

TEST_F(ListTestString, TEST_18) {
    s21::list<std::string> my_tmp;
    std::list<std::string> orig_tmp;

    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ListTestString, TEST_19) {
    s21::list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(ListTestString, TEST_20) {
    s21::list<std::string> my_tmp;
    std::list<std::string> orig_tmp;

    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(ListTestString, TEST_21) {
    s21::list<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::list<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back("999");
    orig_tmp.push_back("999");

    my_tmp.push_front("777");
    orig_tmp.push_front("777");

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    auto my_it{my_tmp.begin()};
    auto orig_it{orig_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(orig_it++));
    }
}

TEST_F(ListTestString, TEST_22) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    *_my = {};
    *_orig = {};
}

TEST_F(ListTestString, TEST_23) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    *_my = {"1", "2", "3", "4", "5"};
    *_orig = {"1", "2", "3", "4", "5"};
}

TEST_F(ListTestString, TEST_24) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    _my->clear();
    _orig->clear();
}

TEST_F(ListTestString, TEST_25) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

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

TEST_F(ListTestString, TEST_26) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(++_my->begin(), num)};
    auto orig_it{_orig->insert(++_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(++_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(++_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(ListTestString, TEST_27) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(--_my->begin(), num)};
    auto orig_it{_orig->insert(--_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(--_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(--_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(ListTestString, TEST_28) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

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

TEST_F(ListTestString, TEST_29) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(++_my->end(), num)};
    auto orig_it{_orig->insert(++_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(++_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(++_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(ListTestString, TEST_30) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    std::string num{"123"};

    auto my_it{_my->insert(--_my->end(), num)};
    auto orig_it{_orig->insert(--_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(--_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(--_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(ListTestString, TEST_31) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

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

TEST_F(ListTestString, TEST_32) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(++_my->begin(), num)};
    auto orig_it{_orig->insert(++_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(++_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(++_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(ListTestString, TEST_33) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(--_my->begin(), num)};
    auto orig_it{_orig->insert(--_orig->begin(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(--_my->begin(), std::move(num_move_my));
    orig_it = _orig->insert(--_orig->begin(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(ListTestString, TEST_34) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

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

TEST_F(ListTestString, TEST_35) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(++_my->end(), num)};
    auto orig_it{_orig->insert(++_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(++_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(++_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(ListTestString, TEST_36) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(--_my->end(), num)};
    auto orig_it{_orig->insert(--_orig->end(), num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    std::string num_move_my{"321"};
    std::string num_move_orig{"321"};

    my_it = _my->insert(--_my->end(), std::move(num_move_my));
    orig_it = _orig->insert(--_orig->end(), std::move(num_move_orig));

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_NE(*my_it, num_move_my);
}

TEST_F(ListTestString, TEST_37) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(--_my->end())};
    auto orig_it{_orig->erase(--_orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
    EXPECT_EQ(*(--my_it), *(--orig_it));

    my_it = _my->erase(_my->begin());
    orig_it = _orig->erase(_orig->begin());

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(*(++my_it), *(++orig_it));

    my_it = _my->erase(++_my->begin());
    orig_it = _orig->erase(++_orig->begin());

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(*(--my_it), *(--orig_it));
    EXPECT_EQ(*(++my_it), *(++orig_it));
}

TEST_F(ListTestString, TEST_38) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(++_my->begin(), --_my->end())};
    auto orig_it{_orig->erase(++_orig->begin(), --_orig->end())};

    EXPECT_EQ(my_it, --_my->end());
    EXPECT_EQ(orig_it, --_orig->end());
    EXPECT_EQ(*(--my_it), *(--orig_it));
}

TEST_F(ListTestString, TEST_39) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(_my->begin(), _my->end())};
    auto orig_it{_orig->erase(_orig->begin(), _orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
}

TEST_F(ListTestString, TEST_40) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(++_my->begin(), ++_my->begin())};
    auto orig_it{_orig->erase(++_orig->begin(), ++_orig->begin())};

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(my_it, ++_my->begin());
    EXPECT_EQ(orig_it, ++_orig->begin());
}

TEST_F(ListTestString, TEST_41) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    std::string str{"123"};

    _my->push_front(str);
    _orig->push_front(str);

    EXPECT_EQ(*_my->begin(), str);
    EXPECT_EQ(*_orig->begin(), str);
    EXPECT_EQ(_my->begin(), --_my->end());
    EXPECT_EQ(_orig->begin(), (--_orig->end()));
}

TEST_F(ListTestString, TEST_42) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    std::string str_1{"123"};
    std::string str_2{"123"};

    _my->push_front(std::move(str_1));
    _orig->push_front(std::move(str_2));

    EXPECT_NE(*_my->begin(), str_1);
    EXPECT_NE(*_orig->begin(), str_2);
    EXPECT_EQ(_my->begin(), (--_my->end()));
    EXPECT_EQ(_orig->begin(), (--_orig->end()));
}

TEST_F(ListTestString, TEST_43) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    std::string str{"123"};

    _my->push_back(str);
    _orig->push_back(str);

    EXPECT_EQ(*_my->begin(), str);
    EXPECT_EQ(*_orig->begin(), str);
    EXPECT_EQ(_my->begin(), --_my->end());
    EXPECT_EQ(_orig->begin(), (--_orig->end()));
}

TEST_F(ListTestString, TEST_44) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    std::string str_1{"123"};
    std::string str_2{"123"};

    _my->push_back(std::move(str_1));
    _orig->push_back(std::move(str_2));;

    EXPECT_NE(*_my->begin(), str_1);
    EXPECT_NE(*_orig->begin(), str_2);
    EXPECT_EQ(_my->begin(), (--_my->end()));
    EXPECT_EQ(_orig->begin(), (--_orig->end()));
}

TEST_F(ListTestString, TEST_45) {
    _my = new s21::list<std::string>();
    _orig = new std::list<std::string>();

    _my->push_back("123");
    _my->push_front("321");

    _orig->push_back("123");
    _orig->push_front("321");

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(--_my->end()), *(--_orig->end()));
}

TEST_F(ListTestString, TEST_46) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    _my->pop_back();
    _orig->pop_back();

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(--_my->end()), *(--_orig->end()));
}

TEST_F(ListTestString, TEST_47) {
    _my = new s21::list<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::list<std::string>({"1", "2", "3", "4", "5"});

    _my->pop_front();
    _orig->pop_front();

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(--_my->end()), *(--_orig->end()));
}
