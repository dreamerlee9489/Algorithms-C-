#include <iostream>

using namespace std;

/**
 * @brief N皇后问题
 * @date 2022-06-06
 */
class NQueens {
    int mN = 0;
    int mWays = 0;
    int *pQueens = nullptr;
    bool *pCols = nullptr;
    bool *pLeftTop = nullptr;
    bool *pRightTop = nullptr;

    void place(int row) {
        if (row == mN) {
            mWays++;
            show();
        } else {
            for (size_t col = 0; col < mN; col++) {
                if (pCols[col])
                    continue;
                int lt_index = row - col + mN - 1;
                if (pLeftTop[lt_index])
                    continue;
                int rt_index = row + col;
                if (pRightTop[rt_index])
                    continue;
                pQueens[row] = col;
                pCols[col] = true;
                pLeftTop[lt_index] = true;
                pRightTop[rt_index] = true;
                place(row + 1);
                pCols[col] = false;
                pLeftTop[lt_index] = false;
                pRightTop[rt_index] = false;
            }
        }
    }

    void show() {
        for (size_t row = 0; row < mN; row++) {
            for (size_t col = 0; col < mN; col++) {
                if (pQueens[row] == col)
                    cout << "1 ";
                else
                    cout << "0 ";
            }
            cout << "\n";
        }
        cout << "----------------------------------" << endl;
    }

public:
    NQueens() = default;

    ~NQueens() = default;

    void place_queens(int n) {
        if (n >= 1) {
            mN = n;
            int len = (n << 1) - 1;
            pQueens = new int[n]{};
            pCols = new bool[n]{};
            pLeftTop = new bool[len]{};
            pRightTop = new bool[len]{};
            place(0);
            cout << n << "皇后一共有" << mWays << "种摆法\n";
        }
    }
};

int main(int argc, char const *argv[]) {
    NQueens().place_queens(4);
    return 0;
}

/*
0 1 0 0
0 0 0 1
1 0 0 0
0 0 1 0
----------------------------------
0 0 1 0
1 0 0 0
0 0 0 1
0 1 0 0
----------------------------------
4皇后一共有2种摆法
*/