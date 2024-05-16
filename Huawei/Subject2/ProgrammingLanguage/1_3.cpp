#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << "\n***01***\n";
    int a = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if ((i + j) % 2 == 0)
            {
                break;
            }
            a++;
        }
    }
    std::cout << a << std::endl;
    return 0;
}