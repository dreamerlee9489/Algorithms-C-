/**
 * @file trapping-rain-water.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 42. 接雨水
 * @version 0.1
 * @date 2022-07-25
 * @link https://leetcode.cn/problems/trapping-rain-water/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目要求我们计算在一个由柱子组成的容器中能接多少雨水。解决这个问题的关键是找到每个柱子上方能够接多少雨水，然后将所有柱子上方的雨水量加起来。以下是几种常见的方法：
 * 暴力法：对于数组中的每个元素，找到其左边和右边最高的柱子，这两个柱子之间的较小者决定了当前位置能接的雨水高度。时间复杂度为O(n^2)。
 * 动态编程：为了减少重复计算，我们可以用两个数组分别存储每个位置左边和右边最高的柱子高度，这样就可以在O(n)的时间内找到任意位置能接的雨水高度。时间复杂度降低为O(n)，但空间复杂度上升为O(n)。
 * 双指针法：动态编程的基础上，可以进一步优化空间复杂度。使用两个指针分别从前后遍历数组，在移动指针的过程中维护左边和右边的最高柱子高度，并根据这两个高度计算雨水量。
 * 使用栈：使用栈来跟踪可能储水的最低点。遍历数组时，保持栈内元素单调递减，如果当前柱子的高度大于栈顶柱子的高度，则意味着可以接雨水。计算雨水量，并将当前柱子压入栈中。
 * 
 */
class Solution {
public:
	int trap(vector<int>& height) {
		int left = 0, right = height.size() - 1;
		int ans = 0;
		int left_max = 0, right_max = 0;

		while (left < right) {
			if (height[left] < height[right]) {
				height[left] >= left_max ? (left_max = height[left]) : ans += (left_max - height[left]);
				++left;
			}
			else {
				height[right] >= right_max ? (right_max = height[right]) : ans += (right_max - height[right]);
				--right;
			}
		}

		return ans;
	}
};