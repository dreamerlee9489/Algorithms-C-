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
#include <unordered_map>
#include <vector>
#include <random>
#include <iostream>

using namespace std;

class RandomizedSet {
    unordered_map<int, int> _map;
    vector<int> _vec;
    uniform_int_distribution<int> d;
    default_random_engine e;

public:
    RandomizedSet() {
    }

    bool insert(int val) {
        if (_map.find(val) == _map.end()) {
            _vec.emplace_back(val);
            _map[val] = _vec.size() - 1;
            return true;
        }
        return false;
    }

    bool remove(int val) {
        if (_map.find(val) != _map.end()) {
            int index = _map[val];
            int back = _vec.back();
            _vec[index] = back;
            _map[back] = index;
            _vec.pop_back();
            _map.erase(val);
            return true;
        }
        return false;
    }

    int getRandom() {
        d = uniform_int_distribution<int>(0, _vec.size() - 1);
        return _vec[d(e)];
    }
};

int main(int argc, char const *argv[]) {
    RandomizedSet randomizedSet = RandomizedSet();
    randomizedSet.insert(1);   // 向集合中插入 1 。返回 true 表示 1 被成功地插入。
    randomizedSet.remove(2);   // 返回 false ，表示集合中不存在 2 。
    randomizedSet.insert(2);   // 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
    randomizedSet.getRandom(); // getRandom 应随机返回 1 或 2 。
    randomizedSet.remove(1);   // 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
    randomizedSet.insert(2);   // 2 已在集合中，所以返回 false 。
    randomizedSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2
    return 0;
}
