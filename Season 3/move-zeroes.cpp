/**
 * @file move-zeroes.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 283. 移动零
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/move-zeroes/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
using namespace std;

/**
 * 解题技巧总结：
 * 为了高效地完成这个任务，可以采用以下方法：
 * 双指针法：使用两个指针，一个用于遍历数组，另一个指向最近的零元素的位置或下一个非零元素应该放置的位置。
 * 遍历一次：遍历数组一次，用一个指针i去遍历数组，另一个指针nonZeroPos记录下一个非零元素应该放置的位置。
 * 交换元素：当i指向的元素非零且i和nonZeroPos不相同时，将其与nonZeroPos指向的元素交换，然后nonZeroPos前移一位。
 * 保持相对顺序：通过上述交换操作，可以保证非零元素的相对顺序不变。
 * 边界条件处理：当数组中没有0或者全是0时，无需任何操作。
 *
 */
class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		int nonZeroPos = 0; // 初始化非零元素应该放置的位置
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] != 0) {
				if (i != nonZeroPos) { // 当前非零元素不在它应该在的位置
					swap(nums[i], nums[nonZeroPos]); // 交换当前元素与nonZeroPos位置上的元素
				}
				nonZeroPos++; // 更新下一个非零元素应该放置的位置
			}
		}
	}
};