#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <memory>
#include <utility>
#include <iterator>
#include <algorithm>
#include <initializer_list>

#include "forward_list_node.h"
#include "forward_list_iterator.h"

namespace s21 {
template<
    class T,
    class Allocator = std::allocator<forward_list_node<T>>

> class forward_list {
    public:
    using value_type       = T;
    using size_type        = std::size_t;
    using difference_type  = std::ptrdiff_t;
    using node             = forward_list_node<T>;

    using reference        = T&;
    using const_reference  = const T&;

    using allocator_type   = Allocator;
    using allocator_traits = std::allocator_traits<Allocator>;

    using pointer          = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer    = typename std::allocator_traits<Allocator>::const_pointer;

    using iterator         = forward_list_iterator<forward_list_node<T>>;
    using const_iterator   = forward_list_iterator<const forward_list_node<T>>;

public:
    forward_list() :
        forward_list(Allocator())
    {}

    explicit forward_list(const Allocator& alloc) :
        _alloc(alloc),
        _before_head(allocator_traits::allocate(_alloc, 1))
    {
        allocator_traits::construct(_alloc, _before_head);
    }

    explicit forward_list(size_type count, const Allocator& alloc = Allocator()) :
        forward_list(alloc)
    {
        for (size_type i{}; i < count; ++i) {
            push_front(T());
        }
    }

    forward_list(size_type count, const T& value, const Allocator& alloc = Allocator()) :
        forward_list(alloc)
    {
        insert_after(cbefore_begin(), count, value);
    }

    template<
        class InputIt,
        typename = std::enable_if_t<std::is_base_of_v<std::input_iterator_tag,
                                    typename std::iterator_traits<InputIt>::iterator_category>>
    > forward_list(InputIt first, InputIt last, const Allocator& alloc = Allocator()) :
        forward_list(alloc)
    {
        insert_after(cbefore_begin(), first, last);
    }

    forward_list(const forward_list& other) :
        forward_list(allocator_traits::select_on_container_copy_construction(other.get_allocator()))
    {
        insert_after(cbefore_begin(), other.begin(), other.end());
    }

    forward_list(const forward_list& other, const Allocator& alloc) :
        forward_list(alloc)
    {
        insert_after(cbefore_begin(), other.begin(), other.end());
    }

    forward_list(forward_list&& other) :
        _alloc(other.get_allocator()),
        _before_head(std::exchange(other._before_head, allocator_traits::allocate(other._alloc, 1)))
    {
        allocator_traits::construct(other._alloc, other._before_head);
    }

    forward_list(forward_list&& other, const Allocator& alloc) :
        forward_list(alloc)
    {
        if (_alloc != other._alloc) {
            insert_after(cbefore_begin(), other.begin(), other.end());
        } else {
            _before_head = std::exchange(other._before_head, allocator_traits::allocate(other._alloc, 1));

            allocator_traits::construct(other._alloc, other._before_head);
        }
    }

    forward_list(std::initializer_list<T> init, const Allocator& alloc = Allocator()) :
        forward_list(alloc)
    {
        insert_after(cbefore_begin(), init);
    }

    ~forward_list() {
        clear();

        allocator_traits::destroy(_alloc, _before_head);
        allocator_traits::deallocate(_alloc, _before_head, 1);
    }

public:
    forward_list& operator=(const forward_list& other) {
        clear();

        if constexpr (allocator_traits::propagate_on_container_copy_assignment::value) {
            auto allocator{other.get_allocator()};

            if (_alloc != allocator) {
                allocator_traits::destroy(_alloc, _before_head);
                allocator_traits::deallocate(_alloc, _before_head, 1);

                _alloc = std::move(allocator);

                _before_head = allocator_traits::allocate(_alloc, 1);
                allocator_traits::construct(_alloc, _before_head);
            }
        }
        
        insert_after(cbefore_begin(), other.begin(), other.end());

        return *this;
    }

    forward_list& operator=(forward_list&& other) noexcept(std::allocator_traits<Allocator>::is_always_equal::value) {
        clear();

        if constexpr (allocator_traits::propagate_on_container_move_assignment::value) {
            allocator_traits::destroy(_alloc, _before_head);
            allocator_traits::deallocate(_alloc, _before_head, 1);

            _alloc = other.get_allocator();

            _before_head = std::exchange(other._before_head, allocator_traits::allocate(other._alloc, 1));

            allocator_traits::construct(other._alloc, other._before_head);
        } else if (_alloc != other._alloc) {
            insert_after(cbefore_begin(), other.begin(), other.end());
        }

        return *this;
    }

    forward_list& operator=(std::initializer_list<value_type> ilist) {
        clear();

        insert_after(cbefore_begin(), ilist);

        return *this;
    }

    allocator_type get_allocator() const {
        return _alloc;
    }

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *cbegin();
    }

    iterator before_begin() noexcept {
        return iterator(_before_head);
    }

    const_iterator before_begin() const noexcept {
        return const_iterator(_before_head);
    }

    const_iterator cbefore_begin() const noexcept {
        return const_iterator(_before_head);
    }

    iterator begin() noexcept {
        return iterator(_before_head->next);
    }

    const_iterator begin() const noexcept {
        return const_iterator(_before_head->next);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(_before_head->next);
    }

    iterator end() noexcept {
        return iterator(nullptr);
    }

    const_iterator end() const noexcept {
        return const_iterator(nullptr);
    }

    const_iterator cend() const noexcept {
        return const_iterator(nullptr);
    }

    bool empty() const noexcept {
        return begin() == end();
    }

    size_type max_size() const {
        return allocator_traits::max_size(_alloc);
    }

    void clear() noexcept {
        while (begin() != end()) {
            pop_front();
        }
    }

    void push_front(const T& value) {
        insert_after(cbefore_begin(), value);
    }

    void push_front(T&& value) {
        insert_after(cbefore_begin(), std::forward<T>(value));
    }

    iterator insert_after(const_iterator pos, const T& value) {
        return insert_after(pos, T{value});
    }

    iterator insert_after(const_iterator pos, T&& value) {
        node* curr{const_cast<node*>(pos.node())};
        node* new_node{allocator_traits::allocate(_alloc, 1)};

        allocator_traits::construct(_alloc, new_node, std::forward<T>(value), curr->next);

        curr->next = new_node;

        return iterator(new_node);
    }

    iterator insert_after(const_iterator pos, size_type count, const T& value) {
        iterator it(const_cast<node*>(pos.node()));

        while (count--) {
            it = insert_after(it, value);
        }

        return it;
    }

    template<
        class InputIt,
        typename = std::enable_if_t<std::is_base_of_v<std::input_iterator_tag,
                                    typename std::iterator_traits<InputIt>::iterator_category>>
    > iterator insert_after(const_iterator pos, InputIt first, InputIt last) {
        iterator it(const_cast<node*>(pos.node()));

        while (first != last) {
            it = insert_after(it, *(first++));
        }

        return it;
    }

    iterator insert_after(const_iterator pos, std::initializer_list<T> ilist) {
        return insert_after(pos, ilist.begin(), ilist.end());
    }

    iterator erase_after(const_iterator pos) {
        node* curr(const_cast<node*>(pos.node()));
        node* next{curr->next};

        curr->next = next->next;

        allocator_traits::destroy(_alloc, next);
        allocator_traits::deallocate(_alloc, next, 1);

        return iterator(curr->next);
    }

    iterator erase_after(const_iterator first, const_iterator last) {
        iterator it(const_cast<node*>(first.node()));
        iterator it_last(const_cast<node*>(last.node()));

        while (it != it_last) {
            it = erase_after(first);
        }

        return it_last;
    }

    void pop_front() {
        erase_after(cbefore_begin());
    }

private:
    Allocator _alloc;
    
    node* _before_head;
};
} // namespace s21

#endif  // FORWARD_LIST_H
