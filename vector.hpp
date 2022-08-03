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

    //constructor
      //(1) empty container constructor (default constructor)
    explicit vector (const allocator_type& alloc = allocator_type())
    : _allocator(alloc),
      _start(nullptr),
      _end(nullptr),
      _capacity(nullptr) {};

      //(2) fill constructor
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

      //(3) range constructor
    template <class InputIterator>
      vector (InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type())
        : _allocator(alloc) {
          size_type n;
          //@ get size ( first <-> last )

          this->_start = this->_allocator.allocate(n);
          while (n--) {
            this->_allocator.construct(_start++, *first++)
          }
          this->_end = this->_start;
          this->_capacity = this->_start; //@ 생성할때니까 2배수로 맞춰주기
        };

      //(4) copy constructor
    vector (const vector& x);

    //destructor
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

    void assign( size_type count, const T& value ){
      this->clear();

      this->_start = this->_allocator.allocate(count);
      this->_capacity = this->_start + count;
      this->end = this->_start;

      while (count--) {
        this->_alloc.construct(this->_end++, value);
      }
      //capacity < count ?
    };

    template< class InputIt >
    void assign( InputIt first, InputIt last );

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
      return (this->--_end);
    };

    const_reference back() const {
      return (this->--_end);
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

    //new_cap은 아무숫자나 들어올 수 있음
    void reserve( size_type new_cap ) {
      if (new_cap > max_size)
        throw std::length_error("vector");
        
      if (new_cap <= this->_capacity)
        return;

      ft::vector<> temp;
      //vec 새로 만들 수 없으면 privete 다시 세팅해주기
      temp->_allocator.allocate(new_cap);
      temp->_start = this->_start;
      temp->_end = this->_end;
      temp->_capacity = new_cap;

      while (this->size--) {
        temp->_allocator.construct(this->_start);
        temp->_allocator.destroy(this->_start);
        _start++;
      }
      
      temp->_allocator.deallocate(this->_start, this->_capacity);
      this = temp;
    };

    size_type capacity() const {
      size_type vec_capacity;

      for (vec_capacity = 0; this->_start == this->_capacity; this->_start++)
        vec_capacity++;

      return vec_capacity;
    };
    /* Modifiers */
    void clear() {
      this->erase(this->_start, this->_capacity);
      // while (this->_start != this->_end)
      //   _allocator.destroy(--(this->_end));
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

    template< class InputIt >
    void insert( iterator pos, InputIt first, InputIt last ) {
      //add capacity malloc
      for (size_type i = 0; first == last; pos++, first++) {
        insert(pos, first);
      }
    };
    // insert first~last before pos
    // return iterator pointing to the first element inserted
    // or return pos if first == last

    iterator erase( iterator pos );
    iterator erase( iterator first, iterator last );
    //erase first ~ last - 1
    /* return Iterator following the last removed element.
    If pos refers to the last element, then the end() iterator is returned.
    If last==end() prior to removal, then the updated end() iterator is returned.
    If [first, last) is an empty range, then last is returned.
    */

    // std::vector<T,Allocator>::push_back
    void push_back( const T& value );
    /*
    Calling push_back will cause reallocation (when size()+1 > capacity()), 
    so some implementations also throw std::length_error 
    when push_back causes a reallocation that would exceed max_size 
    (due to implicitly calling an equivalent of reserve(size()+1)).
    */
    
    // std::vector<T,Allocator>::pop_back
    void pop_back();

    // std::vector<T,Allocator>::resize
    void resize( size_type count, T value = T() );

    // std::vector<T,Allocator>::swap
    void swap( vector& other ) {
      // temp = other;
      pointer start_temp = other.capacity;
      pointer end_temp = other.capacity;
      pointer capacity_temp = other.capacity;
      // other = this;
      other.start = this->_start;
      other.end = this->_end;
      other.capacity = this->_capacity;
      //this = temp;
      this->_start = start_temp;
      this->_end = end_temp;
      this->_capacity = capacity_temp;
    };

    /* operator */
    template< class T, class Alloc >
    bool operator==( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator!=( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator<( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator<=( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator>( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );
    template< class T, class Alloc >
    bool operator>=( const std::vector<T,Alloc>& lhs,
                    const std::vector<T,Alloc>& rhs );

  };
}
template< class T, class Alloc >
void std::swap( ft::vector<T,Alloc>& lhs,
          ft::vector<T,Alloc>& rhs ) {
            lhs.swap(rhs);
          }