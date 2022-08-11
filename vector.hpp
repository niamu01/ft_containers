#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //allocator
#include <limits> //std::numeric_limits
#include <exception> //exception
#include <stdexcept> //length_error, out_of_range
#include "iterator.hpp" //ft::reverse_iterator
#include "type_traits.hpp" //ft::enable_if, ft::is_integral

// #include <iterator> //random_access_iterator_tag
// #include <type_traits> //std::enable_if, std::is_integral -> delete

namespace ft {
  template <typename T>
  class vector_iterator {
  public:
    typedef typename ft::iterator_traits<T *>::value_type           value_type;
    typedef typename ft::iterator_traits<T *>::difference_type      difference_type;
    typedef typename ft::iterator_traits<T *>::pointer              pointer;
    typedef typename ft::iterator_traits<T *>::reference            reference;
    typedef typename ft::iterator_traits<T *>::iterator_category    iterator_category;

  private:
    pointer _p;

  public:
    explicit vector_iterator(pointer ptr = nullptr) : _p(ptr) {};

    template<typename Iter>
    vector_iterator(const vector_iterator<Iter>& other) : _p(other.base()) {};

    ~vector_iterator() {};

    pointer base() const {
      return _p;
    }

    reference operator*() {
      return *_p;
    };
    
    //legacy_random_access_iterator
    vector_iterator& operator+=(difference_type n) {
      _p += n;

      return (*this->_p);
    };

    vector_iterator operator+(difference_type n) {
//      value_type temp = *_p;
//      temp += n;

      return (vector_iterator(base()+n));
    };

    vector_iterator& operator-=(difference_type n) {
      return (this->*_p -= n);
    };

    vector_iterator operator-(difference_type n) {
//      return (this->*_p - n);
      return (vector_iterator(base()-n));
    };

    difference_type operator-(value_type i) {
      return (this->*_p - i);
    };

    reference operator[](difference_type n) {
      return (this->_p[n]);
    };

    bool operator<(value_type b) {
      return (0 < b - this->*_p);
    };

    bool operator>(value_type b) {
      return (this->*_p > b);
    };

    bool operator<=(value_type b) {
      return (!(this->*_p > b));
    };

    bool operator>=(value_type b) {
      return (!(0 < b - this->*_p));
    };

    //legacy_bidirectional_iterator
    vector_iterator& operator--() {
      --this->_p;

      return *this;
    };

    // const vector_iterator& operator--() {
    //   --this->_p;

    //   return *_p;
    // };

    vector_iterator operator--(value_type) {
      vector_iterator ip = *this;
      --this->_p;

      return ip;
    };

    //legacy_forward_iterator
    vector_iterator& operator++() {
      ++this->_p;

      return *this;
    };

    vector_iterator operator++(value_type) {
      vector_iterator ip = *this;
      ++this->_p;

      return ip;
    };

//    // *a--
//    reference operator--(pointer) {
//      pointer ip = this->_p;
//      --this->_p;
//
//      return *ip;
//    };
//
//    //*i++
//    reference operator++(pointer) {
//      pointer ip = this->_p;
//      ++this->_p;
//
//      return *ip;
//    };

    //legacy_input_iterator
    bool operator!=(const vector_iterator<T>& other) {
      return (!(this->_p == other._p));
    }

    value_type operator*(reference) {
      return (this->_p);
    }
    
    pointer operator->() const {
      return &(operator*());
    };
    
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
    typedef typename ft::reverse_iterator<vector_iterator<value_type> > reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  private:
    allocator_type _allocator;
    pointer _start;
    pointer _end;
    size_type _size;
    size_type _capacity;

  public:
    explicit vector (const allocator_type& alloc = allocator_type())
    : _allocator(alloc),
      _start(nullptr),
      _end(_start),
      _size(0),
      _capacity(0) {};

    explicit vector (size_type n, const value_type& val = value_type(),
      const allocator_type& alloc = allocator_type())
      : _allocator(alloc) {
        _start = this->_allocator.allocate(_capacity);
        _end = _start;
        _size = n;
        _capacity = cal_cap(_size);

        while (n--)
          this->_allocator.construct(_end++, val);
      };

    template <class InputIterator>
      vector (InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type())
        : _allocator(alloc) {
          _start = this->_allocator.allocate(_capacity);
          _end = _start;

          size_type n = distance(first, last);
          _size = n;
          _capacity = cal_cap(_size);

          while (n--) {
            this->_allocator.construct(_end++, *first++);
          }
        };

      //(4) copy constructor
    vector (const vector& x);

    ~vector() {
      this->_allocator.deallocate(this->_start, _capacity);
      this->_start = nullptr;
      this->_end = nullptr;
      this->_size = 0;
      this->_capacity = 0;
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
      this->_end = this->_start;
      this->_size = count;
      if (this->_capacity < count)
        this->_capacity = count;

      while (count--) {
        this->_allocator.construct(this->_end++, value);
      }
    };

    template< class InputIt >
    void assign( InputIt first, InputIt last,
      typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 ) {
        size_type count = distance(first, last);
        // if (_capacity < count)
        this->clear();

        this->_start = this->_allocator.allocate(count);
        this->_end = this->_start;
        this->_size = count;
        if (this->_capacity < count)
          this->_capacity = count;

        while (!(first == last)) {
          this->_allocator.construct(this->_end++, *first++);
      }
    };

    allocator_type get_allocator() const {
      return (this->_allocator);
    };

    reference at( size_type pos ) {
      if (!(pos < this->_size))
        throw std::out_of_range("vector");

      return (this->_start[pos]);
    };

    const_reference at( size_type pos ) const {
      if (!(pos < this->_size))
        throw std::out_of_range("vector");

      return (this->_start[pos]);
    };

    reference operator[]( size_type pos ) {
      return (this->_start[pos]);
    };

    const_reference operator[]( size_type pos ) const {
      return (this->_start[pos]);
    };

    // Calling front on an empty container is undefined.
    reference front() {
      return *(this->_start);
    };

    const_reference front() const {
      return *(this->_start);
    };
    
    reference back() {
      return *(this->_end - 1);
    };

    const_reference back() const {
      return *(this->_end);
    };

    T* data() {
      return (this->_start);
    };

    const T* data() const {
      return (this->_start);
    };

    /* iterators */
    iterator begin() {
      return iterator(this->_start);
    };

    const_iterator begin() const {
      return const_iterator(this->_start);
    };

    iterator end() {
      return iterator(this->_end);
    };

    const_iterator end() const {
      return const_iterator(this->_end);
    };

    reverse_iterator rbegin() {
      return reverse_iterator(this->end());
    };

    const_reverse_iterator rbegin() const {
      return const_reverse_iterator(this->end());
    };

    reverse_iterator rend() {
      return reverse_iterator(this->begin());
    };

    const_reverse_iterator rend() const {
      return const_reverse_iterator(this->begin());
    };

    /* capacity */
    bool empty() const {
      return (this->_start == this->_end);
    };

    size_type size() const {
      return (this->_size);
    };

    size_type max_size() const {
      return (std::numeric_limits<size_type>::max() / sizeof(value_type));
    };

    void reserve( size_type new_cap ) {
      if (new_cap > this->max_size())
        throw std::length_error("vector");
        
      if (new_cap <= this->_capacity) {
        //deallocate?
        // this->_capacity = new_cap;
        return;
      }

      pointer temp = _allocator.allocate(new_cap);

      for (size_type i = 0; i < this->_size; i++) {
        _allocator.construct(&temp[i], _start[i]);
        _allocator.destroy(this->_start);
      }

      _allocator.deallocate(_start, _capacity);

      _start = temp;
      _end = _start + _size;
      _capacity = new_cap;
    };

    size_type capacity() const {
      return (_capacity);
    };

    /* Modifiers */
    void clear() {
      while (--this->_size)
        _allocator.destroy(--this->_end);
    };

    // insert value before pos
    // return iterator pointing to the inserted value
    iterator insert( iterator pos, const T& value ) {
      this->_allocator.destroy(pos); //@
      this->_allocator.construct(pos, value); //@
      
      this->_size++;
      this->_end++;
      this->_capacity = cal_cap(_size);

      return (this->_start + pos); //@
    };

    // insert count copies of the value before pos
    // return iterator pointing to the first element inserted
    // or return pos if count == 0
    void insert( iterator pos, size_type count, const T& value ) {
      if (this->_size + count > this->_capacity)
        this->reserve(cal_cap(this->_size));

      while (count--)
        this->insert(pos++, value);
    };

    // insert first~last before pos
    // return iterator pointing to the first element inserted
    // or return pos if first == last
    template< class InputIt >
    void insert( iterator pos, InputIt first, InputIt last,
      typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 ) {
        size_type n = this->distance(first, last);

        if (this->_size + n > this->_capacity)
          this->reserve(cal_cap(this->_size));
        
        while (first != last)
          insert(pos++, *first++);
    };

    //erase first ~ last - 1
    /* return Iterator following the last removed element.
    If pos refers to the last element, then the end() iterator is returned.
    If last==end() prior to removal, then the updated end() iterator is returned.
    If [first, last) is an empty range, then last is returned.
    */
    iterator erase( iterator pos ) {
      size_type i = 0;
      for (; pos + i != this->end(); i++) {
        this->_allocator.destroy(pos.base() + i);
        this->_allocator.construct(pos.base() + i, *(pos + i + 1));
      }
      this->_allocator.destroy(pos.base() + i);
      --this->_size;
      --this->_end;
      return ((pos)); //_start + pos or _start + pos - i
//      size_type pos_index = &(*pos) - _start;
//      this->_allocator.destroy(&(*pos));
//
//      for (size_type i = 0; i < _size - pos_index; ++i) {
//        this->_allocator.construct(_start + pos_index + i, *(_start + pos_index + i + 1));
//        this->_allocator.destroy(_start + pos_index + i + 1);
//      }
//      --this->_size;
//      --this->_end;
//
//      return iterator(_start + pos_index);
    };

    iterator erase( iterator first, iterator last ) {
      iterator temp_first = first;

      while (temp_first != last) {
        this->erase(temp_first);
        temp_first++;
      }

      return (first + _start);
    };

    /*
    Calling push_back will cause reallocation (when size()+1 > capacity()),
    so some implementations also throw std::length_error
    when push_back causes a reallocation that would exceed max_size
    (due to implicitly calling an equivalent of -(size()+1)).
    */
    void push_back( const T& value ) {
      if (this->_size == 0) {
        this->reserve(1);
      } else if (this->_start + this->_size == this->_end) {
        this->reserve(cal_cap(_size));
      }

      this->_allocator.construct(this->_end++, value);
      this->_size++;
      this->_capacity = cal_cap(_size);
    };

    void pop_back() {
      this->_allocator.destroy(--this->_end);
      this->_size--;
    };

    void resize( size_type count, T value = T() ) {
      int range = count - this->_capacity;

      if (range >= 0) {
        while (range--) {
          this->_allocator.allocate(1);
          this->_allocator.construct(this->_start + count + range, value);
          this->_size++;
        }
      } else {
        while (range++ < 0) {
          this->_allocator.destroy(this->_end);
          this->_end--;
          this->_size--; 
        }
      }
    };

    void swap( vector& other ) {
      pointer start_temp = other._start;
      pointer end_temp = other._end;
      size_type size_temp = other._size;
      size_type capacity_temp = other._capacity;

      other._start = this->_start;
      other._end = this->_end;
      other._size = this->_size;
      other._capacity = this->_capacity;

      this->_start = start_temp;
      this->_end = end_temp;
      this->_size = size_temp;
      this->_capacity = capacity_temp;
    };

  private:
    size_type distance(iterator first, iterator second) {
      size_type ret;

      while (first != second) {
        first++;
        ret++;
      }

      return ret;
    };

    size_type cal_cap(size_type size) {
      size_type ret = 1;

      while (ret < size)
        ret *= 2;

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

#endif