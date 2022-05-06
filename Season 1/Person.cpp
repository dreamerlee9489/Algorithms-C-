#include <memory>
#include "./Person.h"
using namespace app;

int main(int argc, char const *argv[])
{
    Person *p1 = new Person(15, "alice15");
    Person *p2 = new Person(16, "alice16");
    shared_ptr<Person> *array = new shared_ptr<Person>[8];

    if (typeid(*p1) == typeid(Person))
        cout << "==Person\n";
    cout << hash<Person>()(*p1) << "\n";

    return 0;
}
