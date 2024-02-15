/**
 * @file sum-of-two-integers.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 371. 两整数之和
 * @version 0.1
 * @date 2022-08-15
 * @link https://leetcode.cn/problems/sum-of-two-integers/
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>

using namespace std;

class Solution {
public:
	int getSum(int a, int b) {
		int sum = 0, carry = 0;
		for (int i = 0; i < 32; i++) {
			int temp = 0;
			if ((a & 1) && (b & 1)) {
				temp |= 0 | carry;
				sum |= temp << i;
				carry = 1;
			}
			else {
				temp = (a & 1) | (b & 1);
				if (temp && carry)
					carry = 1;
				else {
					temp |= carry;
					sum |= temp << i;
					carry = 0;
				}
			}
			a >>= 1;
			b >>= 1;
		}
		return sum;
	}
};

int main(int argc, char const* argv[]) {
	cout << Solution().getSum(9, 2) << "\n";
	cout << Solution().getSum(9, 3) << "\n";
	cout << Solution().getSum(11, 3) << "\n";
	cout << Solution().getSum(15, -16) << "\n";
	cout << Solution().getSum(-12, 15) << "\n";
	cout << Solution().getSum(-12, -15) << "\n";
	return 0;
}
