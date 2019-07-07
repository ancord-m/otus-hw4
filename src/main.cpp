#include "print.h"

int main(int argc, const char* argv[])
{
	print_ip(char(-1));
	print_ip(short(0));
	print_ip(int(2130706433));
	print_ip(long(8875824491850138409));
	print_ip(std::string("127.0.0.1"));
	//print_ip(vector)
	//print_ip(list)
	//print_ip(tuple)

	char b = 255;
	std::make_unsigned_t<char> ua = b;

	std::cout << ua << std::endl;

	return 0;
}