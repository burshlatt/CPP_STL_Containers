#ifndef DEQUE_H
#define DEQUE_H

#include <cmath>
#include <utility>
#include <algorithm>
#include <initializer_list>

#include "../vector/vector.h"
#include "deque_iterator.h"

namespace s21 {
template<
    class T,
    class Allocator = std::allocator<T>

> class deque {
public:
    using value_type       = T;
    using size_type        = std::size_t;

    using reference        = T&;
    using const_reference  = const T&;

    using allocator_type   = Allocator;
    using allocator_traits = std::allocator_traits<Allocator>;

    using iterator         = deque_iterator<T>;
    using const_iterator   = deque_iterator<const T>;

public:
    deque() :
        deque(Allocator())
    {}

    explicit deque(const Allocator& alloc) :
        _alloc(alloc),
        _start_offset(0),
        _end_offset(0)
    {
        _blocks.push_back(allocate_block());
    }

    explicit deque(size_type count, const Allocator& alloc = Allocator()) :
        deque(alloc)
    {
        while (count--) {
            push_back(T());
        }
    }

    deque(size_type count, const T& value, const Allocator& alloc = Allocator()) :
        deque(alloc)
    {
        while (count--) {
            push_back(value);
        }
    }

    template <
        class InputIt,
        typename = typename std::enable_if<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>::type
    > deque(InputIt first, InputIt last, const Allocator& alloc = Allocator()) :
        deque(alloc)
    {
        insert(begin(), first, last);
    }

    deque(const deque& other) :
        deque(allocator_traits::select_on_container_copy_construction(other.get_allocator()))
    {
        for (const auto& elem : other) {
            push_back(elem);
        }
    }

    deque(deque&& other) :
        deque(std::move(other), other.get_allocator())
    {}

    deque(const deque& other, const Allocator& alloc) :
        deque(alloc)
    {
        for (const auto& elem : other) {
            push_back(elem);
        }
    }

    deque(deque&& other, const Allocator& alloc) :
        _alloc(alloc),
        _start_offset(std::exchange(other._start_offset, 0)),
        _end_offset(std::exchange(other._end_offset, 0)),
        _blocks(std::move(other._blocks))
    {
        other._blocks.push_back(other.allocate_block());
    }

    deque(std::initializer_list<T> init, const Allocator& alloc = Allocator()) :
        deque(init.begin(), init.end(), alloc)
    {}

    ~deque() {
        for (T* block : _blocks) {
            deallocate_block(block);
        }
    }

public:
    deque& operator=(const deque& other) {
        if constexpr (allocator_traits::propagate_on_container_copy_assignment::value) {
            if (_alloc != other._alloc) {
                clear();

                _alloc = other._alloc;
            }
        }

        deque temp(other);
        swap(temp);

        return *this;
    }

    deque& operator=(deque&& other) noexcept(
        allocator_traits::is_always_equal::value || 
        allocator_traits::propagate_on_container_move_assignment::value) 
    {
        if constexpr (allocator_traits::propagate_on_container_move_assignment::value) {
            if (_alloc != other._alloc) {
                clear();

                _alloc = std::move(other._alloc);
            }
        }

        deque temp(std::move(other), _alloc);
        swap(temp);

        return *this;
    }

    deque& operator=(std::initializer_list<value_type> ilist) {
        deque temp(ilist, _alloc);

        swap(temp);

        return *this;
    }

    allocator_type get_allocator() const {
        return _alloc;
    }

    reference operator[](size_type pos) {
        size_type block_index = (_start_offset + pos) / _block_size;
        size_type offset = (_start_offset + pos) % _block_size;

        return _blocks[block_index][offset];
    }

    const_reference operator[](size_type pos) const {
        size_type block_index = (_start_offset + pos) / _block_size;
        size_type offset = (_start_offset + pos) % _block_size;

        return _blocks[block_index][offset];
    }

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *begin();
    }

    reference back() {
        return *std::prev(end());
    }

    const_reference back() const {
        return *std::prev(end());
    }

    iterator begin() noexcept {
        return iterator(_blocks.data(), start_block(), _start_offset);
    }

    const_iterator begin() const noexcept {
        return const_iterator(_blocks.data(), start_block(), _start_offset);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(_blocks.data(), start_block(), _start_offset);
    }

    iterator end() noexcept {
        return iterator(_blocks.data(), end_block(), _end_offset);
    }

    const_iterator end() const noexcept {
        return const_iterator(_blocks.data(), end_block(), _end_offset);
    }

    const_iterator cend() const noexcept {
        return const_iterator(_blocks.data(), end_block(), _end_offset);
    }

    bool empty() const {
        return begin() == end();
    }

    size_type size() const {
        return std::distance(begin(), end());
    }

    void clear() {
        for (T* block : _blocks) {
            deallocate_block(block);
        }

        _blocks.clear();

        _blocks.push_back(allocate_block());

        _start_offset = 0;
        _end_offset = 0;
    }

    iterator insert(const_iterator pos, const T& value) {
        return insert(pos, T{value});
    }

    iterator insert(const_iterator pos, T&& value) {
        auto offset{static_cast<size_type>(std::distance(cbegin(), pos))};

        if (pos == begin()) {
            push_front(std::forward<T>(value));

            return begin();
        }

        push_back(std::forward<T>(value));

        if (pos == end()) {
            return end() - 1;
        }

        auto it{end() - 1};

        for ( ; it != begin() + offset; --it) {
            std::swap(*it, *(it - 1));
        }

        return begin() + offset;
    }

    template <
        class InputIt,
        typename = typename std::enable_if<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>::type
    > iterator insert(const_iterator pos, InputIt first, InputIt last) {
        auto offset{std::distance(cbegin(), pos)};

        for (auto it{begin() + offset}; first != last; ++it) {
            it = insert(it, *first++);
        }

        return begin() + offset;
    }

    iterator erase(const_iterator pos) {
        if (pos == cbegin()) {
            pop_front();

            return begin();
        }

        if (pos == cend() - 1) {
            pop_back();

            return end();
        }

        auto offset{std::distance(cbegin(), pos)};

        for (auto it{begin() + offset}; it + 1 != end(); ++it) {
            *it = std::move(*(it + 1));
        }

        pop_back();

        return begin() + offset;
    }

    iterator erase(const_iterator first, const_iterator last) {
        auto offset_frist{std::distance(cbegin(), first)};
        auto offset{std::distance(first, last)};

        iterator it{begin() + offset_frist};

        while (offset) {
            it = erase(it++);

            --offset;
        }

        return it;
    }

    void push_front(const T& value) {
        push_front(T{value});
    }

    void push_front(T&& value) {
        if (_start_offset == 0) {
            _blocks.insert(_blocks.begin(), allocate_block());

            _start_offset = _block_size;
        }

        _blocks[start_block()][--_start_offset] = std::move(value);
    }

    void pop_front() {
        ++_start_offset;

        if (_start_offset == _block_size && start_block() != end_block()) {
            deallocate_block(_blocks[start_block()]);

            _blocks.erase(_blocks.begin());

            _start_offset = 0;
        }
    }

    void push_back(const T& value) {
        push_back(T{value});
    }

    void push_back(T&& value) {
        if (_end_offset == _block_size) {
            _blocks.push_back(allocate_block());

            _end_offset = 0;
        }

        _blocks[end_block()][_end_offset++] = std::move(value);
    }

    void pop_back() {
        if (_end_offset == 0 && end_block() != start_block()) {
            deallocate_block(_blocks[end_block()]);

            _blocks.pop_back();

            _end_offset = _block_size;
        }

        --_end_offset;
    }

    void swap(deque& other) noexcept(allocator_traits::is_always_equal::value) {
        if constexpr (allocator_traits::propagate_on_container_swap::value) {
            std::swap(_alloc, other._alloc);
        }

        std::swap(_start_offset, other._start_offset);
        std::swap(_end_offset, other._end_offset);
        std::swap(_blocks, other._blocks);
    }

private:
    T* allocate_block() {
        T* block{allocator_traits::allocate(_alloc, _block_size)};

        std::uninitialized_value_construct(block, block + _block_size);

        return block;
    }

    void deallocate_block(T* block) {
        for (size_type i{}; i < _block_size; ++i) {
            allocator_traits::destroy(_alloc, block + i);
        }
        
        allocator_traits::deallocate(_alloc, block, _block_size);
    }

    inline size_type end_block() const noexcept {
        return _blocks.size() - 1;
    }

    inline size_type start_block() const noexcept {
        return 0;
    }

private:
    Allocator _alloc;

    size_type _start_offset;
    size_type _end_offset;

    s21::vector<T*> _blocks;

    size_type _block_size{4096 / sizeof(T)};
};
} // namespace s21

#endif  // DEQUE_H
