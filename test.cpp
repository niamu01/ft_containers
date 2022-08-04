#include <iostream>

#if 0
  #include <vector>
  namespace ft = std;
#else
  #include "vector.hpp"
#endif

int main()
{

    ft::vector<int> a(1,'a');

    std::cout << "a";
    std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;

//    ft::vector<int>::iterator b_it = a.begin();
//    ft::vector<int>::iterator e_it = --a.end();
//    ft::vector<int>::reverse_iterator rb_it = a.rbegin();
//    ft::vector<int>::reverse_iterator re_it = --a.rend();

//     std::cout << *b_it << std::endl;
//     std::cout << *e_it << std::endl;
//     std::cout << *rb_it << std::endl;
//     std::cout << *re_it << std::endl;

//ft::vector<int>::iterator print = a.begin();

//    ft::vector<int>::iterator it = a.begin() + 2;
//    ft::vector<int>::iterator it2 = a.begin() + 1;


    // std::cout << a.size() << ", " << a.capacity() << std::endl;

    // a.reserve(1);

    // std::cout << a.size() << ", " << a.capacity() << std::endl;

    // int i = 5;

    // while (--i) {
    //     std::cout << "1" << std::endl;
    // }

    // i = 5;
    // while (i--) {
    //     std::cout << "2" << std::endl;
    // }



    // try {

    // ft::vector<int> a;

    // a.push_back(1);
    // a.push_back(2);
    // a.push_back(3);
    // a.push_back(4);

    // std::cout << a.at(2);
    // std::cout << '\n';

    // for (unsigned i=0; i<a.size(); i++)
    //     std::cout << a.at(i) << ' ';
    // std::cout << '\n';

    // std::cout << a.at(5) << std::endl;
    // } catch (ft::out_of_range& e) {
    //     std::cout << "a: " << e.what() << std::endl;
    // }

    // std::cout << "b" << std::endl;
}