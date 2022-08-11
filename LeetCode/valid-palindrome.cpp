/**
 * @file valid-palindrome.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 125. 验证回文串
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/valid-palindrome/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        string str;
        for (int i = 0; i < s.size(); i++) {
            if ((s[i] - '0' >= 0 && s[i] - '0' <= 9) || (s[i] - 'a' >= 0 && s[i] - 'a' <= 25) ||
                (s[i] - 'A' >= 0 && s[i] - 'A' <= 25))
                str += tolower(s[i]);
        }
        int left = 0, right = str.size() - 1;
        while (left < right) {
            if (str[left] != str[right])
                return false;
            ++left;
            --right;
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    cout << Solution().isPalindrome("A man, a plan, a canal: Panama") << "\n";
    cout << Solution().isPalindrome("race a car") << "\n";
    cout << Solution().isPalindrome("") << "\n";
    return 0;
}
