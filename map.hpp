#ifndef MAP_HPP
#define MAP_HPP

#include <functional> //std::less
#include "utility.hpp" //ft::pair, ft::make_pair, use_first, ft::rebind
#include "iterator.hpp" //ft::reverse_iterator, ft::distance
#include "type_traits.hpp" //ft::enable_if, ft::is_integral

#include "_tree.hpp" //ft::_tree

namespace ft {
//  template <typename T> // T -> pair
//  class map_iterator {
//  public:
//
//  }; //map_iterator

  template<
    class     Key,
    class     Value,
    class     Compare = std::less<Key>,
    class     Allocator = std::allocator <ft::pair<const Key, Value> >
    // typename  ExtractKey = ft::use_first<ft::pair<Key, Value> >,
    // bool      bMutableIterators = true, //map: true, set: false
    // bool      bUniqueKeys = true //map,set: true, multi: false
  >
  class map {
  public:
    typedef Key                                                                           key_type;
    typedef Value                                                                         mapped_type;
    typedef ft::pair<const key_type, mapped_type>                                         value_type;
    typedef Compare                                                                       key_compare;

    typedef Allocator                                                                     allocator_type;
    typedef typename allocator_type::reference                                            reference;
    typedef typename allocator_type::const_reference                                      const_reference;
    typedef typename allocator_type::pointer                                              pointer;
    typedef typename allocator_type::const_pointer                                        const_pointer;
    typedef typename allocator_type::size_type                                            size_type;
    typedef typename allocator_type::difference_type                                      difference_type;

    typedef typename ft::tree_iterator<value_type, value_type*, value_type&>              iterator;
    typedef typename ft::tree_iterator<value_type, const value_type*, const value_type&>  const_iterator;
    typedef typename ft::reverse_iterator<iterator>                                       reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>                                 const_reverse_iterator;

  public:
  /* MEMBER CLASS */
    class value_compare {
    friend class map; //todo

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
    }; //class value_compare

  public:
    typedef typename ft::tree_node<value_type>                                            node_type;
    typedef typename ft::_tree<value_type, value_compare>                                 tree_type;

  private:
    ft::rebind<Node>    _allocator;
    Compare             _comp;
    tree_type           _tree;

  public:
    explicit map( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
    : _allocator(alloc),
      _comp(comp),
      _tree() {};

    template< class InputIt >
    map( InputIt first, InputIt last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type(),
      typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0 )
      : _allocator(alloc),
        _comp(comp),
        _tree() {
        insert(first, last);
    };

    map( const map& other )
    : _allocator(other.alloc),
      _comp(other.comp),
      _tree() {
      *this = other;
    };

    ~map() {};

    map& operator=( const map& other ) {
      if (this != &other)
        //copy
      return *this;
    };

    iterator begin()                      { return _tree.begin(); };
    const_iterator begin() const          { return _tree.begin(); };
    iterator end()                        { return _tree.end();   };
    const_iterator end() const            { return _tree.end();   };
    reverse_iterator rbegin()             { return _tree.end();   };
    const_reverse_iterator rbegin() const { return _tree.end();   };
    reverse_iterator rend()               { return _tree.begin(); };
    const_reverse_iterator rend() const   { return _tree.begin(); };

    bool empty() const      { return _tree.empty(); };
    size_type size() const  { return _tree.size();  };
    size_type max_size() const { return; }; //todo: max_size in... tree...?

    mapped_type& operator[]( const Key& key ) {
      return _tree.insert(ft::make_pair(key, mapped_type())).first; //todo: ->second? *().value->second?
    };

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

    void swap( map& other ) { _tree.swap(other._tree); };
    void clear() { _tree.clear(); };

    key_compare key_comp() const { return key_compare(); };
    ft::map::value_compare value_comp() const { return value_compare(); };

    iterator find( const Key& key ) {
      return iterator(_tree.find(value_type(key, mapped_type())));
    };

    const_iterator find( const Key& key ) const {
      return const_iterator(_tree.find(value_type(key, mapped_type())));
    };

    size_type count( const Key& key ) const {
      if (_tree.find(value_type(key, mapped_type())) != NULL) //todo: ->value?
        return 1;
      return 0;
    };

    iterator lower_bound( const Key& key )              { return iterator(_tree.lower_bound(key)); };
    const_iterator lower_bound( const Key& key ) const  { return iterator(_tree.lower_bound(key)); };
    iterator upper_bound( const Key& key )              { return iterator(_tree.upper_bound(key)); };
    const_iterator upper_bound( const Key& key ) const  { return iterator(_tree.upper_bound(key)); };

    //todo: key == value_type(key, mapped_type())

    ft::pair<iterator,iterator> equal_range( const Key& key ) {
      return ft::make_pair(lower_bound(key), upper_bound(key));
    };
    ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
      return ft::make_pair(lower_bound(key), upper_bound(key));
    };

    allocator_type get_allocator() const { return _allocator; };

//    reference at( const Key& key ) {};
//    const reference at( const Key& key ) const {};

  }; //class map

  /* NON-MEMBER FUNCTIONS */
  template< class Key, class T, class Compare, class Alloc >
  bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    //same number, position of elements
    return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
  }

  template< class Key, class T, class Compare, class Alloc >
  bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return !(operator==(lhs, rhs));
  }

  template< class Key, class T, class Compare, class Alloc >
  bool operator< ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }

  template< class Key, class T, class Compare, class Alloc >
  bool operator> ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return !(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
  } //todo: add condition

  template< class Key, class T, class Compare, class Alloc >
  bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return !(operator>(lhs, rhs));
  }

  template< class Key, class T, class Compare, class Alloc >
  bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
    return !(operator<(lhs, rhs));
  }

  template < class Key, class T, class Compare, class Alloc >
  void swap(ft::map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
    x.swap(y);
  }
} //namespace

#endif
