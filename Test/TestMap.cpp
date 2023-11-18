#include <map>
#include <iostream>
using namespace std;

class Test
{
public:
	int i = 0;
	Test(int i) { this->i = i; }
	~Test() = default;
};

int main(int argc, char const* argv[])
{
	map<int, Test*> m;
	m[1] = new Test(10);
	cout << m[1]->i << ", " << m[2] << "\n";
	return 0;
}

