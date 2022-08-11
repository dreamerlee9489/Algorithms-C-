/**
 * @file palindrome-partitioning.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 131. 分割回文串
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/palindrome-partitioning/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <string>

using namespace std;

class Solution {
    bool isPalindrome(string s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            if (s[l] != s[r])
                return false;
            ++l;
            --r;
        }
        return true;
    }

    void backTrack(string s, int index, vector<string> &path, vector<vector<string>> &res) {
        if (index == s.size()) {
            res.emplace_back(path);
            return;
        }
        for (int i = index + 1; i <= s.size(); i++) {
            string frac = s.substr(index, i - index);
            if (isPalindrome(frac)) {
                path.emplace_back(frac);
                backTrack(s, i, path, res);
                path.erase(prev(path.end()));
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> path;
        backTrack(s, 0, path, res);
        return res;
    }
};