/**
 * @file insert-delete-getrandom-o1.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 380. O(1) 时间插入、删除和获取随机元素
 * @version 0.1
 * @date 2022-08-15
 * @link https://leetcode.cn/problems/insert-delete-getrandom-o1/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <unordered_set>
#include <random>
#include <iostream>

using namespace std;

class RandomizedSet {
    unordered_set<int> _set;
    uniform_int_distribution<int> d;
    default_random_engine e;

public:
    RandomizedSet() {
    }

    bool insert(int val) {
        if (_set.find(val) == _set.end()) {
            _set.emplace(val);
            return true;
        }
        return false;
    }

    bool remove(int val) {
        if (_set.find(val) != _set.end()) {
            _set.erase(val);
            return true;
        }
        return false;
    }

    int getRandom() {
        d = uniform_int_distribution<int>(0, _set.size() - 1);
        return *next(_set.begin(), d(e));
    }
};

int main(int argc, char const *argv[]) {
    RandomizedSet randomizedSet = RandomizedSet();
    cout << randomizedSet.insert(1) << "\n";   // 向集合中插入 1 。返回 true 表示 1 被成功地插入。
    cout << randomizedSet.remove(2) << "\n";   // 返回 false ，表示集合中不存在 2 。
    cout << randomizedSet.insert(2) << "\n";   // 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
    cout << randomizedSet.getRandom() << "\n"; // getRandom 应随机返回 1 或 2 。
    cout << randomizedSet.insert(2) << "\n";   // 2 已在集合中，所以返回 false 。
    cout << randomizedSet.getRandom() << "\n"; // 由于 2 是集合中唯一的数字，getRandom 总是返回 2
    return 0;
}
