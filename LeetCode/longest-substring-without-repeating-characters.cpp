/**
 * @file longest-substring-without-repeating-characters.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 3. 无重复字符的最长子串
 * @version 0.1
 * @date 2022-07-30
 * @remark https://leetcode.cn/problems/longest-substring-without-repeating-characters/
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
        if(s.empty())
            return 0;
        vector<int> indexes = vector<int>(128, -1);
        int maxLen = 1;    
        int beginIndex = 0;                 // 上一个最长不重复子串开始索引
        for (int i = 0; i < s.size(); i++)
        {
            int lastIndex = indexes[s[i]];  // 当前字符上次出现的索引
            if(beginIndex <= lastIndex)     // 当前字符上次出现的索引在最长不重复子串开始索引之后    
                beginIndex = lastIndex + 1; // 将最长不重复子串的开始索引更新为当前字符上次出现索引的下一个位置
            indexes[s[i]] = i;  
            maxLen = max(maxLen, i - beginIndex + 1);
        }
        return maxLen;
    }
};

int main(int argc, char const *argv[])
{
    cout << Solution().lengthOfLongestSubstring("abcabcbb") << "\n";
    cout << Solution().lengthOfLongestSubstring("bbbbb") << "\n";
    cout << Solution().lengthOfLongestSubstring("pwwkew") << "\n";
    return 0;
}
