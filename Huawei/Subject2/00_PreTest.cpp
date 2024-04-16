#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "***01***\n";
    int* const p = nullptr; // const修饰p，p不可修改
    int i = 10, j = 20;
    const int* q = &i;      // const修饰int，q可修改
    // p = q;
    q = &j;
    cout << "***02***\n"; 
    // 考察运算符优先级  
    int a = 6, b = 5;
    cout << (b | a * b & a + b) << "\n";
    cout << "***19***\n";   
    // ++i 返回 i 的引用
    // 右值：无名称，不可识别地址值
    decltype (++i) var8 = i;
    cout << typeid(var8).name() << endl;
    return 0;
}