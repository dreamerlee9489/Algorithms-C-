/**
 * @file container-with-most-water.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 11. 盛最多水的容器
 * @version 0.1
 * @date 2022-07-25
 * @link https://leetcode.cn/problems/container-with-most-water/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm> // 为了使用std::min和std::max

 /**
  * 为了解决这个问题，我们可以使用两个指针，一个指向数组的开始，另一个指向数组的末尾。我们计算两指针之间构成的容器的容量，并逐渐向中间移动，直到两指针相遇。在移动的过程中，我们总是移动指向较短线段的指针，这是因为容器的容量由较短的线段决定，移动较长的线段不会增加容器的容量。
  * 解题思路总结：
  * 初始化最大容量maxArea为0。
  * 初始化两个指针，left指向数组的开始（索引0），right指向数组的末尾（索引height.size() - 1）。
  * 当left小于right时，执行以下步骤：
  * 	计算当前left和right指向的线段构成的容器容量，容量计算方法是min(height[left], height[right]) * (right - left)。
  * 	更新maxArea为当前容量和maxArea之间的较大者。
  * 	如果height[left]小于height[right]，则移动left指针向右（left++），否则移动right指针向左（right--）。
  * 当两个指针相遇时，我们已经考虑了所有可能的容器，maxArea包含了最大的水量。
  * 返回maxArea。
  *
  */
class Solution {
public:
	int maxArea(std::vector<int>& height) {
		int maxArea = 0;
		int left = 0;
		int right = height.size() - 1;
		while (left < right) {
			// 计算并更新最大面积
			maxArea = std::max(maxArea, std::min(height[left], height[right]) * (right - left));
			// 移动指向较短线段的指针
			if (height[left] < height[right]) {
				left++;
			}
			else {
				right--;
			}
		}
		return maxArea;
	}
};