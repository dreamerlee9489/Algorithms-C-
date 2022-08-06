/**
 * @file container-with-most-water.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 11. 盛最多水的容器
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/container-with-most-water/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxArea(vector<int> &height) {
        int area = 0;
        int l = 0, r = height.size() - 1;
        while (l < r) {
            if (height[l] <= height[r]) {
                area = max((r - l) * height[l], area);
                l++;
            } else {
                area = max((r - l) * height[r], area);
                r--;
            }
        }
        return area;
    }
};