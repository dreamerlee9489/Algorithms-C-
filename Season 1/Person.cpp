#include "./Person.h"
using namespace std;

int main(int argc, char const *argv[])
{
    Person *p1 = new Person(15, "alice15");
    Person *p2 = new Person(16, "alice16");

    if (typeid(p1) == typeid(Person))
        cout << "==Person\n";
    if (typeid(p1) == typeid(IHashable))
        cout << "==IHashable\n";

    cout << "p1=" << p1 << "\n" << "p2=" << p2 << "\n";
    cout << "p1-p2=" << p1 - p2 << "\n";
    cout << "p2-p1=" << p2 - p1 << "\n";

    return 0;
}
