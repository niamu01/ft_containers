#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {
  template <class T1, class T2>
  struct pair {
    /*  MEMBER TYPES  */
    typedef T1 first_type;
    typedef T2 second_type;

    /*  MEMBER OBJECTS  */
    first_type first;
    second_type second;

    /*  MEMBER FUNCTIONS  */
    pair() : first(), second() {};

    pair(const first_type& x, const second_type& y) : first(x), second(y) {};

    template<class U1, class U2>
    pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {};

    pair& operator=(const pair& other) {
      if (this != &other) {
        this->first = other.first;
        this->second = other.second;
      }

      return (*this);
    };
  }; //struct pair

  /*  NON-MEMBER FUNCTIONS  */
  template< class T1, class T2 >
  ft::pair<T1,T2> make_pair( T1 t, T2 u ) {
    return (pair<T1, T2>(t, u));
  };

  template< class T1, class T2 >
  bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    if (lhs.first == rhs.first)
      return (lhs.second == rhs.second);
    return false;
  };

  template< class T1, class T2 >
  bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    return !(operator==(lhs, rhs));
  };

  template< class T1, class T2 >
  bool operator< ( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    if (lhs.first == rhs.first)
      return (lhs.second < rhs.second);
    return (lhs.first < rhs.first);
  };

  template< class T1, class T2 >
  bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    if (lhs.first == rhs.first)
      return (lhs.second <= rhs.second);
    return (lhs.first <= rhs.first);
  };

  template< class T1, class T2 >
  bool operator> ( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    if (lhs.first == rhs.first)
      return (lhs.second > rhs.second);
    return (lhs.first > rhs.first);
  };

  template< class T1, class T2 >
  bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
    if (lhs.first == rhs.first)
      return (lhs.second >= rhs.second);
    return (lhs.first >= rhs.first);
  };

  template <typename Pair>
  struct use_first {
    typedef typename Pair::first_type result_type;

    const result_type& operator()(const Pair& x) const {
      return x.first;
    }
  };

  template <typename T>
  struct use_self {
    typedef T result_type;

    const result_type& operator()(const T& x) const {
      return x;
    }
  };

  template< class U >
  struct rebind {
    typedef std::allocator<U> other;
  };

} //namespace

#endif
