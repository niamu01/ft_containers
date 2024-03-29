#ifndef MAP_HPP
#define MAP_HPP

#include "_tree.hpp" //ft::_tree

namespace ft {
	template<
    class     Key,
    class     Value,
    class     Compare = ft::less<Key>,
    class     Allocator = std::allocator <ft::pair<const Key, Value> >
  >
	class map {
  public:
    typedef Key                                                                           key_type;
    typedef Value                                                                         mapped_type;
    typedef ft::pair<const key_type, mapped_type>                                         value_type;
    typedef ft::use_first<value_type>                                                     use_first;
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
    public:
      typedef bool            result_type;
      typedef const key_type  first_argument_type;
      typedef mapped_type     second_argument_type;

    public:
      key_compare comp;
      value_compare() : comp() {};

    public:
      bool operator()( const value_type& lhs, const value_type& rhs ) const {
        return (comp(lhs.first, rhs.first));
      };
    }; //class value_compare

  public:
			typedef typename ft::tree_node<value_type>					                                  node_type;
			typedef typename ft::_tree<value_type, use_first, value_compare>		                  tree_type;

  private:
    allocator_type     _allocator;
    key_compare        _comp;
    tree_type          _tree;

  public:
    explicit map( const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type() )
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
    : _allocator(other._allocator),
      _comp(other._comp),
      _tree() {
      *this = other;
    };

    ~map() {};

    map& operator=( const map& other ) {
      if (this != &other)
        _tree.copy(other._tree);
      return *this;
    };

    iterator begin() { return iterator(_tree.tree_min(_tree.get_root())); };
    const_iterator begin() const { return const_iterator(_tree.tree_min(_tree.get_root())); };
    iterator end() { return iterator(_tree.get_nil()); };
    const_iterator end() const { return const_iterator(_tree.get_nil()); };
    reverse_iterator rbegin() { return reverse_iterator(_tree.get_nil()); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree.get_nil()); };
    reverse_iterator rend() { return reverse_iterator(_tree.tree_min(_tree.get_root())); };
    const_reverse_iterator rend() const { return const_reverse_iterator(_tree.tree_min(_tree.get_root())); };

    bool empty() const          { return _tree.empty();    };
    size_type size() const      { return _tree.size();     };
    size_type max_size() const  { return _tree.max_size(); };

    mapped_type& operator[]( const Key& key ) {
      return (*(_tree.insert(ft::make_pair(key, mapped_type())).first))._value->second;
    };

  /*  INSERT  */
    pair<iterator, bool> insert(const value_type& value) {
      ft::pair<node_type*, bool> res = _tree.insert(value);
      return (ft::make_pair(iterator(res.first), res.second));
    };

    iterator insert(iterator hint, const value_type& val) {
      return (iterator(_tree.insert(val, hint.base()).first));
    };

    template <class InputIt>
    void insert(InputIt first, InputIt last,
                typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0) {
      while (first != last)
        _tree.insert(*first++);
    };

  /*  ERASE  */
    void erase(iterator pos) {
      _tree.erase(pos.base());
    };

    void erase(iterator first, iterator last) {
      while (first != last)
        erase(first++);
    };

    size_type erase(const key_type& key) {
      return (_tree.erase(_tree.find(value_type(key, mapped_type()))));
    };

    void swap( map& other ) { _tree.swap(other._tree); };
    void clear() { _tree.clear(); };

    key_compare    key_comp()    const { return key_compare(); };
    value_compare  value_comp()  const { return value_compare(); };

    iterator        find( const Key& key )        { return iterator(_tree.find(value_type(key, mapped_type()))); };
    const_iterator  find( const Key& key ) const  { return const_iterator(_tree.find(value_type(key, mapped_type()))); };

    size_type count( const Key& key ) const {
      if (_tree.find(value_type(key, mapped_type()))->_value != NULL)
        return 1;
      return 0;
    };

    iterator        lower_bound(const key_type& key)       { return iterator(_tree.lower_bound(value_type(key, mapped_type()))); };
    const_iterator  lower_bound(const key_type& key) const { return const_iterator(_tree.lower_bound(value_type(key, mapped_type()))); };
    iterator        upper_bound(const key_type& key)       { return iterator(_tree.upper_bound(value_type(key, mapped_type()))); };
    const_iterator  upper_bound(const key_type& key) const { return const_iterator(_tree.upper_bound(value_type(key, mapped_type()))); };

    ft::pair<iterator,iterator>             equal_range( const Key& key )       { return ft::make_pair(lower_bound(key), upper_bound(key)); };
    ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const { return ft::make_pair(lower_bound(key), upper_bound(key)); };

    allocator_type get_allocator() const { return _allocator; };

  }; //class map

  /* NON-MEMBER FUNCTIONS */
  template< class Key, class T, class Compare, class Alloc >
  bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
    //same number, position of elements
    return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
    return !(operator==(lhs, rhs));
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator< ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  };

	template< class Key, class T, class Compare, class Alloc >
	bool operator> (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return rhs < lhs;
	};

  template< class Key, class T, class Compare, class Alloc >
  bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
    return !(operator>(lhs, rhs));
  };

  template< class Key, class T, class Compare, class Alloc >
  bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
    return !(operator<(lhs, rhs));
  };

  template < class Key, class T, class Compare, class Alloc >
  void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
    x.swap(y);
  };
} //namespace

#endif
