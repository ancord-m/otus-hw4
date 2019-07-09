#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>

/**
	@brief The simpliest print_ip for stringt
*/
void print_ip(const std::string& ip)
{
	std::cout << ip << std::endl;
}

template<typename IP_TYPE>
std::enable_if_t<
	std::is_integral_v<IP_TYPE>,
	void>
print_ip(const IP_TYPE& ip)
{
	const unsigned char BYTE_MASK = 0xFF;
	const unsigned char BYTE_SIZE = 8;
	std::make_unsigned_t<IP_TYPE> u_ip  = ip;

    for(unsigned int bytes_left = sizeof(IP_TYPE); bytes_left > 0; --bytes_left)
    {
    	unsigned int bit_shift = (bytes_left - 1)    * BYTE_SIZE;
    	unsigned int ip_part   = (u_ip >> bit_shift) & BYTE_MASK;
    	
    	if(bytes_left != sizeof(IP_TYPE)) std::cout << ".";
    	std::cout << ip_part;    	
    }

    std::cout << std::endl;
}

template<typename IP_TYPE>
std::enable_if_t<
	std::is_same_v<IP_TYPE, std::vector<typename IP_TYPE::value_type>> ||
	std::is_same_v<IP_TYPE, std::list  <typename IP_TYPE::value_type>>,
	void>
print_ip(const IP_TYPE& ip)
{
	for(auto ip_iterator = ip.cbegin(); ip_iterator != ip.cend(); ++ip_iterator )
	{
		if(ip_iterator != ip.cbegin())  std::cout << ".";
		std::cout << *ip_iterator;
	}

	std::cout << std::endl;
}

/* for tuple */

template<typename T, typename... Args>
struct are_tuple_types_same { };

template<typename T>
struct are_tuple_types_same<T> : std::true_type {};

template<typename T, typename U, typename... Args>
struct are_tuple_types_same<T, U, Args...>
{
	static const bool value = std::is_same_v<T, U> && are_tuple_types_same<U, Args...>::value;
};

template<size_t cur_index, size_t tuple_size, typename... Args>
struct print_tuple
{
    void operator()(const std::tuple<Args...>& ip_parts)
    {
        if (cur_index != 0) std::cout << ".";
        
        std::cout << std::get<cur_index>(ip_parts);
        print_tuple<cur_index + 1, tuple_size, Args...>{}(ip_parts);
    }
};

template<size_t tuple_size, typename... Args>
struct print_tuple<tuple_size, tuple_size, Args...>
{
    void operator()(const std::tuple<Args...>& ip_parts)
    {
        std::cout << std::endl;
    }
};

template<typename... Args>
std::enable_if_t<
	are_tuple_types_same<Args...>::value,//std::is_same_v<IP_TYPE, std::tuple<Args...>,
	void>
print_ip(const std::tuple<Args...>& ip)
{
	print_tuple<
		0,
		std::tuple_size_v<std::remove_reference_t<decltype(ip)>>,
		Args...
	> {} (ip);	
}

#endif /* PRINT_H */