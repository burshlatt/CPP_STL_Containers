#ifndef CONTAINERS_MAP_MAP_HPP
#define CONTAINERS_MAP_MAP_HPP

#include <memory>
#include <initializer_list>

#include "node.hpp"
#include "m_iterator.hpp"

namespace s21 {
template<
    class Key,
    class T,
    class Compare = std::less<Key>
> class map {
    public:
        using key_type       = Key;
        using mapped_type    = T;
        using value_type     = std::pair<Key, T>;
        using size_type      = std::size_t;
        using compare_type   = Compare;

        using node_type      = node<Key, T>;
        using iterator       = m_iterator<node_type>;
        using const_iterator = m_iterator<const node_type>;

    public:
        map() :
            null_(new node_type),
            root_(null_)
        {}

        explicit map(const map &other) {
            for (const auto &kv : other)
                insert(kv);
        }

        explicit map(map &&other) noexcept :
            null_(other.null_),
            root_(other.root_),
            compare_(other.compare_),
            size_(other.size_)
        {
            other.null_ = nullptr;
            other.root_ = nullptr;
            other.size_ = size_type{};
        }

        map(std::initializer_list<value_type> init) {
            for (const auto& value : init)
                insert(value);
        }

        ~map() noexcept {
            if (root_ != null_)
                clear();

            delete null_;
        }

        map &operator=(const map &other) {
            if (this == &other)
                return *this;

            if (!empty())
                clear_recursive(root_);

            for (const auto &kv : other)
                insert(kv);

            return *this;
        }

        map &operator=(map &&other) noexcept {
            if (this == &other)
                return *this;

            std::swap(null_, other.null_);
            std::swap(root_, other.root_);
            std::swap(compare_,other.compare_);
            std::swap(size_, other.size_);

            return *this;
        }

        map& operator=(std::initializer_list<value_type> ilist) {
            this->~map();
            map<Key, T, Compare> new_map(ilist);
            *this = new_map;
            return *this;
        }

    public:
        iterator begin() noexcept {
            node_type* min = find_min(root_);
            return iterator(min, null_, root_);
        }

        const_iterator begin() const noexcept {
            node_type* min = find_min(root_);
            return const_iterator(min, null_, root_);
        }

        iterator end() noexcept { return iterator(null_, null_, root_); }
        const_iterator end() const noexcept { return const_iterator(null_, null_, root_); }

    public:
        [[nodiscard]] bool empty() const noexcept { return size_ == size_type{}; }

        size_type size() const noexcept { return size_; }

    public:
        void clear() {
            if (root_ && size_ != size_type{})
                clear_recursive(root_);
        }

        std::pair<iterator, bool> insert(const value_type &kv) {
            node_type* node = root_;
            node_type* parent = nullptr;

            while (!is_null(node)) {
                parent = node;

                if (kv.first == node->key_value.first)
                    return std::make_pair(iterator(node, null_, root_), false);

                if (compare_(kv.first, node->key_value.first))
                    node = node->left;
                else
                    node = node->right;
            }

            node = new node_type(kv);
            node->parent = parent;
            node->left = null_;
            node->right = null_;
            node->color = node_color::kRed;

            if (parent) {
                if (compare_(node->key_value.first, parent->key_value.first))
                    parent->left = node;
                else
                    parent->right = node;
            } else {
                root_ = node;
            }

            insert(node);
            size_++;
            return std::make_pair(iterator(node, null_, root_), true);
        }

        std::pair<iterator, bool> insert(value_type &&kv) {
            value_type tmp{std::move(kv)};
            return insert(tmp);
        }

        void insert(std::initializer_list<value_type> ilist) {
            for (const auto& value : ilist)
                insert(value);
        }

        template<class M>
        std::pair<iterator, bool> insert_or_assign(const Key& k, M&& obj) {
            return this->insert_or_assign(std::move(key_type(k)), obj);
        }

        template<class M>
        std::pair<iterator, bool> insert_or_assign(Key&& k, M&& obj) {
            auto ret{this->try_emplace(std::move(k), std::forward<M>(obj))};
            if (!ret.second)
                ret.first->second = std::forward<M>(obj);
            return ret;
        }

        template<class... Args>
        std::pair<iterator, bool> emplace(Args&&... args) {
            std::tuple<Args...> arg(std::forward<Args>(args)...);

            key_type key{std::get<0>(arg)};
            mapped_type value{std::get<1>(arg)};
            value_type elem(key, value);

            return this->insert(std::move(elem));
        }

        template<class... Args>
        std::pair<iterator, bool> try_emplace(const Key& k, Args&&... args) {
            return this->try_emplace(std::move(key_type(k)), args ...);
        }

        template<class... Args>
        std::pair<iterator, bool> try_emplace(Key&& k, Args&&... args) {
            iterator exists{this->find(k)};
            if (exists != this->end())
                return std::make_pair(exists, false);
                
            value_type tmp{std::piecewise_construct,
                           std::forward_as_tuple(std::move(k)),
                           std::forward_as_tuple(std::forward<Args>(args)...)};

           return insert(tmp);
        }

        iterator erase(iterator it) {
            auto next_it{it};
            ++next_it;
            erase(it->first);
            return next_it;
        }

        size_type erase(const key_type &key) {
            node_type* node = find(root_, key);
            if (!node || is_null(node))
                return 0;

            node_type* child = nullptr;
            node_type* delete_node = nullptr;
            if (is_null(node->left) || is_null(node->right)) {
                delete_node = node;
            } else {
                delete_node = find_min(node->right);
                node->key_value = delete_node->key_value;
            }

            if (!is_null(delete_node->left)) {
                child = delete_node->left;
            } else {
                child = delete_node->right;
            }

            child->parent = delete_node->parent;
            if (delete_node->parent) {
                if (delete_node->is_left()) {
                    delete_node->parent->left = child;
                } else {
                    delete_node->parent->right = child;
                }
            } else {
                root_ = child;
            }

            if (delete_node->color == node_color::kBlack)
                erase(child);

            delete delete_node;
            size_--;
            return 1;
        }

        void swap(map& other) noexcept {
            std::swap(this->null_, other.null_);
            std::swap(this->root_, other.root_);
            std::swap(this->compare_, other.compare_);
            std::swap(this->size_, other.size_);
        }

    public:
        T& at(const Key& key) {
            auto elem{this->find(key)};
            if (elem == this->end())
                throw std::out_of_range("_Map_base::at");
            return elem->second;
        }

        const T& at(const Key& key) const {
            auto elem{this->find(key)};
            if (elem == this->end())
                throw std::out_of_range("_Map_base::at");
            return elem->second;
        }

        T& operator[](const Key& key) {
            return this->try_emplace(key).first->second;
        }

        T& operator[](Key&& key) {
            return this->try_emplace(std::move(key)).first->second;
        }

        size_type count(const Key& key) const {
            return this->find(key) != this->end() ? 1 : 0;
        }

        iterator find(const key_type &key) {
            node_type* node = find(root_, key);
            if (node && !is_null(node))
                return iterator(node, null_, root_);
            return end();
        }

        const_iterator find(const key_type &key) const {
            node_type* node = find(root_, key);
            if (node && !is_null(node))
                return const_iterator(node, null_, root_);
            return end();
        }

    private:
        void clear_recursive(node_type* node) {
            if (node && !is_null(node)) {
                clear_recursive(node->left);
                clear_recursive(node->right);

                delete node;
                size_--;
            }
        }

        bool is_null(node_type* node) const { return node == null_; }

        void insert(node_type* x) {
            while (x != root_ && x->parent->color == node_color::kRed) {
                auto parent = x->parent;
                auto grandparent = parent->parent;
                if (grandparent->left && grandparent->right &&
                    grandparent->left->color == node_color::kRed &&
                    grandparent->right->color == node_color::kRed) {

                    grandparent->color = node_color::kRed;
                    grandparent->left->color = node_color::kBlack;
                    grandparent->right->color = node_color::kBlack;
                    x = std::move(grandparent);
                } else {
                    if (parent->is_left()) {
                        if (x->is_right()) {
                            x = x->parent;
                            rotate_left(x);
                        }

                        x->parent->color = node_color::kBlack;
                        x->parent->parent->color = node_color::kRed;
                        rotate_right(grandparent);
                    } else {
                        if (x->is_left()) {
                            x = x->parent;
                            rotate_right(x);
                        }

                        x->parent->color = node_color::kBlack;
                        x->parent->parent->color = node_color::kRed;
                        rotate_left(grandparent);
                    }
                }
            }
            root_->color = node_color::kBlack;
        }

        void erase(node_type* x) {
            while (x != root_ && x->color == node_color::kBlack) {
                if (x->is_left()) {
                    erase_left(x);
                } else {
                    erase_right(x);
                }
                null_->parent = nullptr;
            }

            x->color = node_color::kBlack;
        }

        void erase_left(node_type* &x) {
            node_type* uncle = x->parent->right;
            if (uncle->color == node_color::kRed) {
                uncle->color = node_color::kBlack;
                x->parent->color = node_color::kRed;
                rotate_left(x->parent);
                uncle = x->parent->right;
            }

            if (uncle->left->color == node_color::kBlack && uncle->right->color == node_color::kBlack) {
                uncle->color = node_color::kRed;
                x = x->parent;
            } else {
                if (uncle->right->color == node_color::kBlack) {
                    uncle->left->color = node_color::kBlack;
                    uncle->color = node_color::kRed;
                    rotate_right(uncle);
                    uncle = x->parent->right;
                }
                uncle->color = x->parent->color;
                x->parent->color = node_color::kBlack;
                uncle->right->color = node_color::kBlack;
                rotate_left(x->parent);
                x = root_;
            }
        }

        void erase_right(node_type* &x) {
            auto uncle = x->parent->left;
            if (uncle->color == node_color::kRed) {
                uncle->color = node_color::kBlack;
                x->parent->color = node_color::kRed;
                rotate_right(x->parent);
                uncle = x->parent->left;
            }
            if (uncle->right->color == node_color::kBlack && uncle->left->color == node_color::kBlack) {
                uncle->color = node_color::kRed;
                x = x->parent;
            } else {
                if (uncle->left->color == node_color::kBlack) {
                    uncle->right->color = node_color::kBlack;
                    uncle->color = node_color::kRed;
                    rotate_left(uncle);
                    uncle = x->parent->left;
                }
                uncle->color = x->parent->color;
                x->parent->color = node_color::kBlack;
                uncle->left->color = node_color::kBlack;
                rotate_right(x->parent);
                x = root_;
            }
        }

        node_type* find(node_type* n, const key_type &key) {
            node_type* node = n;
            if (!node || is_null(node))
                return null_;

            while (!is_null(node)) {
                if (node->key_value.first == key)
                    return node;

                if (compare_(key, node->key_value.first))
                    node = node->left;
                else
                    node = node->right;
            }
            return null_;
        }

        node_type* find(node_type* n, const key_type &key) const {
            node_type* node = n;
            if (!node || is_null(node))
                return null_;

            while (!is_null(node)) {
                if (node->key_value.first == key)
                    return node;

                if (compare_(key, node->key_value.first))
                    node = node->left;
                else
                    node = node->right;
            }
            return null_;
        }

        void rotate_left(node_type* node) {
            node_type* y = node->right;
            node_type* mid = y->left;
            node->right = mid;

            if (y != null_) {
                y->parent = node->parent;
                if (y->left != null_)
                    y->left->parent = node;
            }

            if (node->parent) {
                if (node->is_left())
                    node->parent->left = y;
                else
                    node->parent->right = y;
            } else {
                root_ = y;
            }

            y->left = node;
            node->parent = y;
        }

        void rotate_right(node_type* node) {
            node_type* x = node->left;
            node_type* mid = x->right;
            node->left = mid;

            if (x != null_) {
                x->parent = node->parent;
                if (mid != null_)
                    mid->parent = node;
            }

            if (node->parent) {
                if (node->is_left())
                    node->parent->left = x;
                else
                    node->parent->right = x;
            } else {
                root_ = x;
            }

            x->right = node;
            node->parent = x;
        }

        node_type* find_min(node_type* n) const {
            node_type* node = n;
            if (is_null(root_))
                return node;

            while (node->left && !is_null(node->left))
                node = node->left;

            return node;
        }

    private:
        node_type* null_{nullptr};
        node_type* root_{nullptr};

        compare_type compare_;
        size_type size_{};
};
} // namespace s21

#endif // CONTAINERS_MAP_MAP_HPP
