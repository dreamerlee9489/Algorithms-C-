/**
 * @file roman-to-integer.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 13. 罗马数字转整数
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/roman-to-integer/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
	unordered_map<char, int> _map = { {'I', 1},   {'V', 5},   {'X', 10},
									 {'L', 50},  {'C', 100}, {'D', 500},
									 {'M', 1000} };

public:
	int romanToInt(string s) {
		int sum = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (i == s.size() - 1) {
				sum += _map[s[i]];
				break;
			}
			if (_map[s[i]] >= _map[s[i + 1]]) {
				sum += _map[s[i]];
			}
			else {
				switch (s[i]) {
				case 'I':
				case 'X':
				case 'C':
					sum += -_map[s[i]];
					break;
				}
			}
		}
		return sum;
	}
};

int main(int argc, char const* argv[]) {
	cout << Solution().romanToInt("III") << "\n";
	cout << Solution().romanToInt("IV") << "\n";
	cout << Solution().romanToInt("IX") << "\n";
	cout << Solution().romanToInt("LVIII") << "\n";
	cout << Solution().romanToInt("MCMXCIV") << "\n";
	cout << Solution().romanToInt("XLIX") << "\n";
	cout << Solution().romanToInt("CMXCIX") << "\n";
	return 0;
}
