#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template <typename T>
class ArrayList
{
private:
	size_t size = 0;
	size_t capacity = 0;
	const static size_t DEFAULT_CAPACITY = 8;
	std::shared_ptr<T> *array = nullptr;
	void expand_capacity();

public:
	ArrayList();
	~ArrayList();
	size_t get_size() { return size; }
	size_t get_capacity() { return capacity; }
	bool is_empty() { return size == 0; }
	void add(std::shared_ptr<T> element);
	void insert(int index, std::shared_ptr<T> element);
	std::shared_ptr<T> remove(int index);
	size_t index_of(std::shared_ptr<T> element);
	std::shared_ptr<T> get(int index);
	void set(int index, std::shared_ptr<T> element);
	bool contains(std::shared_ptr<T> element);
	void clear();
};

class Person
{
	friend bool operator==(const Person &lhs, const Person &rhs);
	friend bool operator!=(const Person &lhs, const Person &rhs);

public:
	int _age = 0;
	std::string _name = "name";
	Person() {}
	Person(int age, std::string name)
	{
		_age = age;
		_name = name;
	}
	~Person() { std::cout << "delete " << " " << this << to_string(); }
	std::string to_string() { return "[" + std::to_string(_age) + ", " + _name + "]\n"; }
};

bool operator==(const Person &lhs, const Person &rhs)
{
	return lhs._age == rhs._age && lhs._name == rhs._name;
}

bool operator!=(const Person &lhs, const Person &rhs)
{
	return !(lhs == rhs);
}

#endif
