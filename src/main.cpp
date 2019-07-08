#include "print.h"

int main(int argc, const char* argv[])
{
	print_ip(char(-1));
	print_ip(short(0));
	print_ip(int(2130706433));
	print_ip(long(8875824491850138409));
	print_ip(std::string("127.0.0.1"));
	print_ip(std::vector<int>{192, 168, 8, 1});
	print_ip(std::list<int>{234, 99, 31, 39, 12});
	//print_ip(tuple)

	return 0;
}