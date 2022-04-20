#include "./13_HashMap.h"
#include "./Person.h"
using namespace std;

int main(int argc, char const *argv[])
{
    HashMap<int, Person> map;
    map.add(make_shared<int>(10), make_shared<Person>(10, "Alice10"));
    map.add(make_shared<int>(11), make_shared<Person>(11, "Alice11"));
    map.add(make_shared<int>(12), make_shared<Person>(12, "Alice12"));
    map.add(make_shared<int>(13), make_shared<Person>(13, "Alice13"));
    map.add(make_shared<int>(14), make_shared<Person>(14, "Alice14"));
    cout << "size=" << map.size() << "\n";
    // map.remove(make_shared<int>(13));
    // map.remove(make_shared<int>(14));
    cout << "size=" << map.size() << "\n";

    return 0;
}
