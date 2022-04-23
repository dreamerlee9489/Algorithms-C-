#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include "./IString.h"
// 测试类
class Person : public IString
{
    friend std::istream &operator>>(std::istream &in, Person &p) { return in >> p._age >> p._name; }
    friend std::ostream &operator<<(std::ostream &out, const Person &p) { return out << p.to_string(); }
    friend bool operator==(const Person &lhs, const Person &rhs) { return lhs._age == rhs._age && lhs._name == rhs._name; }
    friend bool operator!=(const Person &lhs, const Person &rhs) { return !(lhs == rhs); }
    friend bool operator<(const Person &lhs, const Person &rhs) { return lhs._age < rhs._age; }
    friend bool operator>(const Person &lhs, const Person &rhs) { return lhs._age > rhs._age; }

public:
    int _age = 0;
    std::string _name = "name";
    Person &operator=(const Person &rhs)
    {
        _age = rhs._age;
        _name = rhs._name;
        return *this;
    }
    Person &operator=(Person &&rhs) noexcept
    {
        _age = std::move(rhs._age);
        _name = std::move((std::string)rhs._name);
        return *this;
    }
    Person() = default;
    Person(int age, std::string name = "unnamed") : _age(age), _name(name) {}
    Person(const Person &p) { *this = p; }
    Person(Person &&p) noexcept { *this = std::move(p); }
    ~Person() { std::cout << "delete " << this << to_string() << "\n"; }
    std::string to_string() const override { return "[" + std::to_string(_age) + ", " + _name + "]"; }
};

template <>
struct std::hash<Person>
{
    size_t operator()(const Person &p) const { return hash<string>()(p._name) ^ hash<int>()(p._age); }
};

#endif /* PERSON_H */
