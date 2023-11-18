#include <iostream>
using namespace std;

class Test {
	int i = 0;

public:
	Test(int i)
	{
		this->i = i;
		cout << "Test() " << this->i << "\n";
	}

	~Test()
	{
		cout << "~Test() " << this->i << "\n";
	}
};

static Test t0(0);
Test t1(1);

int main(int argc, char const* argv[])
{
	cout << "main\n";
	static Test t2(2);
	Test t3(3);
	static Test t4(4);
	return 0;
}
