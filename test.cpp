// #include "vector.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <iterator>

int main()
{

    std::vector<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);


std::vector<int>::iterator print = a.begin();

    std::vector<int>::iterator it = a.begin() + 2;
    std::vector<int>::iterator it2 = a.begin() + 1;
    a.erase(it, it2);

    for ( ; print != a.end(); print++)
        std::cout << *print << std::endl;




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

    // std::vector<int>::reverse_iterator rb_it = a.rbegin();
    // std::vector<int>::reverse_iterator re_it = a.rend();
    // std::vector<int>::iterator b_it = a.begin();
    // std::vector<int>::iterator e_it = a.end();

    // std::cout << *rb_it << std::endl;
    // std::cout << *re_it << std::endl;
    // std::cout << *b_it << std::endl;
    // std::cout << *e_it << std::endl;

    // try {

    // std::vector<int> a;

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
    // } catch (std::out_of_range& e) {
    //     std::cout << "a: " << e.what() << std::endl;
    // }

    // std::cout << "b" << std::endl;
}