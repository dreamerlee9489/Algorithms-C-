/**
 * @file string-to-integer-atoi.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 8. 字符串转换整数 (atoi)
 * @version 0.1
 * @date 2022-08-06
 * @link https://leetcode.cn/problems/string-to-integer-atoi/
 * @copyright Copyright (c) 2022
 *
 */
#include <cmath>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class Solution {
public:
	int myAtoi(string s) {
		long res = 0;
		char sign = '\0';
		if (!s.empty()) {
			int i = 0;
			while (s[i] == ' ')
				++i;
			while (s[i] == '+' || s[i] == '-') {
				if (sign != '\0')
					return 0;
				sign = s[i];
				++i;
			}
			queue<int> digits;
			for (; i < s.size(); i++) {
				if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {
					if (s[i] == '0' && digits.empty())
						continue;
					digits.push(s[i] - '0');
				}
				else if (s[i] == '+' || s[i] == '-') {
					if (digits.empty())
						return 0;
					else
						break;
				}
				else
					break;
			}
			if (digits.size() > 10)
				return sign == '-' ? INT_MIN : INT_MAX;
			while (!digits.empty()) {
				int digit = digits.front();
				digits.pop();
				res += digit * pow(10, digits.size());
				if (res > INT_MAX)
					return sign == '-' ? INT_MIN : INT_MAX;
			}
		}
		return sign == '-' ? (int)res * -1 : (int)res;
	}
};

int main(int argc, char const* argv[]) {
	// cout << INT_MAX << ", " << INT_MIN << "\n";
	// cout << Solution().myAtoi("2147483647") << "\n";
	// cout << Solution().myAtoi("2147483648") << "\n";
	// cout << Solution().myAtoi("-2147483648") << "\n";
	// cout << Solution().myAtoi("-2147483649") << "\n";
	cout << Solution().myAtoi("  -42") << "\n";
	return 0;
}
