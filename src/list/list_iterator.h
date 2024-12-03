#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include <iterator>

namespace s21 {
template <typename Node>
class list_iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;

    using node_type         = Node;
    using difference_type   = std::ptrdiff_t;
    using value_type        = typename Node::value_type;

    using pointer           = std::conditional_t<std::is_const_v<Node>, typename Node::const_pointer, typename Node::pointer>;
    using reference         = std::conditional_t<std::is_const_v<Node>, typename Node::const_reference, typename Node::reference>;

public:
    list_iterator() :
        _curr(nullptr)
    {}

    list_iterator(Node* curr) :
        _curr(curr)
    {}

    template <
        typename NT = Node,
        typename = std::enable_if_t<std::is_const_v<NT>>
    > list_iterator(const list_iterator<std::remove_const_t<Node>>& other) :
        _curr(other.node())
    {}

public:
    reference operator*() const {
        return *_curr->value;
    }

    pointer operator->() const {
        return _curr->value.get();
    }

    node_type* node() const {
        return _curr;
    }

    list_iterator& operator++() {
        _curr = _curr->next;

        return *this;
    }

    list_iterator operator++(int) {
        list_iterator tmp(*this);

        _curr = _curr->next;
        
        return tmp;
    }

    list_iterator& operator--() {
        _curr = _curr->prev;

        return *this;
    }

    list_iterator operator--(int) {
        list_iterator tmp(*this);

        _curr = _curr->prev;

        return tmp;
    }

    list_iterator& operator+=(difference_type n) noexcept {
        while (n) {
            _curr = _curr->next;

            --n;
        }
        
        return *this;
    }

    list_iterator operator+(difference_type n) const noexcept {
        list_iterator tmp(_curr);

        tmp += n;

        return tmp;
    }

    list_iterator& operator-=(difference_type n) noexcept {
        while (n) {
            _curr = _curr->prev;

            --n;
        }
        
        return *this;
    }

    list_iterator operator-(difference_type n) const noexcept {
        list_iterator tmp(_curr);

        tmp -= n;

        return tmp;
    }

    [[nodiscard]] bool operator==(const list_iterator& other) const {
        return _curr == other._curr;
    }

    [[nodiscard]] bool operator!=(const list_iterator& other) const {
        return _curr != other._curr;
    }

private:
    Node* _curr;
};
} // namespace s21

#endif  // LIST_ITERATOR_H
