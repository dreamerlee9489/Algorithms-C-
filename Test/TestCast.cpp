#include <iostream>
using namespace std;

class Base
{
public:
	int i = 10;
	Base(/* args */) = default;
	~Base() = default;
	virtual void Output() { cout << "i = " << i << "\n"; }
};

class DeriveA : public Base
{
public:
	float j = 3.14f;
	DeriveA(/* args */) = default;
	~DeriveA() = default;
	void Output() override { cout << "i = " << i << " j = " << j << "\n"; }
	void HelloA() { cout << "Hello DeriveA.\n"; }
};

class DeriveB : public Base
{
public:
	size_t k = 314;
	DeriveB(/* args */) = default;
	~DeriveB() = default;
	void Output() override { cout << "i = " << i << " k = " << k << "\n"; }
	void HelloB() { cout << "Hello DeriveB.\n"; }
};

int main()
{
	Base* b = new Base();
	DeriveA* da = new DeriveA();
	DeriveB* db = new DeriveB();
	Base* pa = da, * pb = db;

	// 编译时，基类指针可以转为任意派生类指针
	// dynamic_cast 运行时进行动态类型识别，类型必须包含虚函数
	// cout << "static_cast " << static_cast<DeriveA*>(pa)->j << "\n";
	// cout << "dynamic_cast " << dynamic_cast<DeriveA*>(pa)->j << "\n";
	// static_cast<DeriveA*>(pa)->Output();
	static_cast<DeriveA*>(pb)->Output();
	static_cast<DeriveA*>(pb)->HelloA();
	// dynamic_cast<DeriveA*>(pa)->Output();
	// dynamic_cast<DeriveA*>(pb)->Output();
	dynamic_cast<DeriveB*>(pb)->Output();
	dynamic_cast<DeriveB*>(pb)->HelloB();

	return 0;
}