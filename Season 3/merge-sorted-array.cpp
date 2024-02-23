/**
 * @file merge-sorted-array.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 合并两个有序数组
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/merge-sorted-array/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
using namespace std;

/**
 * 解题技巧总结：
 * 从后向前合并：由于nums1数组的后端有足够的空间容纳nums2，可以从两个数组的末尾开始，逐一比较元素，并把较大的元素放到nums1的末尾。这样可以减少元素移动的次数。
 * 三个指针：使用三个指针分别指向nums1的有效元素末尾、nums2的末尾以及nums1的末尾（合并后的位置）。
 * 边界条件：在合并过程中，需要考虑nums1或nums2可能先被合并完的情况。如果nums2还有剩余元素，需要将它们复制到nums1的前面；如果nums1先合并完，由于元素已在正确位置，不需要额外操作。
 * 直接操作原数组：因为题目要求直接在nums1数组上修改，所以不需要使用额外的数组空间。
 *
 */
class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int p1 = m - 1; // 指向nums1最后一个有效元素
		int p2 = n - 1; // 指向nums2最后一个元素
		int p = m + n - 1; // 指向合并后nums1的最后一个位置

		// 从后向前合并
		while (p1 >= 0 && p2 >= 0) {
			// 比较nums1和nums2末尾元素，取较大者放到p的位置
			if (nums1[p1] > nums2[p2]) {
				nums1[p--] = nums1[p1--];
			}
			else {
				nums1[p--] = nums2[p2--];
			}
		}

		// 如果nums2还有剩余，复制到nums1前面
		while (p2 >= 0) {
			nums1[p--] = nums2[p2--];
		}
		// 如果nums1有剩余，则它们已经在正确位置，无需额外操作
	}
};