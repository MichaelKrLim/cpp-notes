*To read in a varable input for a variety of different input cases :*

```cpp
std::istream & operator >> (std::istream & in, join & name)
{
   if(std::isdigit(in.peek()))
   {
      in >> name.place;
      in >> name.character;
   }
   else
   {
      in >> name.character;
      in >> name.place;
   }
   if(!in.eof() && in.peek() == '-')
   {
    char t;
    in >> t;
   }
   return in;
}


 std::vector<join> answer(std::istream_iterator<join>{std::cin},{});
 ```
 
---------------------------------------------------------------------

*you may use copy to a vecor's output stream to output*
   
```cpp
std::copy(answer.begin(),answer.end(),std::ostream_iterator<join>{std::cout});
```

---------------------------------------------------------------------
   
*accumulate can sum values from two iterators, the type is determined based on the last parameter of accumulate*
                                                                                  
```cpp
long long sum_e = std::accumulate(std::istream_iterator<long long> {stream}, {}, 0ll);
```

---------------------------------------------------------------------
   
*conversion between bases:*


```cpp
digits = ////
   
int base = out == "dec" ? 10 : out == "hex" ? 16 : 2;
            std::string output;
            do 
            { 
                output += digits[dec % base];
                dec /= base;
            } while (dec > 0);
```

*output must be big enough to store converted value:*

```cpp
output.resize(1000);
std::to_chars(&output[0], &output[output.size()], dec, base);
```

----------------------------------------------------------------------

*Template meta programming*

```cpp
#include <iostream>
#include <vector>
#include <array>
#include <tuple>

template <typename T>
void swap(T& one, T& two)
{
	auto one_copy = one;
	one = two;
	two = one_copy;
}

template <typename T, std::size_t capacity>
class Fixed_vector
{
	std::array<T, capacity> underlying_container;
	std::size_t used_elements{};

	public:
	std::size_t size() const
	{
		return used_elements;
	}
	void push_back(T to_push)
	{
		underlying_container[used_elements++] = to_push;
	}
	void pop_back() 
	{
		--used_elements;
	}

	T& operator [](std::size_t index)
	{
		return underlying_container[index];
	}
};

template <std::size_t capacity>
class Fixed_vector<bool, capacity>
{
	std::array<std::uint8_t, (capacity+7)/8> underlying_container;
	std::size_t used_elements{};

	public:
	std::size_t size() const
	{
		return used_elements;
	}
	void push_back(bool to_push)
	{
		std::size_t array_index = used_elements/8;
		std::size_t bit_index = used_elements%8;
		if(to_push)
			underlying_container[array_index] |= 1u << bit_index;
		else
			underlying_container[array_index] &= ~(1u << bit_index);
		++used_elements;
	}
	void pop_back() 
	{
		--used_elements;
	}

	bool operator [](std::size_t index) const
	{
		std::size_t array_index = index/8;
		std::size_t bit_index = index%8;
		return (underlying_container[array_index] & (1u << bit_index)) != 0;
	}
};

template <typename T, typename J>
struct is_same
{
	static constexpr bool value = false;
};

template <typename T>
struct is_same<T, T>
{
	static constexpr bool value = true;
};

template <typename T>
struct is_vector
{
	static constexpr bool value = false;
};

template <typename T>
struct is_vector<std::vector<T>>
{
	static constexpr bool value = true;
};

template <typename T>
[[nodiscard]] auto last_element(const T& container)
{
	if constexpr(is_vector<T>::value)
	{
		return container.back();
	}
	else
	{
		return container[container.size()-1];
	}
}

int add(int a, int b)
{
	return a+b;
}
double multiply(double a, double b, double c)
{
	return a*b*c;
}

template <typename T, T>
struct a;

template<typename R, typename ... argstypes, R(*function)(argstypes...)>
struct a<R(*)(argstypes...), function>
{
	template <std::size_t ... indices>
	static R call_helper(std::index_sequence<indices...> asdf)
	{
		std::tuple<argstypes...> args;
		((std::cin >> std::get<indices>(args)),...);
		return function(std::get<indices>(args)...);
	}
	static R call()
	{
		return call_helper(std::make_index_sequence<sizeof...(argstypes)>());
	}
};

int main()
{
	//std::add_pointer_t<int(int,int)> to_call = multiply;
	//int (*to_call)(int, int) = multiply;
	//int a = 1, b = 2;	
	//std::cerr << to_call(a, b) << "\n";
	std::cerr << a<decltype(&multiply), &multiply>::call() << "\n";
	return 0;
	Fixed_vector<bool, 8> v;
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);
	for(std::size_t i{0}; i<v.size(); ++i)
	{
		std::cerr << v[i] << ' ';
	}
	std::cerr << last_element(v) << std::endl;
	std::cerr << "\n";
}
```
