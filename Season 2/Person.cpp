#include "./Person.hpp"
#include <iostream>
#include <map>
#include <vector>

using namespace app;

int main(int argc, char const *argv[]) {
    vector<Person> _vec, _vec2;
    map<Person, string> _map;
    _vec.push_back(Person(10));
    _vec.push_back(Person(11));
    _vec.push_back(Person(12));
    _map.emplace(make_pair(Person(13), "aaa"));
    _map.emplace(make_pair(Person(14), "bbb"));
    _map.emplace(make_pair(Person(15), "ccc"));
    for (Person p: _vec)
        cout << p << "\n";
    for (pair<Person, string> p: _map)
        cout << p.first << "-" << p.second << "\n";
    for (map<Person, string>::iterator iter = _map.begin(); iter != _map.end();
         ++iter)
        cout << iter->first << "-" << iter->second << "\n";
    return 0;
}
