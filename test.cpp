#include <iostream>

#if 0
  #include <vector>
  namespace ft = std;
#else  
  #include "vector.hpp"
#endif

int main()
{
	ft::vector<int> foo(3, 15);
	ft::vector<int> bar(5, 42);
	
	ft::vector<int>::const_iterator it_foo = foo.begin();
	ft::vector<int>::const_iterator it_bar = bar.begin();

	std::cout << "BEFORE SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	for (ft::vector<int>::iterator it3 = foo.begin(); it3 != foo.end(); it3++) {
      std::cout << *it3 << ' ';
    }
	std::cout << "bar contains:" << std::endl;
	for (ft::vector<int>::iterator it4 = bar.begin(); it4 != bar.end(); it4++) {
    std::cout << *it4 << ' ';
  }

	foo.swap(bar);

	std::cout << "AFTER SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	for (ft::vector<int>::iterator it2 = foo.begin(); it2 != foo.end(); it2++) {
      std::cout << *it2 << ' ';
    }
	std::cout << "bar contains:" << std::endl;
	for (ft::vector<int>::iterator it1 = bar.begin(); it1 != bar.end(); it1++) {
      std::cout << *it1 << ' ';
    }

	std::cout << "Iterator validity:" << std::endl;
	std::cout << (it_bar == foo.begin()) << std::endl;
	std::cout << (it_foo == bar.begin()) << std::endl; //const가 뒤에 있다면...

/* iterator operator */
//    ft::vector<int> vec;
//
//    vec.push_back(1);
//    vec.push_back(2);
//    vec.push_back(3);

/* iterator */
    // ft::vector<int>::iterator it = vec.begin();
    // ft::vector<int>::iterator it2 = vec.end();

    // std::cout << *it << ", " << *it2 << std::endl;

    // ++it;
    // --it2;

    // std::cout << *it << ", " << *it2 << std::endl;

    // it++;
    // it2--;

    // std::cout << *it << ", " << *it2 << std::endl;

    // *it = 100;
    // std::cout << *it << ", " << *it2 << std::endl;

/* reverse iterator */
//    ft::vector<int>::reverse_iterator it3 = vec.rbegin();
//    ft::vector<int>::reverse_iterator it4 = vec.rend();
//
//    std::cout << *it3 << ", " << *it4 << std::endl;
//
//    ++it3;
//    --it4;
//
//    std::cout << *it3 << ", " << *it4 << std::endl;
//
//    it3++;
//    it4--;
//
//    std::cout << *it3 << ", " << *it4 << std::endl;
//
//    *it3 = 100;
//    std::cout << *it3 << ", " << *it4 << std::endl;

/* const iterator */
//     ft::vector<int>::const_iterator c_it1 = vec.begin();
//     ft::vector<int>::const_iterator c_it2 = vec.end();
//
//     std::cout << *c_it1 << ", " << *c_it2 << std::endl;
//
////      *c_it1 = 100;
////      std::cout << *c_it1 << ", " << *c_it2 << std::endl;
//
//     ft::vector<int>::const_reverse_iterator c_it3 = vec.rbegin();
//     ft::vector<int>::const_reverse_iterator c_it4 = vec.rend();
//
//     std::cout << *c_it3 << ", " << *c_it4 << std::endl;
//
////      *c_it3 = 100;
////      std::cout << *c_it3 << ", " << *c_it4 << std::endl;

//    *it++;
//    *it2--;
//    std::cout << *it << ", " << *it2 << std::endl;

/* != test */
//     for (ft::vector<int>::iterator it3 = vec.begin(); it3 != vec.end(); it3++) {
//       std::cout << *it3 << ' ';
//     }
//     std::cout << std::endl;

/* push_back, pop_back, size, capacity */
//     ft::vector<int> a;
//
//     std::cout << "a:\n";
//     std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
//
//     std::cout << "    push_back 1 2 3:\n";
//     a.push_back(1);
//     a.push_back(2);
//     a.push_back(3);
//
//     std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
//
//     a.pop_back();
//
//     std::cout << "    pop_back:\n";
//     std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
//
//     a.pop_back();
//     std::cout << "    pop_back:\n";
//     std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
//     a.pop_back();
//     std::cout << "    pop_back:\n";
//     std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
//     a.pop_back();
//     std::cout << "    pop_back:\n";
//     std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
//     a.pop_back();
//     std::cout << "    pop_back:\n";
//     std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;

/* front, back */
//     ft::vector<int> b;
//
//     std::cout << "b:\n";
//     std::cout << "size: " << b.size() << ", capacity: " << b.capacity() << std::endl;
//
//     std::cout << "    push_back 4 5 6:\n";
//     b.push_back(4);
//     b.push_back(5);
//     b.push_back(6);
//
//     std::cout << "b:\n";
//     std::cout << "size: " << b.size() << ", capacity: " << b.capacity() << std::endl;
//
//     std::cout << "front:\n";
//     std::cout << b.front() << std::endl;
//
//     std::cout << "back:\n";
//     std::cout << b.back() << std::endl;
//
//     std::cout << "\n";

/* erase */
  //    ft::vector<int> c;

  //    std::cout << "    push_back 4 5 6:\n";
  //    c.push_back(4);
  //    c.push_back(5);
  //    c.push_back(6);

  //    ft::vector<int>::iterator it1 = c.begin();
  //    std::cout << "c.begin(): " << *it1 << std::endl;
  //    for (ft::vector<int>::iterator print = c.begin(); print != c.end(); print++) {
  //      std::cout << "print: " << *print << ' ';
  //    }
  //    std::cout << std::endl;

  //    ft::vector<int>::iterator erase_it1 = c.erase(it1);
  //    std::cout << "erase_it: " << *erase_it1 << std::endl;
  //     for (ft::vector<int>::iterator print = c.begin(); print != c.end(); print++) {
  //       std::cout << "print: " << *print << ' ';
  //     }
  //     std::cout << std::endl;

  //    ft::vector<int>::iterator it2 = c.begin();
  //    std::cout << "c.begin(): " << *it2 << std::endl;
  //     for (ft::vector<int>::iterator print = c.begin(); print != c.end(); print++) {
  //       std::cout << "print: " << *print << ' ';
  //     }
  //     std::cout << std::endl;

  //    ft::vector<int>::iterator erase_it2 = c.erase(it2);
  //    std::cout << "erase_it: " << *erase_it2 << std::endl;
  //     for (ft::vector<int>::iterator print = c.begin(); print != c.end(); print++) {
  //       std::cout << "print: " << *print << ' ';
  //     }
  //     std::cout << std::endl;

  //    ft::vector<int>::iterator it3 = c.begin();
  //    std::cout << "c.begin(): " << *it3 << std::endl;
  //   for (ft::vector<int>::iterator print = c.begin(); print != c.end(); print++) {
  //     std::cout << "print: " << *print << ' ';
  //     std::cout << std::endl;
  // }

/* iterator test */
//     ft::vector<int> d;
//
//     std::cout << "    push_back 4 5 6:\n";
//     d.push_back(4);
//     d.push_back(5);
//     d.push_back(6);
//
//     std::cout << "begin:\n";
//     ft::vector<int>::iterator b_it = d.begin();
//     std::cout << *b_it << std::endl;
//
//     std::cout << "end:\n";
//     ft::vector<int>::iterator e_it = d.end();
//     std::cout << *e_it << std::endl;
//
//     std::cout << "rbegin:\n";
//     ft::vector<int>::reverse_iterator rb_it = d.rbegin();
//     std::cout << *rb_it << std::endl;
//
//     std::cout << "rend:\n";
//     ft::vector<int>::reverse_iterator re_it = d.rend();
//     std::cout << *re_it << std::endl;

/* at, operator test */
//     ft::vector<int> e;
//
//     std::cout << "    push_back 7 8 9:\n";
//     e.push_back(7);
//     e.push_back(8);
//     e.push_back(9);
//
//     std::cout << e.at(1) << std::endl;
//     std::cout << e[1] << std::endl;

/* max size */
//     ft::vector<int> f;
//     ft::vector<double> g;
//     ft::vector<char> h;
//
//     std::cout << "int:" << f.max_size() << std::endl;
//     std::cout << "double:" << g.max_size() << std::endl;
//     std::cout << "char:" << h.max_size() << std::endl;

/* clear, empty */
//     ft::vector<int> i;
//
//     std::cout << "empty: " << (i.empty() ? "true" : "false") << std::endl;
//     std::cout << "size: " << i.size() << "\ncapacity: " << i.capacity() << std::endl;
//
//     std::cout << "    push_back 1 2 3\n";
//     i.push_back(1);
//     i.push_back(2);
//     i.push_back(3);
//
//     std::cout << "empty: " << (i.empty() ? "true" : "false") << std::endl;
//     std::cout << "size: " << i.size() << "\ncapacity: " << i.capacity() << std::endl;
//
//     i.clear();
//
//     std::cout << "empty: " << (i.empty() ? "true" : "false") << std::endl;
//     std::cout << "size: " << i.size() << "\ncapacity: " << i.capacity() << std::endl;

/* reserve, resize */
//     ft::vector<int> j;
//
//     std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
//
//     std::cout << "    push_back 1 2 3\n";
//     j.push_back(1);
//     j.push_back(2);
//     j.push_back(3);
//     std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
//
//     std::cout << "    reserve 6\n";
//     j.reserve(6);
//     std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
//     std::cout << "    reserve 2\n";
//     j.reserve(2);
//     std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
//     std::cout << "    reserve 7\n";
//     j.reserve(7);
//     std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
//
//     std::cout << "    resize 5\n";
//     j.resize(5, 0);
//     std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
//     std::cout << "    resize 1\n";
//     j.resize(1, 0);
//     std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;
//     std::cout << "    resize 7\n";
//     j.resize(7, 0);
//     std::cout << "size: " << j.size() << "\ncapacity: " << j.capacity() << std::endl;

/* assign - count, value */
//     ft::vector<int> k;
//
//     k.push_back(1);
//     k.push_back(2);
//     k.push_back(3);
//     k.push_back(4);
//     k.push_back(5);
//
//     ft::vector<int>::iterator it3 = k.begin();
//     while (it3 != k.end()) {
//         std::cout << *it3 << ' ';
//         it3++;
//     }
//     std::cout << "size: " << k.size() << ", capacity: " << k.capacity() << std::endl;
//
//     // count, value
//     k.assign(2, 14);
//     ft::vector<int>::iterator it = k.begin();
//     while (it != k.end()) {
//         std::cout << *it << ' ';
//         it++;
//     }
//     std::cout << "size: " << k.size() << ", capacity: " << k.capacity() << std::endl;
//
//     k.assign(9, 15);
//     ft::vector<int>::iterator it2 = k.begin();
//     while (it2 != k.end()) {
//         std::cout << *it2 << ' ';
//         it2++;
//     }
//     std::cout << "size: " << k.size() << ", capacity: " << k.capacity() << std::endl;
//     std::cout << k.front() << std::endl;

/* assign - it, it */
//     ft::vector<int> n;
//
//     n.push_back(1);
//     n.push_back(2);
//     n.push_back(3);
//     n.push_back(4);
//     n.push_back(5);
//
//     ft::vector<int>::iterator it = ++n.begin();
//     ft::vector<int>::iterator it2 = --n.end();
//     std::cout << *it << ", " << *it2 << std::endl;
//
//     ft::vector<int> o;
//
//     o.push_back(0);
//     o.push_back(0);
//     o.push_back(0);
//
//     std::cout << "size: " << o.size() << ", capacity: " << o.capacity() << std::endl;
//
//     o.assign(it, it2);
//
//     ft::vector<int>::iterator it3 = o.begin();
//     while (it3 != o.end()) {
//         std::cout << *it3 << ' ';
//         it3++;
//     }
//     std::cout << "size: " << o.size() << ", capacity: " << o.capacity() << std::endl;

/* insert - iterator, value */
//    ft::vector<int>p;
//    p.push_back(1);
//    p.push_back(2);
//    p.push_back(3);
//
//    for (ft::vector<int>::iterator it = p.begin(); it != p.end(); it++) {
//      std::cout << *it << ' ';
//    }
//    std::cout << std::endl;
//
//    ft::vector<int>::iterator p_it = ++p.begin();
//
//    std::cout << "insert (p_it, 10)" << std::endl;
//    p.insert(p_it, 10);
//    for (ft::vector<int>::iterator it = p.begin(); it != p.end(); it++) {
//       std::cout << *it << ' ';
//    }
//    std::cout << std::endl;

/* insert - iterator, count, value */
//    ft::vector<int>q;
//    q.push_back(1);
//    q.push_back(2);
//    q.push_back(3);
//
//    for (ft::vector<int>::iterator it = q.begin(); it != q.end(); it++) {
//      std::cout << *it << ' ';
//    }
//    std::cout << std::endl;
//    std::cout << "insert (1, 3, 10)" << std::endl;
//    q.insert(1, 3, 10);
//    for (ft::vector<int>::iterator it = q.begin(); it != q.end(); it++) {
//       std::cout << *it << ' ';
//    }
//    std::cout << std::endl;

/* insert - iterator pos, iterator, iterator */
//    ft::vector<int>r;
//    r.push_back(1);
//    r.push_back(2);
//    r.push_back(3);
//
//    for (ft::vector<int>::iterator it = r.begin(); it != r.end(); it++) {
//      std::cout << *it << ' ';
//    }
//    std::cout << std::endl;
//    std::cout << "insert (1, it1, it2)" << std::endl;
//    ft::vector<int>::iterator it1 = r.begin();
//    ft::vector<int>::iterator it2 = ++r.begin();
//    r.insert(1, it1, it2);
//    for (ft::vector<int>::iterator it = r.begin(); it != r.end(); it++) {
//       std::cout << *it << ' ';
//    }
//    std::cout << std::endl;

/* swap */
//     ft::vector<int> l;
//
//     l.push_back(1);
//     l.push_back(2);
//     l.push_back(3);
//
//     std::cout << "l: " << l.front() << std::endl;
//
//     ft::vector<int> m;
//
//     m.push_back(4);
//     m.push_back(5);
//     m.push_back(6);
//
//     std::cout << "m: " << m.front() << std::endl;
//
//     l.swap(m);
//     std::cout << "l: " << l.front() << std::endl;
//     std::cout << "m: " << m.front() << std::endl;

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

/* test... - capacity == size -> capacity? */
/* test... - range로 넣을 때 capacity 값 */

/* test... - enable_if */
// #include <type_traits>

// template<class T>
// T foo2(T t, typename std::enable_if<!std::is_integral<T>::value >::type* = 0) {
//     std::cout << "not integral" << std::endl;
//     return t;
// }

// template<class T>
// T foo2(T t, typename std::enable_if<std::is_integral<T>::value >::type* = 0) {
//     std::cout << "integral" << std::endl;
//     return t;
// }

// int main() {
//     foo2(0.1);
//     foo2(7);
// }

    return 0;
}