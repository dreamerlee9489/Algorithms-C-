#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include "./IString.h"
// 测试类
class Person : public IString
{
    friend STD_ istream &operator>>(STD_ istream &in, Person &p) { return in >> p._age >> p._name; }
    friend STD_ ostream &operator<<(STD_ ostream &out, const Person &p) { return out << p.to_string(); }
    friend bool operator==(const Person &lhs, const Person &rhs) { return lhs._age == rhs._age && lhs._name == rhs._name; }
    friend bool operator!=(const Person &lhs, const Person &rhs) { return !(lhs == rhs); }
    friend bool operator<(const Person &lhs, const Person &rhs) { return lhs._age < rhs._age; }
    friend bool operator>(const Person &lhs, const Person &rhs) { return lhs._age > rhs._age; }

public:
    int _age = 0;
    STD_ string _name = "name";
    Person &operator=(const Person &rhs)
    {
        _age = rhs._age;
        _name = rhs._name;
        return *this;
    }
    Person &operator=(Person &&rhs) noexcept
    {
        _age = STD_ move(rhs._age);
        _name = STD_ move((STD_ string)rhs._name);
        return *this;
    }
    Person() = default;
    Person(int age, STD_ string name = "unnamed") : _age(age), _name(name) {}
    Person(const Person &p) { *this = p; }
    Person(Person &&p) noexcept { *this = STD_ move(p); }
    ~Person() { STD_ cout << "delete " << this << to_string() << "\n"; }
    STD_ string to_string() const override { return "[" + STD_ to_string(_age) + ", " + _name + "]"; }
};

template <>
struct STD_ hash<Person>
{
    size_t operator()(const Person &p) const { return hash<string>()(p._name) ^ hash<int>()(p._age); }
};

#endif /* PERSON_H */
