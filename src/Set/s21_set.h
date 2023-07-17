#ifndef SRC_SET_S21_SET_H
#define SRC_SET_S21_SET_H

#include <iostream>
#include <limits>

#include "../Iterator/iterator.h"

namespace s21 {
template <typename T>
class set {
 public:
  using key_type = const T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator<key_type>;
  using const_iterator = ConstIterator<key_type>;
  using size_type = size_t;
  set() = default;
  set(std::initializer_list<value_type> const& items) {
    for (auto i : items) {
      insert(i);
    }
  }
  set(const set& s) {
    for (auto it = s.begin(); it != s.end(); ++it) {
      insert(*it);
    }
  }
  set(set&& s) noexcept {
    root_ = s.root_;
    s.root_ = nullptr;
  }
  ~set() {
    FreeRec(root_);
    root_ = nullptr;
  }
  set& operator=(set&& s) noexcept {
    for (auto it = s.begin(); it != s.end(); ++it) {
      insert(it.current_->value_);
    }
    return *this;
  }
  set& operator=(const set& s) {
    if (this->root_ != s.root_) {
      for (auto it = s.begin(); it != s.end(); ++it) {
        insert(it.current_->value_);
      }
    }
    return *this;
  }
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
  std::pair<iterator, bool> insert(const_reference value) {
    if (root_ == nullptr) {
      root_ = new TreeNode<key_type>(value);
      return {iterator(root_), true};
    }
    TreeNode<key_type>* cur = root_;
    while (true) {
      if (value < cur->value_) {
        if (cur->left_ == nullptr) {
          cur->left_ = new TreeNode<key_type>(cur, value);
          return {iterator(cur->left_), true};
        }
        cur = cur->left_;
      } else if (cur->value_ < value) {
        if (cur->right_ == nullptr) {
          cur->right_ = new TreeNode<key_type>(cur, value);
          return {iterator(cur->right_), true};
        }
        cur = cur->right_;
      } else {
        return {iterator(cur), false};
      }
    }
  }
  void erase(iterator pos) { root_ = deleteNode(root_, pos.current_); }
  void swap(set& other) {
    TreeNode<key_type>* temp = root_;
    root_ = other.root_;
    other.root_ = temp;
  }
  void merge(set& other) {
    auto it = other.begin();
    while (it != other.end()) {
      if ((insert(*it)).second) {
        auto tmp_it = it;
        ++it;
        other.erase(tmp_it);
      } else {
        ++it;
      }
    }
  }
  iterator find(const key_type& key) {
    auto it = begin();
    while (it != end()) {
      if ((*it) == key) {
        return it;
      }
      ++it;
    }
    return it;
  }
  const_iterator find(const key_type& key) const {
    const_iterator it = begin();
    while (it != end()) {
      if ((*it) == key) {
        return it;
      }
      ++it;
    }
    return it;
  }
  bool contains(const key_type& key) const {
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
  TreeNode<key_type>* FindMinimum(TreeNode<key_type>* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->left_ == nullptr) {
      return node;
    }
    return FindMinimum(node->left_);
  }
  TreeNode<key_type>* deleteNode(TreeNode<key_type>* root,
                                 TreeNode<key_type>* k) {
    if (root == nullptr) return root;
    if (root->value_ > k->value_) {
      TreeNode<key_type>* temp = deleteNode(root->left_, k);
      if (temp) {
        temp->parent_ = root;
      }
      root->left_ = temp;
      return root;
    } else if (root->value_ < k->value_) {
      TreeNode<key_type>* temp = deleteNode(root->right_, k);
      if (temp) {
        temp->parent_ = root;
      }
      root->right_ = temp;
      return root;
    } else if (root == k) {
      if (root->left_ == NULL) {
        TreeNode<key_type>* temp = root->right_;
        if (temp) {
          temp->parent_ = root->parent_;
        }

        delete root;
        return temp;
      } else if (root->right_ == NULL) {
        TreeNode<key_type>* temp = root->left_;
        temp->parent_ = root->parent_;
        delete root;
        return temp;
      } else {
        TreeNode<key_type>* succParent = root;

        TreeNode<key_type>* succ = root->right_;
        while (succ->left_ != NULL) {
          succParent = succ;
          succ = succ->left_;
        }

        if (succParent != root)
          succParent->left_ = succ->right_;
        else
          succParent->right_ = succ->right_;

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
  void FreeRec(TreeNode<key_type>* head) {
    if (head != nullptr) {
      FreeRec(head->left_);
      FreeRec(head->right_);
      delete head;
    }
  }

  TreeNode<key_type>* root_{};
};
}  // namespace s21

#endif  // SRC_SET_S21_SET_H
