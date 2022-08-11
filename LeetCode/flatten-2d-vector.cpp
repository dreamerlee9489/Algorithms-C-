/**
 * @file flatten-2d-vector.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 251. 展开二维向量
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/flatten-2d-vector/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <iostream>

using namespace std;

class Vector2D {
    vector<int> mVec;
    int mIdx = 0;

public:
    Vector2D(vector<vector<int>> &vec) {
        for (int i = 0; i < vec.size(); i++)
            for (int j = 0; j < vec[i].size(); j++)
                mVec.emplace_back(vec[i][j]);
    }

    int next() {
        return mVec[mIdx++];
    }

    bool hasNext() {
        return mIdx < mVec.size();
    }
};

int main(int argc, char const *argv[]) {
    vector<vector<int>> vec = {{1, 2},
                               {3},
                               {4}};
    Vector2D iterator = Vector2D(vec);
    cout << iterator.next() << "\n";    // 返回 1
    cout << iterator.next() << "\n";    // 返回 2
    cout << iterator.next() << "\n";    // 返回 3
    cout << iterator.hasNext() << "\n"; // 返回 true
    cout << iterator.hasNext() << "\n"; // 返回 true
    cout << iterator.next() << "\n";    // 返回 4
    cout << iterator.hasNext() << "\n"; // 返回 false
    return 0;
}
