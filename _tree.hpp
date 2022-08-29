#ifndef _TREE_HPP
#define _TREE_HPP

#include <functional> //std::less
#include "utility.hpp" //ft::pair, ft::make_pair, use_first, rebind
#include "iterator.hpp" //ft::reverse_iterator, ft::distance
#include "type_traits.hpp" //ft::enable_if, ft::is_integral

#define BLACK 0
#define RED 1

namespace ft {
/*  TREE NODE  */
  template<typename T>
  class tree_node {
  public:
    typedef T             value_type;

  private:
    bool            _color;
    value_type      _value; //data
    tree_node*      _left;
    tree_node*      _right;
    tree_node*      _parent;

  public:
    tree_node() {};

    tree_node(value_type value, tree_node left, tree_node right, tree_node parent)
        : _value(value), _left(left), _right(right), _parent(parent) {};

    tree_node(const tree_node &x) { *this = x; };

    ~tree_node() {};
  }; // class tree node

/*  TREE  */
  template<
    typename Key,
    typename Value,
    typename Compare = std::less <Key>,
    typename Allocator = std::allocator <Value>
  >

//  template<typename T>
  class _tree {
  public:
    typedef T value_type;
    typedef const T& const_ref_type;
    typedef tree_node<T> node_value_type;
    typedef tree_node<T>* node_pointer;
    typedef const node_pointer const_node_pointer;

    typedef tree_iterator<value_type>                     iterator;
    typedef tree_iterator<const value_type>               const_iterator;
    typedef ft::reverse_iterator <iterator>               reverse_iterator;
    typedef ft::reverse_iterator <const_iterator>         const_reverse_iterator;

    typedef Key                                           key_type;
    typedef Value                                         value_type;
    typedef tree_node<ft::pair<key_type, value_type> >    node_type;
    typedef tree_node<ft::pair<key_type, value_type> >    *node_pointer;
    //  typedef ft::pair<const key_type, value_type>          node_type;
    typedef Compare                                       key_compare;
    typedef Allocator                                     allocator_type;
    typedef value_type&                                   reference;
    typedef const value_type&                             const_reference;
    typedef value_type*                                   pointer;
    typedef const value_type*                             const_pointer;
    typedef std::size_t                                   size_type;
    typedef std::ptrdiff_t                                difference_type;

    //  typedef rbtree_node<value_type>                         node_type;

    //  typedef integral_constant<bool, bUniqueKeys>            has_unique_keys_type;
    //  typedef typename tree_node::extract_key                 extract_key;

  private:
    allocator_type  _allocator;
    key_compare     _compare;
    node_pointer    _root;
    pointer         _anchor;
    size_type       _size;

  public:
    _tree() : _root(NULL) {};

    explicit _tree(const Compare &comp, const Allocator &alloc = Allocator())
        : _allocator(alloc),
          _compare(comp),
          _root(NULL),
          _anchor(NULL),
          _size(0) {};

    template<class InputIt>
    _tree(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator())
        : _allocator(alloc),
          _compare(comp) {
      difference_type diff = ft::distance(first, last);

      _root = _allocator.allocate(diff);
      _anchor->_value = 0;
      _anchor->_left = this->begin();
      _anchor->_right = this->end();
      _anchor->_parent = _root;
      _size = diff;

      while (diff--) {
//        this->_allocator.construct(_root++, *first++)
      }
    };

    _tree(const _tree &other) {
      *this = other;
//      _compare = other._compare;
//      _allocator = other._allocator;
//      _size = other._size;
//      _anchor = other._anchor;
//      _root = other._root;
    };

    ~_tree() {
      erase(begin());
    };

    _tree &operator=(const _tree &other) {
      if (this != &other) {
        clear();
//        copy
      }
      return *this;
    };

    allocator_type get_allocator() const {
      return _allocator;
    };

    const key_compare& key_comp() const {
      return _compare;
    };

    key_compare& key_comp() {
      return _compare;
    };

    void swap(_tree &x) {
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

    //insert된 인자의 iterator or element that prevented the insertion && insert성공여부
    std::pair<iterator, bool> insert(const value_type& value) {
      return (ft::make_pair(iterator(value), true));
    };

    //hint: iterator, used as a suggestion as to where to start the search
    iterator insert( iterator hint, const value_type& value );
    //Returns an iterator to the inserted element, or to the element that prevented the insertion.

    template< class InputIt >
    void insert( InputIt first, InputIt last );

    void erase(iterator pos);

    void erase(iterator first, iterator last) {
      while (first++ != last)
        erase(first);
      return ;
    };

    size_type erase(const Key& key);

    void clear() {
      for (iterator it = this->begin(); it != this->end(); it++)
        _allocator.destory(it);
      _allocator.deallocate(this->begin(), _size);
    };

    iterator find(const key_type &key) {
      return iterator(search(key, _root));
    };

    const_iterator find(const key_type &key) const {
      return const_iterator(search(key, _root));
    };

    //first element that is not less than key. (key <= return)
    iterator lower_bound(const key_type &key) {
      return (find(key));
    };

    const_iterator lower_bound(const key_type &key) const {
      return (find(key));
    };

    //first element that is greater than key. (key > return)
    iterator upper_bound(const key_type &key) {
      return (++find(key));
    };

    const_iterator upper_bound(const key_type &key) const {
      return (++find(key));
    };

    /*  PRIVATE FUNCTION  */
  private:
    node_pointer tree_min(node_pointer node) {
      while (node->_parent)
        node = node->_parent;
      while (node->_left)
        node = node->_left;
      return node;
    };

    node_pointer tree_max(node_pointer node) {
      while (node->_parent)
        node = node->_parent;
      while (node->_right)
        node = node->_right;
      return node;
    };

    node_pointer get_root(node_pointer node) {
      while (node->_parent)
        node = node->_parent;
      return node;
    };

    key_type search(key_type key, node_type *node) {
      if (node && node->left && _compare(key, node->value.first))
        search(key, node->left);
      else if (node && node->right && _compare(node->value.first, key))
        search(key, node->right);
      else
        return NULL;
      return node;
    };

    node_pointer left_rotate(node_pointer p) {
      node_pointer ret = p->_right;

      p->_right = ret->_left;

      if (ret->_left)
        ret->_left->_parent = p;

      ret->_parent = p->_parent;

      if (p->_parent == NULL)
        _root = ret;
      else if (p->_parent->_left == p)
        p->_parent->_left = ret;
      else
        p->_parent->_right = ret;

      ret->_left = p;
      p->_parent = ret;

      return ret;
    };

    node_pointer right_rotate(node_pointer p) {
      node_pointer ret = p->_left;

      p->_left = ret->_right;

      if (ret->_right)
        ret->_right->_parent = p;

      ret->_parent = p->_parent;

      if (p->_parent == NULL)
        _root = ret;
      else if (p->_parent->_left == p)
        p->_parent->_left = ret;
      else
        p->_parent->_right = ret;

      ret->_right = p;
      p->_parent = ret;

      return ret;
    };
  };












  template<typename T, typename Pointer = T *, typename Reference = T &>
  struct tree_iterator {
    //  typedef std::size_t                                             size_type;
    typedef std::ptrdiff_t                                              difference_type;
    typedef T                                                           value_type;
    typedef T*                                                          pointer;
    typedef T&                                                          reference;
//    typedef ft::tree_node<T>*                                           node_type;
    typedef ft::tree_node::node_pointer                                 node_type;
    //  typedef tree_iterator<T, pointer, reference>                    this_type;
    //  typedef tree_iterator<T, pointer, reference>                    iterator;
    //  typedef tree_iterator<T, const pointer, const reference>        const_iterator;
    //  typedef rbtree_node_base                                        base_node_type;
    typedef std::bidirectional_iterator_tag                             iterator_category;

  private:
    node_type _node;

  public:
    explicit tree_iterator(const node_type* pNode = NULL) : _node(pNode) {};

    tree_iterator(const iterator &other) : _node(other._node) {};

    ~tree_iterator() {};

    tree_iterator& operator=(const iterator &x) {
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

    tree_iterator operator--(int) {
      tree_iterator temp(*this);
      this->operator--();
      return (temp);
    };
  }; // tree_iterator

/*  NON-MEMBER FUNCTIONS  */
  template<class Key, class T, class Compare, class Alloc>
  bool operator==(const std::map <Key, T, Compare, Alloc> &lhs, const std::map <Key, T, Compare, Alloc> &rhs) {
    return lhs.base() == rhs.base();
  }

  template<class Key, class T, class Compare, class Alloc>
  bool operator!=(const std::map <Key, T, Compare, Alloc> &lhs, const std::map <Key, T, Compare, Alloc> &rhs) {
    return !(operator==(lhs, rhs));
  }

  template< class Key, class T, class Compare, class Alloc>
  bool operator< (const std::map <Key, T, Compare, Alloc> &lhs, const std::map <Key, T, Compare, Alloc> &rhs) {
    return lhs.base() < rhs.base();
  }

  template<class Key, class T, class Compare, class Alloc>
  bool operator> (const std::map <Key, T, Compare, Alloc> &lhs, const std::map <Key, T, Compare, Alloc> &rhs) {
    return lhs.base() > rhs.base();
  }

  template<class Key, class T, class Compare, class Alloc>
  bool operator<=(const std::map <Key, T, Compare, Alloc> &lhs, const std::map <Key, T, Compare, Alloc> &rhs) {
    return !(operator>(lhs, rhs));
  }

  template<class Key, class T, class Compare, class Alloc>
  bool operator>=(const std::map <Key, T, Compare, Alloc> &lhs, const std::map <Key, T, Compare, Alloc> &rhs) {
    return !(operator<(lhs, rhs));
  }

} //namespace

#endif
