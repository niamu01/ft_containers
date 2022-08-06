#include <iostream>

#if 0
  #include <vector>
  #include <type_traits>
  namespace ft = std;
#else
  #include "vector.hpp"
#endif

int main()
{
    // int i = 5;
    // int* ptr = &i;
    // int& ref = i;
    // ft::vector<int> a;
    // a.push_back(1);
    // a.push_back(2);
    // ft::vector<int>::iterator iter = a.begin();

    // std::cout << i << std::endl;

    // std::cout << ptr << std::endl;
    // std::cout << &ref << std::endl;

    // std::cout << *ptr << std::endl;
    // std::cout << ref << std::endl;

    // std::cout << &ptr << std::endl;
    // std::cout << "*ref indirection requires pointer operand" << std::endl;

    // std::cout << *iter << std::endl;

/* push_back, pop_back, size, capacity */
    // ft::vector<int> a;

    // std::cout << "a:\n";
    // std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;

    // std::cout << "    push_back 1 2 3:\n";
    // a.push_back(1);
    // a.push_back(2);
    // a.push_back(3);

    // std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;

    // a.pop_back();

    // std::cout << "    pop_back:\n";
    // std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
    
    // a.pop_back();
    // std::cout << "    pop_back:\n";
    // std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
    // a.pop_back();
    // std::cout << "    pop_back:\n";
    // std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
    // a.pop_back();
    // std::cout << "    pop_back:\n";
    // std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
    // a.pop_back();
    // std::cout << "    pop_back:\n";
    // std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;

/* front, back */
    // ft::vector<int> b;

    // std::cout << "b:\n";
    // std::cout << "size: " << b.size() << ", capacity: " << b.capacity() << std::endl;

    // std::cout << "    push_back 4 5 6:\n";
    // b.push_back(4);
    // b.push_back(5);
    // b.push_back(6);

    // std::cout << "b:\n";
    // std::cout << "size: " << b.size() << ", capacity: " << b.capacity() << std::endl;

    // std::cout << "front:\n";
    // std::cout << b.front() << std::endl;

    // std::cout << "back:\n";
    // std::cout << b.back() << std::endl;

    // std::cout << "\n";

/* erase */
    // ft::vector<int> c;

    // std::cout << "    push_back 4 5 6:\n";
    // c.push_back(4);
    // c.push_back(5);
    // c.push_back(6);

    // ft::vector<int>::iterator it = c.begin();
    // std::cout << "c.begin(): " << *it << std::endl;

    // ft::vector<int>::iterator erase_it1 = c.erase(it);
    // std::cout << "erase_it: " << *erase_it1 << std::endl;

    // ft::vector<int>::iterator it1 = c.begin();
    // std::cout << "c.begin(): " << *it1 << std::endl;

    // ft::vector<int>::iterator erase_it2 = c.erase(it);
    // std::cout << "erase_it: " << *erase_it2 << std::endl;

    // ft::vector<int>::iterator it2 = c.begin();
    // std::cout << "c.begin(): " << *it2 << std::endl;

    // ft::vector<int>::iterator erase_it3 = c.erase(it);
    // std::cout << "erase_it: " << *erase_it3 << std::endl;

/* iterator test */
    // ft::vector<int> d;

    // std::cout << "    push_back 4 5 6:\n";
    // d.push_back(4);
    // d.push_back(5);
    // d.push_back(6);

    // std::cout << "begin:\n";
    // ft::vector<int>::iterator b_it = d.begin();
    // std::cout << *b_it << std::endl;

    // std::cout << "end:\n";
    // ft::vector<int>::iterator e_it = d.end();
    // std::cout << *e_it << std::endl;

    // std::cout << "rbegin:\n";
    // std::cout << *rb_it << std::endl;
    // ft::vector<int>::reverse_iterator rb_it = a.rbegin();

    // std::cout << "rend:\n";
    // std::cout << *re_it << std::endl;
    // ft::vector<int>::reverse_iterator re_it = a.rend();

/* at, operator test */
    // ft::vector<int> e;

    // std::cout << "    push_back 7 8 9:\n";
    // e.push_back(7);
    // e.push_back(8);
    // e.push_back(9);

    // std::cout << e.at(1) << std::endl;
    // std::cout << e[1] << std::endl;

/* max size */
    // ft::vector<int> f;
    // ft::vector<double> g;
    // ft::vector<char> h;

    // std::cout << "int:" << f.max_size() << std::endl;
    // std::cout << "double:" << g.max_size() << std::endl;
    // std::cout << "char:" << h.max_size() << std::endl;

/* clear, empty */
    // ft::vector<int> i;

    // std::cout << "empty: " << (i.empty() ? "true" : "false") << std::endl;
    // std::cout << "size: " << i.size() << "\ncapacity: " << i.capacity() << std::endl;

    // std::cout << "    push_back 1 2 3\n";
    // i.push_back(1);
    // i.push_back(2);
    // i.push_back(3);

    // std::cout << "empty: " << (i.empty() ? "true" : "false") << std::endl;
    // std::cout << "size: " << i.size() << "\ncapacity: " << i.capacity() << std::endl;

    // i.clear();

    // std::cout << "empty: " << (i.empty() ? "true" : "false") << std::endl;
    // std::cout << "size: " << i.size() << "\ncapacity: " << i.capacity() << std::endl;

/* reserve, resize */
    // ft::vector<int> j;

    // std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;

    // std::cout << "    push_back 1 2 3\n";
    // j.push_back(1);
    // j.push_back(2);
    // j.push_back(3);
    // std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;

    // std::cout << "    reserve 6\n";
    // j.reserve(6);
    // std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
    // std::cout << "    reserve 2\n";
    // j.reserve(2);
    // std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
    // std::cout << "    reserve 7\n";
    // j.reserve(7);
    // std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;

    // std::cout << "    resize 5\n";
    // j.resize(5, 0);
    // std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
    // std::cout << "    resize 1\n";
    // j.resize(1, 0);
    // std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
    // std::cout << "    resize 7\n";
    // j.resize(7, 0);
    // std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;

/* insert, assign */
//     ft::vector<int> k;

//     k.push_back(1);
//     k.push_back(2);
//     k.push_back(3);

//     // pos, value
//     k.insert(2, 14);
//     // pos, count, value
//     k.insert(3, 5, 15);
//     // pos, it, it

//     ft::vector<int>::iterator it = k.begin();
//     while (it != k.end()) {
//         std::cout << *it << std::endl;
//         it++;
//     }

//     // count, value
//     k.assign(2, 14);
//     // it, it
//     k.assign(2, 14);

// std::cout << "=============" << std::endl;

//     ft::vector<int>::iterator it2 = k.begin();
//     while (it2 != k.end()) {
//         std::cout << *it2 << std::endl;
//         it2++;
//     }

/* swap */
    // ft::vector<int> l;

    // l.push_back(1);
    // l.push_back(2);
    // l.push_back(3);

    // std::cout << "l: " << l.front() << std::endl;

    // ft::vector<int> m;

    // m.push_back(4);
    // m.push_back(5);
    // m.push_back(6);

    // std::cout << "m: " << m.front() << std::endl;

    // l.swap(m);
    // std::cout << "l: " << l.front() << std::endl;
    // std::cout << "m: " << m.front() << std::endl;

/* test... - out_of_range error message*/
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
/* test... - capacity == size -> change capacity? */

    return 0;
}