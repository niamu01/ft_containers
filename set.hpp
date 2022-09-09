#ifndef SET_HPP
#define SET_HPP

#include "_tree.hpp"

namespace ft {
  template<
    class Key,
    class Compare = ft::less<Key>,
    class Allocator = std::allocator<Key>
  >
  class set {
  public:
    typedef Key                                               key_type;
    typedef Key                                               value_type;
    typedef typename std::size_t                              size_type;
    typedef typename std::ptrdiff_t                           difference_type;
    typedef Compare                                           key_compare;
    typedef Compare                                           value_compare;
    typedef Allocator                                         allocator_type;
    typedef value_type&                                       reference;
    typedef const value_type&                                 const_reference;
    typedef value_type*                                       pointer;
    typedef const value_type*                                 const_pointer;
    typedef typename ft::tree_iterator<value_type>            iterator;
    typedef typename ft::tree_iterator<value_type>            const_iterator;
    typedef typename ft::reverse_iterator<iterator>           reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>     const_reverse_iterator;
    typedef ft::tree_node<value_type>				              	  node_type;
    typedef ft::_tree<value_type, value_compare>		          tree_type;

  private:
    allocator_type      _allocator;
    key_compare         _comp;
    tree_type           _tree;

  public:
    explicit set( const key_compare& comp = key_compare(),
                  const allocator_type& alloc = allocator_type() )
                  : _allocator(alloc),
                    _comp(comp),
                    _tree() {};

    template< class InputIt >
    set( InputIt first, InputIt last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type(),
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

    allocator_type get_allocator() const { return (_allocator); };

    iterator begin() { return iterator(_tree.tree_min(_tree.get_root())); };
    const_iterator begin() const { return const_iterator(_tree.tree_min(_tree.get_root())); };
    iterator end() { return iterator(_tree.get_nil()); };
    const_iterator end() const { return const_iterator(_tree.get_nil()); };
    reverse_iterator rbegin() { return reverse_iterator(_tree.get_nil()); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree.get_nil()); };
    reverse_iterator rend() { return reverse_iterator(_tree.tree_min(_tree.get_root())); };
    const_reverse_iterator rend() const { return const_reverse_iterator(_tree.tree_min(_tree.get_root())); };

    bool empty() const { return ( _tree.empty()); };
    size_type size() const { return ( _tree.size()); };
    size_type max_size() const { return ( _tree.max_size()); };

    void clear() {
      _tree.clear();
    };

    pair<iterator, bool> insert(const value_type& val) {
      ft::pair<node_type*, bool> res = _tree.insert(val);
      return (ft::make_pair(iterator(res.first), res.second));
    };

    iterator insert(iterator position, const value_type& val) {
      return (iterator(_tree.insert(val, position.base()).first));
    };

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
      while (first != last)
        _tree.insert(*first++);
    };

    void erase(iterator position) {
      _tree.erase(position.base());
    };

    size_type erase(const key_type& k) {
      return (_tree.erase(_tree.find(value_type(k))));
    };

    void erase(iterator first, iterator last) {
      while (first != last)
        erase(first++);
    };

    void swap(set& x) {
      _tree.swap(x._tree);
    };

    size_type count(const key_type& k) const {
      if (_tree.find(value_type(k))->_value != NULL)
        return 1;
      return 0;
    };

    iterator find(const key_type& k) {
      return (iterator(_tree.find(value_type(k))));
    };

    const_iterator find(const key_type& k) const {
      return (const_iterator(_tree.find(value_type(k))));
    };


    pair<iterator, iterator> equal_range(const key_type& k) {
      return (ft::make_pair(lower_bound(k), upper_bound(k)));
    };

    pair<const_iterator, const_iterator> equal_range(const key_type& x) const {
      return(ft::make_pair<const_iterator, const_iterator>(lower_bound(x), upper_bound(x)));
    };

    iterator lower_bound(const key_type& k) {
      return (iterator(_tree.lower_bound(value_type(k))));
    };

    const_iterator lower_bound(const key_type& k) const {
      return (const_iterator(_tree.lower_bound(value_type(k))));
    };

    iterator upper_bound(const key_type& k) {
      return (iterator(_tree.upper_bound(value_type(k))));
    };
    const_iterator upper_bound(const key_type& k) const {
      return (const_iterator(_tree.upper_bound(value_type(k))));
    };

    key_compare key_comp() const { return (key_compare()); };
    value_compare value_comp() const { return (value_compare()); };

  }; // class set

  /*  NON-MEMBER FUNCTIONS  */
	template <class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return (!(lhs == rhs));
	};

	template <class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return (!(rhs < lhs));
	};

	template <class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return (rhs < lhs);
	};

	template <class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return (!(lhs < rhs));
	};

	template <class Key, class Compare, class Alloc>
	void swap(set<Key, Compare, Alloc>& x, set<Key, Compare, Alloc>& y) {
		x.swap(y);
	};
  
}; // namespace ft

#endif
