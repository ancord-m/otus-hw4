#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>


void print_ip(const std::string& ip)
{
	std::cout << ip << std::endl;
}

template<typename IP_TYPE>
std::enable_if_t<std::is_integral_v<IP_TYPE>, void> print_ip(const IP_TYPE& ip)
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

#endif /* PRINT_H */