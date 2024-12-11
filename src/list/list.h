#ifndef LIST_H
#define LIST_H

#include <memory>
#include <utility>
#include <iterator>
#include <algorithm>
#include <initializer_list>

#include "list_node.h"
#include "list_iterator.h"

namespace s21 {
template<
    class T,
    class Allocator = std::allocator<list_node<T>>
    
> class list {
public:
    using value_type             = T;
    using size_type              = std::size_t;
    using node                   = list_node<T>;

    using reference              = T&;
    using const_reference        = const T&;

    using allocator_type         = Allocator;
    using allocator_traits       = std::allocator_traits<Allocator>;

    using pointer                = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer          = typename std::allocator_traits<Allocator>::const_pointer;

    using iterator               = list_iterator<list_node<T>>;
    using const_iterator         = list_iterator<const list_node<T>>;

    using reverse_iterator       = std::reverse_iterator<list_iterator<list_node<T>>>;
    using const_reverse_iterator = std::reverse_iterator<list_iterator<const list_node<T>>>;

public:
    list() :
        list(Allocator())
    {}

    explicit list(const Allocator& alloc) :
        _alloc(alloc),
        _null(allocator_traits::allocate(_alloc, 1)),
        _head(_null),
        _tail(_null)
    {
        allocator_traits::construct(_alloc, _null);
    }

    explicit list(size_type count, const Allocator& alloc = Allocator()) :
        list(alloc)
    {
        for (size_type i{}; i < count; ++i) {
            push_front(T());
        }
    }

    list(size_type count, const T& value, const Allocator& alloc = Allocator()) :
        list(alloc)
    {
        insert(begin(), count, value);
    }

    template<
        class InputIt,
        typename = std::enable_if_t<std::is_base_of_v<std::input_iterator_tag,
                                    typename std::iterator_traits<InputIt>::iterator_category>>
    > list(InputIt first, InputIt last, const Allocator& alloc = Allocator()) :
        list(alloc)
    {
        insert(begin(), first, last);
    }

    list(const list& other) :
        list(allocator_traits::select_on_container_copy_construction(other.get_allocator()))
    {
        insert(begin(), other.begin(), other.end());
    }

    list(const list& other, const Allocator& alloc) :
        list(alloc)
    {
        insert(begin(), other.begin(), other.end());
    }

    list(list&& other) :
        _alloc(other.get_allocator()),
        _null(std::exchange(other._null, allocator_traits::allocate(other._alloc, 1))),
        _head(std::exchange(other._head, other._null)),
        _tail(std::exchange(other._tail, other._null))
    {
        allocator_traits::construct(other._alloc, other._null);
    }

    list(list&& other, const Allocator& alloc) :
        list(alloc)
    {
        if (_alloc != other._alloc) {
            insert(begin(), other.begin(), other.end());
        } else {
            _null = std::exchange(other._null, allocator_traits::allocate(other._alloc, 1));
            _head = std::exchange(other._head, other._null);
            _tail = std::exchange(other._tail, other._null);

            allocator_traits::construct(other._alloc, other._null);
        }
    }

    list(std::initializer_list<T> init, const Allocator& alloc = Allocator()) :
        list(alloc)
    {
        insert(begin(), init);
    }

    ~list() {
        clear();

        allocator_traits::destroy(_alloc, _null);
        allocator_traits::deallocate(_alloc, _null, 1);
    }

public:
    list& operator=(const list& other) {
        clear();

        if constexpr (allocator_traits::propagate_on_container_copy_assignment::value) {
            auto allocator{other.get_allocator()};

            if (_alloc != allocator) {
                allocator_traits::destroy(_alloc, _null);
                allocator_traits::deallocate(_alloc, _null, 1);

                _alloc = std::move(allocator);

                _null = allocator_traits::allocate(_alloc, 1);
                allocator_traits::construct(_alloc, _null);

                _head = _null;
                _tail = _null;
            }
        }
        
        insert(begin(), other.begin(), other.end());

        return *this;
    }

    list& operator=(list&& other) noexcept(std::allocator_traits<Allocator>::is_always_equal::value) {
        clear();

        if constexpr (allocator_traits::propagate_on_container_move_assignment::value) {
            allocator_traits::destroy(_alloc, _null);
            allocator_traits::deallocate(_alloc, _null, 1);

            _alloc = other.get_allocator();

            _null = std::exchange(other._null, allocator_traits::allocate(other._alloc, 1));
            _head = std::exchange(other._head, other._null);
            _tail = std::exchange(other._tail, other._null);

            allocator_traits::construct(other._alloc, other._null);
        } else if (_alloc != other._alloc) {
            insert(begin(), other.begin(), other.end());
        }

        return *this;
    }

    list& operator=(std::initializer_list<value_type> ilist) {
        clear();

        insert(begin(), ilist);

        return *this;
    }

    allocator_type get_allocator() const {
        return _alloc;
    }

    iterator begin() noexcept {
        return iterator(_head);
    }

    const_iterator begin() const noexcept {
        return const_iterator(_head);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(_head);
    }

    iterator end() noexcept {
        return iterator(_null);
    }

    const_iterator end() const noexcept {
        return const_iterator(_null);
    }

    const_iterator cend() const noexcept {
        return const_iterator(_null);
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(cend());
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(cbegin());
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }

    reference front() {
        return *_head->value;
    }

    const_reference front() const {
        return *_head->value;
    }

    reference back() {
        return *_tail->value;
    }

    const_reference back() const {
        return *_tail->value;
    }

    size_type size() const noexcept {
        return std::distance(begin(), end());
    }

    bool empty() const noexcept {
        return begin() == end();
    }

    void clear() noexcept {
        while (_head != _null) {
            pop_front();
        }

        _tail = _null;
    }

    iterator insert(const_iterator pos, const T& value) {
        return insert(pos, T{value});
    }

    iterator insert(const_iterator pos, T&& value) {
        node* curr{const_cast<node*>(pos.node())};
        node* new_node{allocator_traits::allocate(_alloc, 1)};

        allocator_traits::construct(_alloc, new_node, std::forward<T>(value), curr->prev, curr);

        curr->prev->next = new_node;
        curr->prev = new_node;

        if (curr == _head) {
            _head = new_node;
        }

        if (curr == _null) {
            _tail = new_node;
        }

        return iterator(new_node);
    }
    
    iterator insert(const_iterator pos, size_type count, const T& value) {
        iterator it(const_cast<node*>(pos.node()));

        for (size_type i{}; i < count; ++i) {
            it = insert(it++, value);
        }

        return it;
    }

    template<
        class InputIt,
        typename = std::enable_if_t<std::is_base_of_v<std::input_iterator_tag,
                                    typename std::iterator_traits<InputIt>::iterator_category>>
    > iterator insert(const_iterator pos, InputIt first, InputIt last) {
        iterator it(const_cast<node*>(pos.node()));

        for ( ; first != last; ++it) {
            it = insert(it, *(first++));
        }

        return it;
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        iterator new_it(const_cast<node*>(pos.node()));

        auto ilist_beg{ilist.begin()};

        for (auto it{ilist_beg}; it != ilist.end(); ++it) {
            if (it != ilist_beg) {
                insert(pos, *it);
            } else {
                new_it = insert(pos, *it);
            }
        }

        return new_it;
    }

    iterator erase(const_iterator pos) {
        node* curr(const_cast<node*>(pos.node()));

        if (curr == _head) {
            _head = _head->next;
        }

        if (curr == _tail) {
            _tail = _tail->prev;
        }

        // curr->value = nullptr;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        iterator new_it(curr->next);

        allocator_traits::destroy(_alloc, curr);
        allocator_traits::deallocate(_alloc, curr, 1);

        return new_it;
    }

    iterator erase(const_iterator first, const_iterator last) {
        iterator it(const_cast<node*>(last.node()));

        while (first != last) {
            it = erase(first++);
        }

        return it;
    }

    void push_front(const T& value) {
        insert(cbegin(), value);
    }

    void push_front(T&& value) {
        insert(cbegin(), std::forward<T>(value));
    }

    void pop_front() {
        erase(cbegin());
    }

    void push_back(const T& value) {
        insert(cend(), value);
    }

    void push_back(T&& value) {
        insert(cend(), std::forward<T>(value));
    }

    void pop_back() {
        erase(--cend());
    }

private:
    Allocator _alloc;
    
    node* _null;
    node* _head;
    node* _tail;
};
} // namespace s21

#endif  // LIST_H
