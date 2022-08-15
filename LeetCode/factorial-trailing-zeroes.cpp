/**
 * @file factorial-trailing-zeroes.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 172. 阶乘后的零
 * @version 0.1
 * @date 2022-08-13
 * @link https://leetcode.cn/problems/factorial-trailing-zeroes/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
    string multiply(string lhs, string rhs) {
        string ans = "";
        vector<string> vec;
        for (int r = rhs.size() - 1; r >= 0; r--) {
            int carry = 0;
            vec.emplace_back("");
            for (int l = lhs.size() - 1; l >= 0; l--) {
                string mul = to_string((lhs[l] - '0') * (rhs[r] - '0') + carry);
                if (mul.size() == 1) {
                    vec.back() += mul[0];
                    carry = 0;
                } else {
                    vec.back() += mul[1];
                    carry = mul[0] - '0';
                }
            }
            if (carry != 0)
                vec.back() += to_string(carry);
            int left = 0, right = vec.back().size() - 1;
            while (left < right) {
                char tmp = vec.back()[left];
                vec.back()[left] = vec.back()[right];
                vec.back()[right] = tmp;
                ++left;
                --right;
            }
            vec.back() += string(rhs.size() - r - 1, '0');
        }
        for (int i = 1; i < vec.size(); i++) {
            string sum = "";
            int carry = 0;
            for (int f = vec[i - 1].size() - 1, b = vec[i].size() - 1; f >= 0, b >= 0; f--, b--) {
                string tmp = "";
                if (f < 0 && b >= 0)
                    tmp += to_string((vec[i][b] - '0') + carry);
                else if (f >= 0 && b < 0)
                    tmp += to_string((vec[i - 1][f] - '0') + carry);
                else
                    tmp += to_string((vec[i - 1][f] - '0') + (vec[i][b] - '0') + carry);
                if (tmp.size() == 1) {
                    sum += tmp[0];
                    carry = 0;
                } else {
                    sum += to_string(tmp[1] - '0');
                    carry = tmp[0] - '0';
                }
            }
            if (carry != 0)
                sum += to_string(carry);
            int left = 0, right = sum.size() - 1;
            while (left < right) {
                char tmp = sum[left];
                sum[left] = sum[right];
                sum[right] = tmp;
                ++left;
                --right;
            }
            vec[i] = sum;
        }
        return vec[vec.size() - 1];
    }

public:
    int trailingZeroes(int n) {
        int res = 0;
        if (n > 4) {
            int up = log(n) / log(5);
            for (int i = 1; i <= up; i++)
                res += n / (int) (pow(5, i));
        }
        return res;
    }

    int trailingZeroes1(int n) {
        if (n == 0)
            return 0;
        string res = to_string(n);
        int count = 0;
        for (int i = n - 1; i > 1; i--)
            res = multiply(res, to_string(i));
        // cout << "res = " << res << "\n";
        for (int i = res.size() - 1; i >= 0; i--) {
            if (res[i] == '0')
                ++count;
            else
                break;
        }
        return count;
    }
};

int main(int argc, char const *argv[]) {
    cout << "1! - " << Solution().trailingZeroes1(1) << "\n";
    cout << "5! - " << Solution().trailingZeroes1(5) << "\n";
    cout << "10! - " << Solution().trailingZeroes1(10) << "\n";
    cout << "15! - " << Solution().trailingZeroes1(15) << "\n";
    cout << "20! - " << Solution().trailingZeroes1(20) << "\n";
    cout << "25! - " << Solution().trailingZeroes1(25) << "\n";
    cout << "30! - " << Solution().trailingZeroes1(30) << "\n";
    cout << "35! - " << Solution().trailingZeroes1(35) << "\n";
    cout << "40! - " << Solution().trailingZeroes1(40) << "\n";
    cout << "45! - " << Solution().trailingZeroes1(45) << "\n";
    cout << "50! - " << Solution().trailingZeroes1(50) << "\n";
    cout << "55! - " << Solution().trailingZeroes1(55) << "\n";
    cout << "60! - " << Solution().trailingZeroes1(60) << "\n";
    cout << "65! - " << Solution().trailingZeroes1(65) << "\n";
    cout << "70! - " << Solution().trailingZeroes1(70) << "\n";
    cout << "75! - " << Solution().trailingZeroes1(75) << "\n";
    cout << "80! - " << Solution().trailingZeroes1(80) << "\n";
    cout << "85! - " << Solution().trailingZeroes1(85) << "\n";
    cout << "90! - " << Solution().trailingZeroes1(90) << "\n";
    cout << "95! - " << Solution().trailingZeroes1(95) << "\n";
    cout << "100! - " << Solution().trailingZeroes1(100) << "\n";
    cout << "200! - " << Solution().trailingZeroes1(200) << "\n";
    cout << "300! - " << Solution().trailingZeroes1(300) << "\n";
    cout << "400! - " << Solution().trailingZeroes1(400) << "\n";
    cout << "500! - " << Solution().trailingZeroes1(500) << "\n";
    return 0;
}
