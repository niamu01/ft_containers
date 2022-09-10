#include <list>

#include <iostream> //print

#if 0
#include <set>
  namespace ft = std;
#else
#include "set.hpp"
#endif


// --- Class foo
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

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
  o << bar.getValue();
  return o;
}
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
  while (n-- > 0)
    ++it;
  return (it);
}

template <typename T>
T	dec(T it, int n)
{
  while (n-- > 0)
    --it;
  return (it);
}

#define _pair ft::pair

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
  o << "value: " << *iterator;
  if (nl)
    o << std::endl;
  return ("");
}

template <typename T_SET>
void	printSize(T_SET const &st, bool print_content = 1)
{
  std::cout << "size: " << st.size() << std::endl;
  std::cout << "max_size: " << st.max_size() << std::endl;
  if (print_content)
  {
    typename T_SET::const_iterator it = st.begin(), ite = st.end();
    std::cout << std::endl << "Content is:" << std::endl;
    for (; it != ite; ++it)
      std::cout << "- " << printPair(it, false) << std::endl;
  }
  std::cout << "###############################################" << std::endl;
}

template <typename T1>
void	printReverse(ft::set<T1> &st)
{
  typename ft::set<T1>::iterator it = st.end(), ite = st.begin();

  std::cout << "printReverse:" << std::endl;
  while (it-- != ite)
    std::cout << "-> " << printPair(it, false) << std::endl;
  std::cout << "_______________________________________________" << std::endl;
}

#define T1 std::string
typedef ft::set<T1>::iterator iterator;

static int iter = 0;

template <typename SET, typename U>
void	ft_insert(SET &st, U param)
{
	_pair<iterator, bool> tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = st.insert(param);
	std::cout << "insert return: " << printPair(tmp.first);
	std::cout << "Created new node: " << tmp.second << std::endl;
	printSize(st);
}

template <typename SET, typename U, typename V>
void	ft_insert(SET &st, U param, V param2)
{
	iterator tst;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tst = st.insert(param, param2);
	std::cout << "insert return: " << printPair(tst);
	printSize(st);
}

int		main(void)
{
	ft::set<T1> st, st2;

	ft_insert(st, "lol");
	ft_insert(st, "mdr");

	ft_insert(st, "mdr");
	ft_insert(st, "funny");

	ft_insert(st, "bunny");
	ft_insert(st, "fizz");
	ft_insert(st, "buzz");

	ft_insert(st, st.begin(), "fuzzy");

	ft_insert(st2, st2.begin(), "beauty");
	ft_insert(st2, st2.end(), "Hello");
	ft_insert(st2, st2.end(), "World");

	return (0);
}
