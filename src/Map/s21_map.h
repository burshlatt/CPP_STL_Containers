#ifndef SRC_MAP_S21_MAP_H
#define SRC_MAP_S21_MAP_H

#include "../Set/s21_set.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = const Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator<value_type>;
  using const_iterator = ConstIterator<value_type>;
  using size_type = size_t;

  map() : root_(nullptr) {}
  map(std::initializer_list<value_type> const& items) {
    for (auto i : items) {
      insert(i);
    }
  }
  map(const map& m) {
    for (auto it = m.begin(); it != m.end(); ++it) {
      insert(*it);
    }
  }
  map(map&& m) {
    root_ = m.root_;
    m.root_ = nullptr;
  }
  ~map() {
    FreeRec(root_);
    root_ = nullptr;
  }
  map operator=(const map& m) {
    for (auto i = m.begin(); i != m.end(); ++i) {
      insert(i.current_->value_);
    }
    return *this;
  }
  map operator=(map&& m) {
    root_ = m.root_;
    m.root_ = nullptr;
    return *this;
  }
  T& at(const key_type& key) {
    TreeNode<value_type>* cur = root_;
    while (cur->value_.first != key) {
      if (cur->value_.first < key) {
        cur = cur->right_;
      } else {
        cur = cur->left_;
      }
    }
    return cur->value_.second;
  }
  const T& at(const key_type& key) const {
    TreeNode<value_type>* cur = root_;
    while (cur->value_.first != key) {
      if (cur->value_.first < key) {
        cur = cur->right_;
      } else {
        cur = cur->left_;
      }
    }
    return cur->value_.second;
  }
  T& operator[](const key_type& key) { return at(key); }
  iterator begin() { return iterator(FindMinimum(root_)); }
  iterator end() { return iterator(nullptr); }
  const_iterator begin() const { return const_iterator(FindMinimum(root_)); }
  const_iterator end() const { return const_iterator(nullptr); }

  [[nodiscard]] bool empty() const { return root_ == nullptr; }
  [[nodiscard]] size_type size() const {
    size_type size = 0;
    for (auto it = begin(); it != end(); ++it) {
      ++size;
    }
    return size;
  }
  [[nodiscard]] size_type max_size() const {
    std::allocator<T> allocator;
    return allocator.max_size() / 10;
  }

  void clear() {
    FreeRec(root_);
    root_ = nullptr;
  }
  std::pair<iterator, bool> insert(const value_type& value) {
    if (root_ == nullptr) {
      root_ = new TreeNode<value_type>(value);
      return {iterator(root_), true};
    }
    TreeNode<value_type>* cur = root_;
    while (true) {
      if (value.first < cur->value_.first) {
        if (cur->left_ == nullptr) {
          cur->left_ = new TreeNode<value_type>(cur, value);
          return {iterator(cur->left_), true};
        }
        cur = cur->left_;
      } else if (cur->value_.first < value.first) {
        if (cur->right_ == nullptr) {
          cur->right_ = new TreeNode<value_type>(cur, value);
          return {iterator(cur->right_), true};
        }
        cur = cur->right_;
      } else {
        return {iterator(cur), false};
      }
    }
  }
  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    return insert(value_type{key, obj});
  }
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    value_type value = {key, obj};
    std::pair<iterator, bool> insert_res = insert(value);
    if (!insert_res.second) {
      (*(insert_res.first)).second = obj;
    }
    return insert_res;
  }
  void erase(iterator pos) { root_ = deleteNode(root_, pos.current_); }
  void swap(map& other) {
    TreeNode<value_type>* temp = root_;
    root_ = other.root_;
    other.root_ = temp;
  }
  void merge(map& other) {
    auto it = other.begin();
    while (it != other.end()) {
      if ((insert(*(it))).second) {
        auto tmp_it = it;
        ++it;
        other.erase(tmp_it);
      } else {
        ++it;
      }
    }
  }
  bool contains(const Key& key) {
    auto it = begin();
    while (it != end()) {
      if ((*it).first == key) {
        return true;
      }
      ++it;
    }
    return false;
  }

 private:
  TreeNode<value_type>* FindMinimum(TreeNode<value_type>* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->left_ == nullptr) {
      return node;
    }
    return FindMinimum(node->left_);
  }

  TreeNode<value_type>* deleteNode(TreeNode<value_type>* root,
                                   TreeNode<value_type>* k) {
    if (root == nullptr) return root;
    if (root->value_.first > k->value_.first) {
      TreeNode<value_type>* temp = deleteNode(root->left_, k);
      if (temp) {
        temp->parent_ = root;
      }
      root->left_ = temp;
      return root;
    } else if (root->value_.first < k->value_.first) {
      TreeNode<value_type>* temp = deleteNode(root->right_, k);
      if (temp) {
        temp->parent_ = root;
      }
      root->right_ = temp;
      return root;
    } else if (root == k) {
      if (root->left_ == NULL) {
        TreeNode<value_type>* temp = root->right_;
        if (temp) {
          temp->parent_ = root->parent_;
        }

        delete root;
        return temp;
      } else if (root->right_ == NULL) {
        TreeNode<value_type>* temp = root->left_;
        temp->parent_ = root->parent_;
        delete root;
        return temp;
      } else {
        TreeNode<value_type>* succParent = root;

        TreeNode<value_type>* succ = root->right_;
        while (succ->left_ != NULL) {
          succParent = succ;
          succ = succ->left_;
        }

        if (succParent != root)
          succParent->left_ = succ->right_;
        else
          succParent->right_ = succ->right_;

        // Copy Successor Data to root
        succ->parent_ = root->parent_;
        succ->left_ = root->left_;
        succ->right_ = root->right_;

        // Delete Successor and return root
        delete root;
        return succ;
      }
    } else {
      return root;
    }
  }

  TreeNode<value_type>* FindMaximum(TreeNode<value_type>* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->right_ == nullptr) {
      return node;
    }
    return FindMaximum(node->right_);
  }

  void FreeRec(TreeNode<value_type>* head) {
    if (head != nullptr) {
      FreeRec(head->left_);
      FreeRec(head->right_);
      delete head;
    }
  }

  TreeNode<value_type>* root_{};
};
}  // namespace s21
#endif  // SRC_MAP_S21_MAP_H
