#ifndef UTILITY_HPP
#define UTILITY_HPP

//  make pair, pair

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
    /*
     * Default constructor.
     * Value-initializes both elements of the pair, first and second.
     */
    pair() {
      first();
      second();
    };

    /*
     * Initializes first with x and second with y.
     */
    pair(const T1 &x, const T2 &y) {
      first(x);
      second(y);
    };

    /*
     * Initializes first with p.first and second with p.second.
     */
    template<class U1, class U2>
    pair(const pair<U1, U2> &p) {
      first(p.first);
      second(p.second);
    };

    /*
     * Copy constructor is implicitly declared
     */
    pair(const pair &p) = default; //todo: default

    /*The assignment operator is implicitly declared.
     * Using this assignment operator makes the program ill-formed
     * if either T1 or T2 is a const-qualified type, or a reference type,
     * or a class type with an inaccessible copy assignment operator,
     * or an array type of such class.
     */
    pair &operator=(const pair &other) {
      first = other.first;
      second = other.second;
    };
  }; //struct pair

  /*  NON-MEMBER FUNCTIONS  */
  /*
   * Creates a std::pair object, deducing the target type from the types of arguments.
   */
  template< class T1, class T2 >
  ft::pair<T1,T2> make_pair( T1 t, T2 u ) {
    ft::pair<T1, T2> p;
    p.first = t;
    p.second = u;

    return (p);
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

} //namespace

#endif
