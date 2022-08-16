/**
 * @file excel-sheet-column-number.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 171. Excel 表列序号
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/excel-sheet-column-number/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <cmath>
#include <string>

using namespace std;

class Solution {
public:
  int titleToNumber(string columnTitle) {
    int res = 0;
    for (int i = 0; i < columnTitle.size(); i++) {
      res += (columnTitle[i] - 'A' + 1) * pow(26, columnTitle.size() - 1 - i);
    }
    return res;
  }
};