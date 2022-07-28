/**
 * @file alien-dictionary.cpp
 * @author your name (you@domain.com)
 * @brief 269. 火星词典
 * @version 0.1
 * @date 2022-07-28
 * @remark https://leetcode.cn/problems/alien-dictionary/
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
    unordered_map<char, char> map;
    unordered_set<char> set;

public:
    string alienOrder(vector<string> &words)
    {
        for (size_t w = 0; w < words.size() - 1; w++)
        {
            size_t len = min(words[w].size(), words[w + 1].size()), i = 0;
            while (i < len)
            {
                set.emplace(words[w][i]);
                set.emplace(words[w + 1][i]);
                if (words[w][i] != words[w + 1][i])
                {
                    if(map.find(words[w + 1][i]) != map.end() && map[words[w + 1][i]] == words[w][i])
                        return "";
                    map.emplace(make_pair(words[w][i], words[w + 1][i]));
                    break;
                }
                else
                {
                    if (++i >= len)
                        map.emplace(make_pair(words[w].size() > words[w + 1].size() ? words[w][len] : words[w + 1][len], words[w][len - 1]));
                }
            }
        }
        list<char> chars;
        string res = "";
        while (chars.size() < set.size())
        {
            for(pair<char, char> p : map)
            {
                if(chars.size() == set.size())
                    break;
                if(chars.front() == p.second)
                    chars.emplace_front(p.first);
                else if(chars.back() == p.first)
                    chars.emplace_back(p.second);
                else
                {
                    chars.emplace_back(p.first);
                    chars.emplace_back(p.second);
                }
            }
        }
        for(char c : chars)
            res += c;
        return res;
    }
};

int main(int argc, char const *argv[])
{
    // vector<string> words1 = {"wrt", "wrf", "er", "ett", "rftt"};
    // cout << Solution().alienOrder(words1) << "\n";
    // vector<string> words2 = {"z", "x"};
    // cout << Solution().alienOrder(words2) << "\n";
    // vector<string> words3 = {"z", "x", "z"};
    // cout << Solution().alienOrder(words3) << "\n";
    // vector<string> words4 = {"z", "z"};
    // cout << Solution().alienOrder(words4) << "\n";
    vector<string> words5 = {"zy", "zx"};
    cout << Solution().alienOrder(words5) << "\n";
    return 0;
}
