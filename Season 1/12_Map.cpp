#include <iostream>
#include <string>
#include "./12_Map.h"
#include "./Person.h"
using namespace std;

int main(int argc, char const *argv[])
{
    Map<int, Person> map;
    map.add(make_shared<int>(2), make_shared<Person>(16, "Alice16"));
    map.add(make_shared<int>(5), make_shared<Person>(18, "Alice18"));
    map.add(make_shared<int>(6), make_shared<Person>(12, "Alice12"));
    map.add(make_shared<int>(8), make_shared<Person>(15, "Alice15"));
    map.traverse();
    return 0;
}

/*
2022年4月18日 09:32:38
输出：
[2-[16, Alice16]]
[5-[18, Alice18]]
[6-[12, Alice12]]
[8-[15, Alice15]]
delete 0xdc66b0[16, Alice16]
delete 0xdc68f0[15, Alice15]
delete 0xdc6830[12, Alice12]
delete 0xdc6770[18, Alice18]
*/
