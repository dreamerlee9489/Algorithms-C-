#include "./19_Trie.h"
#include "./Person.h"
using namespace std;

int main(int argc, char const *argv[])
{
    Trie<Person> tree;
    tree.add("cat", make_shared<Person>(1));
    tree.add("dog", make_shared<Person>(2));
    tree.add("catalog", make_shared<Person>(3));
    tree.add("cast", make_shared<Person>(4));
    tree.add("dreamer", make_shared<Person>(5));
    cout << "size=" << tree.size() << "\n";
    cout << "get(dreamer):" << *tree.get("dreamer") << "\n";
    cout << "start_with(do)=" << tree.start_with("do") << "\n";
    cout << "start_with(ha)=" << tree.start_with("ha") << "\n";
    cout << "remove(cat):" << *tree.remove("cat") << "\n";
    cout << "remove(cast):" << *tree.remove("cast") << "\n";
    cout << "size=" << tree.size() << "\n";
    return 0;
}

/*
size=5
get(dreamer):[5, unnamed]
start_with(do)=1
start_with(ha)=0
remove(cat):[1, unnamed]
delete 0xe266c0[1, unnamed]
remove(cast):[4, unnamed]
delete 0x25e2560[4, unnamed]
size=3
*/
