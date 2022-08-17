#ifndef MAP_HPP
#define MAP_HPP

#include <functional> //std::less
#include "utility.hpp" //ft::pair, ft::make_pair
#include "iterator.hpp" //ft::reverse_iterator, ft::distance

#include "_tree.hpp" //ft::tree

namespace ft {
  template <typename T> // T -> pair
  class map_iterator {
  public:

  }; //map_iterator

template<
  class     Key,
  class     Value,
  class     Compare = std::less<Key>,
  class     Allocator = std::allocator <std::pair<const Key, Value> >,
  typename  ExtractKey = ft::use_first<ft::pair<Key, Value> >,
  bool      bMutableIterators = true, //map: true, set: false
  bool      bUniqueKeys = true //map,set: true, multi: false
>
class map
: public _tree<Key, ft::pair<const Key, Value>, Compare, Allocator>
  {
  public:
    typedef Key key_type;
    typedef Value mapped_type;
    typedef pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef typename ft::map_iterator<Key, Value, Compare, Allocator> iterator;
    typedef typename ft::map_iterator<const Key, Value, Compare, Allocator> const_iterator;
    typedef typename ft::reverse_iterator<iterator> reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

    template< class U >
    struct rebind {
      typedef std::allocator <U> other;
    };

  private:
    struct Node {
      ft::pair<const Key, Value>  content;
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
    map();

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
//     * at
  reference at( const Key& key );
  const reference at( const Key& key ) const;
//     * operator[]
  reference operator[]( const Key& key );
//     * begin
  iterator begin();
  const_iterator begin() const;
//     * end
  iterator end();
  const_iterator end() const;
//     * rbegin
  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;
//     * rend
  reverse_iterator rend();
  const_reverse_iterator rend() const;
//     * empty
  bool empty() const;
//     * size
  size_type size() const;
//     * max_size
  size_type max_size() const;
//     * clear
  void clear();
//     * insert
  ft::pair<iterator, bool> insert( const value_type& value );

  template< class InputIt >
  void insert( InputIt first, InputIt last );
//     * erase
  void erase( iterator pos );
  void erase( iterator first, iterator last );
  size_type erase( const Key& key );
//     * swap
  void swap( map& other );
//     * count
  size_type count( const Key& key ) const;
//     * find
  iterator find( const Key& key );
  const_iterator find( const Key& key ) const;
//     * equal_range
  ft::pair<iterator,iterator> equal_range( const Key& key );
  ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
//     * lower_bound
  iterator lower_bound( const Key& key );
  const_iterator lower_bound( const Key& key ) const;
//     * upper_bound
  iterator upper_bound( const Key& key );
  const_iterator upper_bound( const Key& key ) const;
//     * key_comp
  key_compare key_comp() const;
//     * value_comp
  ft::map::value_compare value_comp() const;

  private:
    Compare& get_compare() { return _comp; }
    const Compare& get_compare() const { return _comp; }

    template <typename Pair>
    struct use_first
    {
      typedef typename Pair::first_type result_type;

      const result_type& operator()(const Pair& x) const
      { return x.first; }
    };
  }; //class map

  /* NON-MEMBER FUNCTIONS */
  template< class Key, class T, class Compare, class Alloc >
  bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    //same number, position of elements
    return (lhs == rhs);
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return !(operator==(lhs, rhs));
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator< ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return ();
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return ();
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator> ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return ();
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return ();
  };
//  operator==, !=, <, <=, >, >=, std::swap



} //namespace

#endif
