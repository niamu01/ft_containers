#ifndef MAP_HPP
#define MAP_HPP

#include <functional> //std::less
#include "utility.hpp" //ft::pair, ft::make_pair
#include "iterator.hpp" //ft::reverse_iterator, ft::distance

namespace ft {
  template <typename T> // T -> pair
  class map_iterator {
  public:

  }; //map_iterator

  template<
      class Key,
      class T,
      class Compare = std::less <Key>,
      class Allocator = std::allocator <std::pair<const Key, T> >
  >
  class map {
  public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef typename ft::map_iterator<Key, T, Compare, Allocator> iterator;
    typedef typename ft::map_iterator<const Key, T, Compare, Allocator> const_iterator;
    typedef typename ft::reverse_iterator<iterator> reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

    template< class U >
    struct rebind {
      typedef std::allocator <U> other;
    };

  private:
    struct Node {
      ft::pair<const Key, T>  content;
      Node*                   parent;
      Node*                   left;
      Node*                   right;
    };

  public:
  /* MEMBER CLASS */
    class value_compare {
    friend class map;

    public:
      typedef bool            result_type;
      typedef const key_type  first_argument_type;
      typedef mapped_type     second_argument_type;

    protected:
      key_compare comp;
      value_compare( Compare c ) : comp(c) {};

    public:
      bool operator()( const value_type& lhs, const value_type& rhs ) const {
        return (comp(lhs.first, rhs.first));
      };

//        : public binary_function<value_type, value_type, bool> {
//      value_compare(key_compare c);

    }; //class value_compare

  private:
    rebind<Node>            _allocator;
    Compare                 _comp;
    Node*                   _root;
    size_type               _size;


  public:
//     * constructor
    map();1

    explicit map( const Compare& comp,
      const Allocator& alloc = Allocator() )
      : _comp(comp), _allocator(alloc) {

    };

    template< class InputIt >
    map( InputIt first, InputIt last,
      const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
      : _comp(comp), _allocator(alloc) {
        size_type n = ft::distance(first, last);
    };

    map( const map& other ) {
//    std::allocator_traits<allocator_type>::select_on_container_copy_construction(
//        other.get_allocator())
    };

//     * destructor
    ~map() {};
//     * operator=
    map& operator=( const map& other );
//     * get_allocator
    allocator_type get_allocator() const;
//     *
//     * at
//     * operator[]
//     *
//     * begin
//     * end
//     * rbegin
//     * rend
//     *
//     * empty
//     * size
//     * max_size
//     * clear
//     * insert
//     * erase
//     * swap
//     * count
//     * find
//     * equal_range
//     * lower_bound
//     * upper_bound
//     * key_comp
//     * value_comp

  }; //class map

  /* NON-MEMBER FUNCTIONS */
  template< class Key, class T, class Compare, class Alloc >
  bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    //same number, position of elements
    return (lhs == rhs);
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return (!(lhs == rhs));
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator< ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator> ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return
  };
//  operator==, !=, <, <=, >, >=, std::swap



} //namespace

#endif
