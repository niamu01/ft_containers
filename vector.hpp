#include <memory>
#include "iterator.hpp"
/* std::vector 
T must meet the requirements of 
CopyAssignable and CopyConstructible.	

An allocator that is used to acquire/release 
memory and to construct/destroy the elements in that memory. 
The type must meet the requirements of Allocator. 
The behavior is undefined 
if Allocator::value_type is not the same as T. 
*/
#include <vector>

namespace ft {
  template <class T, class Allocator = std::allocator<T> >
  class vector {
  public:
    /* Member types */
    typedef T                                        value_type;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    // typedef implementation-defined                   iterator;
    // typedef implementation-defined                   const_iterator;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    // typedef std::reverse_iterator<iterator>          reverse_iterator;
    // typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

    /*
    =================std::allocator=================
    멤버 변수
    value_type T : 할당한 데이터 타입을 의미한다.
    pointer T* : 데이터 타입의 포인터형이다.
    const_pointer const T* : 데이터 타입의 상수 포인터형이다.
    reference T& : 데이터 타입의 레퍼런스이다.
    const_reference const T& : 데이터 타입의 상수 레퍼런스이다.
    size_type std::size_t : 할당할 데이터의 개수를 의미한다.
    difference_type std::ptrdiff_t : 두 포인터 간 차이를 의미한다.
    rebind "template struct rebind"
    멤버 함수
    생성자
    파괴자
    address()
    allocate() : 인수 n만큼의 메모리를 할당하고 첫번째 요소의 포인터를 반환한다. 성능 향상을 위해 인수 hint를 집어넣을 수 있다.
    deallocate()
    max_size() : 할당 가능한 최대 크기를 의미한다.
    construct()
    destroy()
    */

    /*
[x]    iterators_traits - <iterator> 헤더 내에 구현된 템플릿 클래스

[x]    reverse_iterator

    enable_if SFINAE
      template< bool B, class T = void >
      struct enable_if;
    
    is_integral

    equal and/or lexicographical_compare
    
    std::pair
    
    std::make_pair

    */




    /* Member functions */

    // std::vector<T,Allocator>::operator=
    // Copy assignment operator. Replaces the contents with a copy of the contents of other.
    vector& operator=( const vector& other ) {
      return *this;
    };
    /*
    other - another container to use as data source
    return - *this
    May throw implementation-defined exceptions.
    */

    // std::vector<T,Allocator>::assign
    void assign( size_type count, const T& value );

    template< class InputIt >
    void assign( InputIt first, InputIt last );

    // std::vector<T,Allocator>::get_allocator
    allocator_type get_allocator() const;

    // std::vector<T,Allocator>::at
    reference at( size_type pos );
    const_reference at( size_type pos ) const;
    // std::vector<T,Allocator>::operator[]
    reference operator[]( size_type pos );
    const_reference operator[]( size_type pos ) const;
    /*
    pos - position of the element to return
    return - Reference to the requested element.
    */

    // std::vector<T,Allocator>::front, back
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    /*
    return - reference to the first element in the container
    Calling front on an empty container is undefined.
    */

    // std::vector<T,Allocator>::data
    T* data();
    const T* data() const;

    /* iterators */
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    iterator rbegin();
    const_iterator rbegin() const;
    iterator rend();
    const_iterator rend() const;

    /* capacity */
    bool empty() const;
    // return - true if the container is empty
    size_type size() const;
    size_type max_size() const;
    // return - Maximum number of elements.

    void reserve( size_type new_cap );
    //if (new_cap > curr_capacity)
    // if (new_cap > max_size) { return std::length_error }

    size_type capacity() const;
    /* Modifiers */
    void clear();

    iterator insert( iterator pos, const T& value );
    // insert value before pos
    // return iterator pointing to the inserted value
    void insert( iterator pos, size_type count, const T& value );
    // insert count copies of the value before pos
    // return iterator pointing to the first element inserted
    // or return pos if count == 0
    template< class InputIt >
    void insert( iterator pos, InputIt first, InputIt last );
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
    void swap( vector& other );

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





    template< class T, class Alloc >
    void swap( std::vector<T,Alloc>& lhs,
              std::vector<T,Alloc>& rhs );

  };
}