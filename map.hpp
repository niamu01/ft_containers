#ifndef MAP_HPP
#define MAP_HPP

#include <functional> //std::less
#include "utility.hpp" //ft::pair, ft::make_pair, use_first, ft::rebind
#include "iterator.hpp" //ft::reverse_iterator, ft::distance

#include "_tree.hpp" //ft::_tree

namespace ft {
  template <typename T> // T -> pair
  class map_iterator {
  public:

  }; //map_iterator

template<
  class     Key,
  class     Value,
  class     Compare = std::less<Key>,
  class     Allocator = std::allocator <ft::pair<const Key, Value> >
  // typename  ExtractKey = ft::use_first<ft::pair<Key, Value> >,
  // bool      bMutableIterators = true, //map: true, set: false
  // bool      bUniqueKeys = true //map,set: true, multi: false
>
class map
: public _tree<Key, ft::pair<const Key, Value>, Compare, Allocator>
  {
  public:
    typedef Key key_type;
    typedef Value mapped_type;
    typedef ft::pair<const key_type, mapped_type> value_type;
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

    typedef typename ft::_tree::Node Node;

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
    ft::rebind<Node>    _allocator;
    Compare             _comp;
    Node*               _root;
    size_type           _size;

  public:
    map();

    explicit map( const Compare& comp, const Allocator& alloc = Allocator() )
    : _comp(comp), _allocator(alloc) {};

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

    ~map() {};

    map& operator=( const map& other );

    allocator_type get_allocator() const {};

    reference at( const Key& key ) {};
    const reference at( const Key& key ) const {};

    reference operator[]( const Key& key ) { return insert(ft::make_pair(key, T())).first->second; };

    iterator begin()                      { return _tree.begin(); };
    const_iterator begin() const          { return _tree.begin(); };
    iterator end()                        { return _tree.end();   };
    const_iterator end() const            { return _tree.end();   };
    reverse_iterator rbegin()             { return _tree.end();   };
    const_reverse_iterator rbegin() const { return _tree.end();   };
    reverse_iterator rend()               { return _tree.begin(); };
    const_reverse_iterator rend() const   { return _tree.begin(); };

    bool empty() const { return (_tree.size() == 0); };

    size_type size() const { return _tree.size(); };

    size_type max_size() const {};

    void clear() { return _tree.clear(); };

    ft::pair<iterator, bool> insert( const value_type& value ) {
      return _tree.insert(value);
    };

    template< class InputIt >
    void insert( InputIt first, InputIt last ) {
      return _tree.insert(first, last);
    };

    void erase( iterator pos ) {
      _tree.erase(pos);
      return;
    };

    void erase( iterator first, iterator last ) {
      _tree.erase(first, last);
      return;
    };

    size_type erase( const Key& key ) {
      if (_tree.erase(find(key)) //check _tree.erase return value
        return 1;
      return 0;
    };

    void swap( map& other ) {};

    size_type count( const Key& key ) const {
      if (_tree.find(key))
        return 1;
      return 0;
    };

    iterator find( const Key& key ) { return _tree.find(key); };

    const_iterator find( const Key& key ) const { return _tree.find(key); };

    ft::pair<iterator,iterator> equal_range( const Key& key ) {};

    ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {};

    iterator lower_bound( const Key& key )              { return _tree.lower_bound(key); };

    const_iterator lower_bound( const Key& key ) const  { return _tree.lower_bound(key); };

    iterator upper_bound( const Key& key )              { return _tree.upper_bound(key); };

    const_iterator upper_bound( const Key& key ) const  { return _tree.upper_bound(key); };

    key_compare key_comp() const { return _comp; };

    ft::map::value_compare value_comp() const {};

  // private:
  //   Compare& get_compare() { return _comp; };
  //   const Compare& get_compare() const { return _comp; };
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
    return;
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator> ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return;
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return !(operator>(lhs, rhs));
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return !(operator<(lhs, rhs));
  };
//  operator==, !=, <, <=, >, >=, std::swap



} //namespace

#endif
