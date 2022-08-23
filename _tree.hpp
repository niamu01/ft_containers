#ifndef _TREE_HPP
#define _TREE_HPP

#include <functional> //std::less
#include "utility.hpp" //ft::pair, ft::make_pair, use_first, rebind
#include "iterator.hpp" //ft::reverse_iterator, ft::distance
#include "type_traits.hpp" //ft::enable_if, ft::is_integral

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

template <typename T>
struct tree_node {
  typedef T value_type;

  value_type      value;
  tree_node*      left;
  tree_node*      right;
  tree_node*      parent;
  //char          color;
};

template <typename T, typename Pointer = T*, typename Reference = T&>
struct tree_iterator {
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
  explicit tree_iterator(const node_type* pNode = NULL) : _node(pNode) {};

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
template <
  typename Key,
  typename Value,
  typename Compare = std::less<Key>,
  typename Allocator = std::allocator<Value>
  >
class _tree {
public:
//  typedef tree<
//          Key, ft::pair<const Key,
//          Value>, Compare, Allocator,
//          ft::use_first<ft::pair<const Key, Value> >,
//          true, true>                                   base_type;
  typedef Key                                           key_type;
  typedef Value                                         value_type;
  typedef tree_node<ft::pair<key_type, value_type> >    node_type;
//  typedef ft::pair<const key_type, value_type>          node_type;
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

public:
  struct Node {
    ft::pair<const Key, Value>  _content;
    Node*                       _parent;
    Node*                       _left;
    Node*                       _right;
    // bool                        _color; //define 0 BLACK, 1 RED
    // int                         _height;
  };

  allocator_type    _allocator;
  key_compare       _compare;
  size_type         _size;
  Node*             _anchor;
  Node*             _root; // == anchor->parent

public:
  explicit _tree( const Compare& comp,
    const Allocator& alloc = Allocator() )
    : _compare(comp),
      _allocator(alloc),
      _size(0),
      _anchor(NULL),
      _root(NULL) {};

  template< class InputIt >
  _tree( InputIt first, InputIt last,
  const Compare& comp = Compare(),
  const Allocator& alloc = Allocator() )
  : _compare(comp),
    _allocator(alloc) {
    _size = ft::distance(first, last);
    _anchor->_left = this->begin();
    _anchor->_right = this->end();
    _anchor->_parent = this->get_root();
    _root = _anchor->_parent;
    };

  _tree(const _tree& other) {
    _compare = other._compare;
    _allocator = other._allocator;
    _size = other._size;
    _anchor = other._anchor; //deep copy
    _root = other._root;
  };

  ~_tree();

  _tree& operator=(const _tree& other);

  allocator_type get_allocator() const {
    return _allocator;
  };

  const key_compare& key_comp() const {
    return _compare;
  };

  key_compare& key_comp() {
    return _compare;
  };

  void swap(_tree& x) {
    _tree temp = this;
    this = x;
    x = temp; //deep
  };

/*  ITERATORS  */
  iterator begin() {
    if (_size == 0)
        return NULL;
    return (iterator(tree_min(_root)));
  };

  const_iterator begin() const {
    if (_size == 0)
      return NULL;
    return (const_iterator(tree_min(_root)));
  };

  iterator end() {
    if (_size == 0)
      return NULL;
    return (++iterator(tree_max(_root)));
  };

  const_iterator end() const {
    if (_size == 0)
      return NULL;
    return (++const_iterator(tree_max(_root)));
  };

  reverse_iterator rbegin() {
    if (_size == 0)
      return NULL;
    return (reverse_iterator(end()));
  };

  const_reverse_iterator rbegin() const {
    if (_size == 0)
      return NULL;
    return (const_reverse_iterator(end()));
  };

  reverse_iterator rend() {
    if (_size == 0)
      return NULL;
    return (reverse_iterator(begin()));
  };

  const_reverse_iterator rend() const {
    if (_size == 0)
      return NULL;
    return (const_reverse_iterator(begin()));
  };

public:
  bool empty() const {
    return (_size == 0);
  };

  size_type size() const {
    return _size;
  };

  std::pair<iterator, bool> insert(const value_type& value);

  template <typename InputIterator>
  void insert(InputIterator first, InputIterator last);

  iterator erase(const_iterator position);
  iterator erase(const_iterator first, const_iterator last);
  reverse_iterator erase(const_reverse_iterator position);
  reverse_iterator erase(const_reverse_iterator first, const_reverse_iterator last);

  void clear() {
    for(iterator it = this->begin(); it != this->end(); it++)
      _allocator.destory(it);
    _allocator.deallocate(this->begin(), _size);
  };

  iterator find(const key_type& key) {
    return iterator(search(key, _root));
  };

  const_iterator find(const key_type& key) const {
    return const_iterator(search(key, _root));
  };

  //first element that is not less than key. (key <= return)
  iterator lower_bound(const key_type& key) {
    return (find(key));
  };

  const_iterator lower_bound(const key_type& key) const {
    return (find(key));
  };

  //first element that is greater than key. (key > return)
  iterator upper_bound(const key_type& key) {
    return (++find(key));
  };

  const_iterator upper_bound(const key_type& key) const {
    return (++find(key));
  };

/*  PRIVATE FUNCTION  */
private:
  Node* tree_min(Node* node) {
    while (node->_parent)
      node = node->_parent;
    while (node->_left)
      node = node->_left;
    return node;
  };

  Node* tree_max(Node* node) {
    while (node->_parent)
      node = node->_parent;
    while (node->_right)
      node = node->_right;
    return node;
  };

  Node* get_root(Node* node) {
    while (node->_parent)
      node = node->_parent;
    return node;
  };

  key_type search(key_type key, node_type* node) {
    if (node && node->left && _compare(key, node->value.first))
      search(key, node->left);
    else if (node && node->right && _compare(node->value.first, key))
      search(key, node->right);
    else
      return NULL;
    return node;
  };

};

#endif
