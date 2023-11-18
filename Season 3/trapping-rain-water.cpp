/**
 * @file trapping-rain-water.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 42. 接雨水
 * @version 0.1
 * @date 2022-07-25
 * @link https://leetcode.cn/problems/trapping-rain-water/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	int trap(vector<int>& height) {
		if (height.empty())
			return 0;
		int l = 0, r = height.size() - 1, lowerMax = 0, water = 0;
		while (l < r) {
			int lower = height[height[l] <= height[r] ? l++ : r--];
			lowerMax = max(lowerMax, lower);
			water += lowerMax - lower;
		}
		return water;
	}

	int trap1(vector<int>& height) {
		if (height.empty())
			return 0;
		int lastIndex = height.size() - 2, water = 0;
		vector<int> leftMaxes = vector<int>(height.size());
		vector<int> rightMaxes = vector<int>(height.size());
		for (int i = 1; i <= lastIndex; ++i)
			leftMaxes[i] = max(leftMaxes[i - 1], height[i - 1]);
		for (int i = lastIndex; i >= 1; --i)
			rightMaxes[i] = max(rightMaxes[i + 1], height[i + 1]);
		for (int i = 1; i <= lastIndex; ++i) {
			int min = std::min(leftMaxes[i], rightMaxes[i]);
			if (min > height[i])
				water += min - height[i];
		}
		return water;
	}
};