#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "./03_IList.h"
// 动态数组模板类(智能指针版)
template <typename T>
class ArrayList : public IList<T>
{
private:
	size_t _capacity = 0;
	const static size_t DEFAULT_CAPACITY = 8;
	std::shared_ptr<T> *array = nullptr;
	void expand_capacity();

public:
	ArrayList();
	~ArrayList();
	size_t capacity() { return _capacity; }
	void insert(size_t index, std::shared_ptr<T> element) override;
	size_t index_of(std::shared_ptr<T> element) override;
	std::shared_ptr<T> remove(size_t index) override;
	std::shared_ptr<T> get(size_t index) override;
	void set(size_t index, std::shared_ptr<T> element) override;
	void clear() override;
};

class Person
{
	friend std::istream &operator>>(std::istream &in, Person &p);
	friend std::ostream &operator<<(std::ostream &out, const Person &p);
	friend bool operator==(const Person &lhs, const Person &rhs);
	friend bool operator!=(const Person &lhs, const Person &rhs);

public:
	int _age = 0;
	std::string _name = "name";
	Person() = default;
	Person(int age, std::string name)
	{
		_age = age;
		_name = name;
	}
	~Person() { std::cout << "delete " << this << "[" << _age << ", " << _name + "]\n"; }
};

std::istream &operator>>(std::istream &in, Person &p) { return in >> p._age >> p._name; }
std::ostream &operator<<(std::ostream &out, const Person &p) { return out << &p << "[" << p._age << ", " << p._name + "]\n"; }
bool operator==(const Person &lhs, const Person &rhs) { return lhs._age == rhs._age && lhs._name == rhs._name; }
bool operator!=(const Person &lhs, const Person &rhs) { return !(lhs == rhs); }

#endif
