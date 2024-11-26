#include <list>

#include "include/test_vector.h"

/*
     ----------------------------------------------------------
    |                                                          |
    |                                                          |
    |                  FUNDAMENTAL TYPE TESTS                  |
    |                                                          |
    |                                                          |
     ----------------------------------------------------------
*/

void VectorTestInt::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->size(), _orig->size());
        EXPECT_EQ(_my->empty(), _orig->empty());
        EXPECT_EQ(_my->capacity(), _orig->capacity());

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

TEST_F(VectorTestInt, TEST_0) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();
}

TEST_F(VectorTestInt, TEST_1) {
    _my = new s21::vector<int>(9);
    _orig = new std::vector<int>(9);
}

TEST_F(VectorTestInt, TEST_2) {
    _my = new s21::vector<int>(0, 9);
    _orig = new std::vector<int>(0, 9);
}

TEST_F(VectorTestInt, TEST_3) {
    _my = new s21::vector<int>(5, 9);
    _orig = new std::vector<int>(5, 9);
}

TEST_F(VectorTestInt, TEST_4) {
    _my = new s21::vector<int>({});
    _orig = new std::vector<int>({});
}

TEST_F(VectorTestInt, TEST_5) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});
}

TEST_F(VectorTestInt, TEST_6) {
    s21::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::vector<int>(my_tmp.begin() + 1, my_tmp.end() - 1);
    _orig = new std::vector<int>(orig_tmp.begin() + 1, orig_tmp.end() - 1);
}

TEST_F(VectorTestInt, TEST_7) {
    s21::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::vector<int>(my_tmp.begin() + 1, my_tmp.begin() + 1);
    _orig = new std::vector<int>(orig_tmp.begin() + 1, orig_tmp.begin() + 1);
}

TEST_F(VectorTestInt, TEST_8) {
    s21::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::vector<int>(my_tmp.end(), my_tmp.end());
    _orig = new std::vector<int>(orig_tmp.end(), orig_tmp.end());
}

TEST_F(VectorTestInt, TEST_9) {
    s21::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::vector<int>(my_tmp.begin() + 1, my_tmp.end());
    _orig = new std::vector<int>(orig_tmp.begin() + 1, orig_tmp.end());
}

TEST_F(VectorTestInt, TEST_10) {
    std::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::vector<int>(my_tmp.begin(), my_tmp.end());
    _orig = new std::vector<int>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(VectorTestInt, TEST_11) {
    s21::vector<int> my_tmp;
    std::vector<int> orig_tmp;

    _my = new s21::vector<int>(my_tmp);
    _orig = new std::vector<int>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(VectorTestInt, TEST_12) {
    s21::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::vector<int>(my_tmp);
    _orig = new std::vector<int>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(VectorTestInt, TEST_13) {
    s21::vector<int> my_tmp;
    std::vector<int> orig_tmp;

    _my = new s21::vector<int>(std::move(my_tmp));
    _orig = new std::vector<int>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(VectorTestInt, TEST_14) {
    s21::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::vector<int>(std::move(my_tmp));
    _orig = new std::vector<int>(std::move(orig_tmp));

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

TEST_F(VectorTestInt, TEST_15) {
    s21::vector<int> my_tmp;
    std::vector<int> orig_tmp;

    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(VectorTestInt, TEST_16) {
    s21::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(VectorTestInt, TEST_17) {
    s21::vector<int> my_tmp;
    std::vector<int> orig_tmp;

    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(VectorTestInt, TEST_18) {
    s21::vector<int> my_tmp({1, 2, 3, 4, 5});
    std::vector<int> orig_tmp({1, 2, 3, 4, 5});

    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

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

TEST_F(VectorTestInt, TEST_19) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    *_my = {};
    *_orig = {};
}

TEST_F(VectorTestInt, TEST_20) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    *_my = {1, 2, 3, 4, 5};
    *_orig = {1, 2, 3, 4, 5};
}

TEST_F(VectorTestInt, TEST_21) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    *_my = {1, 2, 3, 4, 5};
    *_orig = {1, 2, 3, 4, 5};

    _my->clear();
    _orig->clear();
}

TEST_F(VectorTestInt, TEST_22) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

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

TEST_F(VectorTestInt, TEST_23) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

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

TEST_F(VectorTestInt, TEST_24) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

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

TEST_F(VectorTestInt, TEST_25) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

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

TEST_F(VectorTestInt, TEST_26) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

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

TEST_F(VectorTestInt, TEST_27) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

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

TEST_F(VectorTestInt, TEST_28) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

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

TEST_F(VectorTestInt, TEST_29) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

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

TEST_F(VectorTestInt, TEST_30) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

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

TEST_F(VectorTestInt, TEST_31) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

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

TEST_F(VectorTestInt, TEST_32) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

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

TEST_F(VectorTestInt, TEST_33) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

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

TEST_F(VectorTestInt, TEST_34) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

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

TEST_F(VectorTestInt, TEST_35) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(_my->begin() + 1, _my->end() - 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->end() - 1)};

    EXPECT_EQ(my_it, _my->end() - 1);
    EXPECT_EQ(orig_it, _orig->end() - 1);
    EXPECT_EQ(*(--my_it), *(--orig_it));
}

TEST_F(VectorTestInt, TEST_36) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(_my->begin(), _my->end())};
    auto orig_it{_orig->erase(_orig->begin(), _orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
}

TEST_F(VectorTestInt, TEST_37) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    auto my_it{_my->erase(_my->begin() + 1, _my->begin() + 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->begin() + 1)};

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(my_it, _my->begin() + 1);
    EXPECT_EQ(orig_it, _orig->begin() + 1);
}

TEST_F(VectorTestInt, TEST_38) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    int str{123};

    _my->push_back(str);
    _orig->push_back(str);

    EXPECT_EQ(*_my->begin(), str);
    EXPECT_EQ(*_orig->begin(), str);
    EXPECT_EQ(_my->begin(), _my->end() - 1);
    EXPECT_EQ(_orig->begin(), (_orig->end() - 1));
}

TEST_F(VectorTestInt, TEST_39) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    int str_1{123};
    int str_2{123};

    _my->push_back(std::move(str_1));
    _orig->push_back(std::move(str_2));;

    EXPECT_EQ(*_my->begin(), str_1);
    EXPECT_EQ(*_orig->begin(), str_2);
    EXPECT_EQ(_my->begin(), (_my->end() - 1));
    EXPECT_EQ(_orig->begin(), (_orig->end() - 1));
}

TEST_F(VectorTestInt, TEST_40) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    _my->push_back(123);
    _orig->push_back(123);

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
}

TEST_F(VectorTestInt, TEST_41) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    _my->pop_back();
    _orig->pop_back();

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
}

TEST_F(VectorTestInt, TEST_42) {
    _my = new s21::vector<int>();
    _orig = new std::vector<int>();

    _my->reserve(100);
    _orig->reserve(100);
}

TEST_F(VectorTestInt, TEST_43) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    _my->reserve(100);
    _orig->reserve(100);

    _my->shrink_to_fit();
    _orig->shrink_to_fit();
}

TEST_F(VectorTestInt, TEST_44) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    _my->clear();
    _orig->clear();
}

TEST_F(VectorTestInt, TEST_45) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    auto it_1{_my->erase(_my->begin())};
    auto it_2{_orig->erase(_orig->begin())};

    EXPECT_EQ(*it_1, *it_2);
    EXPECT_EQ(*(it_1 + 1), *(it_2 + 1));
}

TEST_F(VectorTestInt, TEST_46) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    auto it_1{_my->erase(_my->begin() + 1)};
    auto it_2{_orig->erase(_orig->begin() + 1)};

    EXPECT_EQ(*it_1, *it_2);

    it_1 = _my->erase(_my->end() - 2);
    it_2 = _orig->erase(_orig->end() - 2);

    EXPECT_EQ(*it_1, *it_2);
}

TEST_F(VectorTestInt, TEST_47) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    auto it_1{_my->erase(_my->begin() + 1, _my->end() - 1)};
    auto it_2{_orig->erase(_orig->begin() + 1, _orig->end() - 1)};

    EXPECT_EQ(*it_1, *it_2);
}

TEST_F(VectorTestInt, TEST_48) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    _my->erase(_my->begin(), _my->end());
    _orig->erase(_orig->begin(), _orig->end());
}

TEST_F(VectorTestInt, TEST_49) {
    _my = new s21::vector<int>({1, 2, 3, 4, 5});
    _orig = new std::vector<int>({1, 2, 3, 4, 5});

    int num{123};

    auto my_it{_my->insert(_my->end() - 1, 7, num)};
    auto orig_it{_orig->insert(_orig->end() - 1, 7, num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    my_it = _my->insert(_my->end() - 1, {1, 2, 3, 4, 5});
    orig_it = _orig->insert(_orig->end() - 1, {1, 2, 3, 4, 5});

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(VectorTestInt, TEST_50) {
    std::list<int> list({1, 2, 3, 4, 5});

    _my = new s21::vector<int>(list.begin(), list.end());
    _orig = new std::vector<int>(list.begin(), list.end());
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

void VectorTestString::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->size(), _orig->size());
        EXPECT_EQ(_my->empty(), _orig->empty());
        EXPECT_EQ(_my->capacity(), _orig->capacity());

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

TEST_F(VectorTestString, TEST_0) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();
}

TEST_F(VectorTestString, TEST_1) {
    _my = new s21::vector<std::string>(9);
    _orig = new std::vector<std::string>(9);
}

TEST_F(VectorTestString, TEST_2) {
    _my = new s21::vector<std::string>(0, "9");
    _orig = new std::vector<std::string>(0, "9");
}

TEST_F(VectorTestString, TEST_3) {
    _my = new s21::vector<std::string>(5, "9");
    _orig = new std::vector<std::string>(5, "9");
}

TEST_F(VectorTestString, TEST_4) {
    _my = new s21::vector<std::string>({});
    _orig = new std::vector<std::string>({});
}

TEST_F(VectorTestString, TEST_5) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});
}

TEST_F(VectorTestString, TEST_6) {
    s21::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>(my_tmp.begin() + 1, my_tmp.end() - 1);
    _orig = new std::vector<std::string>(orig_tmp.begin() + 1, orig_tmp.end() - 1);
}

TEST_F(VectorTestString, TEST_7) {
    s21::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>(my_tmp.begin() + 1, my_tmp.begin() + 1);
    _orig = new std::vector<std::string>(orig_tmp.begin() + 1, orig_tmp.begin() + 1);
}

TEST_F(VectorTestString, TEST_8) {
    s21::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>(my_tmp.end(), my_tmp.end());
    _orig = new std::vector<std::string>(orig_tmp.end(), orig_tmp.end());
}

TEST_F(VectorTestString, TEST_9) {
    s21::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>(my_tmp.begin() + 1, my_tmp.end());
    _orig = new std::vector<std::string>(orig_tmp.begin() + 1, orig_tmp.end());
}

TEST_F(VectorTestString, TEST_10) {
    std::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>(my_tmp.begin(), my_tmp.end());
    _orig = new std::vector<std::string>(orig_tmp.begin(), orig_tmp.end());
}

TEST_F(VectorTestString, TEST_11) {
    s21::vector<std::string> my_tmp;
    std::vector<std::string> orig_tmp;

    _my = new s21::vector<std::string>(my_tmp);
    _orig = new std::vector<std::string>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(VectorTestString, TEST_12) {
    s21::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>(my_tmp);
    _orig = new std::vector<std::string>(orig_tmp);

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(VectorTestString, TEST_13) {
    s21::vector<std::string> my_tmp;
    std::vector<std::string> orig_tmp;

    _my = new s21::vector<std::string>(std::move(my_tmp));
    _orig = new std::vector<std::string>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(VectorTestString, TEST_14) {
    s21::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>(std::move(my_tmp));
    _orig = new std::vector<std::string>(std::move(orig_tmp));

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

TEST_F(VectorTestString, TEST_15) {
    s21::vector<std::string> my_tmp;
    std::vector<std::string> orig_tmp;

    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(VectorTestString, TEST_16) {
    s21::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    *_my = my_tmp;
    *_orig = orig_tmp;

    auto my_it{_my->begin()};
    auto my_tmp_it{my_tmp.begin()};

    for (size_t i{}; i < orig_tmp.size(); ++i) {
        EXPECT_EQ(*(my_it++), *(my_tmp_it++));
    }
}

TEST_F(VectorTestString, TEST_17) {
    s21::vector<std::string> my_tmp;
    std::vector<std::string> orig_tmp;

    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    *_my = std::move(my_tmp);
    *_orig = std::move(orig_tmp);

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(VectorTestString, TEST_18) {
    s21::vector<std::string> my_tmp({"1", "2", "3", "4", "5"});
    std::vector<std::string> orig_tmp({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

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

TEST_F(VectorTestString, TEST_19) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    *_my = {};
    *_orig = {};
}

TEST_F(VectorTestString, TEST_20) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    *_my = {"1", "2", "3", "4", "5"};
    *_orig = {"1", "2", "3", "4", "5"};
}

TEST_F(VectorTestString, TEST_21) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    *_my = {"1", "2", "3", "4", "5"};
    *_orig = {"1", "2", "3", "4", "5"};

    _my->clear();
    _orig->clear();
}

TEST_F(VectorTestString, TEST_22) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

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

TEST_F(VectorTestString, TEST_23) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

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

TEST_F(VectorTestString, TEST_24) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

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

TEST_F(VectorTestString, TEST_25) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

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

TEST_F(VectorTestString, TEST_26) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

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

TEST_F(VectorTestString, TEST_27) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

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

TEST_F(VectorTestString, TEST_28) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

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

TEST_F(VectorTestString, TEST_29) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

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

TEST_F(VectorTestString, TEST_30) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

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

TEST_F(VectorTestString, TEST_31) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

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

TEST_F(VectorTestString, TEST_32) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

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

TEST_F(VectorTestString, TEST_33) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

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

TEST_F(VectorTestString, TEST_34) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

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

TEST_F(VectorTestString, TEST_35) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(_my->begin() + 1, _my->end() - 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->end() - 1)};

    EXPECT_EQ(my_it, _my->end() - 1);
    EXPECT_EQ(orig_it, _orig->end() - 1);
    EXPECT_EQ(*(--my_it), *(--orig_it));
}

TEST_F(VectorTestString, TEST_36) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(_my->begin(), _my->end())};
    auto orig_it{_orig->erase(_orig->begin(), _orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
}

TEST_F(VectorTestString, TEST_37) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    auto my_it{_my->erase(_my->begin() + 1, _my->begin() + 1)};
    auto orig_it{_orig->erase(_orig->begin() + 1, _orig->begin() + 1)};

    EXPECT_EQ(*(my_it), *(orig_it));
    EXPECT_EQ(my_it, _my->begin() + 1);
    EXPECT_EQ(orig_it, _orig->begin() + 1);
}

TEST_F(VectorTestString, TEST_38) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    std::string str{"123"};

    _my->push_back(str);
    _orig->push_back(str);

    EXPECT_EQ(*_my->begin(), str);
    EXPECT_EQ(*_orig->begin(), str);
    EXPECT_EQ(_my->begin(), _my->end() - 1);
    EXPECT_EQ(_orig->begin(), (_orig->end() - 1));
}

TEST_F(VectorTestString, TEST_39) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    std::string str_1{"123"};
    std::string str_2{"123"};

    _my->push_back(std::move(str_1));
    _orig->push_back(std::move(str_2));;

    EXPECT_NE(*_my->begin(), str_1);
    EXPECT_NE(*_orig->begin(), str_2);
    EXPECT_EQ(_my->begin(), (_my->end() - 1));
    EXPECT_EQ(_orig->begin(), (_orig->end() - 1));
}

TEST_F(VectorTestString, TEST_40) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    _my->push_back("123");
    _orig->push_back("123");

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
}

TEST_F(VectorTestString, TEST_41) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    _my->pop_back();
    _orig->pop_back();

    EXPECT_EQ(*_my->begin(), *_orig->begin());
    EXPECT_EQ(*(_my->end() - 1), *(_orig->end() - 1));
}

TEST_F(VectorTestString, TEST_42) {
    _my = new s21::vector<std::string>();
    _orig = new std::vector<std::string>();

    _my->reserve(100);
    _orig->reserve(100);
}

TEST_F(VectorTestString, TEST_43) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    _my->reserve(100);
    _orig->reserve(100);

    _my->shrink_to_fit();
    _orig->shrink_to_fit();
}

TEST_F(VectorTestString, TEST_44) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    _my->clear();
    _orig->clear();
}

TEST_F(VectorTestString, TEST_45) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    auto it_1{_my->erase(_my->begin())};
    auto it_2{_orig->erase(_orig->begin())};

    EXPECT_EQ(*it_1, *it_2);
    EXPECT_EQ(*(it_1 + 1), *(it_2 + 1));
}

TEST_F(VectorTestString, TEST_46) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    auto it_1{_my->erase(_my->begin() + 1)};
    auto it_2{_orig->erase(_orig->begin() + 1)};

    EXPECT_EQ(*it_1, *it_2);

    it_1 = _my->erase(_my->end() - 2);
    it_2 = _orig->erase(_orig->end() - 2);

    EXPECT_EQ(*it_1, *it_2);
}

TEST_F(VectorTestString, TEST_47) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    auto it_1{_my->erase(_my->begin() + 1, _my->end() - 1)};
    auto it_2{_orig->erase(_orig->begin() + 1, _orig->end() - 1)};

    EXPECT_EQ(*it_1, *it_2);
}

TEST_F(VectorTestString, TEST_48) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    _my->erase(_my->begin(), _my->end());
    _orig->erase(_orig->begin(), _orig->end());
}

TEST_F(VectorTestString, TEST_49) {
    _my = new s21::vector<std::string>({"1", "2", "3", "4", "5"});
    _orig = new std::vector<std::string>({"1", "2", "3", "4", "5"});

    std::string num{"123"};

    auto my_it{_my->insert(_my->end() - 1, 7, num)};
    auto orig_it{_orig->insert(_orig->end() - 1, 7, num)};

    EXPECT_EQ(*my_it, *orig_it);
    EXPECT_EQ(*my_it, num);

    my_it = _my->insert(_my->end() - 1, {"1", "2", "3", "4", "5"});
    orig_it = _orig->insert(_orig->end() - 1, {"1", "2", "3", "4", "5"});

    EXPECT_EQ(*my_it, *orig_it);
}

TEST_F(VectorTestString, TEST_50) {
    std::list<std::string> list({"1", "2", "3", "4", "5"});

    _my = new s21::vector<std::string>(list.begin(), list.end());
    _orig = new std::vector<std::string>(list.begin(), list.end());
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

void VectorTestUniquePtr::TearDown() {
    if (_my && _orig) {
        EXPECT_EQ(_my->size(), _orig->size());
        EXPECT_EQ(_my->empty(), _orig->empty());
        EXPECT_EQ(_my->capacity(), _orig->capacity());

        if (_my->empty() && _orig->empty()) {
            EXPECT_EQ(_my->begin(), _my->end());
        }
    }

    delete _my;
    delete _orig;

    _my = nullptr;
    _orig = nullptr;
}

TEST_F(VectorTestUniquePtr, TEST_0) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();
}

TEST_F(VectorTestUniquePtr, TEST_1) {
    _my = new s21::vector<std::unique_ptr<std::string>>(9);
    _orig = new std::vector<std::unique_ptr<std::string>>(9);
}

TEST_F(VectorTestUniquePtr, TEST_2) {
    s21::vector<std::unique_ptr<std::string>> my_tmp;
    std::vector<std::unique_ptr<std::string>> orig_tmp;

    _my = new s21::vector<std::unique_ptr<std::string>>(std::move(my_tmp));
    _orig = new std::vector<std::unique_ptr<std::string>>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());
}

TEST_F(VectorTestUniquePtr, TEST_3) {
    s21::vector<std::unique_ptr<std::string>> my_tmp;
    std::vector<std::unique_ptr<std::string>> orig_tmp;

    my_tmp.push_back(std::make_unique<std::string>("123"));
    orig_tmp.push_back(std::make_unique<std::string>("123"));

    _my = new s21::vector<std::unique_ptr<std::string>>(std::move(my_tmp));
    _orig = new std::vector<std::unique_ptr<std::string>>(std::move(orig_tmp));

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    my_tmp.push_back(std::make_unique<std::string>());
    orig_tmp.push_back(std::make_unique<std::string>());

    EXPECT_EQ(my_tmp.size(), orig_tmp.size());
    EXPECT_EQ(my_tmp.empty(), orig_tmp.empty());

    EXPECT_EQ(*(*_my->begin()), *(*_orig->begin()));
    EXPECT_EQ(*(*my_tmp.begin()), *(*orig_tmp.begin()));
}

TEST_F(VectorTestUniquePtr, TEST_4) {
    s21::vector<std::unique_ptr<std::string>> my_tmp;
    std::vector<std::unique_ptr<std::string>> orig_tmp;

    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

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

TEST_F(VectorTestUniquePtr, TEST_5) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    _my->clear();
    _orig->clear();
}

TEST_F(VectorTestUniquePtr, TEST_6) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    auto val_move_my{std::make_unique<std::string>("321")};
    auto val_move_orig{std::make_unique<std::string>("321")};

    auto my_it{_my->insert(_my->begin(), std::move(val_move_my))};
    auto orig_it{_orig->insert(_orig->begin(), std::move(val_move_orig))};

    EXPECT_EQ(*(*my_it), *(*orig_it));
}

TEST_F(VectorTestUniquePtr, TEST_7) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    _my->push_back(std::make_unique<std::string>("123"));
    _orig->push_back(std::make_unique<std::string>("123"));

    auto val_move_my{std::make_unique<std::string>("321")};
    auto val_move_orig{std::make_unique<std::string>("321")};

    auto my_it{_my->insert(++_my->begin(), std::move(val_move_my))};
    auto orig_it{_orig->insert(++_orig->begin(), std::move(val_move_orig))};

    EXPECT_EQ(*(*my_it), *(*orig_it));
}

TEST_F(VectorTestUniquePtr, TEST_8) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    auto val_move_my{std::make_unique<std::string>("321")};
    auto val_move_orig{std::make_unique<std::string>("321")};

    auto my_it{_my->insert(_my->end(), std::move(val_move_my))};
    auto orig_it{_orig->insert(_orig->end(), std::move(val_move_orig))};

    EXPECT_EQ(*(*my_it), *(*orig_it));
}

TEST_F(VectorTestUniquePtr, TEST_9) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

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

TEST_F(VectorTestUniquePtr, TEST_10) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

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

TEST_F(VectorTestUniquePtr, TEST_11) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    auto my_it{_my->erase(_my->begin(), _my->end())};
    auto orig_it{_orig->erase(_orig->begin(), _orig->end())};

    EXPECT_EQ(my_it, _my->end());
    EXPECT_EQ(orig_it, _orig->end());
}

TEST_F(VectorTestUniquePtr, TEST_12) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

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

TEST_F(VectorTestUniquePtr, TEST_13) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    _my->push_back(std::make_unique<std::string>("123"));
    _orig->push_back(std::make_unique<std::string>("123"));

    EXPECT_EQ(_my->begin(), _my->end() - 1);
    EXPECT_EQ(_orig->begin(), _orig->end() - 1);
    EXPECT_EQ(**_my->begin(), **_orig->begin());
    EXPECT_EQ(**(_my->end() - 1), **(_orig->end() - 1));
}

TEST_F(VectorTestUniquePtr, TEST_14) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    _my->pop_back();
    _orig->pop_back();

    EXPECT_EQ(**_my->begin(), **_orig->begin());
    EXPECT_EQ(**(_my->end() - 1), **(_orig->end() - 1));
}

TEST_F(VectorTestUniquePtr, TEST_15) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    _my->reserve(100);
    _orig->reserve(100);
}

TEST_F(VectorTestUniquePtr, TEST_16) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    _my->reserve(100);
    _orig->reserve(100);

    _my->shrink_to_fit();
    _orig->shrink_to_fit();
}

TEST_F(VectorTestUniquePtr, TEST_17) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    _my->clear();
    _orig->clear();
}

TEST_F(VectorTestUniquePtr, TEST_18) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    for (int i{}; i < 10; ++i) {
        _my->push_back(std::make_unique<std::string>(std::to_string(i)));
        _orig->push_back(std::make_unique<std::string>(std::to_string(i)));
    }

    auto it_1{_my->erase(_my->begin())};
    auto it_2{_orig->erase(_orig->begin())};

    EXPECT_EQ(**it_1, **it_2);
    EXPECT_EQ(**(it_1 + 1), **(it_2 + 1));
}

TEST_F(VectorTestUniquePtr, TEST_19) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

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

TEST_F(VectorTestUniquePtr, TEST_20) {
    _my = new s21::vector<std::unique_ptr<std::string>>();
    _orig = new std::vector<std::unique_ptr<std::string>>();

    _my->erase(_my->begin(), _my->end());
    _orig->erase(_orig->begin(), _orig->end());
}
