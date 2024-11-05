#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <utility>
#include <algorithm>
#include <initializer_list>

namespace s21 {
template <class T>
class vector {
public:
    using value_type      = T;
    using size_type       = std::size_t;

    using iterator        = T*;
    using const_iterator  = const T*;

    using reference       = T&;
    using const_reference = const T&;

public:
    vector() :
        _size(0),
        _capacity(0),
        _data(nullptr)
    {}

    vector(const vector& other) :
        _size(other._size),
        _capacity(other._capacity),
        _data(!other._data ? nullptr : new value_type[_capacity]())
    {
        std::copy(other._data.get(), other._data.get() + other._size, _data.get());
    }

    vector(vector&& other) noexcept {
        _size = std::exchange(other._size, 0);
        _capacity = std::exchange(other._capacity, 0);
        _data = std::exchange(other._data, nullptr);
    }

    vector(size_type count, const T& value) :
        _size(count),
        _capacity(count),
        _data(new value_type[_capacity]())
    {
        std::fill(_data.get(), _data.get() + count, value);
    }

    explicit vector(size_type count) :
        vector(count, value_type())
    {}

    template<
        class InputIt,
        typename = std::enable_if_t<std::is_same_v<typename std::iterator_traits<InputIt>::value_type, T>>
    > vector(InputIt first, InputIt last) :
        _size(static_cast<size_type>(last - first)),
        _capacity(static_cast<size_type>(last - first)),
        _data(new value_type[_capacity]())
    {
        std::copy(first, last, _data.get());
    }

    vector(std::initializer_list<T> init) :
        _size(init.size()),
        _capacity(init.size()),
        _data(new value_type[_capacity]())
    {
        std::copy(init.begin(), init.end(), _data.get());
    }

    ~vector() = default;

public:
    iterator begin() noexcept {
        return _data.get();
    }

    const_iterator begin() const noexcept {
        return _data.get();
    }

    const_iterator cbegin() const noexcept {
        return _data.get();
    }

    iterator end() noexcept {
        return _data.get() + _size;
    }

    const_iterator end() const noexcept {
        return _data.get() + _size;
    }

    const_iterator cend() const noexcept {
        return _data.get() + _size;
    }

    T* data() noexcept {
        return _data.get();
    }

    const T* data() const noexcept {
        return _data.get();
    }

    reference back() {
        return *std::prev(end());
    }

    const_reference back() const {
        return *std::prev(cend());
    }

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *cbegin();
    }

    bool empty() const noexcept {
        return !_size;
    }

    size_type size() const noexcept {
        return _size;
    }

    size_type capacity() const noexcept {
        return _capacity;
    }

    iterator insert(const_iterator pos, const T& value) {
        T copy_value{value};

        return insert(pos, std::move(copy_value));
    }

    iterator insert(const_iterator pos, T&& value) {
        size_type offset{static_cast<size_type>(pos - cbegin())};

        if (_size == _capacity) {
            reserve(!_capacity ? 1 : _capacity * 2);

            pos = cbegin() + offset;
        }
        
        if (pos < cend()) {
            std::move_backward(pos, cend(), end() + 1);

            _data[offset] = std::move(value);
        } else {
            _data[offset] = std::move(value);
        }

        ++_size;

        return begin() + offset;
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {
        size_type offset{static_cast<size_type>(pos - cbegin())};

        if (_capacity - _size < count) {
            reserve(_capacity + (count - (_capacity -_size)));

            pos = cbegin() + offset;
        }

        for (size_type i{}; i < count; ++i) {
            insert(pos++, value);
        }

        return begin() + offset;
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        size_type offset{static_cast<size_type>(pos - cbegin())};

        if (_capacity - _size < ilist.size()) {
            reserve(_capacity + (ilist.size() - (_capacity -_size)));

            pos = cbegin() + offset;
        }

        for (const auto& elem : ilist) {
            insert(pos++, elem);
        }

        return begin() + offset;
    }

    iterator erase(const_iterator pos) {
        size_type offset{static_cast<size_type>(pos - cbegin())};
        
        if (pos < cend()) {
            std::move(pos + 1, cend(), begin() + offset);

            *(end() - 1) = value_type();
        } else {
            _data[offset] = value_type();
        }

        --_size;

        return begin() + offset;
    }

    iterator erase(const_iterator first, const_iterator last) {
        size_type offset_begin{static_cast<size_type>(first - begin())};
        size_type offset_end{static_cast<size_type>(last - begin())};
        size_type offset{static_cast<size_type>(last - first)};

        if (!offset) {
            return begin() + offset_end;
        }

        if (last < cend()) {
            std::move(last, cend(), begin() + offset_begin);

            std::fill(begin() + offset_end, end(), value_type());
        } else {
            std::fill(begin() + offset_begin, begin() + offset_end, value_type());

            if (last > cend()) {
                offset -= static_cast<size_type>(last - cend());
            }
        }

        _size -= offset;

        return begin() + offset_begin;
    }

    void push_back(const T& value) {
        if (_size == _capacity) {
            reserve(!_capacity ? 1 : _capacity * 2);
        }

        _data[_size++] = value;
    }

    void push_back(T&& value) {
        if (_size == _capacity) {
            reserve(!_capacity ? 1 : _capacity * 2);
        }
        
        _data[_size++] = std::move(value);
    }

    void pop_back() {
        if (_size) {
            --_size;
        }
    }

    vector& operator=(const vector& other) {
        if (!other._capacity) {
            _data = nullptr;
        } else if (_capacity != other._capacity) {
            realloc(other._capacity);

            std::copy(other._data.get(), other._data.get() + other._size, _data.get());
        }

        _size = other._size;
        _capacity = other._capacity;

        return *this;
    }

    vector& operator=(vector&& other) noexcept {
        _size = std::exchange(other._size, 0);
        _capacity = std::exchange(other._capacity, 0);
        _data = std::exchange(other._data, nullptr);

        return *this;
    }

    vector& operator=(std::initializer_list<value_type> ilist) {
        if (ilist.size() <= _capacity) {
            std::copy(ilist.begin(), ilist.end(), _data.get());

            _size = ilist.size();
        } else {
            _size = 0;
            _capacity = 0;
            _data = nullptr;

            insert(begin(), ilist);
        }

        return *this;
    }

    reference operator[](size_type pos) {
        return _data[pos];
    }

    const_reference operator[](size_type pos) const {
        return _data[pos];
    }

    reference at(size_type pos) {
        if (pos >= _size) {
            throw std::out_of_range("vector: pos (which is " + std::to_string(pos) +
                                    ") >= this->size() (which is " + std::to_string(_size) + ")");
        }

        return *(begin() + pos);
    }

    const_reference at(size_type pos) const {
        if (pos >= _size) {
            throw std::out_of_range("vector: pos (which is " + std::to_string(pos) +
                                    ") >= this->size() (which is " + std::to_string(_size) + ")");
        }

        return *(begin() + pos);
    }

    void clear() {
        _size = 0;
    }

    void shrink_to_fit() {
        realloc(_size);
    }

    void swap(vector& other) noexcept {
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
        std::swap(_data, other._data);
    }

    void reserve(size_type new_cap) {
        if (new_cap > _capacity) {
            realloc(new_cap);
        }
    }

    void resize(size_type count) {
        resize(count, value_type());
    }

    void resize(size_type count, const value_type& value) {
        if (count > _size) {
            if (count <= _capacity) {
                std::fill(end(), begin() + count, value);
            } else {
                realloc(count);

                std::fill(begin() + _size, begin() + count, value);
            }
        }

        _size = count;
    }

private:
    void realloc(size_type new_cap) {
        std::unique_ptr<T[]> tmp(new T[new_cap]());

        if (new_cap < _size) {
            _size = new_cap;
        }

        if (_size) {
            std::copy(_data.get(), _data.get() + _size, tmp.get());
        }

        _data = std::move(tmp);
        _capacity = new_cap;
    }

private:
    size_type _size;
    size_type _capacity;

    std::unique_ptr<value_type[]> _data;
};
}  // namespace s21

#endif  // VECTOR_H
