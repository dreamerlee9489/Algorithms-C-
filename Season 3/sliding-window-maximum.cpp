/**
 * @file sliding-window-maximum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 239. 滑动窗口最大值
 * @version 0.1
 * @date 2022-07-19
 * @link https://leetcode.cn/problems/sliding-window-maximum/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        if (nums.empty() || k < 1)
            return vector<int>();
        if (k == 1)
            return nums;
        vector<int> win = vector<int>(nums.size() - k + 1);
        deque<int> deq = deque<int>();
        for (int ri = 0; ri < nums.size(); ri++) {
            while (!deq.empty() && nums[ri] >= nums[deq.back()])
                deq.pop_back();
            deq.push_back(ri);
            int li = ri - k + 1;
            if (li >= 0) {
                if (deq.front() < li)
                    deq.pop_front();
                win[li] = nums[deq.front()];
            }
        }
        return win;
    }
};
