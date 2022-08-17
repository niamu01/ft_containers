#include <iostream> //print

#if 1
  #include <map>
  namespace ft = std;
#else
  #include "map.hpp"
  #include "_tree.hpp"
#endif

/* iterator */
ft::map<int, char> m;
ft::pair<int, char> p(0, 'a');

m[0] = 'a';

ft::map<int, char>::iterator it = m.end();

std::cout << *it << std::endl;