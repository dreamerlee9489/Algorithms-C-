/**
 * @file plus-one.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 66. 加一
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/plus-one/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        vector<int> res = vector<int>(digits.size());
        int ahead = 1;
        for (int i = digits.size() - 1, j = res.size() - 1; i >= -1 || j >= 0; i--, j--) {
            if (i == -1) {
                if (ahead == 1) {
                    vector<int> tmp = vector<int>(digits.size() + 1);
                    tmp[0] = 1;
                    for (int i = 1; i < tmp.size(); i++)
                        tmp[i] = res[i - 1];
                    return tmp;
                }
                break;
            }
            if (digits[i] + ahead < 10) {
                res[j] = digits[i] + ahead;
                ahead = 0;
            } else {
                res[j] = 0;
                ahead = 1;
            }
        }
        return res;
    }

    // vector<int> plusOne(vector<int> &digits)
    // {
    //     vector<int> res;
    //     string str = "";
    //     int num = 0;
    //     for (int i = 0; i < digits.size(); i++)
    //         str += to_string(digits[i]);
    //     num = stoi(str) + 1;                     
    //     str = to_string(num);
    //     for (int i = 0; i < str.size(); i++)
    //         res.emplace_back(stoi(str[i] + ""));
    //     return res;
    // }
};