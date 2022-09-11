#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //allocator
#include <limits> //std::numeric_limits
#include <exception> //exception
#include <stdexcept> //length_error, out_of_range
#include "iterator.hpp" //ft::reverse_iterator, ft::distance
#include "type_traits.hpp" //ft::enable_if, ft::is_integral
#include "algorithm.hpp" //ft::equal

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
    explicit vector_iterator(pointer ptr = NULL) : _p(ptr) {};

    template<typename Iter>
    vector_iterator(const vector_iterator<Iter>& other) : _p(other.base()) {};

    ~vector_iterator() {};

    vector_iterator& operator=(const vector_iterator &x) {
      if (this != &x)
        _p = x._p;
      return *this;
    };

    pointer base() const {
      return _p;
    };

    reference operator*() const {
      return *_p;
    };

    pointer operator->() const {
      return &(operator*());
    };

    vector_iterator& operator++() {
      ++_p;

      return *this;
    };

    vector_iterator operator++(int) {
      vector_iterator ip = *this;
      ++(*this);

      return ip;
    };

    vector_iterator& operator--() {
      --_p;

      return *this;
    };

    vector_iterator operator--(int) {
      vector_iterator ip = *this;
      --(*this);

      return ip;
    };

    bool operator==(const vector_iterator<T>& other) const { return (_p == other._p); };
    bool operator!=(const vector_iterator<T>& other) const { return (_p != other._p); };
    bool operator< (const vector_iterator<T>& other) const { return (_p <  other._p); };
    bool operator> (const vector_iterator<T>& other) const { return (_p >  other._p); };
    bool operator<=(const vector_iterator<T>& other) const { return (_p <= other._p); };
    bool operator>=(const vector_iterator<T>& other) const { return (_p >= other._p); };

    vector_iterator& operator+=(difference_type n) {
      _p += n;

      return *this;
    };

    vector_iterator operator+ (difference_type n) const {
      return vector_iterator(base()+n);
    };

    vector_iterator& operator-=(difference_type n) {
      _p -= n;

      return *this;
    };

    vector_iterator operator- (difference_type n) const {
      return vector_iterator(base()-n);
    };

    reference operator[](difference_type n) {
      return _p[n];
    };
  }; //vector_iterator

/*  NON-MEMBER OPERATOR OVERLOADS  */
  template< class Iter >
  vector_iterator<Iter> operator+ (
    typename vector_iterator<Iter>::difference_type n,
    const vector_iterator<Iter>& it) {
      return vector_iterator<Iter>(it.base() + n);
  }

  template< class Iterator >
  typename vector_iterator<Iterator>::difference_type operator- (
    const vector_iterator<Iterator>& lhs,
    const vector_iterator<Iterator>& rhs) {
      return lhs.base() - rhs.base();
  }

/*  CONST_ITERATOR (OPERATOR) ITERATOR  */
  template< class Iterator_L, class Iterator_R >
    typename vector_iterator<Iterator_L>::difference_type operator- (
      const vector_iterator<Iterator_L>& lhs,
      const vector_iterator<Iterator_R>& rhs) {
        return lhs.base() - rhs.base();
  }

  template< class Iterator_L, class Iterator_R >
  bool operator==(const vector_iterator<Iterator_L>& lhs,
                  const vector_iterator<Iterator_R>& rhs) {
    return lhs.base() == rhs.base();
  };

  template< class Iterator_L, class Iterator_R >
  bool operator!=(const vector_iterator<Iterator_L>& lhs,
                  const vector_iterator<Iterator_R>& rhs) {
    return lhs.base() != rhs.base();
  };

  template< class Iterator_L, class Iterator_R >
  bool operator< (const vector_iterator<Iterator_L>& lhs,
                  const vector_iterator<Iterator_R>& rhs) {
    return lhs.base() < rhs.base();
  };

  template< class Iterator_L, class Iterator_R >
  bool operator> (const vector_iterator<Iterator_L>& lhs,
                  const vector_iterator<Iterator_R>& rhs) {
    return lhs.base() > rhs.base();
  };

  template< class Iterator_L, class Iterator_R >
  bool operator<=(const vector_iterator<Iterator_L>& lhs,
                  const vector_iterator<Iterator_R>& rhs) {
    return lhs.base() <= rhs.base();
  };

  template< class Iterator_L, class Iterator_R >
  bool operator>=(const vector_iterator<Iterator_L>& lhs,
                  const vector_iterator<Iterator_R>& rhs) {
    return lhs.base() >= rhs.base();
  };

  template <class T, class Allocator = std::allocator<T> >
  class vector {
  public:
    /* Member types */
    typedef Allocator                                       allocator_type;
    typedef typename allocator_type::value_type             value_type;
    typedef typename allocator_type::size_type              size_type;
    typedef typename allocator_type::difference_type        difference_type;
    typedef typename allocator_type::pointer                pointer;
    typedef typename allocator_type::const_pointer          const_pointer;
    typedef typename allocator_type::reference              reference;
    typedef typename allocator_type::const_reference        const_reference;
    typedef typename ft::vector_iterator<value_type>        iterator;
    typedef typename ft::vector_iterator<const value_type>  const_iterator;
    typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

  private:
    allocator_type    _allocator;
    pointer           _start;
    pointer           _end;
    size_type         _size;
    size_type         _capacity;

  public:
    explicit vector (const allocator_type& alloc = allocator_type())
    : _allocator(alloc),
      _start(NULL),
      _end(_start),
      _size(0),
      _capacity(0) {};

    explicit vector (size_type n, const value_type& value = value_type(),
      const allocator_type& alloc = allocator_type())
      : _allocator(alloc) {
        _size = n;
        _capacity = _size;
        _start = _allocator.allocate(_capacity);
        _end = _start;

        while (n--)
          _allocator.construct(_end++, value);
      };

    template <class InputIterator>
    vector (InputIterator first, InputIterator last,
      const allocator_type& alloc = allocator_type(),
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 )
      : _allocator(alloc) {
        difference_type diff = ft::distance(first, last);
        _size = diff;
        _capacity = cal_cap(_size, 0);
        _start = _allocator.allocate(_capacity);
        _end = _start;

        while (diff--) {
          _allocator.construct(_end++, *first++);
        }
      };

    vector (const vector& x)
    : _allocator(x._allocator) {
      difference_type n = x._size;

      _start = _allocator.allocate(n);
      _end = _start;
      _size = x._size;
      _capacity = x._capacity;

      pointer temp = x._start;

      while (n--) {
        _allocator.construct(_end++, *temp++);
      }
    };

    ~vector() {
      _allocator.deallocate(_start, _capacity);
      _start = NULL;
      _end = NULL;
      _size = 0;
      _capacity = 0;
    };

    vector& operator=( const vector& other ) {
      if (this != &other) {
        clear();

        for(const_iterator it = other.begin(); it != other.end(); it++)
          push_back(*it);

        _size = other._size;
        _capacity = other._size;
      }

      return *this;
    };

    void assign( size_type count, const T& value ) {
      clear();

      _start = _allocator.allocate(count);
      _end = _start;
      _size = count;
      if (_capacity < count)
        _capacity = count;

      while (count--) {
        _allocator.construct(_end++, value);
      }
    };

    template< class InputIt >
    void assign( InputIt first, InputIt last,
      typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 ) {
        size_type diff = ft::distance(first, last);

        clear();

        _start = _allocator.allocate(diff);
        _end = _start;
        _size = diff;
        if (_capacity < diff)
          _capacity = diff;

        while (first != last) {
          _allocator.construct(_end++, *first++);
      }
    };

    allocator_type get_allocator() const {
      return _allocator;
    };

    reference at( size_type pos ) {
      if (!(pos < _size))
        throw std::out_of_range("vector");

      return _start[pos];
    };

    const_reference at( size_type pos ) const {
      if (!(pos < _size))
        throw std::out_of_range("vector");

      return _start[pos];
    };

    reference operator[]( size_type pos ) {
      return _start[pos];
    };

    const_reference operator[]( size_type pos ) const {
      return _start[pos];
    };

    // Calling front on an empty container is undefined.
    reference front() {
      return *(_start);
    };

    const_reference front() const {
      return *(_start);
    };
    
    reference back() {
      return *(_end - 1);
    };

    const_reference back() const {
      return *(_end - 1);
    };

    pointer data() {
      return _start;
    };

    const_pointer data() const {
      return _start;
    };

    /* iterators */
    iterator begin() {
      return iterator(_start);
    };

    const_iterator begin() const {
      return const_iterator(_start);
    };

    iterator end() {
      return iterator(_end);
    };

    const_iterator end() const {
      return const_iterator(_end);
    };

    reverse_iterator rbegin() {
      return reverse_iterator(end());
    };

    const_reverse_iterator rbegin() const {
      return const_reverse_iterator(end());
    };

    reverse_iterator rend() {
      return reverse_iterator(begin());
    };

    const_reverse_iterator rend() const {
      return const_reverse_iterator(begin());
    };

    /* capacity */
    bool empty() const {
      return _start == _end;
    };

    size_type size() const {
      return _size;
    };

    size_type max_size() const {
      return std::numeric_limits<size_type>::max() / sizeof(value_type);
    };

    void reserve( size_type new_cap ) {
      if (new_cap > max_size())
        throw std::length_error("reserve");
        
      if (new_cap < _capacity)
        return;

      pointer temp = _allocator.allocate(new_cap);

      for (size_type i = 0; i < _size; i++) {
        _allocator.construct(&temp[i], _start[i]);
        _allocator.destroy(_start);
      }

      _allocator.deallocate(_start, _capacity);

      _start = temp;
      _end = _start + _size;
      _capacity = new_cap;
    };

    size_type capacity() const {
      return _capacity;
    };

    /* Modifiers */
    void clear() {
      while (_size--)
        _allocator.destroy(--_end);
      _size = 0;
    };

    iterator insert( iterator pos, const T& value ) {
      if (_size + 1 > max_size())
        throw (std::length_error("insert"));

      size_type pos_idx = &(*pos) - _start;

      if (_capacity >= _size + 1) {
        for (size_type i = 0; i < _size - pos_idx; i++)
          _allocator.construct(_end - i, *(_end - i - 1));
        _allocator.construct(_start + pos_idx, value);
        _size = _size + 1;
        _end = _end + 1;
      } else {
        pointer new_start;
        pointer new_end;
        size_type new_capacity;

        new_capacity = cal_cap(_size + 1, _capacity);
        new_start = _allocator.allocate(new_capacity);
        new_end = new_start + _size + 1;

        for (size_type i = 0; i < pos_idx; i++)
          _allocator.construct(new_start + i, *(_start + i));

        for (size_type j = 0; j < 1; j++)
          _allocator.construct(new_start + pos_idx + j, value);

        for (size_type m = 0; m < (_size - pos_idx); m++)
          _allocator.construct(new_end - m - 1, *(_end - m - 1));

        for (size_type n = 0; n < _size; n++)
          _allocator.destroy(_start + n);
        _allocator.deallocate(_start, _capacity);

        _start = new_start;
        _end = new_end;
        _size = _size + 1;
        _capacity = new_capacity;
      }

      return (iterator(_start + pos_idx));
    };

    void insert( iterator pos, size_type count, const T& value ) {
      if (count == 0)
        return ;

      if (_size + count > max_size())
        throw (std::length_error("insert"));

      size_type pos_idx = &(*pos) - _start;

      if (_capacity >= _size + count) {
        pointer temp_end = _end + count;

        if (_capacity - _size >= count) {
          for (size_type i = 0; i < size() - pos_idx; i++)
            _allocator.construct(_end - i + (count - 1), *(_end - i - 1));
          _end += count;
          while (count) {
            _allocator.construct(&(*pos) + (count - 1), value);
            count--;
            _size++;
          }
        }
        _end = temp_end;
      } else {
        pointer new_start;
        pointer new_end;
        size_type new_capacity;

        new_capacity = cal_cap(_size + count, _capacity);
        new_start = _allocator.allocate(new_capacity);
        new_end = new_start + _size + count;

        for (size_type i = 0; i < pos_idx; i++)
          _allocator.construct(new_start + i, *(_start + i));

        for (size_type j = 0; j < count; j++)
          _allocator.construct(new_start + pos_idx + j, value);

        for (size_type m = 0; m < _size - pos_idx; m++)
          _allocator.construct(new_end - m - 1, *(_end - m - 1));

        for (size_type n = 0; n < _size; n++)
          _allocator.destroy(_start + n);
        _allocator.deallocate(_start, _capacity);

        _start = new_start;
        _end = new_end;
        _size = _size + count;
        _capacity = new_capacity;
      }
    };

    template< class InputIt >
    void insert( iterator pos, InputIt first, InputIt last,
      typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 ) {
      size_type count = ft::distance(first, last);

      if (count == 0)
        return ;

      if (count > max_size())
        throw (std::length_error("insert"));

      size_type pos_idx = &(*pos) - _start;

      if (_capacity - _size >= count) {
        for (size_type i = 0; i < _size - pos_idx; i++)
          _allocator.construct(_end - i + (count - 1), *(_end - i - 1));
        _end += count;
        _size += count;
        while (count--)
          _allocator.construct(&(*pos) + count, *--last);
      } else {
        pointer new_start;
        pointer new_end;
        size_type new_capacity;

        new_capacity = (_size + count) * 2;
        new_start = _allocator.allocate(new_capacity);
        new_end = new_start + _size + count;

        for (size_type i = 0; i < pos_idx; i++)
          _allocator.construct(new_start + i, *(_start + i));

        for (size_type j = 0; j < count; j++)
          _allocator.construct(new_start + pos_idx + j, *first++);

        for (size_type m = 0; m < (_size - pos_idx); m++)
          _allocator.construct(new_end - m - 1, *(_end - m - 1));

        for (size_type n = 0; n < _size; n++)
          _allocator.destroy(_start + n);
        _allocator.deallocate(_start, _capacity);

        _start = new_start;
        _end = new_end;
        _size = _size + count;
        _capacity = new_capacity;
      }
    };

    iterator erase( iterator pos ) {
      size_type i = 0;
      for (; pos + i != end(); i++) {
        _allocator.destroy(pos.base() + i);
        _allocator.construct(pos.base() + i, *(pos + i + 1));
      }
      _allocator.destroy(pos.base() + i);
      --_size;
      --_end;
      return pos;
    };

    iterator erase( iterator first, iterator last ) {
      difference_type diff = ft::distance(first, last);
      iterator temp_first = first;

      while (diff--) {
        erase(first);
      }

      return temp_first;
    };

    void push_back( const T& value ) {
      if (_size == 0) {
        reserve(1);
      } else if (_start + _size == _end) {
        reserve(cal_cap(_size, _capacity));
      }

      _allocator.construct(_end++, value);
      _size++;
      _capacity = cal_cap(_size, _capacity);
    };

    void pop_back() {
      _allocator.destroy(--_end);
      _size--;
    };

    void resize( size_type count, T value = T() ) {
      if (count > max_size())
        throw (std::length_error("resize"));

      if (_size == 0)
        return;

      int range = count - _size;

      if (range >= 0) {
        insert(end(), range, value);
      } else {
        while (range++ < 0) {
          _end--;
          _allocator.destroy(_end);
          _size--;
        }
      }
      _capacity = cal_cap(_size, _capacity);
    };

    void swap( vector& other ) {
      pointer start_temp = other._start;
      pointer end_temp = other._end;
      size_type size_temp = other._size;
      size_type capacity_temp = other._capacity;

      other._start = _start;
      other._end = _end;
      other._size = _size;
      other._capacity = _capacity;

      _start = start_temp;
      _end = end_temp;
      _size = size_temp;
      _capacity = capacity_temp;
    };

  private:
    size_type cal_cap(size_type size, size_type capacity) {
      if (capacity == 0)
        capacity = 1;

      if (size >= capacity)
        capacity *= 2;

      if (size > capacity)
        capacity = size;

      return capacity;
    };
  };
} //namespace

/* operator */
template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return !(operator==(lhs, rhs));
}

template< class T, class Alloc >
bool operator< ( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class T, class Alloc >
bool operator> ( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && operator!=(lhs, rhs);
}

template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return !(operator>(lhs, rhs));
}

template< class T, class Alloc >
bool operator>=( const ft::vector<T>& lhs, const ft::vector<T,Alloc>& rhs ) {
  return !(operator<(lhs, rhs));
}

#endif