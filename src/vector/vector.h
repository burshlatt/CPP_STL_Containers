#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <utility>
#include <iterator>
#include <algorithm>
#include <initializer_list>

#include "vector_iterator.h"

namespace s21 {
template<
    class T,
    class Allocator = std::allocator<T>

> class vector {
public:
    using value_type       = T;
    using size_type        = std::size_t;
    using difference_type  = std::ptrdiff_t;

    using allocator_type   = Allocator;
    using allocator_traits = std::allocator_traits<Allocator>;

    using reference        = value_type&;
    using const_reference  = const value_type&;

    using pointer          = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer    = typename std::allocator_traits<Allocator>::const_pointer;

    using iterator         = vector_iterator<T>;
    using const_iterator   = vector_iterator<const T>;

public:
    vector() noexcept(noexcept(Allocator())) :
        vector(Allocator())
    {}

    explicit vector(const Allocator& alloc) noexcept :
        vector(0, alloc)
    {}

    explicit vector(size_type count, const Allocator& alloc = Allocator()) :
        _alloc(alloc),
        _size(count),
        _capacity(count),
        _data(count ? allocator_traits::allocate(_alloc, _capacity) : nullptr)
    {
        if (_data) {
            std::uninitialized_value_construct(_data, _data + _capacity);
        }
    }

    vector(size_type count, const T& value, const Allocator& alloc = Allocator()) :
        _alloc(alloc),
        _size(count),
        _capacity(count),
        _data(count ? allocator_traits::allocate(_alloc, _capacity) : nullptr)
    {
        if (_data) {
            for (size_type i{}; i < _capacity; ++i) {
                allocator_traits::construct(_alloc, _data + i, value);
            }
        }
    }

    template <
        class InputIt,
        typename = typename std::enable_if<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>::type
    > vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()) :
        _alloc(alloc),
        _size(std::distance(first, last)),
        _capacity(_size),
        _data(_capacity ? allocator_traits::allocate(_alloc, _capacity) : nullptr)
    {
        if (_data) {
            std::uninitialized_copy(first, last, _data);
        }
    }

    vector(const vector& other) :
        _alloc(allocator_traits::select_on_container_copy_construction(other.get_allocator())),
        _size(other._size),
        _capacity(other._capacity),
        _data(_capacity ? allocator_traits::allocate(_alloc, _capacity) : nullptr)
    {
        if (_data) {
            std::uninitialized_copy(other.begin(), other.end(), _data);
        }
    }

    vector(vector&& other) noexcept :
        _alloc(other.get_allocator()),
        _size(std::exchange(other._size, 0)),
        _capacity(std::exchange(other._capacity, 0)),
        _data(std::exchange(other._data, nullptr))
    {}

    vector(const vector& other, const Allocator& alloc) :
        _alloc(alloc),
        _size(other._size),
        _capacity(other._capacity),
        _data(_capacity ? allocator_traits::allocate(_alloc, _capacity) : nullptr)
    {
        if (_data) {
            std::uninitialized_copy(other.begin(), other.end(), _data);
        }
    }

    vector(vector&& other, const Allocator& alloc) :
        _alloc(alloc),
        _size(std::exchange(other._size, 0)),
        _capacity(std::exchange(other._capacity, 0)),
        _data(_capacity ? allocator_traits::allocate(_alloc, _capacity) : nullptr)
    {
        if (_data) {
            std::uninitialized_copy(std::make_move_iterator(other.begin()), std::make_move_iterator(other.end()), _data);
        }
    }

    vector(std::initializer_list<T> init, const Allocator& alloc = Allocator()) :
        vector(init.begin(), init.end(), alloc)
    {}

    ~vector() {
        dealloc();
    }

public:
    vector& operator=(const vector& other) {
        if constexpr (allocator_traits::propagate_on_container_copy_assignment::value) {
            auto allocator{other.get_allocator()};

            if (_alloc != allocator) {
                dealloc();

                _alloc = std::move(allocator);

                _data = allocator_traits::allocate(_alloc, other._capacity);
                
                if (_data) {
                    std::uninitialized_copy(other._data, other._data + other._capacity, _data);
                }

                _size = other._size;
                _capacity = other._capacity;

                return *this;
            }
        }
        
        realloc(other._capacity);
        insert(begin(), other.begin(), other.end());

        return *this;
    }

    vector& operator=(vector&& other) noexcept(
        allocator_traits::propagate_on_container_move_assignment::value ||
        allocator_traits::is_always_equal::value)
    {
        dealloc();

        if constexpr (allocator_traits::propagate_on_container_move_assignment::value) {
            _alloc = std::move(other._alloc);

        } else if (!allocator_traits::is_always_equal::value && _alloc != other._alloc) {
            reserve(other._size);

            for (size_t i{}; i < other._size; ++i) {
                push_back(std::move(other[i]));
            }

            return *this;
        }

        _size = std::exchange(other._size, 0);
        _capacity = std::exchange(other._capacity, 0);
        _data = std::exchange(other._data, nullptr);

        return *this;
    }

    vector& operator=(std::initializer_list<value_type> ilist) {
        realloc(ilist.size());
        insert(begin(), ilist);

        return *this;
    }

    allocator_type get_allocator() const noexcept {
        return _alloc;
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

    T* data() noexcept {
        return _data;
    }

    const T* data() const noexcept {
        return _data;
    }

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *cbegin();
    }

    reference back() {
        return *std::prev(end());
    }

    const_reference back() const {
        return *std::prev(cend());
    }

    iterator begin() noexcept {
        return _data;
    }

    const_iterator begin() const noexcept {
        return _data;
    }

    const_iterator cbegin() const noexcept {
        return _data;
    }

    iterator end() noexcept {
        return _data + _size;
    }

    const_iterator end() const noexcept {
        return _data + _size;
    }

    const_iterator cend() const noexcept {
        return _data + _size;
    }

    bool empty() const noexcept {
        return begin() == end();
    }

    size_type size() const noexcept {
        return _size;
    }

    size_type max_size() const {
        return allocator_traits::max_size(_alloc);
    }

    void reserve(size_type new_cap) {
        if (new_cap > max_size()) {
            throw std::length_error("vector::reserve");
        }
        
        if (new_cap > _capacity) {
            realloc(new_cap);
        }
    }

    size_type capacity() const noexcept {
        return _capacity;
    }

    void shrink_to_fit() {
        realloc(_size);
    }

    void clear() {
        size_type cap{_capacity};

        dealloc();

        _data = allocator_traits::allocate(_alloc, cap);
                
        if (_data) {
            std::uninitialized_value_construct(_data, _data + cap);

            _capacity = cap;
        }
    }

    iterator erase(const_iterator pos) {
        iterator it{begin() + std::distance(cbegin(), pos)};

        auto tail{std::move(it + 1, end(), it)};

        *tail = std::move(value_type());

        --_size;

        return it;
    }

    iterator erase(const_iterator first, const_iterator last) {
        iterator f_it{begin() + std::distance(cbegin(), first)};
        iterator l_it{begin() + std::distance(cbegin(), last)};

        if (first == last) {
            return f_it;
        }

        std::move(l_it, end(), f_it);

        auto count{std::distance(first, last)};

        for (iterator it{end() - count}; it != end(); ++it) {
            *it = std::move(value_type());
        }

        _size -= count;

        return f_it;
    }

    iterator insert(const_iterator pos, const T& value) {
        return insert(pos, T{value});
    }

    iterator insert(const_iterator pos, T&& value) {
        if (pos > cend()) {
            return end();
        }

        auto offset{std::distance(cbegin(), pos)};

        if (_size == _capacity) {
            reserve(!_capacity ? 1 : _capacity * 2);
        }

        iterator it{begin() + offset};
    
        std::move_backward(it, end(), end() + 1);

        *it = std::move(value);

        ++_size;

        return it;
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {
        if (pos > cend()) {
            return end();
        }

        auto offset{std::distance(cbegin(), pos)};

        if (_capacity - _size < count) {
            reserve(_capacity + (count - (_capacity -_size)));
        }

        iterator it{begin() + offset};

        std::move_backward(it, end(), end() + count);
        std::fill_n(it, count, value);

        _size += count;

        return it;
    }

    template <
        class InputIt,
        typename = typename std::enable_if<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>::type
    > iterator insert(const_iterator pos, InputIt first, InputIt last) {
        auto offset{std::distance(cbegin(), pos)};

        for (auto it{begin() + offset}; first != last; ++it) {
            it = insert(it, *(first++));
        }

        return begin() + offset;
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        return insert(pos, ilist.begin(), ilist.end());
    }

    void push_back(const T& value) {
        insert(end(), value);
    }

    void push_back(T&& value) {
        insert(end(), std::forward<T>(value));
    }

    void pop_back() {
        if (_size) {
            erase(end() - 1);
        }
    }

private:
    void realloc(size_type new_cap) {
        if (new_cap == _capacity) {
            return;
        } else if (!new_cap) {
            dealloc();

            return;
        }

        value_type* tmp{allocator_traits::allocate(_alloc, new_cap)};

        if (tmp) {
            std::uninitialized_value_construct(tmp, tmp + new_cap);
        }

        size_type offset{std::min(new_cap, _size)};

        std::move(begin(), begin() + offset, tmp);

        dealloc();

        _data = tmp;
        _size = offset;
        _capacity = new_cap;
    }

    void dealloc() {
        if (_data) {
            for (size_type i{}; i < _size; ++i) {
                allocator_traits::destroy(_alloc, _data + i);
            }

            allocator_traits::deallocate(_alloc, _data, _capacity);

            _size = 0;
            _capacity = 0;
            _data = nullptr;
        }
    }

private:
    Allocator _alloc;

    size_type _size;
    size_type _capacity;

    value_type* _data;
};
}  // namespace s21

#endif  // VECTOR_H
