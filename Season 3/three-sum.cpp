/**
 * @file 3sum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 15. 三数之和
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/3sum/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目要求我们从数组中找出所有可能的三个数，它们的和等于0。为了解决这个问题，我们可以采取以下步骤：
 * 排序：首先对数组进行排序，这样可以方便我们后续的双指针操作，并且能够帮助我们避免重复的三元组。
 * 遍历+双指针：遍历排序后的数组，对于每个元素nums[i]，使用两个指针分别指向i+1和数组的尾部，进行双指针扫描，寻找两个数的和为-nums[i]。
 * 跳过重复元素：在遍历和双指针移动过程中，如果遇到重复的元素，应该跳过，避免产生重复的三元组。
 * 移动指针：当三数之和小于0时，移动左指针；当三数之和大于0时，移动右指针；当三数之和等于0时，记录这个三元组，并同时移动两个指针，同时注意跳过重复元素。
 * 时间和空间复杂度：排序的时间复杂度为O(nlogn)，双指针遍历的时间复杂度为O(n^2)，因此总的时间复杂度为O(n^2)。空间复杂度为O(1)，如果不考虑存储答案所使用的空间。
 *
 */
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		int n = nums.size();

		for (int i = 0; i < n; ++i) {
			// 跳过重复元素
			if (i > 0 && nums[i] == nums[i - 1]) continue;

			int target = -nums[i];
			int left = i + 1, right = n - 1;

			while (left < right) {
				int sum = nums[left] + nums[right];
				if (sum < target) {
					++left;
				}
				else if (sum > target) {
					--right;
				}
				else {
					res.push_back({ nums[i], nums[left], nums[right] });
					// 跳过重复元素
					while (left < right && nums[left] == nums[left + 1]) ++left;
					while (left < right && nums[right] == nums[right - 1]) --right;
					++left;
					--right;
				}
			}
		}
		return res;
	}
};