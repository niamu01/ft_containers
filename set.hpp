#ifndef SET_HPP
#define SET_HPP

#include "_tree.hpp"

namespace ft {
  template<
    class   Key,
    class   Compare = std::less<Key>,
    class   Allocator = std::allocator<Key>
  >
  class set {
  public:
    typedef Key                                                 key_type;
    typedef key_type                                            value_type;
    typedef Compare                                             key_compare;
    typedef key_compare                                         value_compare;
    typedef Allocator                                           allocator_type;
    typedef typename allocator_type::reference                  reference;
    typedef typename allocator_type::const_reference            const_reference;
    typedef typename allocator_type::size_type                  size_type;
    typedef typename allocator_type::difference_type            difference_type;
    typedef typename allocator_type::pointer                    pointer;
    typedef typename allocator_type::const_pointer              const_pointer;

    typedef typename ft::tree_iterator<value_type>              iterator;
    typedef typename ft::tree_iterator<const value_type>        const_iterator;
    typedef typename ft::reverse_iterator<iterator>             reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>       const_reverse_iterator;

    typedef typename ft::tree_node<value_type>                  node_type;
    typedef typename ft::_tree<value_type>                      tree_type;

  private:
    allocator_type     _allocator;
    key_compare        _comp;
    tree_type          _tree;

  public:
    explicit set( const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type() );

    template< class InputIt >
    set( InputIt first, InputIt last,
        const Compare& comp = Compare(),
        const Allocator& alloc = Allocator(),
        typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0 )
        : _allocator(alloc),
          _comp(comp),
          _tree() {
          insert(first, last);
        };

    set( const set& other )
    : _allocator(other._allocator),
      _comp(other._comp),
      _tree() {
      *this = other;
    };

    ~set() {};

    set& operator=( const set& other ) {
      if (this != &other)
        _tree.copy(other._tree);
      return *this;
    };

    allocator_type get_allocator() const { return _allocator; };

    iterator begin() { };
    const_iterator begin() const { };
    iterator end() { };
    const_iterator end() const { };
    reverse_iterator rbegin() { };
    const_reverse_iterator rbegin() const { };
    reverse_iterator rend() { };
    const_reverse_iterator rend() const { };

    bool empty() const          { return _tree.empty();    };
    size_type size() const      { return _tree.size();     };
    size_type max_size() const  { return _tree.max_size(); };

    void clear() { _tree.clear(); };

  /*  INSERT  */
    std::pair<iterator,bool> insert( const value_type& value );
    iterator insert( iterator hint, const value_type& value );
    template< class InputIt >
    void insert( InputIt first, InputIt last );

  /*  ERASE  */
    void erase( iterator pos );
    void erase( iterator first, iterator last );
    size_type erase( const Key& key );

    void swap( set& other ) { _tree.swap(other._tree); };

//todo: 오잉!!
    size_type count( const Key& key ) const {
      if (_tree.find(value_type(key))->value != NULL)
        return 1;
      return 0;
    };

    iterator        find( const Key& key )        { return iterator(_tree.find(value_type(key))); };
    const_iterator  find( const Key& key ) const  { return const_iterator(_tree.find(value_type(key))); };

    std::pair<iterator,iterator> equal_range( const Key& key );
    std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

    iterator        lower_bound(const key_type& key)       { return iterator(_tree.lower_bound(value_type(key))); };
    const_iterator  lower_bound(const key_type& key) const { return const_iterator(_tree.lower_bound(value_type(key))); };
    iterator        upper_bound(const key_type& key)       { return iterator(_tree.upper_bound(value_type(key))); };
    const_iterator  upper_bound(const key_type& key) const { return const_iterator(_tree.upper_bound(value_type(key))); };

    key_compare    key_comp()    const { return key_compare(); };
    value_compare  value_comp()  const { return value_compare(); };

  }; // class set

  /* NON-MEMBER FUNCTIONS */
  template< class Key, class Compare, class Alloc >
  bool operator==( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) {
    return 
  };

  template< class Key, class Compare, class Alloc >
  bool operator!=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) {
    return !(operator==(lhs, rhs));
  };

  template< class Key, class Compare, class Alloc >
  bool operator<( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) {
    return 
  };

  template< class Key, class Compare, class Alloc >
  bool operator>( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) {
    return 
  };

  template< class Key, class Compare, class Alloc >
  bool operator<=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) {
    return !(operator>(lhs, rhs));
  };

  template< class Key, class Compare, class Alloc >
  bool operator>=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) {
    return !(operator<(lhs, rhs));
  };

  template< class Key, class Compare, class Alloc >
  void swap( set<Key,Compare,Alloc>& x, set<Key,Compare,Alloc>& y ) {
    x.swap(y);
  };
} // namespace

#endif