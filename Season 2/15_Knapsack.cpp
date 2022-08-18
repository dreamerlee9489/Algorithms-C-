#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief 0-1背包
 * @remark 动态规划
 * @date 2022-07-08
 * @param values
 * @param weights
 * @param capacity
 * @return int
 */
int maxValue(vector<int> &values, vector<int> &weights, size_t capacity) {
    if (values.size() == 0 || weights.size() == 0)
        return 0;
    if (values.size() != weights.size() || capacity <= 0)
        return 0;
    int *dp = new int[capacity + 1]{};
    for (size_t i = 1; i <= values.size(); i++)
        for (size_t j = capacity; j >= weights[i - 1]; j--)
            dp[j] = max(dp[j], values[i - 1] + dp[j - weights[i - 1]]);
    return dp[capacity];
}

int main(int argc, char const *argv[]) {
    vector<int> values = {6, 3, 5, 4, 6};
    vector<int> weights = {2, 2, 6, 5, 4};
    int capacity = 10;
    cout << maxValue(values, weights, capacity);
    return 0;
}
