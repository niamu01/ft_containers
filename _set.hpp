
#ifndef set_HPP
#define set_HPP

#include "_tree.hpp"

namespace ft
{
	template <typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key> > 
	class set
	{
	public:
		typedef Key 																key_type;
		typedef const Key															value_type;
		typedef Compare 															key_compare;
		typedef Compare 															value_compare;
		typedef Allocator 															allocator_type;
		typedef typename Allocator::reference 										reference;
		typedef typename Allocator::const_reference 								const_reference;
		typedef ft::tree_iterator<value_type> 									iterator;
		typedef ft::tree_iterator<value_type> 									const_iterator;
		typedef ft::reverse_iterator<iterator> 										reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
		typedef typename allocator_type::size_type									size_type;
		typedef typename Allocator::pointer 										pointer;
		typedef typename Allocator::const_pointer									const_pointer;
	    typedef ft::tree_node<value_type>				              	  node_type;

	private:
		Allocator 		alloc;
		Compare 		comp;
		size_type 		_capacity;
		size_type		_size;
		Key 			_def_value;
		typedef 		ft::_tree < value_type, value_compare, Allocator > rb_tree;
		rb_tree 		_curr;
	};

		explicit set(const Compare& c = Compare(), const Allocator& a = Allocator()) : alloc(a), comp(c), _def_value(Key()), _curr(rb_tree()) {}

		template <class InputIterator>
		set(InputIterator first, InputIterator last, const Compare& c = Compare(), const Allocator &a = Allocator())  :  alloc(a), comp(c), _curr(rb_tree())
		{
			insert(first, last);
		}

		set(const set<Key, Compare, Allocator>& x) : alloc(x.alloc), comp(x.comp), _def_value(Key()), _curr(rb_tree())
		{
			*this = x;
		}

		~set() {}

		set<Key, Compare, Allocator>& operator=(const set<Key, Compare, Allocator>& x)
		{
			if (*this != x || _size != x.size())
			{
				erase(begin(), end());
				insert(x.begin(), x.end());
			}
			return (*this);
		}

	
		allocator_type get_allocator() const
		{
			return Allocator();
		}

		iterator begin()
		{
			return iterator(_curr.tree_min(_curr.get_root()));
		}

		const_iterator begin() const
		{
			return const_iterator(_curr.tree_min(_curr.get_root()));
		}

		iterator end()
		{
			return iterator(_curr.get_nil());
		}

		const_iterator end() const
		{
			return const_iterator(_curr.get_nil());
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end()); 
		}
	
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end()); 
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		size_type size() const
		{
			return (_curr.size());
		}

		size_type max_size() const
		{
			return (alloc.max_size()); 
		}

		bool empty() const
		{
			if (_curr.size() == 0)
				return true;
			return (false);
		}

    pair<iterator, bool> insert(const value_type& val) {
      ft::pair<node_type*, bool> res = _curr.insert(val);
      return (ft::make_pair(iterator(res.first), res.second));
    };

    iterator insert(iterator position, const value_type& val) {
      return (iterator(_curr.insert(val, position.base()).first));
    };

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
      while (first != last)
        _curr.insert(*first++);
    };
	
    void erase(iterator position) {
      _curr.erase(position.base());
    };

    size_type erase(const key_type& k) {
      return (_curr.erase(_curr.find(value_type(k))));
    };

    void erase(iterator first, iterator last) {
      while (first != last)
        erase(first++);
    };

		void swap(set<Key, Compare, Allocator>& other)
		{
			_curr.swap(other._curr);
		}

		void clear()
		{
			erase(begin(), end());
		}

		key_compare key_comp() const 
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(comp);
		}

		iterator find(const key_type& x)
		{
			return iterator(_curr.find(x));
		}

		const_iterator find(const key_type& x) const
		{
			return const_iterator(_curr.find(x));
		}

		size_type count(const key_type& x) const
		{
			if (_curr.find(x) != _curr.get_nil())
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type& x)
		{
			iterator it = _curr.find(x);
			if (it == _curr.get_nil())
			{
				for (iterator new_it = begin(); new_it != end(); new_it++)
				{
					if (*new_it > x)
					{
						it = new_it;
						break;
					}
				}
			}
			return (it);
		}
	
		const_iterator lower_bound(const key_type& x) const
		{
			const_iterator it = (_curr.find(x));
			if (it == const_iterator(_curr.get_nil()))
			{
				for (const_iterator new_it = begin(); new_it != end(); new_it++)
				{
					if (*new_it > x)
					{
						it = new_it;
						break;
					}
				}
			}
			return (it);
		}

		iterator upper_bound(const key_type& x)
		{
			iterator it;
			for (it = begin(); it != end(); it++)
			{
				if (*it > x)
					break;
			}
			return (it);
		}
		const_iterator upper_bound(const key_type& x) const
		{
			const_iterator it;
			for (it = begin(); it != end(); it++)
			{
				if (*it > x)
					break;
			}
			return (it);
		}

		pair<iterator, iterator>
		equal_range(const key_type& x)
		{
			return(ft::make_pair(lower_bound(x), upper_bound(x)));
		}

		pair<const_iterator, const_iterator>
		equal_range(const key_type& x) const
		{
			return(ft::make_pair<const_iterator, const_iterator>(lower_bound(x), upper_bound(x)));
		}

	template <class K, class Comp, class Alloc>
	friend bool operator==(const set<K, Comp, Alloc>& lhs, const set<K,  Comp, Alloc>& rhs);
	template <class K,  class Comp, class Alloc>
	friend bool operator<(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs);


	template <class Key, class Compare, class Allocator>
	void swap(set<Key,  Compare, Allocator>& lhs, set<Key,  Compare, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}
	template <class Key,  class Compare, class Allocator>
	bool operator==(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class Key,  class Compare, class Allocator>
	bool operator!=(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class Key,  class Compare, class Allocator>
	bool operator<(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class Key,  class Compare, class Allocator>
	bool operator>(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		return (rhs < lhs);
	}
	template <class Key,  class Compare, class Allocator>
	bool operator>=(const set<Key,  Compare, Allocator>& lhs, const set<Key,  Compare, Allocator>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key,  class Compare, class Allocator>
	bool operator<=(const set<Key,  Compare, Allocator>& lhs,const set<Key,  Compare, Allocator>& rhs)
	{
		return (!(rhs < lhs));
	}
};

#endif
