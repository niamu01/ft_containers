#include <iostream> //print

#if 0
  #include <map>
  namespace ft = std;
#else
  #include "map.hpp"
#endif

int main(void) {
  ft::map<int, char> m;
  ft::pair<int, char> p(1, 'a');

  m.insert(p);

  std::cout << m.size() << std::endl;

  return 0;
}