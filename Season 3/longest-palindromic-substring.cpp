/**
 * @file longest-palindromic-substring.cpp
 * @author your name (you@domain.com)
 * @brief 5. 最长回文子串
 * @version 0.1
 * @date 2022-07-21
 * @remark https://leetcode.cn/problems/longest-palindromic-substring/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
    int palindromeLength(string &s, int l, int r)
    {
        while (l >= 0 && r < s.size() && s[l] == s[r])
        {
            l--;
            r++;
        }
        return r - l - 1;
    }

public:
    /**
     * @brief 扩展中心法优化
     * @param s
     * @return string
     */
    string longestPalindrome(string s)
    {
        if (s.size() <= 1)
            return s;
        int maxLen = 1, begin = 0, i = 0;
        while (i < s.size())
        {
            int l = i - 1, r = i;
            while (++r < s.size() && s[r] == s[i]);
            i = r;
            while (l >= 0 && r < s.size() && s[l] == s[r])
            {
                l--;
                r++;
            }
            int len = r - ++l;
            if(len > maxLen)
            {
                maxLen = len;
                begin = l;
            }    
        }
        return string(s, begin, maxLen);
    }

    /**
     * @brief 扩展中心法
     * @param s
     * @return string
     */
    string longestPalindrome2(string s)
    {
        if (s.size() <= 1)
            return s;
        int maxLen = 1, begin = 0;
        for (int i = s.size() - 2; i >= 1; i--)
        {
            int len1 = palindromeLength(s, i - 1, i + 1);
            int len2 = palindromeLength(s, i, i + 1);
            len1 = max(len1, len2);
            if (len1 > maxLen)
            {
                maxLen = len1;
                begin = i - ((maxLen - 1) >> 1);
            }
        }
        if (s[0] == s[1] && maxLen == 1)
        {
            begin = 0;
            maxLen = 2;
        }
        return string(s, begin, maxLen);
    }

    /**
     * @brief 动态规划
     * @param s
     * @return string
     */
    string longestPalindrome1(string s)
    {
        if (s.size() <= 1)
            return s;
        int maxLen = 1, begin = 0;
        vector<vector<bool>> dp = vector<vector<bool>>(s.size(), vector<bool>(s.size()));
        for (int i = s.size() - 1; i >= 0; --i)
        {
            for (int j = i; j < s.size(); ++j)
            {
                int len = j - i + 1;
                dp[i][j] = s[i] == s[j] && (len <= 2 || dp[i + 1][j - 1]);
                if (dp[i][j] && len > maxLen)
                {
                    maxLen = len;
                    begin = i;
                }
            }
        }
        return string(s, begin, maxLen);
    }
};