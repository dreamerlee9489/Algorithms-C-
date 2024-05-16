#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "\n***01***\n";
    int a = 12, b = 3;
    cout << (b || a - 4 & a / b);
    cout << "\n***02***\n"; 
    b = 0;
    cout << (a+=b*=a-=b/=a-b);
    return 0;
}