/**
 * @file longest-substring-with-at-most-k-distinct-characters.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 340. 至多包含 K 个不同字符的最长子串
 * @version 0.1
 * @date 2022-08-14
 * @link https://leetcode.cn/problems/longest-substring-with-at-most-k-distinct-characters/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0)
            return 0;
        unordered_map<char, int> _map = {{s[0], 0}};
        vector<int> _dp(s.size(), 1);
        int maxLen = 1;
        for (int i = 1; i < s.size(); i++) {
            _map[s[i]] = i;
            if (_map.size() <= k) {
                _dp[i] = _dp[i - 1] + 1;
                maxLen = max(maxLen, _dp[i]);
            } else {
                auto temp = _map.begin();
                for (auto iter = _map.begin(); iter != _map.end(); ++iter)
                    if (iter->second < temp->second)
                        temp = iter;
                _dp[i] = i - _map[temp->first];
                _map.erase(temp);
                maxLen = max(maxLen, _dp[i]);
            }
        }
        return maxLen;
    }
};