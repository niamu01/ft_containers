#ifndef _TREE_HPP
# define _TREE_HPP

#include <stdexcept>
#include <memory>

#include "functional.hpp" //ft::less
#include "utility.hpp" //ft::rebind, ft::pair, ft::use_first
#include "iterator.hpp" //ft::reverse_iterator, ft::distance

#include "algorithm.hpp" //ft::equal, ft::lexicographical_compare
#include "type_traits.hpp" //ft::enable_if, ft::is_integral

#define RED 0
#define BLACK 1

#define LEFT 0
#define RIGHT 1

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
  template<typename T, typename Pointer = T*, typename Reference = T&>
  struct tree_iterator {
    public :
      typedef const T		                          value_type; //todo: const?!
      typedef ft::tree_node<T>                    node_type;
      typedef std::ptrdiff_t                      difference_type;
      typedef std::bidirectional_iterator_tag     iterator_category;
      typedef Pointer pointer; //todo: cannot be used directly?
      typedef Reference reference;

    private:
      node_type* _node;

    public:
      //todo: construct matching is not possible because of explicit keyword
      tree_iterator(node_type* pNode = NULL) : _node(pNode) {};

      tree_iterator(const tree_iterator<T>& other) : _node(other.base()) {};

      //todo: virtual keyword: not an inherited class
      virtual ~tree_iterator() {};

      tree_iterator& operator=(const tree_iterator<T>& x) {
        if (this != &x)
          _node = x.base();

        return *this;
      };

      //todo: const &base -> base
      node_type* const &base() const {
        return _node;
      };

      //todo: maybe another return value
      reference operator*() const {
        return *this->_node->_value;
      };

      pointer operator->() const {
        return this->_node->_value;
      };

      tree_iterator& operator++() {
        node_type* temp = NULL;

        if (_node->_right->_value) {
          temp = _node->_right;
          while (temp->_left->_value)
            temp = temp->_left;
        } else {
          temp = _node->_parent;
          if (temp->_right == _node) {
            while (temp->_parent->_right == temp)
              temp = temp->_parent;
            temp = temp->_parent;
          }
        }
        _node = temp;

        return *this;
      };

      tree_iterator operator++(int) {
        tree_iterator temp(*this);
        this->operator++();
        return (temp);
      };

      tree_iterator& operator--() {
        node_type* temp = NULL;

        if (_node->_value == NULL) {
          temp = _node->_parent;
        } else if (_node->_left->_value != NULL) {
          temp = _node->_left;
          while (temp->_right->_value != NULL)
            temp = temp->_right;
        } else {
          temp = _node->_parent;
          if (temp->_left == _node) {
            while (temp->_parent->_left == temp)
              temp = temp->_parent;
            temp = temp->_parent;
          }
        }
        _node = temp;

        return *this;
      };

      tree_iterator operator--(int) {
        tree_iterator temp(*this);
        this->operator--();
        return temp;
      };

      bool operator==(const tree_iterator& iter) { return (_node == iter.base()); };
      bool operator!=(const tree_iterator& iter) { return (_node != iter.base()); };

  }; // tree_iterator

/*  TREE  */
	template<
    typename T,
    typename ExtractKey,
    typename Compare = ft::less<T>,
    typename Allocator = std::allocator<T>
  // bool      bMutableIterators = true, //map: true, set: false
  // bool      bUniqueKeys = true //map,set: true, multi: false
  >
  class _tree {
    public:
      typedef Allocator                                                           allocator_type;
      typedef Compare                                                             key_compare;
      typedef T                                                                   value_type;
      typedef std::size_t                                                         size_type;
      typedef std::ptrdiff_t                                                      difference_type;
      typedef value_type *                                                        pointer;
      typedef const value_type *                                                  const_pointer;
      typedef value_type &                                                        reference;
      typedef const value_type &                                                  const_reference;
      typedef typename ft::tree_node<T>::color_type                               color_type;
      typedef ft::tree_node<T>                                                    node_type;
      typedef ft::tree_node<T> *                                                  node_pointer;
      typedef typename ft::rebind<node_type>::other                               node_allocator_type;
      typedef ft::tree_iterator<value_type, pointer, reference>                   iterator;
      typedef ft::tree_iterator<value_type, const_pointer, const_reference>       const_iterator;
      typedef ft::reverse_iterator<iterator>                                      reverse_iterator;
      typedef ft::reverse_iterator<const_iterator>                                const_reverse_iterator;

    private:
      node_allocator_type     _node_alloc;
      key_compare             _compare;
      node_pointer            _root;
      node_pointer            _nil;
      size_type               _size;

    public:
      _tree()
      : _node_alloc(node_allocator_type()),
        _compare(key_compare()),
        _root(NULL),
        _nil(NULL),
        _size(0) {
        _nil = make_nil();
        _root = _nil;
      };
      
      _tree(const _tree &other)
      : _node_alloc(node_allocator_type()),
        _compare(key_compare()),
        _root(NULL),
        _nil(NULL),
        _size(0) {
        _nil = make_nil();
        copy(other);
        _nil->_parent = tree_max(get_root()); //todo: change func
      };

      ~_tree() {
        clear();
        _node_alloc.destroy(_nil);
        _node_alloc.deallocate(_nil, 1);
      };

      _tree &operator=(const _tree &other) {
        if (this != &other)
          copy(other);

        return *this;
      };

      bool empty() const { return (_size == 0); };

      size_type size() const { return _size; };

      size_type max_size() const { return _node_alloc.max_size(); };

    /*  INSERT  */
      ft::pair<node_pointer, bool> insert(const value_type &value, node_pointer hint = NULL) {
        node_pointer insert_node = make_node(value);
        node_pointer insert_position = _root;
        
        //if tree was empty
        if (this->empty()) {
          _root = insert_node;
          _root->_left = _nil;
          _root->_right = _nil;
          _root->_parent = _nil; 
          _root->_color = BLACK;
          _nil->_parent = _root; 
          _size++;

          return ft::make_pair(_root, true); 
        }
        
        if (hint != NULL && hint->_value != NULL) //todo: check hint->_value != NULL
          insert_position = find_position_by_hint(hint, value);
        
        ft::pair<node_pointer, bool> ret_pair = try_insert(insert_position, insert_node);
        
        //insert fail
        if (ret_pair.second == false) {
          _node_alloc.destroy(insert_node);
          _node_alloc.deallocate(insert_node, 1);

          return ret_pair;
        }

        check_sort_insert(insert_node);

        _nil->_parent = tree_max(get_root());
        _size++;

        return ft::make_pair(insert_node, true);
      };

    /*  ERASE  */
      bool erase(node_pointer node) {
        if (node->_value == NULL)
          return 0;

        node_pointer target = replace_erase_node(node);

        node_pointer child;
        if (target->_right->_value == NULL)
          child = target->_left;
        else
          child = target->_right;

        replace_a_to_b(target, child);
        if (target->_color == BLACK) {
          if (child->_color == RED)
            child->_color = BLACK;
          else
            check_sort_erase(child);
        }

        if (target->_parent->_value == NULL)
          _root = _nil;

        _nil->_parent = tree_max(get_root());
        _size--;
        delete target;
        
        return 1;
      };

      void clear(node_pointer node = NULL) {
        if (node == NULL)
          node = _root;

        if (node->_left->_value != NULL) {
          clear(node->_left);
          node->_left = _nil;
        }

        if (node->_right->_value != NULL) {
          clear(node->_right);
          node->_right = _nil;
        }
        
        if (node->_value != NULL) {
          if (node == _root)
            _root = _nil;
          _node_alloc.destroy(node);
          _node_alloc.deallocate(node, 1);
          _size--;
        }
      };

      node_pointer find(value_type value) const { //todo: add const, & to parameter 
        node_pointer ret = _root;

        if (_size == 0)
          return (_nil);

        while (ret->_value != NULL && (_compare(value, *ret->_value) || _compare(*ret->_value, value))) {
          if (_compare(value, *ret->_value))
            ret = ret->_left;
          else
            ret = ret->_right;
        }

        return ret;
      };

      template<typename U>
      void swap(U &a, U &b) {
        U temp;

        temp = a;
        a = b;
        b = temp;
      };

      void swap(_tree &x) {
        swap(_node_alloc, x._node_alloc);
        swap(_compare, x._compare);
        swap(_root, x._root);
        swap(_nil, x._nil);
        swap(_size, x._size);
      };

      void copy(const _tree& tree) {
        clear();
        copy(tree._root);
      };

      void copy(node_pointer node) {
        if (node->_value == NULL)
          return;

        insert(*node->_value);

        if (node->_left->_value != NULL)
          copy(node->_left);

        if (node->_right->_value != NULL)
          copy(node->_right);
      };

    /*  BOUND  */
      node_pointer lower_bound(const value_type &value) const {
        iterator it(tree_min(get_root()));
        iterator ite(get_nil());
        while (it != ite && _compare(*it, value))
          it++;

        return it.base();
      };

      node_pointer upper_bound(const value_type &value) const {
        iterator it(tree_min(get_root()));
        iterator ite(get_nil());
        while (it != ite && !_compare(value, *it))
          it++;

        return it.base();
      };

      /*  PUBLIC UTIL FUNCTIONS */
      node_pointer tree_min(node_pointer node) {
        while (node->_left->_value)
          node = node->_left;

        return node;
      };

      node_pointer tree_min(node_pointer node) const {
        while (node->_left->_value)
          node = node->_left;

        return node;
      };

      node_pointer tree_max(node_pointer node) {
        while (node->_right->_value)
          node = node->_right;

        return node;
      };

      node_pointer tree_max(node_pointer node) const {
        while (node->_right->_value)
          node = node->_right;

        return node;
      };

      node_pointer get_root() const {
        return _root;
      };

      node_pointer get_nil() const {
        return _nil;
      };
      
			node_pointer get_sibling(node_pointer node) const {
				if (node->_parent->_left == node)
					return node->_parent->_right;
				else //if (node->_parent->_right == node)
					return node->_parent->_left;
			}; 

			node_pointer get_uncle(node_pointer node) const {
				node_pointer grand = get_grand(node);
				if (grand == NULL)
					return NULL;

				if (grand->_left == node->_parent)
					return grand->_right;
				else //if (node->_parent == grand->_right)
					return grand->_left;
			};

			node_pointer get_grand(node_pointer node) const {
        if (node && node->_parent && node->_parent->_parent->_value)
					return node->_parent->_parent;
				else
					return NULL;
			};
      
      node_pointer make_nil() {
        node_pointer nil;
        
        nil = _node_alloc.allocate(1);
        _node_alloc.construct(nil, node_type());

        nil->_color = BLACK;
        nil->_left = nil;
        nil->_right = nil;
        nil->_parent = nil;
        nil->_value = NULL;

        return nil;
      };

      node_pointer make_node(const value_type &value) {
        node_pointer node;

        node = _node_alloc.allocate(1);
        _node_alloc.construct(node, node_type(value));

        return node;
      };

      void left_rotate(node_pointer p) {
        node_pointer child = p->_right;
        node_pointer parent = p->_parent;
        
        if (child->_left->_value != NULL)
          child->_left->_parent = p;

        p->_right = child->_left;
        p->_parent = child;
        child->_left = p;
        child->_parent = parent;
        
        if (parent->_value != NULL) {
          if (parent->_left == p)
            parent->_left = child;
          else
            parent->_right = child;
        } else {
          this->_root = child;
        }
      };
      
      void right_rotate(node_pointer p) {
        node_pointer child = p->_left;
        node_pointer parent = p->_parent;

        if (child->_right->_value != NULL)
          child->_right->_parent = p;

        p->_left = child->_right;
        p->_parent = child;
        child->_right = p;
        child->_parent = parent;

        if (parent->_value != NULL) {
          if (parent->_right == p)
            parent->_right = child;
          else
            parent->_left = child;
        } else {
          this->_root = child;
        }
      };

          /*  INSERT UTILS  */
      void insert_LR(node_pointer insert_position, node_pointer insert_node, bool direction) {
        if (direction == LEFT) {
          insert_position->_left = insert_node;
        } else if (direction == RIGHT) {
          insert_position->_right = insert_node;
        }

        insert_node->_parent = insert_position;
        insert_node->_left = _nil;
        insert_node->_right = _nil;
        insert_node->_color = RED;
      };

      ft::pair<node_pointer, bool> try_insert(node_pointer insert_position, node_pointer insert_node) {
        while (insert_position->_value) {
          if (_compare(*insert_node->_value, *insert_position->_value)) {
            if (insert_position->_left->_value == NULL) {
              insert_LR(insert_position, insert_node, LEFT);
              break;
            } else
              insert_position = insert_position->_left;
          } else if (_compare(*insert_position->_value, *insert_node->_value)) {
            if (insert_position->_right->_value == NULL) {
              insert_LR(insert_position, insert_node, RIGHT);
              break;
            } else
              insert_position = insert_position->_right;
          } else
            return ft::make_pair(insert_position, false);
        }
        return ft::make_pair(insert_position, true);
      };

      node_pointer find_position_by_hint(node_pointer hint, value_type value) {
        if (_compare(*hint->_value, *_root->_value) && _compare(value, *hint->_value))
          return (hint);
        else if (_compare(*hint->_value, *_root->_value) && _compare(*hint->_value, value))
          return (_root);
        else if (_compare(*_root->_value, *hint->_value) && _compare(value, *hint->_value))
          return (_root);
        else if (_compare(*_root->_value, *hint->_value) && _compare(*hint->_value, value))
          return (hint);
        else
          return (_root);
      };

      void check_sort_insert(node_pointer node) {
      //empty라서 root로 insert되는 경우는 밖에서 진행
        if (node->_parent->_value == NULL) {
          node->_color = BLACK;
          return;
        }

        //insert되는 node는 RED라 부모가 BLACK인 경우 문제 없음
        if (node->_parent->_color == BLACK)
          return;

        //case1. x의 uncle_node가 RED
        node_pointer uncle = get_uncle(node);
        node_pointer grand = get_grand(node);
        if (uncle->_value && uncle->_color == RED) {
          node->_parent->_color = BLACK;
          uncle->_color = BLACK;
          grand->_color = RED;
          check_sort_insert(grand);
        } else {
          if (node == node->_parent->_right && node->_parent == grand->_left) {
            rotate_LR(node->_parent, LEFT);
            node = node->_left;
          } else if (node == node->_parent->_left && node->_parent == grand->_right) {
            rotate_LR(node->_parent, RIGHT);
            node = node->_right;
          }
          grand->_color = RED;
          node->_parent->_color = BLACK;
          if (node == node->_parent->_left)
            rotate_LR(grand, RIGHT);
          else
            rotate_LR(grand, LEFT);
          }
      };

    /*  ERASE UTILS  */
      node_pointer replace_erase_node(node_pointer node) {
        node_pointer res;
        if (node->_left->_value) {
          res = node->_left;
          while (res->_right->_value)
            res = res->_right;
        } else if (node->_right->_value) {
          res = node->_right;
          while (res->_left->_value)
            res = res->_left;
        } else {
          return (node);
        }

        node_pointer tmp_parent = node->_parent;
        node_pointer tmp_left = node->_left;
        node_pointer tmp_right = node->_right;
        bool tmp_color = node->_color;

        
        node->_left = res->_left;
        if (res->_left->_value)
          res->_left->_parent = node;

        node->_right = res->_right;
        if (res->_right->_value)
          res->_right->_parent = node;

        if (tmp_parent->_left == node)
          tmp_parent->_left = res;
        else if (tmp_parent->_right == node)
          tmp_parent->_right = res;

        if (res == tmp_left) {
          tmp_right->_parent = res;
          res->_right = tmp_right;
          node->_parent = res;
          res->_left = node;
        } else if (res == tmp_right) {
          tmp_left->_parent = res;
          res->_left = tmp_left;
          node->_parent = res;
          res->_right = node;
        } else {
          tmp_left->_parent = res;
          res->_left = tmp_left;
          tmp_right->_parent = res;
          res->_right = tmp_right;
          node->_parent = res->_parent;
          res->_parent->_right = node;
        }

        res->_parent = tmp_parent;

        if (res->_parent->_value == NULL)
          this->_root = res;

        node->_color = res->_color;
        res->_color = tmp_color;

        return node;
      };

      void replace_a_to_b(node_pointer a, node_pointer b) {
        b->_parent = a->_parent;

        if (a->_parent->_left == a)
          a->_parent->_left = b;

        else if (a->_parent->_right == a)
          a->_parent->_right = b;
      };

      void rotate_LR(node_pointer target, bool direction) {
        if (direction == LEFT)
          left_rotate(target);
        else if (direction == RIGHT)
          right_rotate(target);
      };

      void check_sort_erase(node_pointer node) {
        //erase힐 노드가 root먄 재정렬할 필요가 없다
        if (node->_parent->_value == NULL)
          return;

        node_pointer sibling = get_sibling(node);
        if (sibling->_color == RED) {
          sibling->_color = BLACK;
          node->_parent->_color = RED;
          if (node == node->_parent->_left)
            rotate_LR(node->_parent, LEFT);
          else
            rotate_LR(node->_parent, RIGHT);
        }

        if (node->_parent->_color == BLACK 
          && sibling->_color == BLACK 
          && sibling->_left->_color == BLACK 
          && sibling->_right->_color == BLACK) {
          sibling->_color = RED;
          check_sort_erase(node->_parent);
        } else {
          check_sort_erase2(node);
        }
      };

      void check_sort_erase2(node_pointer node) {
        node_pointer sibling = get_sibling(node);

        if (node->_parent->_color == RED
          && sibling->_color == BLACK 
          && sibling->_left->_color == BLACK 
          && sibling->_right->_color == BLACK) {
          sibling->_color = RED;
          node->_parent->_color = BLACK;
        } else {
          if (sibling->_color == BLACK) {
            if (node == node->_parent->_left 
              && sibling->_right->_color == BLACK 
              && sibling->_left->_color == RED) {
              sibling->_left->_color = BLACK;
              sibling->_color = RED;
              rotate_LR(sibling, RIGHT);
            } else if (node == node->_parent->_right 
              && sibling->_left->_color == BLACK 
              && sibling->_right->_color == RED) {
              sibling->_color = RED;
              sibling->_right->_color = BLACK;
              rotate_LR(sibling, LEFT);
            }
          }
          sibling->_color = node->_parent->_color;
          node->_parent->_color = BLACK;
          if (node == node->_parent->_left) {
            sibling->_right->_color = BLACK;
            left_rotate(node->_parent);
          } else {
            sibling->_left->_color = BLACK;
            right_rotate(node->_parent);
          }
        }
      };
	}; // class tree
} // namespace

#endif
