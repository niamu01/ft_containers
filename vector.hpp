#include <memory> //allocator
#include <limits> //std::numeric_limits
#include <exception> //exception
#include <stdexcept> //length_error, out_of_range
#include <iterator> //random_access_iterator_tag

//@ : make private util func

namespace ft {

  template <typename T>
  class vector_iterator {
  public:
    typedef T                                 value_type;
    typedef ptrdiff_t                         difference_type;
    typedef T*                                pointer;
    typedef T&                                reference;
    typedef std::random_access_iterator_tag   iterator_category;

  private:
    value_type _a;
    reference _r;
    pointer _p;

    /*
     * i, a, b => It
     * r => a value of It&
     * n => int of difference type
     */

  public:
    //legacy_random_access_iterator
    reference operator+=(difference_type n) {
      difference_type m = n;

      if (m >= 0)
        while (m--)
          ++_r;
      else
        while (m++)
          --_r;

      return (*this->_r);
    };

    value_type operator+(difference_type n) {
      value_type temp = this->_a;
      temp += n;

      return (temp);
    };

    reference operator-=(difference_type n) {
      return (this->_r -= n);
    };

    value_type operator-(difference_type n) {
      return (this->_a - n);
    };

    difference_type operator-(value_type i) {
      return (this->_a - i);
    };

    reference operator[](difference_type n) {
      return (this->_r[n]);
    };

    bool operator<(value_type b) {
      return (0 < b - this->_a);
    };

    bool operator>(value_type b) {
      return (this->_a > b);
    };

    bool operator<=(value_type b) {
      return (!(this->_a > b));
    };

    bool operator>=(value_type b) {
      return (!(0 < b - this->_a));
    };

    //legacy_bidirectional_iterator
    reference operator--() {
      --this->_a;

      return *this;
    };

    reference operator--(value_type) const {
      value_type temp = this->_a;
      --this->_a;

      return temp;
    };

//    // *a--
//    reference operator--(pointer) {
//      reference rp = --(*this->_a);
//
//      return (rp);
//      return (*this->_a--); //?
//    };

    //legacy_forward_iterator
    value_type operator++() {
      value_type ip = this->_a;
      ++this->_a;

      return ip;
    };

//    //*i++
//    reference operator++(pointer) {
//      return (*this->_a++); //?
//    };

  };

  template <class T, class Allocator = std::allocator<T> >
  class vector {
  public:
    /* Member types */
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::value_type      value_type;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename ft::vector_iterator<value_type> iterator;
    typedef typename ft::vector_iterator<const value_type> const_iterator;

  private:
    allocator_type _allocator;
    pointer _start;
    pointer _end;
    pointer _capacity;

  public:
    /* Member functions */

    explicit vector (const allocator_type& alloc = allocator_type())
    : _allocator(alloc),
      _start(nullptr),
      _end(nullptr),
      _capacity(nullptr) {};

    explicit vector (size_type n, const value_type& val = value_type(),
      const allocator_type& alloc = allocator_type())
      : _allocator(alloc) {
        _start = this->_allocator.allocate(n);

        while (n--) {
          this->_allocator.construct(_start, val);
          this->_start++;
        }

        this->_end = this->_start;
        this->_capacity = this->_start;
      };

    template <class InputIterator>
      vector (InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type())
        : _allocator(alloc) {
          size_type n;
          n = cal_size(first, last);

          this->_start = this->_allocator.allocate(n);
          while (n--) {
            this->_allocator.construct(_start++, *first++);
          }
          this->_end = this->_start;
          this->_capacity = this->_start;
        };

      //(4) copy constructor
    vector (const vector& x);

    ~vector() {
      this->clear();
      this->_allocator.deallocate(this->_start, this->size()); //capacity
    };

    // May throw implementation-defined exceptions. <- ?
    
    vector& operator=( const vector& other ) {
      if (this != &other) {
        this->clear();
        this->insert(this->_start, other.begin(), other.end());
      }

      return *this;
    };

    void assign( size_type count, const T& value ) {
      this->clear();

      this->_start = this->_allocator.allocate(count);
      this->end = this->_start;
      this->_capacity = this->_start + count;

      while (count--) {
        this->_allocator.construct(this->_end++, value);
      }
    };

    template< class InputIt >
    void assign( InputIt first, InputIt last ) {
      size_type n;
      n = cal_size(first, last);

      this->clear();

      this->_start = this->_allocator.allocate(n);
      this->_end = this->_start;
      this->_capacity = this->_start + n;

      while (n--) {
        this->_allocator.construct(this->_end++, *first++);
      }
      // capacity == n 일때 capacity값?
    };

    allocator_type get_allocator() const {
      return (this->_allocator);
    };

    reference at( size_type pos ) {
      if (!(pos < size()))
        throw std::out_of_range("vector");

      return (this->_start[pos]);
    };

    const_reference at( size_type pos ) const {
      if (!(pos < size()))
        throw std::out_of_range("vector");

      return (this->_start[pos]);
    };

    reference operator[]( size_type pos ) {
      return (this->_start[pos]);
    };

    const_reference operator[]( size_type pos ) const {
      return (this->_start[pos]);
    };
    /*
      at과 operator[]의 차이는 range를 체크하는 것
    */

    // Calling front on an empty container is undefined.
    reference front() {
      return (this->_start);
    };

    const_reference front() const {
      return (this->_start);
    };
    
    reference back() {
      return (--this->_end);
    };

    const_reference back() const {
      return (--this->_end);
    };

    T* data() {
      return (this->_start);
    };

    const T* data() const {
      return (this->_start);
    };

    /* iterators */
    //return iterator
    iterator begin() {
      return (this->_start);
    };

    const_iterator begin() const {
      return (this->_start);
    };

    iterator end() {
      return (this->_end);
    };

    const_iterator end() const {
      return (this->_end);
    };

    iterator rbegin() {
      return reverse_iterator(this->end());
    };

    const_iterator rbegin() const {
      return reverse_iterator(this->end());
    };

    iterator rend() {
      return reverse_iterator(this->begin());
    };

    const_iterator rend() const {
      return reverse_iterator(this->begin());
    };

    /* capacity */
    bool empty() const {
      if (this->_start == this->_end)
        return true;
      return false;
    };

    size_type size() const {
      size_type vec_size;
      pointer vec_start = _start;

      for (vec_size = 0; this->_start == this->_end; vec_start++)
        vec_size++;

      return vec_size;
    };

    size_type max_size() const {
      return (std::numeric_limits<size_type>::max() / sizeof(value_type));
    };

    void reserve( size_type new_cap ) {
      if (new_cap > this->max_size())
        throw std::length_error("vector");
        
      if (new_cap <= this->size()) //capacity
        return;

      pointer temp = _allocator.allocate(new_cap);

      for (int i = 0; i < size(); i++) {
        _allocator.construct(&temp[i], _start[i]);
        _allocator.destroy(this->_start);
      }

      _allocator.deallocate(_start, this->size()); //capacity

      _start = temp;
      _end = _start + size();
      _capacity = _start + new_cap;
    };

    size_type capacity() const {
      size_type vec_capacity;
      pointer vec_start = _start;

      for (vec_capacity = 0; this->_start == this->_capacity; vec_start++)
        vec_capacity++;

      return vec_capacity;
    };
    /* Modifiers */
    void clear() {
      while (this->_start != this->_end)
        _allocator.destroy(--this->_end);
    };

    // insert value before pos
    // return iterator pointing to the inserted value
    iterator insert( iterator pos, const T& value ) {
        this->_allocator.destroy(pos);
        this->_allocator.deallocate(pos);
        this->_allocator.construct(pos, value);

      return (this->_start + pos);
    };

    // insert count copies of the value before pos
    // return iterator pointing to the first element inserted
    // or return pos if count == 0
    void insert( iterator pos, size_type count, const T& value ) {
      if (this->size() + count > this->_capacity)
        this->reserve(this->size() + count);

      while (count--)
        this->insert(pos++, value);
    };

    // insert first~last before pos
    // return iterator pointing to the first element inserted
    // or return pos if first == last
    template< class InputIt >
    void insert( iterator pos, InputIt first, InputIt last ) {
      size_type n;
      n = this->cal_size(first, last);

      if (this->size() + n > this->_capacity)
        this->reserve(this->size() + n);
      
      while (first != last)
        insert(pos++, first++);
    };

    //erase first ~ last - 1
    /* return Iterator following the last removed element.
    If pos refers to the last element, then the end() iterator is returned.
    If last==end() prior to removal, then the updated end() iterator is returned.
    If [first, last) is an empty range, then last is returned.
    */
    iterator erase( iterator pos ) {
      size_type pos_index = _start - pos;
      this->_allocator.destroy(pos);

      for (size_type i = 0; i < this->size() - pos_index; ++i) {
        this->_allocator.construct();
        this->_allocator.destroy();
      }
      // this->_allocator.deallocate(this->_end); -> capacity, alloc 유지
      --this->_end;

      return ;//pos+start
    };

    iterator erase( iterator first, iterator last ) {
      while (first != last) {
        this->erase(first);
        first++;
      }
      return (first + _start); //first바뀌기전
    };

    /*
    Calling push_back will cause reallocation (when size()+1 > capacity()),
    so some implementations also throw std::length_error
    when push_back causes a reallocation that would exceed max_size
    (due to implicitly calling an equivalent of -(size()+1)).
    */
    void push_back( const T& value ) {
      if (this->size() == 0) {
        this->reserve(1);
      } else if (this->_capacity == this->_end) {
        this->reserve(this->size() * 2); //capacity
      }

      this->_allocator.construct(this->_end++, value);
    };

    void pop_back() {
      this->_allocator.destroy(--this->_end);
    };


    void resize( size_type count, T value = T() ) {
      size_type range = this->size() - count;

      if (range > 0) {
        while (range--)
          this->_allocator.destroy(this->_end--);
      } else {
//        this->reserve(this->size() + count);
        while (count--)
          this->_allocator.construct(this->size() + count, value);
      }
    };

    void swap( vector& other ) {
      pointer start_temp = other._start;
      pointer end_temp = other._end;
      pointer capacity_temp = other._capacity;

      other.start = this->_start;
      other.end = this->_end;
      other.capacity = this->_capacity;

      this->_start = start_temp;
      this->_end = end_temp;
      this->_capacity = capacity_temp;
    };


  private:
    size_type cal_size(iterator first, iterator second) {
      size_type ret;

      while (first != second) {
        first++;
        ret++;
      }

      return ret;
    };
  };
}

// @
//template< class T, class Alloc >
//void std::swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
//  lhs.swap(rhs);
//}

/* operator */
template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return (lhs == rhs);
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return (lhs != rhs);
}

template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return (lhs < rhs);
}

template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return (lhs <= rhs);
}

template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return (lhs > rhs);
}

template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return (lhs >= rhs);
}
