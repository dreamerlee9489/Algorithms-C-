/**
 * @file container-with-most-water.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 11. 盛最多水的容器
 * @version 0.1
 * @date 2022-07-25
 * @link https://leetcode.cn/problems/container-with-most-water/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	int maxArea(vector<int>& height) {
		if (height.empty())
			return 0;
		int l = 0, r = height.size() - 1;
		int minH = 0, area = 0;
		while (l < r) {
			if (height[l] <= height[r]) {
				minH = height[l];
				area = max(area, (r - l) * minH);
				while (l < r && height[l] <= minH)
					l++;
			}
			else {
				minH = height[r];
				area = max(area, (r - l) * minH);
				while (l < r && height[r] <= minH)
					r--;
			}
		}
		return area;
	}
};