/**
 * @file longest-palindromic-substring.cpp
 * @author your name (you@domain.com)
 * @brief 5. 最长回文子串
 * @version 0.1
 * @date 2022-07-27
 * @remark https://leetcode.cn/problems/longest-palindromic-substring/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        if (s.size() < 2)
            return s;
        int maxLen = 1, begin = 0, center = 0;
        while (center < s.size())
        {
            int left = center - 1, right = center + 1;
            while (s[right] == s[center] && right < s.size())
                right++;
            center = right;
            while (left >= 0 && right < s.size() && s[left] == s[right])
            {
                left--;
                right++;
            }
            int len = right - ++left;
            if(len > maxLen)
            {
                maxLen = len;
                begin = left;
            }
        }
        return string(s, begin, maxLen);
    }

    string longestPalindrome1(string s)
    {
        if (s.size() < 2)
            return s;
        vector<vector<bool>> dp = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));
        int maxLen = 1, begin = 0;
        for (int i = s.size() - 1; i >= 0; --i)
        {
            for (int j = i; j < s.size(); ++j)
            {
                int len = j - i + 1;
                dp[i][j] = s[i] == s[j] && (len <= 2 || dp[i + 1][j - 1]);
                if(dp[i][j] && len > maxLen)
                {
                    maxLen = len;
                    begin = i;
                }
            }
        }
        return string(s, begin, maxLen);
    }
};