#include <ctime>
#include <iostream>

using namespace std;

int fib0(int n) {
    if (n <= 2)
        return 1;
    return fib0(n - 1) + fib0(n - 2);
}

int fib1(int n) {
    if (n <= 2)
        return 1;
    int array[2] = {1, 1};
    for (size_t i = 3; i <= n; i++)
        array[i & 1] = array[(i - 1) & 1] + array[(i - 2) & 1];
    return array[n & 1];
}

int fib2(int n) {
    if (n <= 2)
        return 1;
    int first = 0, second = 1;
    for (size_t i = 0; i < n - 1; i++) {
        int sum = first + second;
        first = second;
        second = sum;
    }
    return second;
}

int main(int argc, char const *argv[]) {
    clock_t start, end0, end1, end2;
    start = clock();
    fib0(48);
    end0 = clock();
    cout << "fib0耗时: " << double(end0 - start) / CLOCKS_PER_SEC << "s" << endl;
    fib1(48);
    end1 = clock();
    cout << "fib1耗时: " << double(end1 - end0) / CLOCKS_PER_SEC << "s" << endl;
    fib2(48);
    end2 = clock();
    cout << "fib2耗时: " << double(end2 - end1) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}

/*
fib0耗时: 6.829s
fib1耗时: 0s
fib2耗时: 0s
*/