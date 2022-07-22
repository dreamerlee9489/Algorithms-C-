/**
 * @file longest-palindromic-substring.cpp
 * @author dreamerlee9489@outlook.com
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
    string preprocess(string str)
    {
        string mStr = string((str.size() << 1) + 3, '#');
        mStr[0] = '^';
        mStr[mStr.size() - 1] = '$';
        for (size_t i = 0; i < str.size(); i++)
            mStr[(i + 1) << 1] = str[i];
        return mStr;
    }

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
     * @brief 马拉车算法
     * @param s
     * @return string
     */
    string longestPalindrome(string s)
    {
        if (s.size() <= 1)
            return s;
        string mStr = preprocess(s);
        vector<int> mCnt = vector<int>(mStr.size());
        size_t c = 1, r = 1, lastIdx = mCnt.size() - 2;
        size_t maxLen = 0, idx = 0, beg = 0;
        for (size_t i = 2; i < lastIdx; i++)
        {
            if (r > i)
            {
                size_t li = (c << 1) - i;
                mCnt[i] = (i + mCnt[li] <= r) ? mCnt[li] : (r - i);
            }
            while (mStr[i + mCnt[i] + 1] == mStr[i - mCnt[i] - 1])
                mCnt[i]++;
            if (i + mCnt[i] > r)
            {
                c = i;
                r = i + mCnt[i];
            }
            if (mCnt[i] > maxLen)
            {
                maxLen = mCnt[i];
                idx = i;
            }
        }
        beg = (idx - maxLen) >> 1;
        return string(s, beg, maxLen);
    }

    /**
     * @brief 扩展中心法优化
     * @param s
     * @return string
     */
    string longestPalindrome3(string s)
    {
        if (s.size() <= 1)
            return s;
        int maxLen = 1, beg = 0, i = 0;
        while (i < s.size())
        {
            int l = i - 1, r = i;
            while (++r < s.size() && s[r] == s[i])
                ;
            i = r;
            while (l >= 0 && r < s.size() && s[l] == s[r])
            {
                l--;
                r++;
            }
            int len = r - ++l;
            if (len > maxLen)
            {
                maxLen = len;
                beg = l;
            }
        }
        return string(s, beg, maxLen);
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
        int maxLen = 1, beg = 0;
        for (int i = s.size() - 2; i >= 1; i--)
        {
            int len1 = palindromeLength(s, i - 1, i + 1);
            int len2 = palindromeLength(s, i, i + 1);
            len1 = max(len1, len2);
            if (len1 > maxLen)
            {
                maxLen = len1;
                beg = i - ((maxLen - 1) >> 1);
            }
        }
        if (s[0] == s[1] && maxLen == 1)
        {
            beg = 0;
            maxLen = 2;
        }
        return string(s, beg, maxLen);
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
        int maxLen = 1, beg = 0;
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
                    beg = i;
                }
            }
        }
        return string(s, beg, maxLen);
    }
};