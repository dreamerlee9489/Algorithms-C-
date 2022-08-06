#include <iostream>
#include <string>
#include "./14_TreeMap.hpp"
#include "./Person.hpp"

using namespace app;

int main(int argc, char const *argv[]) {
    TreeMap<int, Person> map;
    map.add(make_shared<int>(10006), make_shared<Person>(12, "Alice12"));
    map.add(make_shared<int>(10008), make_shared<Person>(15, "Alice15"));
    map.add(make_shared<int>(10002), make_shared<Person>(16, "Alice16"));
    map.add(make_shared<int>(10005), make_shared<Person>(18, "Alice18"));
    map.traverse();
    return 0;
}

/*
<10002-[16, Alice16]>
<10005-[18, Alice18]>
<10006-[12, Alice12]>
<10008-[15, Alice15]>
delete 0xf868f0[18, Alice18]
delete 0xf86830[16, Alice16]
delete 0xf86770[15, Alice15]
delete 0xf866b0[12, Alice12]
*/
