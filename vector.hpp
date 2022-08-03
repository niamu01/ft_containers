#include <memory>
#include <limits> //std::numeric_limits
#include <exception> //exception
#include <stdexcept>  //length_error, out_of_range
#include "iterator.hpp"

//@ : make private util func

namespace ft { 
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

/*
[ ]  iterators_traits - <iterator> 헤더 내에 구현된 템플릿 클래스
[ ]  reverse_iterator
    // typedef implementation-defined                   iterator;
    // typedef implementation-defined                   const_iterator;
    // typedef ft::reverse_iterator<iterator>           reverse_iterator;
    // typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

[ ]  enable_if SFINAE
    // template< bool B, class T = void >
    // struct enable_if
    
[ ]  is_integral

[ ]  equal and/or lexicographical_compare
    
[ ]  std::pair
[ ]  std::make_pair
*/

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
        this->_capacity = this->_start; //@ 생성할때니까 2배수로 맞춰주기
      };

    template <class InputIterator>
      vector (InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type())
        : _allocator(alloc) {
          size_type n;
          n = cal_size(first, second);

          this->_start = this->_allocator.allocate(n);
          while (n--) {
            this->_allocator.construct(_start++, *first++)
          }
          this->_end = this->_start;
          this->_capacity = this->_start; //@ 생성할때니까 2배수로 맞춰주기
        };

      //(4) copy constructor
    vector (const vector& x);

    ~vector() {
      this->clear();
      this->_allocator.deallocate(this->_start, this->_capacity);
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
        this->_allocator.construct(this->_end++, *first++)
      }
      // capacity == n 일때 capacity값?
    };

    allocator_type get_allocator() const {
      return (this->_allocator);
    };

    reference at( size_type pos ) {
      while (pos--)
        this->_start++;

      if (!*_start)
        throw std::out_of_range("vector");

      return (this->_start);
    };

    const_reference at( size_type pos ) const;

    reference operator[]( size_type pos );

    const_reference operator[]( size_type pos ) const;
    /*
    pos - position of the element to return
    return - Reference to the requested element.
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

      for (vec_size = 0; this->_start == this->_end; this->_start++)
        vec_size++;

      return vec_size;
    };

    size_type max_size() const {
      return (std::numeric_limits<size_type>::max() / sizeof(value_type));
    };

    void reserve( size_type new_cap ) {
      if (new_cap > max_size)
        throw std::length_error("vector");
        
      if (new_cap <= this->_capacity)
        return;

      pointer temp = _allocator.allocate(new_cap);

      for (int i = 0; i < size(); i++) {
        _allocator.construct(&temp[i], _start[i]);
        _allocator.destroy(this->_start);
      }

      _allocator.deallocate(_start, _capacity);

      _start = temp;
      _end = _start + size();
      _capacity = new_cap;
    };

    size_type capacity() const {
      size_type vec_capacity;

      for (vec_capacity = 0; this->_start == this->_capacity; this->_start++)
        vec_capacity++;

      return vec_capacity;
    };
    /* Modifiers */
    void clear() {
      // this->erase(this->_start, this->_capacity); //@
      while (this->_start != this->_end)
        _allocator.destroy(--(this->_end));
    };

    // insert value before pos
    // return iterator pointing to the inserted value
    iterator insert( iterator pos, const T& value ) {
      this->insert(pos, 1, value);

      return (this->_start + pos);
    };

    // insert count copies of the value before pos
    // return iterator pointing to the first element inserted
    // or return pos if count == 0
    void insert( iterator pos, size_type count, const T& value );

    // insert first~last before pos
    // return iterator pointing to the first element inserted
    // or return pos if first == last
    template< class InputIt >
    void insert( iterator pos, InputIt first, InputIt last ) {
      //add capacity malloc
      // size_type n; //first~last
      // this->reserve(this->size() + n);
      
      for (size_type i = 0; first == last; pos++, first++) {
        insert(pos, first);1
      }
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
        this->_allocator.construct()
        this->_allocator.destroy()
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

    void push_back( const T& value );
    /*
    Calling push_back will cause reallocation (when size()+1 > capacity()), 
    so some implementations also throw std::length_error 
    when push_back causes a reallocation that would exceed max_size 
    (due to implicitly calling an equivalent of -(size()+1)).
    */
    
    void pop_back();

    void resize( size_type count, T value = T() ) {
      if (this->size() >= count) {
        // this->erase(count);
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

    /* operator */
    template< class T, class Alloc >
    bool operator==( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
      return (lhs == rhs);
    };

    template< class T, class Alloc >
    bool operator!=( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
      return (lhs != rhs);
    };

    template< class T, class Alloc >
    bool operator<( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
      return (lhs < rhs);
    };

    template< class T, class Alloc >
    bool operator<=( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
      return (lhs <= rhs);
    };

    template< class T, class Alloc >
    bool operator>( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
      return (lhs > rhs);
    };

    template< class T, class Alloc >
    bool operator>=( const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs ) {
      return (lhs >= rhs);
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

template< class T, class Alloc >
void std::swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
  lhs.swap(rhs);
}