#include <iostream>
#include <string.h>
#include <vector>

int main(int argc, char const* argv[]) {
	int arr[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	std::cout << std::dec << (size_t)arr << " " << (size_t)&arr[0][0] << "\n";
	std::cout << sizeof(arr) << "\n";

	std::vector<int> vec(30);
	vec.emplace(vec.begin(), 100);
	std::cout << "size = " << vec.size() << "\n";
	return 0;
}
