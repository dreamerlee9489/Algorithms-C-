/**
 * @file remove-duplicates-from-sorted-array.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 26. 删除有序数组中的重复项
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/remove-duplicates-from-sorted-array/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int> &nums) {
        int index = 1, num = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != num) {
                nums[index++] = nums[i];
                num = nums[i];
            }
        }
        return index;
    }
};