#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
// 测试类
class Person
{
    friend std::istream &operator>>(std::istream &in, Person &p);
    friend std::ostream &operator<<(std::ostream &out, const Person &p);
    friend bool operator==(const Person &lhs, const Person &rhs);
    friend bool operator!=(const Person &lhs, const Person &rhs);

public:
    int _age = 0;
    std::string _name = "name";
    Person &operator=(const Person &rhs);
    Person &operator=(Person &&rhs) noexcept;
    Person() = default;
    Person(int age, std::string name) : _age(age), _name(name) {}
    Person(const Person &p) { *this = p; }
    Person(Person &&p) noexcept { *this = std::move(p); }
    ~Person() { std::cout << "delete " << this << "[" << _age << ", " << _name + "]\n"; }
};

Person &Person::operator=(const Person &rhs)
{
    _age = rhs._age;
    _name = rhs._name;
    return *this;
}

Person &Person::operator=(Person &&rhs) noexcept
{
    _age = std::move(rhs._age);
    _name = std::move((std::string)rhs._name);
    return *this;
}

std::istream &operator>>(std::istream &in, Person &p) { return in >> p._age >> p._name; }
std::ostream &operator<<(std::ostream &out, const Person &p) { return out << &p << "[" << p._age << ", " << p._name + "]\n"; }
bool operator==(const Person &lhs, const Person &rhs) { return lhs._age == rhs._age && lhs._name == rhs._name; }
bool operator!=(const Person &lhs, const Person &rhs) { return !(lhs == rhs); }

#endif // !PERSON_H
