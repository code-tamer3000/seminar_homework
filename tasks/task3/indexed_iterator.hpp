template <class Iterator>
class IndexedIterator {
  private: 
    size_t index_;
    Iterator it_;

  public:

    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using reference = typename std::iterator_traits<Iterator>::reference;

    explicit IndexedIterator(Iterator it, size_t index = 0) : it_(it), index_(index) {}
    
    IndexedIterator(const IndexedIterator<Iterator>& other) {
        it_ = other.it_;
        index_ = other.index_;
    }
    
    size_t index() const {
        return index_;
    }
    
    reference operator*() const {
        return *it_;
    }

    reference operator->() const {
        return it_;
    }
    
    IndexedIterator<Iterator>& operator++() {
        ++it_;
        ++index_;
        return *this;
    }
    
    IndexedIterator<Iterator>& operator--() {
        --it_;
        --index_;
        return *this;
    }
    
    IndexedIterator<Iterator> operator++(int) {
        IndexedIterator<Iterator> copy = *this;
        ++it_;
        ++index_;
        return copy;
    }
    
    IndexedIterator<Iterator> operator--(int) {
        IndexedIterator<Iterator> copy = *this;
        --it_;
        --index_;
        return copy;
    }
    
    IndexedIterator<Iterator>& operator+=(int n) {
        std::advance(it_, n);
        index_ += n;
        return *this;
    }
    
    IndexedIterator<Iterator>& operator-=(int n) {
        std::advance(it_, -n);
        index_ -= n;
        return *this;
    }
    
    IndexedIterator<Iterator> operator+(int n) {
        IndexedIterator<Iterator> copy = *this;
        copy += n;
        return copy;
    }
    
    IndexedIterator<Iterator> operator-(int n) {
        IndexedIterator<Iterator> copy = *this;
        copy -= n;
        return copy;
    }
    
    int operator-(const IndexedIterator<Iterator>& other) {
        int dif = it_ - other.it_;
        return dif;
    }
    
    bool operator==(const IndexedIterator<Iterator>& other) const{
        return it_ == other.it_;
    }
    
    bool operator==(const Iterator& other) const{
        return it_ == other;
    }
    
    bool operator!=(const IndexedIterator<Iterator>& other) const {
        return it_ != other.it_;
    }

    bool operator!=(const Iterator& other) const{
        return it_ != other;
    }
};

template <class It>
IndexedIterator<It> CreateIndexedIterator(It iterator, size_t index = 0) {
    return IndexedIterator<It>(iterator, index);
}