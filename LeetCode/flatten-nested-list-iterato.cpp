/**
 * @file flatten-nested-list-iterato.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 341. 扁平化嵌套列表迭代器
 * @version 0.1
 * @date 2022-08-15
 * @link https://leetcode.cn/problems/flatten-nested-list-iterator/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class NestedIterator {
    vector<int> list;
    int index = 0;

    void dfs(const vector<NestedInteger> &nest) {
        for (int i = 0; i < nest.size(); i++) {
            if (nest[i].isInteger())
                list.emplace_back(nest[i].getInteger());
            else
                dfs(nest[i].getList());
        }
    }

public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        dfs(nestedList);
    }

    int next() {
        return list[index++];
    }

    bool hasNext() {
        if (index < list.size())
            return true;
        return false;
    }
};

