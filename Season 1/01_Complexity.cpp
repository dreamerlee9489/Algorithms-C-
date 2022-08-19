/**
 * @file 01_Complexity.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 斐波那契数列
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <ctime>
#include <iostream>

using namespace std;

// 递归算法
int fib1(int n) {
  if (n <= 1)
    return n;
  return fib1(n - 1) + fib1(n - 2);
}

// 迭代算法
int fib2(int n) {
  if (n <= 1)
    return n;
  int first = 0, second = 1;
  for (size_t i = 0; i < n - 1; i++) {
    int sum = first + second;
    first = second;
    second = sum;
  }
  return second;
}

int main() {
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

/*
time1 = 13.218s
time2 = 0.002s
*/