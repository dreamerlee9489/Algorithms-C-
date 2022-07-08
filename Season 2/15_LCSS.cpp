#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * @brief 最长公共子串长度
 * @remark 动态规划
 * @return int
 */
int lcss(string str1, string str2)
{
    if (str1.length() == 0 || str2.length() == 0)
        return 0;
    string &rowStr = str1.length() < str2.length() ? str2 : str1;
    string &colStr = str1.length() < str2.length() ? str1 : str2;
    int *dp = new int[colStr.length() + 1]{};
    int max = 0;
    for (size_t row = 1; row <= rowStr.length(); row++)
    {
        for (size_t col = colStr.length(); col >= 1; col--)
        {
            if(str1[row - 1] != str2[col - 1])
                dp[col] = 0;
            else
            {
                dp[col] = dp[col - 1] + 1;
                max = std::max(dp[col], max);
            }
        }
    }
    return max;
}

int main(int argc, char const *argv[])
{
    cout << lcss("ABDCBA", "ABCBA");
    return 0;
}
