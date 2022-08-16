#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
  /* equal */
  // # include <algorithm>
  // Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), and false otherwise.
  template< class InputIt1, class InputIt2 >
  bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ) {
    for (; first1 != last1; first1++, first2++) {
      if (!(*first1 == *first2))
        return false;
    }
    return true;
  };

  template< class InputIt1, class InputIt2, class BinaryPredicate >
  bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p ) {
    (void)p;
    for (; first1 != last1; first1++, first2++) {
      if (!pred(*first1, *first2))
        return false;
    }
    return true;
  };

  /* p:
  binary predicate which returns ​true if the elements should be treated as equal.
  The signature of the predicate function should be equivalent to the following:

    bool pred(const Type1 &a, const Type2 &b);

  While the signature does not need to have const &, 
  the function must not modify the objects passed to it 
  and must be able to accept all values of type (possibly const) Type1 and Type2 
  regardless of value category (thus, Type1 & is not allowed, 
  nor is Type1 unless for Type1 a move is equivalent to a copy (since C++11)).

  The types Type1 and Type2 must be such that objects of types InputIt1 and InputIt2 
  can be dereferenced and then implicitly converted to Type1 and Type2 respectively.​
  */

} //namespace

#endif