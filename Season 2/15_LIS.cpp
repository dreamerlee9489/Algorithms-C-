#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * @brief 最长上升子序列长度
 * @remark 动态规划
 * @date 2022-07-08 
 * @param nums 
 * @return int 
 */
int lengthOfLIS(vector<int> nums) {
    if (nums.size() == 0)
        return 0;
    int *dp = new int[nums.size()]{};
    int max = dp[0] = 1;
    for (size_t i = 1; i < nums.size(); i++) {
        dp[i] = 1;
        for (size_t j = 0; j < i; j++) {
            if (nums[i] > nums[j])
                dp[i] = std::max(dp[i], dp[j] + 1);
        }
        max = std::max(dp[i], max);
    }
    return max;
}

int main(int argc, char const *argv[]) {
    cout << lengthOfLIS(vector<int>({10, 2, 2, 5, 1, 7, 101, 18}));
    return 0;
}
