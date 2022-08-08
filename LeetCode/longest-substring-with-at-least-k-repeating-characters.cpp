/**
 * @file longest-substring-with-at-least-k-repeating-characters.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 395. 至少有 K 个重复字符的最长子串
 * @version 0.1
 * @date 2022-08-08
 * @link https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int dfs(string &str, int l, int r, int k) {
        vector<int> counts(26);
        for (int i = l; i <= r; i++)
            ++counts[str[i] - 'a'];
        char split = 0;
        for (int i = 0; i < counts.size(); i++) {
            if (counts[i] > 0 && counts[i] < k) {
                split = 'a' + i;
                break;
            }
        }
        if (split == 0)
            return r - l + 1;
        int i = l, res = 0;
        while (i <= r) {
            while (i <= r && str[i] == split)
                ++i;
            if (i > r)
                break;
            int start = i;
            while (i <= r && str[i] != split)
                ++i;
            int len = dfs(str, start, i - 1, k);
            res = max(len, res);
        }
        return res;
    }

public:
    int longestSubstring(string s, int k) {
        return dfs(s, 0, s.size() - 1, k);
    }
};