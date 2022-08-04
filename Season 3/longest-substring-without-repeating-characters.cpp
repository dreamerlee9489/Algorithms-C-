/**
 * @file longest-substring-without-repeating-characters.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 3. 无重复字符的最长子串
 * @version 0.1
 * @date 2022-07-20
 * @link https://leetcode.cn/problems/longest-substring-without-repeating-characters/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.empty())
            return 0;
        vector<int> prevIdxs = vector<int>(128, -1);
        prevIdxs[s[0]] = 0;
        int li = 0, max = 1;
        for (int i = 1; i < s.size(); ++i)
        {
            int pi = prevIdxs[s[i]];
            if (li <= pi)
                li = pi + 1;
            prevIdxs[s[i]] = i;
            max = std::max(max, i - li + 1);
        }
        return max;
    }
};

int main(int argc, char const *argv[])
{
    // cout << Solution().lengthOfLongestSubstring("abcabcbb") << "\n";
    // cout << Solution().lengthOfLongestSubstring("bbbbb") << "\n";
    cout << Solution().lengthOfLongestSubstring("pwwkew") << "\n";
    return 0;
}
