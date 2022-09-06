#ifndef _TREE_HPP
#define _TREE_HPP

#include <functional> //std::less
#include "utility.hpp" //ft::rebind, ft::pair
#include "iterator.hpp" //ft::reverse_iterator
#include "functional.hpp" //ft::less<T>
//#include "type_traits.hpp" //ft::enable_if, ft::is_integral

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
  template<typename T, typename pointer = T*, typename reference = T&>
  struct tree_iterator {
    typedef T                                         value_type;
    typedef ft::tree_node<T>                          node_type;
    typedef std::ptrdiff_t                            difference_type;
    typedef std::bidirectional_iterator_tag           iterator_category;

  private:
    node_type* _node;

  public:
    explicit tree_iterator(node_type* pNode = NULL) : _node(pNode) {};

    tree_iterator(const tree_iterator<T>& other) : _node(other.base()) {};

    virtual ~tree_iterator() {};

    tree_iterator& operator=(const tree_iterator<T>& x) {
      if (this != &x)
        _node = x.base();

      return *this;
    };

    node_type* base() const {
      return _node;
    };

    reference operator*() const {
      return (*this->_node->_value);
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
//      if (_node->_right->_value) {
//        _node = _node->_right;
//        while (_node->_left->_value)
//          _node = _node->_left;
//      } else {
//        if (_node == _node->_parent->_left)
//          _node = _node->_parent;
//        else {
//          while (_node->_parent->_value && _node != _node->_parent->_left)
//            _node = _node->_parent;
//          if (_node->_parent->_value)
//            _node = _node->_parent;
//        }
//      }
//      return *this;

    tree_iterator operator++(int) {
      tree_iterator temp(*this);
      this->operator++();
      return (temp);
    };

    tree_iterator& operator--() {
      node_type *temp = NULL;

      if (_node->_value == NULL){
        temp = _node->_parent;
      } else if (_node->_left->_value != NULL) {
        temp = _node->_left;
        while (temp->_right->_value != NULL)
          temp = temp->_right;
      } else {
        temp = _node->_parent;
        if (temp->_left ==_node) {
          while (temp->_parent->_left == temp)
            temp = temp->_parent;
          temp = temp->_parent;
        }
      }
      _node = temp;

      return *this;
    };
//      if (_node->_left->_value) {
//        _node = _node->_left;
//        while (_node->_right->_value)
//          _node = _node->_right;
//      } else {
//        if (_node == _node->_parent->_right)
//          _node = _node->_parent;
//        else {
//          while (_node->_parent->_value && _node != _node->_parent->_right)
//            _node = _node->_parent;
//          if (_node->_parent->_value)
//            _node = _node->_parent;
//        }
//      }
//      return *this;

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

    _tree(const _tree &other, const key_compare &comp = key_compare(),
          const node_allocator_type &alloc = node_allocator_type())
    : _node_alloc(alloc),
      _compare(comp),
      _root(NULL),
      _nil(NULL),
      _size(0) {
      _nil = make_nil();
      copy(other);
      _nil->_parent = tree_max(_root);
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

      if (hint != NULL)
        insert_position = find_position_by_hint(hint, value); //check hint->value was NULL in this function

      ft::pair<node_pointer, bool> ret_pair = try_insert(insert_position, insert_node);

      //insert fail
      if (ret_pair.second == false) {
        _node_alloc.destroy(insert_node);
        _node_alloc.deallocate(insert_node, 1);

        return (ret_pair); //<insert_position, false>
      }
      //insert success -> check balance
      check_sort_insert(insert_node);

//      node_pointer last_node = tree_max(_root);
//      _nil = last_node->_right;
      _nil->_parent = tree_max(_root);

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

      //target이랑 target의 child랑 교체
      replace_a_to_b(target, child);

      if (target->_color == BLACK) {
        if (child->_color == RED)
          child->_color = BLACK;
        else
          check_sort_erase(child);
      }

      if (target->_parent->_value == NULL)
        _root = _nil;

      _nil->_parent = tree_max(_root);
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

    node_pointer find(const value_type &value) {
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
    }

    void copy(const _tree& tree) {
      clear();
      copy(tree._root);
    }

    //copy tree by root node
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
    //value보다 크거나 같은 범위
    node_pointer lower_bound(const value_type &value) const {
      iterator it(tree_min(_root));
      iterator ite(_nil);

      while (it != ite && _compare(*it, value))
        it++;

      return it.base();
    };

    //value보다 작거나 같은 범위
    node_pointer upper_bound(const value_type &value) const {
      iterator it(tree_min(_root));
      iterator ite(_nil);

      while (it != ite && !_compare(value, *it))
        it++;

      return it.base();
    };

  /*  ITERATORS  */
    iterator begin()                        { return iterator(tree_min(_root)); };
    const_iterator begin() const            { return const_iterator(tree_min(_root)); };
    iterator end()                          { return iterator(_nil); };
    const_iterator end() const              { return const_iterator(_nil); };
    reverse_iterator rbegin()               { return reverse_iterator(end()); };
    const_reverse_iterator rbegin() const   { return const_reverse_iterator(end()); };
    reverse_iterator rend()                 { return reverse_iterator(begin()); };
    const_reverse_iterator rend() const     { return const_reverse_iterator(begin()); };

/*  PRIVATE FUNCTION  */
  private:
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

    node_pointer& get_sibling(node_pointer node) const {
      if (node->_parent->_left == node)
        return node->_parent->_right;

      else //if (node->_parent->_right == node)
        return node->_parent->_left;
    };

    node_pointer get_uncle(node_pointer node) {
      if (node->_parent == node->_parent->_parent->_left)
        return node->_parent->_parent->_right;
      else if(node->_parent == node->_parent->_parent->_right)
        return node->_parent->_parent->_left;
      else
        return NULL;
    }

    node_pointer get_grand(node_pointer node) const {
      return node->_parent->_parent;
    }

    node_pointer make_nil() {
      node_pointer nil;

      nil = _node_alloc.allocate(1);
      _node_alloc.construct(nil, node_type());

      nil->_color = BLACK;
      nil->_left = nil;
      nil->_right = nil;
      nil->_parent = nil;
      nil->_value = NULL;

      return (nil);
    };

    //have to set color, child, parent after
    node_pointer make_node(const value_type &value) {
      node_pointer ret = _node_alloc.allocate(1);
      _node_alloc.construct(ret, node_type(value));

      return (ret);
    }

  /*  ROTATE  */
//    node_pointer left_rotate(node_pointer p) {
//      node_pointer ret = p->_right;
//
//      p->_right = ret->_left;
//
//      if (ret->_left)
//        ret->_left->_parent = p;
//
//      ret->_parent = p->_parent;
//
//      if (p->_parent == NULL)
//        _root = ret;
//      else if (p->_parent->_left == p)
//        p->_parent->_left = ret;
//      else
//        p->_parent->_right = ret;
//
//      ret->_left = p;
//      p->_parent = ret;
//
//      return ret;
//    };
    node_pointer left_rotate(node_pointer p) {
      node_pointer ret = p->_right;
      node_pointer parent = p->_parent;

      if (ret->_left->_value)
        ret->_left->_parent = p;

      p->_right = ret->_left;

      p->_parent = ret;

      ret->_left = p;
      ret->_parent = parent;

      if (parent->_value) {
        if (parent->_left == p)
          parent->_left = ret;
        else
          parent->_right = ret;
      } else {
        _root = ret;
      }

      return ret;
    };

//  node_pointer right_rotate(node_pointer p) {
//    node_pointer ret = p->_left;
//
//    p->_left = ret->_right;
//
//    if (ret->_right)
//      ret->_right->_parent = p;
//
//    ret->_parent = p->_parent;
//
//    if (p->_parent == NULL)
//      _root = ret;
//    else if (p->_parent->_left == p)
//      p->_parent->_left = ret;
//    else
//      p->_parent->_right = ret;
//
//    ret->_right = p;
//    p->_parent = ret;
//
//    return ret;
//  };
    node_pointer right_rotate(node_pointer p) {
      node_pointer ret = p->_left;
      node_pointer parent = p->_parent;

      if (ret->_right->_value)
        ret->_right->_parent = p;

      p->_left = ret->_right;

      p->_parent = ret;

      ret->_right = p;
      ret->_parent = parent;

      if (parent->_value != NULL) {
        if (parent->_right == p)
          parent->_right = ret;
        else
          parent->_left = ret;
      } else {
        _root = ret;
      }

        return ret;
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
          return (ft::make_pair(insert_position, false));
      }
      return ft::make_pair(insert_position, true);
    };

//  find_position_by_hint(hint, value) -> insert_position
    node_pointer find_position_by_hint(node_pointer hint, value_type value) {//todo: make func
      (void) hint;
      (void) value;

      node_pointer null_ret = NULL;
      return null_ret;
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

      //uncle 이 없는 경우 일자 형태의 tree일 수 있어 rotate해주기
//      if (uncle->_value == NULL) {
//        rotate_LR(node->_parent, node == node->_parent->_left);
//        return;
//      }

      if (uncle->_value && uncle->_color == RED) {
        node->_parent->_color = BLACK;
        uncle->_color = BLACK;
        node->_parent->_parent->_color = RED;
        check_sort_insert(node->_parent->_parent);
      } else { //if (uncle->_value && uncle->_color == BLACK) {
        node_pointer grand = node->_parent->_parent;

        //case2. uncle이 BLACK이고 x가 right child:
        if (grand->_value) {
          if (node == node->_parent->_right && node->_parent == grand->_left) {
            // x->_parent에서 l-r한 후 case3으로 이동
            rotate_LR(node->_parent, LEFT);
            node = node->_left;
          } else if (node == node->_parent->_left && node->_parent == grand->_right) {
            // case2와 대칭인 경우
            rotate_LR(node->_parent, RIGHT);
            node = node->_right;
          }
          check_sort_insert_2(node);
        }
      }
    };

    void check_sort_insert_2(node_pointer node) {
      node_pointer grand = node->_parent->_parent;

      if (grand->_value) {
        grand->_color = RED;
        node->_parent->_color = BLACK;
        rotate_LR(grand, node == node->_parent->_left);
      }
    }

  /*  ERASE UTILS  */
  node_pointer replace_erase_node(node_pointer node)
  {
    /**
     * @brief replace and erase
     * 이진 탐색 트리에서 삭제를 수행할 때에는 왼쪽 서브트리에서의 최댓값이나,
     * 오른쪽 서브트리에서의 최솟값을 삭제한 노드의 위치에 삽입한다는 것.
     * 삭제한 노드를 대체할 노드에는 반드시 1개의 자식 노드만 있다는 점이다.
     * 그 이유는 즉슨, 자식 2개를 보유한 노드일 경우,
     * 왼쪽 자식 < 대체 노드 < 오른쪽 자식이라는 결론이 도출되므로, 자식 2개를 보유할 가능성은 절대적으로 0이라는 것이다.
     *
     * ->node의 leftChild가 있으면, 왼쪽 서브트리에서 최댓값,
     * ->node의 leftChild가 없으면, 오른쪽 서브트리에서 최솟값을 찾는다.
     * 찾은 값의 value를 node에 복사하고, 찾은 그 노드는 삭제해야 하므로 리턴한다.
     */

    node_pointer res;
    if (node->_left->_value != NULL)
    {
      res = node->_left;
      while (res->_right->_value != NULL)
        res = res->_right;
    }
    else if (node->_right->_value != NULL)
    {
      res = node->_right;
      while (res->_left->_value != NULL)
        res = res->_left;
    }
    else
      return (node);

    node_pointer tmp_parent = node->_parent;
    node_pointer tmp_left = node->_left;
    node_pointer tmp_right = node->_right;
    bool tmp_color = node->_color;

    //node의 left/rightChild 설정
    node->_left = res->_left;
    if (res->_left->_value != NULL)
      res->_left->_parent = node;
    node->_right = res->_right;
    if (res->_right->_value != NULL)
      res->_right->_parent = node;

    //res를 node->_parent의 left/rightChild로 설정
    if (tmp_parent->_left == node)
      tmp_parent->_left = res;
    else if (tmp_parent->_right == node)
      tmp_parent->_right = res;

    if (res == tmp_left)
    {
      //res의 형제를 res의 left/rightChild로 연결
      tmp_right->_parent = res;
      res->_right = tmp_right;
      //node를 res의 left/rightChild로 연결
      node->_parent = res;
      res->_left = node;
    }
    else if (res == tmp_right)
    {
      tmp_left->_parent = res;
      res->_left = tmp_left;
      node->_parent = res;
      res->_right = node;
    }
    else
    {
      //res와 node가 멀리 떨어진 경우
      tmp_left->_parent = res;
      res->_left = tmp_left;
      tmp_right->_parent = res;
      res->_right = tmp_right;
      node->_parent = res->_parent;
      res->_parent->_right = node;
    }

    //res의 parent 연결
    res->_parent = tmp_parent;

    if (res->_parent->_value == NULL)
      this->_root = res;
    node->_color = res->_color;
    res->_color = tmp_color;

    return (node);
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

      //case1. sibling노드 w가 RED
      //w->_color를 BLACK, node->_parent를 RED로 바꾼 뒤
      //left rotate(node->_parent)
      // node의 자매노드를 w로 두면 case 2, 3, 4로 넘어갈 수 있다.
      if (sibling->_color == RED) {
        sibling->_color = BLACK;
        node->_parent->_color = RED;

        rotate_LR(node->_parent, node != node->_parent->_left);

      } else if (sibling->_color == BLACK) {

        if (sibling->_left->_color == BLACK
            && sibling->_right->_color == BLACK) {
          //case2. sibling노드 w가 BLACK이고 w의 두 자식 노드가 BLACK
          //w->color = RED
          //x를 x->parent로 옮김
          //x->parent는 x->parent->parent로 옮김
          //x->parent가 RED였다면 여기서 종료
          sibling->_color = RED;
          if (node->_parent->_color == RED)
            return;
//      x -> x_p, x_p-> x_p_p
//      check_sort_erase(node->_parent);
        } else if (sibling->_left->_color == RED
                   && sibling->_right->_color == BLACK) {
          //case3. sibling이 BLACK이고 left는 RED right는 BLACK
          //sibling->left = BLACK
          //sibling = RED
          //right_rotate(sibling)
          //이후 w를 x->p->r로 옮기면 case4
          sibling->_left->_color = BLACK;
          sibling->_color = RED;
          rotate_LR(sibling, RIGHT);
//      w -> x_p, x_p -> x_p_p 옮기면 case4가 됨 //todo: 3->4
        } else if (sibling->_right->_color == RED) {
          //case4. w가 BLACK이고 w->right가 RED
          //w의 color를 x_p의 color로 바꾸고
          //x_p의 color는 BlACK으로 바꿈
          //w->right를 BLACK으로 바꿈
          //left_rotate()
          sibling->_color = node->_parent->_color;
          node->_parent->_color = BLACK;
          sibling->_right->_color = BLACK;
          rotate_LR(sibling, LEFT); //z의 parent가 x->parent->right인 경우 대칭이라 반대로 rotation한다
        }
      }
    };
  }; //class tree
} //namespace

#endif
