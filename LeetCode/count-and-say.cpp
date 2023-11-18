/**
 * @file count-and-say.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 38. 外观数列
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/count-and-say/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>

using namespace std;

class Solution {
	string parse(string s) {
		int count = 1;
		char ch = s[0];
		string res;
		for (int i = 1; i < s.size(); i++) {
			if (s[i] == ch)
				++count;
			else {
				res += to_string(count) + ch;
				ch = s[i];
				count = 1;
			}
		}
		return res += to_string(count) + s[s.size() - 1];
	}

public:
	string countAndSay(int n) {
		if (n == 1)
			return "1";
		return parse(countAndSay(n - 1));
	}
};

int main(int argc, char const* argv[]) {
	cout << Solution().countAndSay(5) << "\n";
	return 0;
}
