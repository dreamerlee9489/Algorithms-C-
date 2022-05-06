#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include "./IString.h"
using namespace std;

namespace app
{
    // 测试类
    class Person : public IString
    {
        friend istream &operator>>(istream &in, Person &p) { return in >> p._age >> p._name; }
        friend ostream &operator<<(ostream &out, const Person &p) { return out << p.to_string(); }
        friend bool operator==(const Person &lhs, const Person &rhs) { return lhs._age == rhs._age && lhs._name == rhs._name; }
        friend bool operator!=(const Person &lhs, const Person &rhs) { return !(lhs == rhs); }
        friend bool operator<(const Person &lhs, const Person &rhs) { return lhs._age < rhs._age; }
        friend bool operator>(const Person &lhs, const Person &rhs) { return lhs._age > rhs._age; }

    public:
        int _age = 0;
        string _name = "name";
        Person &operator=(const Person &rhs)
        {
            _age = rhs._age;
            _name = rhs._name;
            return *this;
        }
        Person &operator=(Person &&rhs) noexcept
        {
            _age = move(rhs._age);
            _name = move((string)rhs._name);
            return *this;
        }
        Person() = default;
        Person(int age, string name = "unnamed") : _age(age), _name(name) {}
        Person(const Person &p) { *this = p; }
        Person(Person &&p) noexcept { *this = move(p); }
        ~Person() { cout << "delete " << this << to_string() << "\n"; }
        string to_string() const override { return "[" + std::to_string(_age) + ", " + _name + "]"; }
    };
} // namespace app

template <>
struct std::hash<app::Person>
{
    size_t operator()(const app::Person &p) const { return std::hash<string>()(p._name) ^ std::hash<int>()(p._age); }
};

#endif /* PERSON_H */
