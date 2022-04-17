#include "./11_TreeSet.h"
#include "./Person.h"
using namespace std;

int main(int argc, char const *argv[])
{
    TreeSet<Person> tree;
    tree.add(make_shared<Person>(12, "Alice12"));
    tree.add(make_shared<Person>(10, "Alice10"));
    tree.add(make_shared<Person>(7, "Alice17"));
    tree.add(make_shared<Person>(11, "Alice11"));
    tree.add(make_shared<Person>(10, "Alice10"));
    tree.add(make_shared<Person>(11, "Alice11"));
    tree.add(make_shared<Person>(9, "Alice19"));
    tree.traverse([](shared_ptr<Person> data)
    {
        cout << "lamdba: " << *data << "\n";
        return false;
    });
    return 0;
}
