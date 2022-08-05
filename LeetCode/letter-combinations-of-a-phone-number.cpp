/**
 * @file letter-combinations-of-a-phone-number.cpp
 * @author your name (you@domain.com)
 * @brief 17. 电话号码的字母组合
 * @version 0.1
 * @date 2022-08-05
 * @link https://leetcode.cn/problems/letter-combinations-of-a-phone-number/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <string>
using namespace std;

class Solution
{
    vector<vector<char>> map = {{},
                                {},
                                {'a', 'b', 'c'},
                                {'d', 'e', 'f'},
                                {'g', 'h', 'i'},
                                {'j', 'k', 'l'},
                                {'m', 'n', 'o'},
                                {'p', 'q', 'r', 's'},
                                {'t', 'u', 'v'},
                                {'w', 'x', 'y', 'z'}};

    void dfs(int layer, string str, string &digits, vector<string> &res)
    {
        if (layer == digits.size())
        {
            res.emplace_back(str);
            return;
        }
        for (size_t j = 0; j < map[digits[layer] - '0'].size(); j++)
            dfs(layer + 1, str + map[digits[layer] - '0'][j], digits, res);
    }

public:
    vector<string> letterCombinations(string digits)
    {
        vector<string> res;
        if(!digits.empty())
            dfs(0, "", digits, res);
        return res;
    }
};

int main(int argc, char const *argv[])
{
    auto res1 = Solution().letterCombinations("2");
    auto res2 = Solution().letterCombinations("23");
    return 0;
}
