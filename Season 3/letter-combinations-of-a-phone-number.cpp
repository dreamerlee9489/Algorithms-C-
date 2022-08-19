/**
 * @file letter-combinations-of-a-phone-number.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 17. 电话号码的字母组合
 * @version 0.1
 * @date 2022-07-23
 * @link https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
 * @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
  vector<vector<char>> lettersVec = {{'a', 'b', 'c'}, {'d', 'e', 'f'},
                                     {'g', 'h', 'i'}, {'j', 'k', 'l'},
                                     {'m', 'n', 'o'}, {'p', 'q', 'r', 's'},
                                     {'t', 'u', 'v'}, {'w', 'x', 'y', 'z'}};
  string digits;
  string combine;
  vector<string> list;

  void dfs(size_t index) {
    if (index == digits.size()) {
      list.emplace_back(combine);
      return;
    }
    vector<char> letters = lettersVec[digits[index] - '2'];
    for (char letter : letters) {
      combine[index] = letter;
      dfs(index + 1);
    }
  }

public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty())
      return vector<string>();
    this->digits = digits;
    this->combine = string(digits);
    dfs(0);
    return list;
  }
};