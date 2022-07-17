#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
using namespace std;

/**
 * @brief 零钱兑换
 * @remark 动态规划
 * @date 2022-07-08 
 * @param faces
 * @param money
 */
int coinChange(int n, vector<int> faces)
{
    if(n < 1 || faces.size() == 0)
        return -1;
    int *dp = new int[n + 1] {};
    for (size_t i = 1; i <= n; i++)
    {
        int min = INT_MAX;
        for(int face : faces)
        {
            if(i >= face)
            {
                int v = dp[i - face];
                if(v >= 0 && v < min)
                    min = v;
            }
        }
        dp[i] = min == INT_MAX ? -1 : (min + 1);
    }
    return dp[n];
}

int main(int argc, char const *argv[])
{
    cout << coinChange(41, vector<int>({1, 5, 25, 20}));
    return 0;
}
