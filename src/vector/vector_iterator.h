#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H

#include <iterator>

namespace s21 {
template <typename T>
class vector_iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;

    using value_type        = T;
    using difference_type   = std::ptrdiff_t;

    using pointer           = std::conditional_t<std::is_const_v<T>, const T*, T*>;
    using reference         = std::conditional_t<std::is_const_v<T>, const T&, T&>;

public:
    vector_iterator() :
        _curr(nullptr)
    {}

    vector_iterator(T* curr) :
        _curr(curr)
    {}

    template <
        typename VT = T,
        typename = std::enable_if_t<std::is_const_v<VT>>
    > vector_iterator(const vector_iterator<std::remove_const_t<T>>& other) :
        _curr(other.base())
    {}

public:
    reference operator*() const noexcept {
        return *_curr;
    }

    pointer operator->() const noexcept {
        return _curr;
    }

    vector_iterator& operator++() noexcept {
        ++_curr;

	    return *this;
    }

    vector_iterator operator++(int) noexcept {
        return vector_iterator(_curr++);
    }

    vector_iterator& operator--() noexcept {
        --_curr;

	    return *this;
    }

    vector_iterator operator--(int) noexcept {
        return vector_iterator(_curr--);
    }

    reference operator[](difference_type n) const noexcept {
        return _curr[n];
    }

    vector_iterator& operator+=(difference_type n) noexcept {
        _curr += n;
        
        return *this;
    }

    vector_iterator operator+(difference_type n) const noexcept {
        return vector_iterator(_curr + n);
    }

    vector_iterator& operator-=(difference_type n) noexcept {
        _curr -= n;

        return *this;
    }

    vector_iterator operator-(difference_type n) const noexcept {
        return vector_iterator(_curr - n);
    }

    difference_type operator-(const vector_iterator& other) const {
        return static_cast<difference_type>(_curr - other._curr);
    }

    T* base() const noexcept {
        return _curr;
    }

    [[nodiscard]] bool operator>(const vector_iterator& other) const {
        return _curr > other._curr;
    }

    [[nodiscard]] bool operator<(const vector_iterator& other) const {
        return _curr < other._curr;
    }

    [[nodiscard]] bool operator==(const vector_iterator& other) const {
        return _curr == other._curr;
    }

    [[nodiscard]] bool operator!=(const vector_iterator& other) const {
        return _curr != other._curr;
    }

private:
    T* _curr;
};
} // namespace s21

#endif  // VECTOR_ITERATOR_H
