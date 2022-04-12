#include <ctime>
#include <iostream>
using namespace std;
//斐波那契数列递归算法
int fib1(int n);
//斐波那契数列迭代算法
int fib2(int n);

int main()
{
    clock_t start, end1, end2;
    start = clock();
    fib1(48);
    end1 = clock();
    cout << "time1 = " << double(end1 - start) / CLOCKS_PER_SEC << "s" << endl;
    fib2(48);
    end2 = clock();
    cout << "time2 = " << double(end2 - end1) / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}

inline int fib1(int n)
{
    if (n <= 1)
        return n;
    return fib1(n - 1) + fib1(n - 2);
}

inline int fib2(int n)
{
    if (n <= 1)
        return n;
    int first = 0, second = 1;
    for (size_t i = 0; i < n - 1; i++)
    {
        int sum = first + second;
        first = second;
        second = sum;
    }
    return second;
}

/*
2022年3月15日 12:17:58
输出：
time1 = 13.218s
time2 = 0.002s
*/