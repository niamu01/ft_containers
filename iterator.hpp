#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft {
/* iterator_traits */
  template<class Iterator>
  struct iterator_traits {
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
  };

  template<class T>
  struct iterator_traits<T*> {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;
  };

  template<class T>
  struct iterator_traits<const T*> {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef std::random_access_iterator_tag iterator_category;
  };

  template<class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T*, class Reference = T&>
  struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
  };

  struct input_iterator_tag  {};
  struct output_iterator_tag {};
  struct forward_iterator_tag       : public input_iterator_tag         {};
  struct bidirectional_iterator_tag : public forward_iterator_tag       {};
  struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/* reverse_iterator */
  template <class Iterator>
  class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference>
  {
	public:
    typedef Iterator                                            iterator_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::reference       reference;
    typedef typename iterator_traits<Iterator>::pointer         pointer;
    // typedef	typename ft::iterator_traits<Iter>::iterator_category iterator_category;
    // typedef	typename ft::iterator_traits<Iter>::value_type value_type;

	protected:
		iterator_type _current; //the underlying iterator of which base() returns a copy

	public:
    explicit reverse_iterator() : _current() {};
    explicit reverse_iterator(iterator_type x) : _current(x) {};

    template< class U > 
    reverse_iterator( const reverse_iterator<U>& other ) : _current(other.base()) {};

    ~reverse_iterator() {};

    template< class U > 
    reverse_iterator& operator=( const reverse_iterator<U>& other ) {
      _current = other.base();

      return *this;
    };

    Iterator base() const {
      return _current;
    };

    reference operator*() const {
    Iterator temp = _current;
    return *--temp;
//      return *_current;
    };

    pointer operator->() const {
      return &(operator*());
      // return std::addressof(operator*());
    };

    reference operator[](difference_type n) const {
      return base()[-n-1]; //base()[-n-1]
    };

    reverse_iterator& operator++() {
      this->_current--;

      return *this;
    };

    reverse_iterator  operator++(int) {
      reverse_iterator temp = *this;

      this->_current--;

      return temp;
    };

    reverse_iterator& operator+=(difference_type n) {
      *this = operator+(n);

      return *this;
    };

    reverse_iterator  operator+ (difference_type n) const {
      return reverse_iterator(_current-n);
    };

    reverse_iterator& operator--() {
      this->_current++;

      return *this;
    };

    reverse_iterator  operator--(int) {
      reverse_iterator temp = *this;

      this->_current++;

      return temp;
    };

    reverse_iterator& operator-=(difference_type n) {
      *this = operator-(n);

      return *this;
    };

    reverse_iterator  operator- (difference_type n) const {
      return reverse_iterator(_current+n);
    };
  };

  template <class Iterator1, class Iterator2>
  bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return lhs.base() == rhs.base();
  };

  template <class Iterator1, class Iterator2>
  bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return lhs.base() != rhs.base();
  };

  template <class Iterator1, class Iterator2>
  bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return lhs.base() > rhs.base();
  };

  template <class Iterator1, class Iterator2>
  bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return lhs.base() >= rhs.base();
  };

  template <class Iterator1, class Iterator2>
  bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return lhs.base() < rhs.base();
  };

  template <class Iterator1, class Iterator2>
  bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return lhs.base() <= rhs.base();
  };

  template< class Iter >
    reverse_iterator<Iter>
      operator+ ( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
        return reverse_iterator<Iter>(it.base() - n);
  };

  template< class Iterator >
    typename reverse_iterator<Iterator>::difference_type
      operator- ( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) {
        return rhs.base() - lhs.base();
  };

  template< class Iterator_L, class Iterator_R >
    typename reverse_iterator<Iterator_L>::difference_type
      operator- ( const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs ) {
        return rhs.base() - lhs.base();
  };

  typedef size_t size_type;

  template<class iterator>
  size_type distance(iterator first, iterator second) {
    size_type ret = 0;

    while (*first != *second) {
      *first++;
      ret++;
    }

    return ret;
  };

} //namespace

#endif