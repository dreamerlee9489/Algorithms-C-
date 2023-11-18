#include <iostream>

int main(int argc, char const* argv[])
{
	int i = 1, j = 2;
	int val = -1;
	val = --i, --j;
	std::cout << val << "\n"; // 0
	return 0;
}