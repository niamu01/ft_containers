#ifndef TREE_HPP
#define TREE_HPP

#include <functional> //std::less
#include "utils.hpp" //ft::use_first
#include "utility.hpp" //ft::pair, ft::make_pair

//template <typename Compare, bool = is_empty<Compare>::value>
//struct rb_base_compare_ebo
//{
//protected:
//  rb_base_compare_ebo() : mCompare() {}
//  rb_base_compare_ebo(const Compare& compare) : mCompare(compare) {}
//
//  Compare& get_compare() { return mCompare; }
//  const Compare& get_compare() const { return mCompare; }
//
//  template <typename T>
//  bool compare(const T& lhs, const T& rhs)
//  {
//    return mCompare(lhs, rhs);
//  }
//
//  template <typename T>
//  bool compare(const T& lhs, const T& rhs) const
//  {
//    return mCompare(lhs, rhs);
//  }
//
//private:
//  Compare mCompare;
//};
//
//template <typename Compare>
//struct rb_base_compare_ebo<Compare, true> : private Compare
//{
//protected:
//  rb_base_compare_ebo() {}
//  rb_base_compare_ebo(const Compare& compare) : Compare(compare) {}
//
//  Compare& get_compare() { return *this; }
//  const Compare& get_compare() const { return *this; }
//
//  template <typename T>
//  bool compare(const T& lhs, const T& rhs)
//  {
//    return Compare::operator()(lhs, rhs);
//  }
//
//  template <typename T>
//  bool compare(const T& lhs, const T& rhs) const
//  {
//    return Compare::operator()(lhs, rhs);
//  }
//};

//template <typename Key,
//  typename Pair,
//  typename Compare,
//  typename RBTree
//  >
//struct tree_base<Key, Pair, Compare, ft::use_first<Pair>, true, RBTree> {
//  typedef ft::use_first<Pair> extract_key;
//
//  public:
//  tree_base() {};
//  tree_base(const Compare& compare) {};
//};
//
//struct tree_node {
//  typedef tree_node node_type;
//
//public:
//  node_type*  NodeRight;
//  node_type*  NodeLeft;
//  node_type*  NodeParent;
//  char        color;
//};

template <typename Value>
struct tree_node {
  Value mValue;
  tree_node* left;
  tree_node* right;
  tree_node* parent;
  //char     color;
};

template <typename T, typename Pointer = T*, typename Reference = T&>
struct tree_iterator
{
//  typedef std::size_t                                             size_type;
  typedef std::ptrdiff_t                                          difference_type;
  typedef T                                                       value_type;
  typedef T*                                                      pointer;
  typedef T&                                                      reference;
  typedef tree_node<T>                                            node_type;
  typedef tree_iterator<T, pointer, reference>                    this_type;
  typedef tree_iterator<T, pointer, reference>                    iterator;
  typedef tree_iterator<T, const pointer, const reference>        const_iterator;
//  typedef rbtree_node_base                                        base_node_type;
  typedef std::bidirectional_iterator_tag                         iterator_category;

private: //public:
  node_type* _node;

public:
  explicit tree_iterator(const node_type* pNode = nullptr) : _node(pNode) {};

  tree_iterator(const iterator& other) : _node(other._node) {};

  ~tree_iterator() {};

  tree_iterator& operator=(const iterator& x) {
    if (this != &x)
      _node = x._node;
    return *this;
  };

  node_type* base() const {
    return _node;
  };

  reference operator*() const {
    return (_node->value);
  };

  pointer operator->() const {
    return &(_node->value);
  };

  tree_iterator& operator++() { //if (_node == begin())
    if (_node->right) {
      _node = _node->right;
      while (_node->left)
        _node = _node->left;
    } else {
      if (_node == _node->parent->left)
        _node = _node->parent;
      else {
        while (_node->parent && _node != _node->parent->left)
          _node = _node->parent;
        if (_node->parent)
          _node = _node->parent;
      }
    }
    return (*this);
  };

  tree_iterator operator++(int) {
    tree_iterator temp(*this);
    this->operator++();
    return (temp);
  };

  tree_iterator& operator--() { //if (_node == end())
    if (_node->left) {
      _node = _node->left;
      while (_node->right)
        _node = _node->right;
    } else {
      if (_node == _node->parent->right)
        _node = _node->parent;
      else {
        while (_node->parent && _node != _node->parent->right)
          _node = _node->parent;
        if (_node->parent)
          _node = _node->parent;
      }
    }
  };

  tree_iterator  operator--(int) {
    tree_iterator temp(*this);
    this->operator--();
    return (temp);
  };
}; // tree_iterator

/*  TREE  */

template <typename Key,
  typename Value,
  typename Compare = std::less<Key>,
  typename Allocator = std::allocator<Value>,
  typename ExtractKey = ft::use_first<ft::pair<Key, Value> >,
  bool     bMutableIterators = true, //map: true, set: false
  bool     bUniqueKeys = true //map,set: true, multi: false
  >
class tree {
  //: tree_base<Key, Value, Compare, ExtractKey, bUniqueKeys,
  //tree<Key, Value, Compare, Allocator, ExtractKey, bMutableIterators, bUniqueKeys> >

public:
//  typedef tree<
//          Key, ft::pair<const Key,
//          Value>, Compare, Allocator,
//          ft::use_first<ft::pair<const Key, Value> >,
//          true, true>                                   base_type;
  typedef Key                                           key_type;
  typedef Value                                         value_type;
  typedef ft::pair<const key_type, value_type>          node_type;
  typedef Compare                                       key_compare;
  typedef Allocator                                     allocator_type;
  typedef value_type&                                   reference;
  typedef const value_type&                             const_reference;
  typedef value_type*                                   pointer;
  typedef const value_type*                             const_pointer;
  typedef u_int64_t                                     size_type; //size_t
  typedef ptrdiff_t                                     difference_type;

//  typedef rbtree_node<value_type>           node_type;

//  typedef integral_constant<bool, bUniqueKeys>           has_unique_keys_type;
//  typedef typename tree_node::extract_key                extract_key;

  typedef tree_iterator<value_type>                 iterator;
  typedef tree_iterator<const value_type>           const_iterator;
  typedef std::reverse_iterator<iterator>           reverse_iterator;
  typedef std::reverse_iterator<const_iterator>     const_reverse_iterator;

  template< class U >
  struct rebind {
    typedef std::allocator <U> other;
  };

private: //public:
  struct Node {
    ft::pair<const Key, Value>  _content;
    Node*                       _parent;
    Node*                       _left;
    Node*                       _right;
  };

  Node*             _anchor;
  Node*             _root;
  size_type         _size;
  allocator_type    _allocator;

public:
  tree();

  explicit tree( const Compare& comp,
                const Allocator& alloc = Allocator() );

  template< class InputIt >
  tree( InputIt first, InputIt last,
  const Compare& comp = Compare(),
  const Allocator& alloc = Allocator() );

  tree(const tree& other);

  ~tree();

  tree& operator=(const tree& other);

  allocator_type        get_allocator() const;
//  void                  set_allocator(const allocator_type& allocator);

//element access
  const key_compare& key_comp() const;
  key_compare&       key_comp();

  void swap(tree& x);

// iterators
  iterator        begin();
  const_iterator  begin() const;

  iterator        end();
  const_iterator  end() const;

  reverse_iterator        rbegin();
  const_reverse_iterator  rbegin() const;

  reverse_iterator        rend();
  const_reverse_iterator  rend() const;

public:
  bool      empty() const EA_NOEXCEPT;
  size_type size() const EA_NOEXCEPT;

  template <class... Args>
  insert_return_type emplace(Args&&... args);

  template <class... Args>
  iterator emplace_hint(const_iterator position, Args&&... args);

  // Standard conversion overload to avoid the overhead of mismatched 'pair<const Key, Value>' types.
  template <class P, class = typename eastl::enable_if<eastl::is_constructible<value_type, P&&>::value>::type>
  insert_return_type insert(P&& otherValue);

  // Currently limited to value_type instead of P because it collides with insert(InputIterator, InputIterator).
  // To allow this to work with templated P we need to implement a compile-time specialization for the
  // case that P&& is const_iterator and have that specialization handle insert(InputIterator, InputIterator)
  // instead of insert(InputIterator, InputIterator). Curiously, neither libstdc++ nor libc++
  // implement this function either, which suggests they ran into the same problem I did here
  // and haven't yet resolved it (at least as of March 2014, GCC 4.8.1).
  iterator insert(const_iterator hint, value_type&& value);

  /// map::insert and set::insert return a pair, while multimap::insert and
  /// multiset::insert return an iterator.
  insert_return_type insert(const value_type& value);

  // C++ standard: inserts value if and only if there is no element with
  // key equivalent to the key of t in containers with unique keys; always
  // inserts value in containers with equivalent keys. Always returns the
  // iterator pointing to the element with key equivalent to the key of value.
  // iterator position is a hint pointing to where the insert should start
  // to search. However, there is a potential defect/improvement report on this behaviour:
  // LWG issue #233 (http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1780.html)
  // We follow the same approach as SGI STL/STLPort and use the position as
  // a forced insertion position for the value when possible.
  iterator insert(const_iterator position, const value_type& value);

  void insert(std::initializer_list<value_type> ilist);

  template <typename InputIterator>
  void insert(InputIterator first, InputIterator last);

  // TODO(rparolin):
  // insert_return_type insert(node_type&& nh);
  // iterator insert(const_iterator hint, node_type&& nh);

  template <class M> pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
  template <class M> pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
  template <class M> iterator             insert_or_assign(const_iterator hint, const key_type& k, M&& obj);
  template <class M> iterator             insert_or_assign(const_iterator hint, key_type&& k, M&& obj);

  iterator         erase(const_iterator position);
  iterator         erase(const_iterator first, const_iterator last);
  reverse_iterator erase(const_reverse_iterator position);
  reverse_iterator erase(const_reverse_iterator first, const_reverse_iterator last);

  // For some reason, multiple STL versions make a specialization
  // for erasing an array of key_types. I'm pretty sure we don't
  // need this, but just to be safe we will follow suit.
  // The implementation is trivial. Returns void because the values
  // could well be randomly distributed throughout the tree and thus
  // a return value would be nearly meaningless.
  void erase(const key_type* first, const key_type* last);

  void clear();
  void reset_lose_memory(); // This is a unilateral reset to an initially empty state. No destructors are called, no deallocation occurs.

  iterator       find(const key_type& key);
  const_iterator find(const key_type& key) const;

  /// Implements a find whereby the user supplies a comparison of a different type
  /// than the tree's value_type. A useful case of this is one whereby you have
  /// a container of string objects but want to do searches via passing in char pointers.
  /// The problem is that without this kind of find, you need to do the expensive operation
  /// of converting the char pointer to a string so it can be used as the argument to the
  /// find function.
  ///
  /// Example usage (note that the compare uses string as first type and char* as second):
  ///     set<string> strings;
  ///     strings.find_as("hello", less_2<string, const char*>());
  ///
  template <typename U, typename Compare2> iterator       find_as(const U& u, Compare2 compare2);
  template <typename U, typename Compare2> const_iterator find_as(const U& u, Compare2 compare2) const;

  iterator       lower_bound(const key_type& key);
  const_iterator lower_bound(const key_type& key) const;

  iterator       upper_bound(const key_type& key);
  const_iterator upper_bound(const key_type& key) const;

};

#endif
