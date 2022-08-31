#include <iostream> //print

#if 0
#include <stack>
  namespace ft = std;
#else
#include "stack.hpp"
#endif


template <typename T>
class foo {
public:
  typedef T	value_type;

  foo(void) : value(), _verbose(false) { };
  foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
  foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
  ~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
  void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
  void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
  foo &operator=(value_type src) { this->value = src; return *this; };
  foo &operator=(foo const &src) {
    if (this->_verbose || src._verbose)
      std::cout << "foo::operator=(foo) CALLED" << std::endl;
    this->value = src.value;
    return *this;
  };
  value_type	getValue(void) const { return this->value; };
  void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

  operator value_type(void) const {
    return value_type(this->value);
  }
private:
  value_type	value;
  bool		_verbose;
};



template <typename T_STACK>
void	printSize(T_STACK &stck, bool print_content = 1)
{
  std::cout << "size: " << stck.size() << std::endl;
  if (print_content)
  {
    std::cout << std::endl << "Content was:" << std::endl;
    while (stck.size() != 0) {
      std::cout << "- " << stck.top() << std::endl;
      stck.pop();
    }
  }
  std::cout << "###############################################" << std::endl;
}



#define TESTED_TYPE foo<int>
#define t_stack_ ft::stack<TESTED_TYPE>
typedef t_stack_::container_type container_type;

int		main(void)
{
  container_type	ctnr;

  ctnr.push_back(21);
  ctnr.push_back(42);
  ctnr.push_back(1337);
  ctnr.push_back(19);
  ctnr.push_back(0);
  ctnr.push_back(183792);

  t_stack_		stck(ctnr);

  std::cout << "empty: " << stck.empty() << std::endl;
  std::cout << "size: " << stck.size() << std::endl;

  stck.push(1);
  stck.push(2);
  stck.push(3);
  stck.push(4);
  stck.push(5);
  stck.push(6);

  std::cout << "Added some elements" << std::endl;

  std::cout << "empty: " << stck.empty() << std::endl;
  printSize(stck);

  return (0);
}
