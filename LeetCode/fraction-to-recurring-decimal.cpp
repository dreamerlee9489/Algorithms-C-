/**
 * @file fraction-to-recurring-decimal.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 166. 分数到小数
 * @version 0.1
 * @date 2022-08-12
 * @link https://leetcode.cn/problems/fraction-to-recurring-decimal/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
    pair<string, string> divide(string nume, string deno) {
        long numerator = stol(nume), denominator = stol(deno);
        if ((numerator * 1.0 / denominator * 1.0) == numerator / denominator)
            return pair<string, string>(to_string(numerator / denominator), "0");
        int div = 0;
        while (numerator >= denominator) {
            numerator -= denominator;
            ++div;
        }
        return pair<string, string>(to_string(div), to_string(numerator));
    }

public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0)
            return "0";
        if (((long) numerator * 1.0 / denominator) == (long) numerator / denominator)
            return to_string((long) numerator / denominator);
        string nume = to_string(abs((long) numerator)), deno = to_string(abs((long) denominator));
        string curNume = nume.substr(0, min(nume.size(), deno.size()));
        string res = "";
        pair<string, string> p;
        int index = curNume.size() - 1;
        while (index < nume.size()) {
            p = divide(curNume, deno);
            res += p.first;
            ++index;
            if (index < nume.size())
                curNume = p.second + nume[index];
        }
        string intFrac = res = to_string(stoi(res));
        string decFrac = "";
        if (p.second != "0") {
            unordered_map<string, int> _map;
            res += ".";
            curNume = p.second + "0";
            while (p.second != "0") {
                if (_map.find(p.second) == _map.end())
                    _map[p.second] = res.size();
                else {
                    int pos = res.find('.');
                    decFrac += res.substr(pos, _map[p.second] - pos);
                    decFrac += "(" + res.substr(_map[p.second], res.size() - _map[p.second]) + ")";
                    res = intFrac + decFrac;
                    break;
                }
                p = divide(curNume, deno);
                res += p.first;
                curNume = p.second + "0";
            }
        }
        if (numerator < 0 && denominator > 0 || numerator > 0 && denominator < 0)
            return "-" + res;
        return res;
    }
};

int main(int argc, char const *argv[]) {
    cout << Solution().fractionToDecimal(12345, 5) << "\n";
    cout << Solution().fractionToDecimal(54321, 5) << "\n";
    cout << Solution().fractionToDecimal(12345, 50) << "\n";
    cout << Solution().fractionToDecimal(54321, 50) << "\n";
    cout << Solution().fractionToDecimal(4, 333) << "\n";
    cout << Solution().fractionToDecimal(-4, 333) << "\n";
    cout << Solution().fractionToDecimal(-1, -3) << "\n";
    cout << Solution().fractionToDecimal(1, 6) << "\n";
    return 0;
}