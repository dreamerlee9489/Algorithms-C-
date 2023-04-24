#include <string.h>
#include <iostream>
using namespace std;

int main()
{
    const char str[] = "HelloWorld";
    cout << "len=" << strlen(str) << ", " << sizeof(str) << "\n";
    return 0;
}