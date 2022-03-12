#include <time.h>
#include <iostream>
using namespace std;
//0 1 1 2 3 5 8 13 21 34
int fib1(int n);
int fib2(int n);

int main()
{
    clock_t start, end;
    start = clock();
    // fib1(40);
    fib2(40);
    end = clock();
    cout << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
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
