/**
 * @file two-sum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 1. 两数之和
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/two-sum/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目要求我们找到数组中的两个数，使得它们的和等于一个给定的目标值target。以下是几种常见的方法和一些解题技巧：
 * 暴力法：遍历数组中的每个元素x，然后再次遍历寻找target - x。这种方法的时间复杂度为O(n^2)。
 * 哈希表：使用哈希表来降低查询时间复杂度。遍历数组，对于每个元素x，我们可以在O(1)时间内查询哈希表中是否存在target - x。如果存在，则找到了答案；如果不存在，则将当前元素x及其索引存入哈希表以供后续查找。这种方法的时间复杂度为O(n)，空间复杂度也为O(n)。
 * 
 */
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> hashTable;
		for (int i = 0; i < nums.size(); i++) {
			auto it = hashTable.find(target - nums[i]);
			if (it != hashTable.end()) {
				return { it->second, i };
			}
			hashTable[nums[i]] = i;
		}
		return {}; // 如果没有解，则返回空数组
	}
};