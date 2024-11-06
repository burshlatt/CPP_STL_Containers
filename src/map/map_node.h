#ifndef MAP_NODE_H
#define MAP_NODE_H

namespace s21 {
enum class node_color : bool { kRed, kBlack };

template <typename Key, typename T>
struct node {
public:
    using key_type        = Key;
    using mapped_type     = T;
    using value_type      = std::pair<Key, T>;
    using pointer         = value_type*;
    using reference       = value_type&;
    using const_pointer   = const pointer;
    using const_reference = const reference;

public:
    node() = default;

    explicit node(const value_type &value) :
        key_value(value)
    {}

    explicit node(value_type &&value) noexcept :
        key_value(std::move(value))
    {}

    ~node() = default;

public:
    [[nodiscard]] bool is_left() const {
        return parent && this == parent->left;
    }

    [[nodiscard]] bool is_right() const {
        return parent && this == parent->right;
    }

public:
    node *left{nullptr};
    node *right{nullptr};
    node *parent{nullptr};

    value_type key_value;

    node_color color{node_color::kBlack};
};
} // namespace s21

#endif  // MAP_NODE_H
