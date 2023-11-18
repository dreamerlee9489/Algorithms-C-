/**
 * @file majority-element.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 169. 多数元素
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/majority-element/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int majorityElement(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int num = nums[0], count = 1, target = nums.size() / 2;
		for (int i = 1; i < nums.size(); i++) {
			if (nums[i] == num) {
				if (++count > target)
					return num;
			}
			else {
				num = nums[i];
				count = 1;
			}
		}
		return num;
	}
};

int main(int argc, char const* argv[]) {
	vector<int> nums1 = { 3, 2, 3 };
	cout << Solution().majorityElement(nums1);
	return 0;
}
