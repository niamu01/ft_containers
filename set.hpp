#ifndef SET_HPP
#define SET_HPP

class set {
private:

  template <typename T>
  struct use_self
  {
    typedef T result_type;

    const result_type& operator()(const T& x) const
    { return x; }
  };

};


#endif