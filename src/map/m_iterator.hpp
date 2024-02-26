#ifndef CONTAINERS_MAP_M_ITERATOR_HPP
#define CONTAINERS_MAP_M_ITERATOR_HPP

#include <iterator>

namespace s21 {
template <typename Node>
class m_iterator {
public:
    using node_type  = Node;
    using value_type = typename Node::value_type;
    using pointer    = std::conditional_t<std::is_const_v<node_type>, typename Node::const_pointer, typename Node::pointer>;
    using reference  = std::conditional_t<std::is_const_v<node_type>, typename Node::const_reference, typename Node::reference>;

public:
    m_iterator(node_type* current, node_type* null, node_type* root) noexcept :
        current_(current),
        null_(null),
        root_(root)
    {};

public:
    reference operator*() { return current_->key_value; }

    pointer operator->() { return &(current_->key_value); }

    m_iterator &operator++() {
        if (current_ == null_)
            current_ = null_;
        else if (current_->right != null_) {
            current_ = current_->right;
            while (current_->left and current_->left != null_)
                current_ = current_->left;
        } else {
            while (current_->is_right())
                current_ = current_->parent;

            if (current_ != root_)
                current_ = current_->parent;
            else
                current_ = null_;
        }
        return *this;
    }

    m_iterator operator++(int) {
        m_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    m_iterator &operator--() {
        if (current_ == null_)
            current_ = null_;
        else if (current_->left != null_) {
            current_ = current_->left;
            while (current_->right and current_->right != null_)
                current_ = current_->right;
        } else {
            while (current_->is_left())
                current_ = current_->parent;

            if (current_ != root_)
                current_ = current_->parent;
            else
                current_ = null_;
        }
        return *this;
    }

    node_type* node() const noexcept { return current_; }

    m_iterator operator--(int) {
        m_iterator tmp(*this);
        --(*this);
        return tmp;
    }

    bool operator==(const m_iterator &other) const {
        return current_ == other.current_;
    }

    bool operator!=(const m_iterator &other) const {
        return current_ != other.current_;
    }

private:
    node_type* current_;
    node_type* null_;
    node_type* root_;
};
} // namespace s21

#endif // CONTAINERS_MAP_M_ITERATOR_HPP
