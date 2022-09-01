#ifndef _TREE_HPP
#define _TREE_HPP

#include <functional> //std::less
#include "utility.hpp" //ft::rebind, ft::pair
#include "iterator.hpp" //ft::reverse_iterator
//#include "type_traits.hpp" //ft::enable_if, ft::is_integral

#define RED 0
#define BLACK 1

namespace ft {
/*  TREE NODE  */
  template<typename T, typename Allocator = std::allocator<T> >
  struct tree_node {
  public:
    typedef T             value_type;
    typedef bool          color_type;
    typedef Allocator     allocator_type;

  public:
    tree_node*            _parent;
    tree_node*            _left;
    tree_node*            _right;
    value_type*           _value;
    color_type            _color;
    allocator_type        _allocator;

  public:
    tree_node (const allocator_type& alloc = allocator_type())
    : _parent(NULL),
      _left(NULL),
      _right(NULL),
      _value(NULL),
      _color(BLACK),
      _allocator(alloc) {};

    tree_node(const value_type& value,
              const allocator_type& alloc = allocator_type())
    : _parent(NULL),
      _left(NULL),
      _right(NULL),
      _value(NULL),
      _color(RED),
      _allocator(alloc) {
      _value = _allocator.allocate(1);
      _allocator.construct(_value, value);
    };

    tree_node(const tree_node &x,
              const allocator_type& alloc = allocator_type())
    : _parent(NULL),
      _left(NULL),
      _right(NULL),
      _value(NULL),
      _allocator(alloc) {
        if (x._value != NULL) {
          _value = _allocator.allocate(1);
          _allocator.construct(_value, *x._value);
          _color = x._color;
        }
      };

    ~tree_node() {
      if (_value != NULL) {
        _allocator.destroy(_value);
        _allocator.deallocate(_value, 1);
      }
    };

    bool operator==(const tree_node& node) const { return (*this->_value == *node->_value); };
    bool operator!=(const tree_node& node) const { return (*this->_value != *node->_value); };

  }; // class tree node

/*  ITERATOR  */
  template<typename T, typename pointer = T*, typename reference = T&>
  struct tree_iterator {
    typedef T                                         value_type;
    typedef ft::tree_node<T>                          node_type;
    typedef std::ptrdiff_t                            difference_type;
    typedef std::bidirectional_iterator_tag           iterator_category;

  private:
    node_type* _node;

  public:
    explicit tree_iterator(const node_type* pNode = NULL) : _node(pNode) {};

    tree_iterator(const tree_iterator<T>& other) : _node(other.base()) {};

    virtual ~tree_iterator() {};

    tree_iterator& operator=(const tree_iterator<T>& x) {
      if (this != &x)
        _node = x.base();

      return *this;
    };

    node_type* &base() const {
      return _node;
    };

    reference operator*() const {
      return (*this->_node->_value);
    };

    pointer operator->() const {
      return this->_node->_value;
    };

    tree_iterator& operator++() {
      if (_node->_right) {
        _node = _node->_right;
        while (_node->_left)
          _node = _node->_left;
      } else {
        if (_node == _node->_parent->_left)
          _node = _node->_parent;
        else {
          while (_node->_parent && _node != _node->_parent->_left)
            _node = _node->_parent;
          if (_node->_parent)
            _node = _node->_parent;
        }
      }
      return (*this);
    };

    tree_iterator operator++(int) {
      tree_iterator temp(*this);
      this->operator++();
      return (temp);
    };

    tree_iterator& operator--() {
      if (_node->_left) {
        _node = _node->_left;
        while (_node->_right)
          _node = _node->_right;
      } else {
        if (_node == _node->_parent->_right)
          _node = _node->_parent;
        else {
          while (_node->_parent && _node != _node->_parent->_right)
            _node = _node->_parent;
          if (_node->_parent)
            _node = _node->_parent;
        }
      }
    };

    tree_iterator operator--(int) {
      tree_iterator temp(*this);
      this->operator--();
      return (temp);
    };

    bool operator==(const tree_iterator& iter) {
      return (_node == iter.base());
    };

    bool operator!=(const tree_iterator& iter) {
      return (_node != iter.base());
    };
  }; // tree_iterator

/*  TREE  */
  template<typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T> >
  class _tree {
  public:
    typedef Allocator                                     allocator_type;
    typedef Compare                                       key_compare;
    typedef T                                             value_type;
    typedef std::size_t                                   size_type;
    typedef std::ptrdiff_t                                difference_type;
    typedef value_type*                                   pointer;
    typedef const value_type*                             const_pointer;
    typedef value_type&                                   reference;
    typedef const value_type&                             const_reference;
    typedef typename ft::tree_node<T>::color_type         color_type;
    typedef ft::tree_node<T>                              node_type;
    typedef ft::tree_node<T>*                             node_pointer;
    typedef typename ft::rebind<node_type>::other         node_allocator_type;
//    typedef ft::tree_iterator<value_type>                 iterator;
//    typedef ft::tree_iterator<const value_type>           const_iterator;
    typedef ft::tree_iterator<value_type, pointer, reference>               iterator;
    typedef ft::tree_iterator<value_type, const_pointer, const_reference>   const_iterator;
    typedef ft::reverse_iterator<iterator>                                  reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                            const_reverse_iterator;

  private:
    node_allocator_type     _node_alloc;
//    Compare                 _compare;
    node_pointer            _root;
    node_pointer            _nil;
    size_type               _size;

  public:
    _tree(//const key_compare& comp = key_compare(),
          const node_allocator_type& alloc = node_allocator_type())
    : _node_alloc(alloc),
//      _compare(comp),
      _root(NULL),
      _nil(NULL),
      _size(0) {
      _nil = make_nil();
      _root = _nil;
    };

    _tree(const _tree& other, //const key_compare& comp = key_compare(),
          const node_allocator_type& alloc = node_allocator_type())
    : _node_alloc(alloc),
//      _compare(comp),
      _root(NULL),
      _nil(NULL),
      _size(0) {
      _nil = make_nil();
      clear();
      copy(other._root);
      _nil->_parent = tree_max(_root);
    };

    ~_tree() {
      clear();
      _node_alloc.destroy(_nil);
      _node_alloc.deallocate(_nil, 1);
    };

    _tree& operator=(const _tree& other) {
      if (this != &other) {
        clear();
        copy(other._root);
      }
      return *this;
    };

    bool empty() const {
      return (_size == 0);
    };

    size_type size() const {
      return _size;
    };

    size_type max_size() const {
      return _node_alloc.max_size();
    }

  /*  INSERT  */
//    ft::pair<node_pointer, bool> insert(const value_type& value) {};

  /*  ERASE  */
//    bool erase(node_pointer node) {};

    void clear(node_pointer node = NULL) {
      if (node == NULL)
        node = this->_root;

      if (node->_left->_value != NULL) {
        clear(node->_left);
        node->_left = this->_nil;
      }

      if (node->_right->_value != NULL) {
        clear(node->_right);
        node->_right = this->_nil;
      }

      if (node->_value != NULL) {
        if (node == this->_root)
          this->_root = this->_nil;
        _node_alloc.destroy(node);
        _node_alloc.deallocate(node, 1);
        this->_size--;
      }
    };

    node_pointer find(const value_type& value) {
      node_pointer ret = _root;

      if (_size == 0)
        return (_nil);

      while (ret->_value != NULL && (_compare(value, *ret->_value) || _compare(*ret->_value, value))) {
        if (_compare(value, *ret->_value))
          ret = ret->_left;
        else
          ret = ret->_right;
      }

      return (ret);
    };

    template<typename U>
    void swap(U& a, U& b) {
      U temp;

      temp = a;
      a = b;
      b = temp;
    };

    void swap(_tree& x)
    {
      swap(_node_alloc, x._node_alloc);
//      swap(_compare, x._compare);
      swap(_root, x._root);
      swap(_nil, x._nil);
      swap(_size, x._size);
    }

    /*  BOUND  */
  //value보다 크거나 같은 범위
    node_pointer lower_bound(const value_type& value) const {
      iterator it(tree_min(_root));
      iterator ite(tree_max(_root)); //ite(_nil)

      while (it != ite && _compare(*it, value))
        it++;

      return (it.base());
    };

  //value보다 작거나 같은 범위
    node_pointer upper_bound(const value_type& value) const {
      iterator it(tree_min(_root));
      iterator ite(tree_max(_root)); //ite(_nil)

      while (it != ite && !_compare(value, *it))
        it++;

      return (it.base());
    };

  /*  ITERATORS  */
//    iterator begin() {
//      if (_size == 0)
//        return NULL;
//      return (iterator(tree_min(_root)));
//    };
//
//    const_iterator begin() const {
//      if (_size == 0)
//        return NULL;
//      return (const_iterator(tree_min(_root)));
//    };
//
//    iterator end() {
//      if (_size == 0)
//        return NULL;
//      return (++iterator(tree_max(_root)));
//    };
//
//    const_iterator end() const {
//      if (_size == 0)
//        return NULL;
//      return (++const_iterator(tree_max(_root)));
//    };
//
//    reverse_iterator rbegin() {
//      if (_size == 0)
//        return NULL;
//      return (reverse_iterator(end()));
//    };
//
//    const_reverse_iterator rbegin() const {
//      if (_size == 0)
//        return NULL;
//      return (const_reverse_iterator(end()));
//    };
//
//    reverse_iterator rend() {
//      if (_size == 0)
//        return NULL;
//      return (reverse_iterator(begin()));
//    };
//
//    const_reverse_iterator rend() const {
//      if (_size == 0)
//        return NULL;
//      return (const_reverse_iterator(begin()));
//    };


    /*  PRIVATE FUNCTION  */
  private:
    node_pointer tree_min(node_pointer node) {
      while (node->_left)
        node = node->_left;
      return node;
    };

    node_pointer tree_max(node_pointer node) {
      while (node->_right)
        node = node->_right;
      return node;
    };

    node_pointer get_root(node_pointer node) {
      while (node->_parent)
        node = node->_parent;
      return node;
    };

    //usage: tree_max(get_root(any_node)) -> max value in tree
    //usage: tree_max(sub_tree_root_node) -> max value in sub_tree

    node_pointer get_sibling(node_pointer node) const {
      if (node->_parent->_left == node)
        return (node->_parent->_right);
      if (node->_parent->_right == node)
        return (node->_parent->_left);
    };

//    key_type search(key_type key, node_pointer node) {
//      if (node && node->_left && _compare(key, node->_value.first))
//        search(key, node->_left);
//      else if (node && node->_right && _compare(node->_value.first, key))
//        search(key, node->_right);
//      else
//        return 0;
//      return node;
//    };

    void copy(node_pointer node) {
      if(node->_value == NULL)
        return ;
      insert(*node->_value);
      if (node->_left->_value != NULL)
        copy(node->_left);
      if (node->_right->_value != NULL)
        copy(node->_right);
    };

    node_pointer make_nil() {
      node_pointer nil = _node_alloc.allocate(1);
      _node_alloc.construct(nil, node_type());
      nil->_color = BLACK;
      nil->_left = nil;
      nil->_right = nil;
      nil->_parent = nil;
      nil->_value = NULL;
      return (nil);
    };

    //have to set color, child, parent after
    node_pointer make_node(const value_type& value) {
      node_pointer ret = _node_alloc.allocate(1);
      _node_alloc.construct(ret, node_type(value));
      return (ret);
    }

  /*  ROTATE  */
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

} //namespace

/*  NON-MEMBER FUNCTIONS  */
//  template<class Key, class T, class Compare, class Alloc>
//  bool operator==(const ft::map <Key, T, Compare, Alloc> &lhs, const ft::map <Key, T, Compare, Alloc> &rhs) {
//    return lhs.base() == rhs.base();
//  }
//
//  template<class Key, class T, class Compare, class Alloc>
//  bool operator!=(const ft::map <Key, T, Compare, Alloc> &lhs, const ft::map <Key, T, Compare, Alloc> &rhs) {
//    return !(operator==(lhs, rhs));
//  }
//
//  template< class Key, class T, class Compare, class Alloc>
//  bool operator< (const ft::map <Key, T, Compare, Alloc> &lhs, const ft::map <Key, T, Compare, Alloc> &rhs) {
//    return lhs.base() < rhs.base();
//  }
//
//  template<class Key, class T, class Compare, class Alloc>
//  bool operator> (const ft::map <Key, T, Compare, Alloc> &lhs, const ft::map <Key, T, Compare, Alloc> &rhs) {
//    return lhs.base() > rhs.base();
//  }
//
//  template<class Key, class T, class Compare, class Alloc>
//  bool operator<=(const ft::map <Key, T, Compare, Alloc> &lhs, const ft::map <Key, T, Compare, Alloc> &rhs) {
//    return !(operator>(lhs, rhs));
//  }
//
//  template<class Key, class T, class Compare, class Alloc>
//  bool operator>=(const ft::map <Key, T, Compare, Alloc> &lhs, const ft::map <Key, T, Compare, Alloc> &rhs) {
//    return !(operator<(lhs, rhs));
//  }




#endif
