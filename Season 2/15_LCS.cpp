#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * @brief 最长公共子序列长度
 * @remark 动态规划
 * @return int
 */
int lcss(vector<int> nums1, vector<int> nums2)
{
    if (nums1.size() == 0 || nums2.size() == 0)
        return 0;
    vector<int> &rowsNums = nums1.size() < nums2.size() ? nums2 : nums1;
    vector<int> &colsNums = nums1.size() < nums2.size() ? nums1 : nums2;
    int *dp = new int[colsNums.size() + 1]{};
    for (size_t i = 1; i <= rowsNums.size(); i++)
    {
        int cur = 0;
        for (size_t j = 1; j <= colsNums.size(); j++)
        {
            int leftTop = cur;
            cur = dp[j];
            dp[j] = rowsNums[i - 1] == colsNums[j - 1] ? (leftTop + 1) : max(dp[j], dp[j - 1]);
        }
    }
    return dp[colsNums.size()];
}

int main(int argc, char const *argv[])
{
    cout << lcss(vector<int>({1, 3, 5, 9, 10}), vector<int>({1, 4, 9, 10}));
    return 0;
}
