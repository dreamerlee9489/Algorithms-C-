#include <iostream>
using namespace std;

#pragma pack(push)
#pragma pack(4)
struct A
{
    int i1;//4
    short sh;//2
    int i2;//2+4, 地址必须是4倍数
    char ch;//1
    //+3，总大小必须是4倍数，方便连续存储
};

struct B
{
    int i1;//4
    short sh;//2
    char ch;//1
    int i2;//1+4, 地址必须是4倍数
};
#pragma pack(pop)

int main()
{
    A a;
    B b;
    cout << sizeof(A) << " - " << sizeof(B) << "\n";
    cout << (size_t)&a.i1 << ", " << (size_t)&a.sh << ", " << (size_t)&a.i2 << ", " << (size_t)&a.ch << "\n";
    cout << (size_t)&b.i1 << ", " << (size_t)&b.sh << ", " << (size_t)&b.ch << ", " << (size_t)&b.i2 << "\n";
}