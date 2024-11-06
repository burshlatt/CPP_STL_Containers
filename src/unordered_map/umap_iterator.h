#ifndef UMAP_ITERATOR_H
#define UMAP_ITERATOR_H

namespace s21 {
template <typename TableIterator, typename BucketIterator>
class umap_iterator {
public:
    using pointer   = typename BucketIterator::pointer;
    using reference = typename BucketIterator::reference;

    umap_iterator() = default;

    explicit umap_iterator(TableIterator it) : table_(it) {}

    umap_iterator(TableIterator main, BucketIterator bucket, TableIterator end) :
        table_(main),
        bucket_(bucket),
        end_(end)
    {}
    
    ~umap_iterator() = default;

    reference operator*() const { return *bucket_; }
    pointer operator->() const { return bucket_.operator->(); }

    bool operator==(const umap_iterator &other) const { return table_ == other.table_; }
    bool operator!=(const umap_iterator &other) const { return table_ != other.table_; }

    umap_iterator &operator++() {
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

    umap_iterator operator++(int) {
        umap_iterator temp{*this};
        ++(*this);
        return temp;
    }

    umap_iterator operator+(int move_count) {
        umap_iterator temp{*this};
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

#endif  // UMAP_ITERATOR_H
