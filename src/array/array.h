#ifndef ARRAY_H
#define ARRAY_H

#include <utility>
#include <algorithm>
#include <initializer_list>

namespace s21 {
template <class T, std::size_t N>
class array {
public:
    using value_type      = T;
    using size_type       = std::size_t;

    using iterator        = T*;
    using const_iterator  = const T*;

    using reference       = T&;
    using const_reference = const T&;

public:
    array() {}

    array(const array& other) {
        std::copy(other.begin(), other.end(), begin());
    }

    array(array&& other) noexcept {
        std::move(other.begin(), other.end(), begin());
    }

    array(std::initializer_list<T> init) {
        std::copy(init.begin(), init.end(), begin());
    }

    ~array() = default;

public:
    constexpr reference at(size_type pos) {
        if (pos >= _size) {
            throw std::out_of_range(
                "array::at: pos (which is " + std::to_string(pos) +
                ") >= _size (which is " + std::to_string(_size) + ")");
        }

        return _data[pos];
    }

    constexpr const_reference at(size_type pos) const {
        if (pos >= _size) {
            throw std::out_of_range(
                "array::at: pos (which is " + std::to_string(pos) +
                ") >= _size (which is " + std::to_string(_size) + ")");
        }

        return _data[pos];
    }

    constexpr reference operator[](size_type pos) {
        return _data[pos];
    }

    constexpr const_reference operator[](size_type pos) const {
        return _data[pos];
    }

    constexpr reference front() {
        return *_data;
    }
    
    constexpr const_reference front() const {
        return *_data;
    }

    constexpr reference back() {
        return *std::prev(end());
    }

    constexpr const_reference back() const {
        return *std::prev(end());
    }

    constexpr T* data() noexcept {
        return _data;
    }

    constexpr const T* data() const noexcept {
        return _data;
    }

    constexpr iterator begin() noexcept {
        return _data;
    }

    constexpr const_iterator begin() const noexcept {
        return _data;
    }

    constexpr const_iterator cbegin() const noexcept {
        return _data;
    }

    constexpr iterator end() noexcept {
        return _data + _size;
    }

    constexpr const_iterator end() const noexcept {
        return _data + _size;
    }

    constexpr const_iterator cend() const noexcept {
        return _data + _size;
    }

    constexpr bool empty() const noexcept {
        return !_size;
    }

    constexpr size_type size() const noexcept {
        return _size;
    }

    void fill(const T& value) {
        std::fill(begin(), end(), value);
    }

    void swap(array& other) noexcept {
        std::swap(_data, other._data);
    }

    array& operator=(const array& other) {
        std::copy(other.begin(), other.end(), begin());

        return *this;
    }

    array& operator=(array&& other) noexcept {
        std::move(other.begin(), other.end(), begin());

        return *this;
    }

private:
    size_type _size{N};

    value_type _data[N + 1]{};
};
} // namespace s21

#endif  // ARRAY_H
