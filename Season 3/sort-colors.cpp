/**
 * @file sort-colors.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 75. 颜色分类
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/sort-colors/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目要求对一个特定的数组进行排序，其中只包含三种元素（0, 1, 2），对应红色、白色和蓝色。这个问题可以用一趟扫描的算法解决，通常被称为"Dutch National Flag problem"（荷兰国旗问题）。以下是解决这个问题的关键步骤和技巧：
 * 使用三个指针：一个指针low用于0的最右边界，一个指针high用于2的最左边界，一个指针i用于当前遍历的位置。
 * 初始化指针：low指针初始化为0，high指针初始化为数组的最后一个索引，i指针初始化为0。
 * 遍历数组：当i指针小于等于high指针时，进行遍历。
 * 分类讨论：
 * 	如果遇到0，需要与low指针所指的元素交换，并将low指针右移一位，i指针也右移一位。
 * 	如果遇到1，不需要交换，只需要将i指针右移一位。
 * 	如果遇到2，需要与high指针所指的元素交换，并将high指针左移一位，注意此时i指针不移动，因为交换过来的元素需要重新判断。
 * 时间和空间复杂度：时间复杂度为O(n)，其中n是数组的长度，因为我们只需要遍历数组一次。空间复杂度为O(1)，因为我们不需要额外的空间。
 *
 */
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int low = 0, high = nums.size() - 1, i = 0;

		while (i <= high) {
			if (nums[i] == 0) {
				swap(nums[i], nums[low]);
				low++;
				i++;
			}
			else if (nums[i] == 1) {
				i++;
			}
			else {
				swap(nums[i], nums[high]);
				high--;
			}
		}
	}
};