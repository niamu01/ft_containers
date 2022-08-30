#include <iostream> //print

#if 0
  #include <map>
  namespace ft = std;
#else
  #include "map.hpp"
#endif

int main(void) {
  ft::map<int, char> m;

  std::cout << m.size() << std::endl;

  return 0;
}