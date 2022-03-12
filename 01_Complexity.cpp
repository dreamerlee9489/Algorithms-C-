#include <time.h>
#include <iostream>
using namespace std;

int fib1(int n);
int fib2(int n);

int main()
{
    clock_t start, end1, end2;
    start = clock();
    fib1(40);
    end1 = clock();
    cout << "time1 = " << double(end1 - start) / CLOCKS_PER_SEC << "s" << endl;
    fib2(40);
    end2 = clock();
    cout << "time2 = " << double(end2 - end1) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}

int fib1(int n)
{
    if (n <= 1)
        return n;
    return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n)
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
时间：
    2022年3月13日 00:15:29
输出：
    time1 = 0.576s
    time2 = 0.001s
*/
