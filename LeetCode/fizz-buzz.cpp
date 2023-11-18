/**
 * @file fizz-buzz.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 412. Fizz Buzz
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/fizz-buzz/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	vector<string> fizzBuzz(int n) {
		vector<string> res(n);
		for (int i = 0; i < n; i++) {
			int mod3 = (i + 1) % 3;
			int mod5 = (i + 1) % 5;
			if (mod3 == 0 && mod5 != 0)
				res[i] += "Fizz";
			else if (mod3 != 0 && mod5 == 0)
				res[i] += "Buzz";
			else if (mod3 == 0 && mod5 == 0)
				res[i] += "FizzBuzz";
			else
				res[i] += to_string(i + 1);
		}
		return res;
	}
};

int main(int argc, char const* argv[]) {
	auto res = Solution().fizzBuzz(3);
	return 0;
}
