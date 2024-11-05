#ifndef DEQUE_H
#define DEQUE_H

#include <initializer_list>

#include "../vector/vector.h"
#include "deque_iterator.h"

namespace s21 {
template <class T>
class deque {
public:
    using value_type      = T;
    using size_type       = std::size_t;

    using reference       = T&;
    using const_reference = const T&;

    using iterator        = deque_iterator<value_type>;
    using const_iterator  = deque_iterator<const value_type>;

public:
    deque() :
        _start_block(0),
        _start_offset(0),
        _end_block(0),
        _end_offset(0)
    {
        _blocks.push_back(allocate_block());
    }

    deque(size_type count, const T& value) :
        deque()
    {
        for (size_type i{}; i < count; ++i) {
            push_back(value);
        }
    }

    explicit deque(size_type count) :
        deque(count, value_type())
    {}

    deque(const deque& other) :
        deque()
    {
        for (const auto& item : other) {
            push_back(item);
        }
    }

    deque(deque&& other) noexcept :
        _start_block(other._start_block),
        _start_offset(other._start_offset),
        _end_block(other._end_block),
        _end_offset(other._end_offset),
        _blocks(std::move(other._blocks))
    {
        other._start_block = other._start_offset = other._end_block = other._end_offset = 0;
    }

    deque(std::initializer_list<T> init) :
        deque()
    {
        for (const auto& item : init) {
            push_back(item);
        }
    }

    ~deque() {
        for (auto block : _blocks) {
            deallocate_block(block);
        }
    }

public:
    iterator begin() noexcept {
        return iterator(_blocks.data(), _start_block, _start_offset);
    }

    const_iterator begin() const noexcept {
        return const_iterator(_blocks.data(), _start_block, _start_offset);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(_blocks.data(), _start_block, _start_offset);
    }

    iterator end() noexcept {
        return iterator(_blocks.data(), _end_block, _end_offset);
    }

    const_iterator end() const noexcept {
        return const_iterator(_blocks.data(), _end_block, _end_offset);
    }

    const_iterator cend() const noexcept {
        return const_iterator(_blocks.data(), _end_block, _end_offset);
    }

    reference front() {
        return _blocks[_start_block][_start_offset];
    }

    const_reference front() const {
        return _blocks[_start_block][_start_offset];
    }

    reference back() {
        return _blocks[_end_block][_end_offset - 1];
    }

    const_reference back() const {
        return _blocks[_end_block][_end_offset - 1];
    }

    void push_back(const T& value) {
        if (_end_offset == _block_size) {
            _blocks.push_back(allocate_block());

            _end_offset = 0;
            ++_end_block;
        }

        _blocks[_end_block][_end_offset++] = value;
    }

    void push_back(T&& value) {
        if (_end_offset == _block_size) {
            _blocks.push_back(allocate_block());
            
            _end_offset = 0;
            ++_end_block;
        }

        _blocks[_end_block][_end_offset++] = std::move(value);
    }

    void push_front(const T& value) {
        if (_start_offset == 0) {
            _blocks.insert(_blocks.begin(), allocate_block());

            _start_offset = _block_size;
            ++_start_block;
        }

        _blocks[_start_block][--_start_offset] = value;
    }

    void push_front(T&& value) {
        if (_start_offset == 0) {
            _blocks.insert(_blocks.begin(), allocate_block());

            _start_offset = _block_size;
            ++_start_block;
        }

        _blocks[_start_block][--_start_offset] = std::move(value);
    }

    void pop_back() {
        if (empty()) {
            return;
        }

        if (_end_offset == 0) {
            deallocate_block(_blocks.back());

            _blocks.pop_back();

            --_end_block;
            _end_offset = _block_size;
        }

        --_end_offset;
    }

    void pop_front() {
        if (empty()) {
            return;
        }

        if (_start_offset == _block_size) {
            deallocate_block(_blocks.front());

            _blocks.erase(_blocks.begin());

            --_start_block;
            _start_offset = 0;
        }

        ++_start_offset;
    }

    bool empty() const {
        return _start_block == _end_block && _start_offset == _end_offset;
    }

    size_type size() const {
        return (_end_block - _start_block) * _block_size + _end_offset - _start_offset;
    }

    reference operator[](size_type pos) {
        size_type block_idx{_start_block + (pos + _start_offset) / _block_size};
        size_type offset{(pos + _start_offset) % _block_size};

        return _blocks[block_idx][offset];
    }

    const_reference operator[](size_type pos) const {
        size_type block_idx{_start_block + (pos + _start_offset) / _block_size};
        size_type offset{(pos + _start_offset) % _block_size};

        return _blocks[block_idx][offset];
    }

private:
    T* allocate_block() {
        return new T[_block_size];
    }

    void deallocate_block(T* block) {
        delete[] block;
    }

private:
    size_type _start_block;
    size_type _start_offset;
    size_type _end_block;
    size_type _end_offset;

    s21::vector<value_type*> _blocks;

    size_type _block_size{4096 / sizeof(T)};
};
}  // namespace s21

#endif  // DEQUE_H
