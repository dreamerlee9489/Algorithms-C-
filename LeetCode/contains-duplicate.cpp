/**
 * @file contains-duplicate.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 217. 存在重复元素
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/contains-duplicate/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
	bool containsDuplicate(vector<int>& nums) {
		unordered_map<int, int> _map;
		for (int i : nums)
			if (++_map[i] > 1)
				return true;
		return false;
	}
};