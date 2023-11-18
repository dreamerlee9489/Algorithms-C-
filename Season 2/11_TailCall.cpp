#include <iostream>

using namespace std;

int factorial0(int n) {
	if (n <= 1)
		return n;
	return n * factorial0(n - 1);
}

// 尾调用版
int factorial1(int n, int result = 1) {
	if (n <= 1)
		return result;
	return factorial1(n - 1, n * result);
}

int main(int argc, char const* argv[]) {
	cout << factorial1(4) << "\n";
	return 0;
}
