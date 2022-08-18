#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief 最大连续子序列和
 * @remark 分治
 * @date 2022-07-08
 * @param nums
 * @return int
 */
int maxSubArray(vector<int> &nums, int beg, int end) {
    if (nums.size() == 0)
        return 0;
    if (end - beg < 2)
        return nums[beg];
    int mid = (beg + end) >> 1;
    int leftMax = nums[mid - 1];
    int leftSum = leftMax;
    for (int i = mid - 2; i >= beg; i--) {
        leftSum += nums[i];
        leftMax = max(leftMax, leftSum);
    }
    int rightMax = nums[mid];
    int rightSum = rightMax;
    for (int i = mid + 1; i < end; i++) {
        rightSum += nums[i];
        rightMax = max(rightMax, rightSum);
    }
    return max(leftMax + rightMax,
               max(maxSubArray(nums, beg, mid), maxSubArray(nums, mid, end)));
}

int main(int argc, char const *argv[]) {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << maxSubArray(nums, 0, nums.size()) << "\n";
    return 0;
}
