#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <type_traits>

template<typename IP_TYPE>
std::enable_if_t<std::is_integral_v<IP_TYPE>, void> print_ip(const IP_TYPE& ip)
{
    std::make_unsigned_t<IP_TYPE> repr  = ip;
	decltype(repr) mask = std::numeric_limits<decltype(repr)>::max();
	for(size_t i = sizeof(IP_TYPE); i > 0; --i) {
    if(i !=  sizeof(IP_TYPE)){
        std::cout << ".";
    }
    unsigned char b = (repr >> (8*(i - 1))) & mask;
    std::cout << +b;
}
std::cout << std::endl;
}

void print_ip(const std::string& ip)
{
	std::cout << ip << std::endl;
}

#endif /* PRINT_H */