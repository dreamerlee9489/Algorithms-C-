/**
 * @file sub-sort-lcci.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 面试题 16.16. 部分排序
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/sub-sort-lcci/
 * @copyright Copyright (c) 2022
 *
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目要求找出数组中需要排序的最短子数组，使得整个数组变为非降序排列。为了做到这一点，我们可以从两个方向来观察数组：
 * 从左往右遍历：找出最后一个破坏非降序的元素的位置，记为end。这个位置之后的所有元素都应该比end位置的元素要大。
 * 从右往左遍历：找出最后一个破坏非升序的元素的位置，记为begin。这个位置之前的所有元素都应该比begin位置的元素要小。
 * 确定排序区间：一旦我们找到begin和end，我们知道在区间[begin, end]之外的元素都已经是有序的。因此，只需要对这个区间的元素进行排序，整个数组就会变得有序。
 * 处理特殊情况：如果整个数组已经是有序的，则返回[-1, -1]。
 * 时间和空间复杂度：时间复杂度为O(n)，因为我们只需要两次遍历整个数组。空间复杂度为O(1)，因为我们只需要常数空间来存储索引。
 *
 */
#include <vector>
using namespace std;

class Solution {
public:
	vector<int> subSort(vector<int>& array) {
		int n = array.size();
		int maxVal = INT_MIN, minVal = INT_MAX;
		int begin = -1, end = -1;

		// 从左向右寻找逆序对，并更新end
		for (int i = 0; i < n; ++i) {
			if (array[i] < maxVal) {
				end = i;
			}
			else {
				maxVal = array[i];
			}
		}

		// 从右向左寻找逆序对，并更新begin
		for (int i = n - 1; i >= 0; --i) {
			if (array[i] > minVal) {
				begin = i;
			}
			else {
				minVal = array[i];
			}
		}

		return { begin, end };
	}
};