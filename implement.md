
[ ]  iterators_traits - <iterator> 헤더 내에 구현된 템플릿 클래스
[ ]  reverse_iterator
    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

[ ]  enable_if SFINAE
    template< bool B, class T = void >
    struct enable_if;

    bool B 에 true가 오면 enable_if 구조체에 type이라는 자료형이 생김
    따라서 enable_if의 첫 인자로 bool을 반환하는 구문을 넣은 후
    type이 생겼는지 아닌지를 판별할 수 있음

    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };
    enable_if::type이 가능할 경우 Cond는 true가 된다

[ ]  is_integral
    template< class T >
    struct is_integral;

    is_integral는 자료형별로 특수화가 되어있고, 
    false_type과 true_type을 상속 받는 빈 구조체로 되어있다

    typedef integral_constant<bool,true> true_type;
    typedef integral_constant<bool,false> false_type;

[ ]  equal and/or lexicographical_compare
    
[ ]  std::pair
[ ]  std::make_pair