/**
 * @file implement-strstr.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 28. 实现 strStr()
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/implement-strstr/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        // size_t pos = haystack.find(needle);
        // return pos == string::npos ? -1 : pos;
        for (int i = 0; i < haystack.size(); i++)
            if (haystack.substr(i, needle.size()) == needle)
                return i;
        return -1;
    }
};