#ifndef CONTAINERS_UNORDERED_MAP_UM_ITERATOR_HPP
#define CONTAINERS_UNORDERED_MAP_UM_ITERATOR_HPP

namespace s21 {
template <typename TableIterator, typename BucketIterator>
class um_iterator {
public:
    using pointer   = typename BucketIterator::pointer;
    using reference = typename BucketIterator::reference;

    um_iterator() = default;

    explicit um_iterator(TableIterator it) : table_(it) {}

    um_iterator(TableIterator main, BucketIterator bucket, TableIterator end) :
        table_(main),
        bucket_(bucket),
        end_(end)
    {}
    
    ~um_iterator() = default;

    reference operator*() const { return *bucket_; }
    pointer operator->() const { return bucket_.operator->(); }

    bool operator==(const um_iterator &other) const { return table_ == other.table_; }
    bool operator!=(const um_iterator &other) const { return table_ != other.table_; }

    um_iterator &operator++() {
        ++bucket_;
        if (bucket_ != table_->end())
            return *this;

        ++table_;
        while (table_->empty()) {
            if (table_ != end_)
                ++table_;
            else
                return *this;
        }

        bucket_ = table_->begin();
        return *this;
    }

    um_iterator operator++(int) {
        um_iterator temp{*this};
        ++(*this);
        return temp;
    }

    um_iterator operator+(int move_count) {
        um_iterator temp{*this};
        for (int i{0}; i < move_count; i++)
            ++temp;
        return temp;
    }

private:
    TableIterator table_;
    BucketIterator bucket_;
    TableIterator end_;
};
} // namespace s21

#endif // CONTAINERS_UNORDERED_MAP_UM_ITERATOR_HPP
