/**
 * @file longest-common-prefix.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 14. 最长公共前缀
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/longest-common-prefix/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        int index = 0;
        while (index < strs[0].size()) {
            for (int i = 1; i < strs.size(); i++) {
                if (index >= strs[i - 1].size() || strs[i][index] != strs[i - 1][index])
                    return strs[0].substr(0, index);
            }
            ++index;
        }
        return strs[0].substr(0, index);
    }
};