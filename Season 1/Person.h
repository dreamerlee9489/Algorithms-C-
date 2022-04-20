#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include "./IString.h"
#include "./IHashable.h"
#include "./IComparable.h"
// 测试类
class Person : public IString, public IHashable, public IComparable
{
    friend std::istream &operator>>(std::istream &in, Person &p) { return in >> p._age >> p._name; }
    friend std::ostream &operator<<(std::ostream &out, const Person &p) { return out << p.to_string(); }
    friend bool operator==(const Person &lhs, const Person &rhs) { return lhs._age == rhs._age && lhs._name == rhs._name; }
    friend bool operator!=(const Person &lhs, const Person &rhs) { return !(lhs == rhs); }
    friend bool operator<(const Person &lhs, const Person &rhs) { return lhs._age < rhs._age; }
    friend bool operator>(const Person &lhs, const Person &rhs) { return lhs._age > rhs._age; }

public:
    size_t _age = 0;
    std::string _name = "name";
    Person &operator=(const Person &rhs);
    Person &operator=(Person &&rhs) noexcept;
    Person() = default;
    Person(size_t age, std::string name) : _age(age), _name(name) {}
    Person(const Person &p) { *this = p; }
    Person(Person &&p) noexcept { *this = std::move(p); }
    ~Person() { std::cout << "delete " << this << to_string() << "\n"; }
    int compare_to(void *data) const override;
    int hash_code() const override;
    bool equals(void *data) const override;
    std::string to_string() const override { return "[" + std::to_string(_age) + ", " + _name + "]"; }
};

inline Person &Person::operator=(const Person &rhs)
{
    _age = rhs._age;
    _name = rhs._name;
    return *this;
}

inline Person &Person::operator=(Person &&rhs) noexcept
{
    _age = std::move(rhs._age);
    _name = std::move((std::string)rhs._name);
    return *this;
}

inline int Person::compare_to(void *data) const
{
    Person *other = (Person *)data;
    if(_age < other->_age)
        return -1;
    else if(_age > other->_age)
        return 1;
    return 0;
}

inline int Person::hash_code() const
{
    int hash = 0;
    for (size_t i = 0; i < _name.size(); ++i)
        hash = (hash << 5) - hash + _name[i];
    return hash + _age;
}

inline bool Person::equals(void *data) const
{
    if (this == data)
        return true;
    Person *other = (Person *)data;
    if (data == nullptr || typeid(*other) != typeid(*this))
        return false;
    return other->_age == _age && other->_name == _name;
}

#endif /* PERSON_H */
