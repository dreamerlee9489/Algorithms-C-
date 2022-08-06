#include <iostream>

using namespace std;

int climb_stairs0(int n) {
    if (n <= 2)
        return n;
    return climb_stairs0(n - 1) + climb_stairs0(n - 2);
}

int climb_stairs1(int n) {
    if (n <= 2)
        return n;
    int first = 0, second = 1;
    for (size_t i = 0; i < n - 1; i++) {
        int sum = first + second;
        first = second;
        second = sum;
    }
    return second;
}