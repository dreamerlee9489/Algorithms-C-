#include <vector>
#include <iostream>
#include "./Person.h"
using namespace app;

int main(int argc, char const *argv[])
{
    vector<Person> vec;
    vec.push_back(Person(10));
    vec.push_back(Person(11));
    vec.push_back(Person(12));
    return 0;
}
