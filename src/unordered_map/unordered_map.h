#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <vector>
#include <forward_list>
#include <initializer_list>

#include "umap_size.h"
#include "umap_iterator.h"

namespace s21 {
template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>
> class unordered_map {
    public:
        using mapped_type           = T;
        using key_type              = Key;
        using size_type             = std::size_t;
        using value_type            = std::pair<const Key, T>;
        using table_type            = std::vector<std::forward_list<value_type>>;
        using bucket_iterator       = typename std::forward_list<value_type>::iterator;
        using bucket_const_iterator = typename std::forward_list<value_type>::const_iterator;
        using table_iterator        = typename std::vector<std::forward_list<value_type>>::iterator;
        using table_const_iterator  = typename std::vector<std::forward_list<value_type>>::const_iterator;
        using iterator              = umap_iterator<table_iterator, bucket_iterator>;
        using const_iterator        = umap_iterator<table_const_iterator, bucket_const_iterator>;

    private:
        using hasher     = Hash;
        using key_equal  = KeyEqual;
        using table_size = s21::um::map_size;

    public:
        unordered_map() = default;
 
        explicit unordered_map(size_type bucket_count) :
            table_(bucket_count)
        {}

        explicit unordered_map(const unordered_map& other) :
            hash_(other.hash_),
            key_eq_(other.key_eq_),
            table_(other.table_),
            size_(other.size_),
            size_index_(other.size_index_)
        {}

        explicit unordered_map(unordered_map&& other) :
            hash_(std::move(other.hash_)),
            key_eq_(std::move(other.key_eq_)),
            table_(std::move(other.table_)),
            size_(std::move(other.size_)),
            size_index_(std::move(other.size_index_))
        {}

        unordered_map(std::initializer_list<value_type> init) {
            for (const auto& value : init)
                this->insert(value);
        }

        ~unordered_map() = default;

        unordered_map& operator=(const unordered_map& other) {
            this->hash_ = other.hash_;
            this->key_eq_ = other.key_eq_;
            this->table_ = other.table_;
            this->size_ = other.size_;
            this->size_index_ = other.size_index_;
            return *this;
        }

        unordered_map& operator=(unordered_map&& other) noexcept {
            this->hash_ = std::move(other.hash_);
            this->key_eq_ = std::move(other.key_eq_);
            this->table_ = std::move(other.table_);
            this->size_ = std::move(other.size_);
            this->size_index_ = std::move(other.size_index_);
            return *this;
        }

        unordered_map& operator=(std::initializer_list<value_type> ilist) {
            this->clear();
            this->insert(ilist);
            return *this;
        }

    public:
        iterator begin() noexcept {
            auto table_end{this->table_.end()};
            for (auto table_it = this->table_.begin(); table_it != table_end; ++table_it) {
                auto bucket_end{table_it->end()};
                for (auto bucket_it = table_it->begin(); bucket_it != bucket_end; ++bucket_it) {
                    return iterator(table_it, bucket_it, this->table_.end());
                }
            }
            return this->end();
        }

        const_iterator begin() const noexcept {
            auto table_end{this->table_.cend()};
            for (auto table_it = this->table_.cbegin(); table_it != table_end; ++table_it) {
                auto bucket_end{table_it->cend()};
                for (auto bucket_it = table_it->cbegin(); bucket_it != bucket_end; ++bucket_it) {
                    return const_iterator(table_it, bucket_it, this->table_.end());
                }
            }
            return this->end();
        }

        iterator end() noexcept { return iterator(this->table_.end()); }
        const_iterator end() const noexcept { return const_iterator(this->table_.end()); }

    public:
        [[nodiscard]] bool empty() const noexcept { return !this->size_; }

        size_type size() const noexcept { return this->size_; }

    public:
        void clear() noexcept {
            this->table_.clear();
            this->size_ = 0;
            this->size_index_ = 0;
        }

        std::pair<iterator, bool> insert(const value_type& value) {
            return this->insert(std::move(value_type(value)));
        }

        std::pair<iterator, bool> insert(value_type&& value) {
            if (this->table_.empty())
                this->resize();

            size_type hash{hash_(value.first)};
            size_type hashed_key{hash % table_size::size[this->size_index_]};

            iterator exists{this->find_by_hash(value.first, hashed_key)};
            if (exists != this->end())
                return std::make_pair(exists, false);

            this->size_++;
            this->update_alpha();

            hashed_key = hash % table_size::size[this->size_index_];
            this->table_[hashed_key].push_front(std::move(value));

            return std::make_pair(iterator(this->table_.begin() + hashed_key,
                                           this->table_[hashed_key].begin(),
                                           this->table_.end()), true);
        }

        void insert(std::initializer_list<value_type> ilist) {
            for (const auto& value : ilist)
                this->insert(value);
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
            if (this->table_.empty())
                this->resize();

            size_type hash{hash_(k)};
            size_type hashed_key{hash % table_size::size[this->size_index_]};

            iterator exists{this->find_by_hash(k, hashed_key)};
            if (exists != this->end())
                return std::make_pair(exists, false);

            this->size_++;
            this->update_alpha();

            hashed_key = hash % table_size::size[this->size_index_];
            this->table_[hashed_key].push_front(value_type(std::piecewise_construct,
                                                           std::forward_as_tuple(std::move(k)),
                                                           std::forward_as_tuple(std::forward<Args>(args)...)));

           return std::make_pair(iterator(this->table_.begin() + hashed_key,
                                          this->table_[hashed_key].begin(),
                                          this->table_.end()), true);
        }

        iterator erase(iterator pos) {
            return this->erase_by_key(pos->first).first;
        }

        iterator erase(iterator first, iterator last) {
            auto it{first};
            while (it != last) {
                it = this->erase_by_key(it->first).first;
                if (it == this->end())
                    return this->end();
            }
            return last;
        }

        size_type erase(const Key& key) {
            return this->erase_by_key(key).second ? 1 : 0;
        }

        void swap(unordered_map& other) noexcept {
            std::swap(this->hash_, other.hash_);
            std::swap(this->key_eq_, other.key_eq_);
            std::swap(this->table_, other.table_);
            std::swap(this->size_, other.size_);
            std::swap(this->size_index_, other.size_index_);
        }

    public:
        T& at(const Key& key) {
            size_type hash{hash_(key) % this->table_.size()};
            auto elem{this->find_by_hash(key, hash)};
            if (elem == this->end())
                throw std::out_of_range("_Map_base::at");
            return elem->second;
        }

        const T& at(const Key& key) const {
            size_type hash{hash_(key) % this->table_.size()};
            auto elem{this->find_by_hash(key, hash)};
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
            size_type hash{hash_(key) % this->table_.size()};
            return this->find_by_hash(key, hash);
        }

        const_iterator find(const Key& key) const {
            size_type hash{hash_(key) % this->table_.size()};
            return this->find_by_hash(key, hash);
        }

    public:
        hasher hash_function() const {
            return this->hash_;
        }

        key_equal key_eq() const {
            return this->key_eq_;
        }

    private:
        iterator find_by_hash(const key_type &key, size_type hash) {
            if (this->empty())
                return this->end();

            auto &bucket{this->table_[hash]};
            auto table_it{this->table_.begin() + hash};
            auto b_end{bucket.end()};

            for (auto b_it = bucket.begin(); b_it != b_end; ++b_it)
                if (this->key_eq_(key, b_it->first))
                    return iterator(table_it, b_it, this->table_.end());

            return this->end();
        }

        const_iterator find_by_hash(const key_type &key, size_type hash) const {
            if (this->empty())
                return this->end();

            auto &bucket{this->table_[hash]};
            auto table_it{this->table_.begin() + hash};
            auto b_end{bucket.end()};

            for (auto b_it = bucket.begin(); b_it != b_end; ++b_it)
                if (this->key_eq_(key, b_it->first))
                    return const_iterator(table_it, b_it, this->table_.end());

            return this->end();
        }

        std::pair<iterator, bool> erase_by_key(const key_type &key) {
            if (this->empty())
                return { this->end(), false };

            size_type hashed_key{hash_(key) % table_size::size[this->size_index_]};

            auto &bucket{this->table_[hashed_key]};
            if (bucket.empty())
                return { this->end(), false };
            
            auto prev_it{bucket.before_begin()};
            for (auto b_it = bucket.begin(); b_it != bucket.end(); ++b_it) {
                if (key_eq_(b_it->first, key)) {
                    auto next_it{iterator(this->table_.begin() + hashed_key,
                                            b_it, this->table_.end()) + 1};
                    bucket.erase_after(prev_it);
                    this->size_--;
                    return { next_it, true };
                }
                prev_it++;
            }
            return { this->end(), false };
        }

        double get_alpha() const {
            return this->size_ / static_cast<double>(table_size::size[this->size_index_]);
        }

        void resize() {
            size_type new_map_size{table_size::size[++this->size_index_]};
            table_type new_table(new_map_size);

            for (auto &bucket : this->table_) {
                for (auto &&[key, value]: bucket) {
                    size_type key_hash_mod = hash_(key) % new_map_size;
                    new_table[key_hash_mod].emplace_front(std::move(key), std::move(value));
                }
            }

            this->table_ = std::move(new_table);
        }

        void update_alpha() noexcept {
            if (this->get_alpha() >= table_size::kResizeAlpha)
                this->resize();
        }

    private:
        hasher hash_;
        key_equal key_eq_;
        table_type table_;
        size_type size_{};
        size_type size_index_{};
};
} // namespace s21

#endif  // UNORDERED_MAP_H
