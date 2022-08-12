#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <string>
#include "./IString.hpp"

using namespace std;

namespace app {
    // 测试类
    class Person : public IString {
        friend istream &operator>>(istream &in, Person &p) { return in >> p.mAge >> p.mName; }

        friend ostream &operator<<(ostream &out, const Person &p) { return out << p.to_string(); }

        friend bool operator==(const Person &lhs, const Person &rhs) {
            return lhs.mAge == rhs.mAge && lhs.mName == rhs.mName;
        }

        friend bool operator!=(const Person &lhs, const Person &rhs) { return !(lhs == rhs); }

        friend bool operator<(const Person &lhs, const Person &rhs) { return lhs.mAge < rhs.mAge; }

        friend bool operator>(const Person &lhs, const Person &rhs) { return lhs.mAge > rhs.mAge; }

    public:
        int mAge = 0;
        string mName = "name";

        Person &operator=(const Person &rhs) {
            mAge = rhs.mAge;
            mName = rhs.mName;
            return *this;
        }

        Person &operator=(Person &&rhs) noexcept {
            mAge = move(rhs.mAge);
            mName = move((string) rhs.mName);
            return *this;
        }

        Person() = default;

        Person(int age, string name = "unnamed") : mAge(age), mName(name) {}

        Person(const Person &p) { *this = p; }

        Person(Person &&p) noexcept { *this = move(p); }

        ~Person() { cout << "delete " << this << to_string() << "\n"; }

        string to_string() const override { return "[" + std::to_string(mAge) + ", " + mName + "]"; }
    };
} // namespace app

template<>
struct std::hash<app::Person> {
    size_t operator()(const app::Person &p) const { return std::hash<string>()(p.mName) ^ std::hash<int>()(p.mAge); }
};

#endif /* PERSON_HPP */
