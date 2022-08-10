#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

// #include <type_traits>

namespace ft {

/* enable_if */
  template<bool B, class T = void>
  struct enable_if {};
  
  template<class T>
  struct enable_if<true, T> {
    typedef T type;
  };

  /* is_integral : 타입을 확인해 true, false로 반환하기 위한 구조체 */
  template< class T >
  struct is_integral;

  template<class T, T v>
  struct integral_constant {
    typedef T value_type;

    static const T value = v;
    // value_type = T;
    // type = integral_constant;
  };

  typedef ft::integral_constant<bool, true>  true_type;
  typedef ft::integral_constant<bool, false> false_type;

  template <class _Tp>
  struct is_integral : public false_type {};

  template <>
  struct is_integral<bool> : public true_type {};

  template <>
  struct is_integral<char> : public true_type {};

  template <>
  struct is_integral<signed char> : public true_type {};

  template <>
  struct is_integral<unsigned char> : public true_type {};

  template <>
  struct is_integral<char16_t> : public true_type {};

  template <>
  struct is_integral<char32_t> : public true_type {};

  template <>
  struct is_integral<wchar_t> : public true_type {};

  template <>
  struct is_integral<short> : public true_type {};

  template <>
  struct is_integral<unsigned short> : public true_type {};

  template <>
  struct is_integral<int> : public true_type {};

  template <>
  struct is_integral<unsigned int> : public true_type {};

  template <>
  struct is_integral<long> : public true_type {};

  template <>
  struct is_integral<unsigned long> : public true_type {};

  template <>
  struct is_integral<long long> : public true_type {};

  template <>
  struct is_integral<unsigned long long> : public true_type {};

}

#endif