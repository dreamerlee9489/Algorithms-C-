#include "./TestHash.h"
using namespace app;

int main(int argc, char const *argv[])
{
    Test<int> t;
    cout << "Test:" << hash<Test<int>>()(t) << "\n";
    // cout << "Test2:" << t.get_hash() << "\n";    
    Test3 t3;
    cout << "Test3:" << hash<Test3>()(t3) << "\n";
    cout << "Test4:" << t3.get_hash() << "\n";
    return 0;
}
