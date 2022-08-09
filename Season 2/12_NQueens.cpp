#include <iostream>

using namespace std;

/**
 * @brief N皇后问题
 * @date 2022-06-06
 */
class NQueens {
    int _n = 0;
    int _ways = 0;
    int *_queens = nullptr;
    bool *_columns = nullptr;
    bool *_leftTop = nullptr;
    bool *_rightTop = nullptr;

    void place(int row) {
        if (row == _n) {
            _ways++;
            show();
        } else {
            for (size_t col = 0; col < _n; col++) {
                if (_columns[col])
                    continue;
                int lt_index = row - col + _n - 1;
                if (_leftTop[lt_index])
                    continue;
                int rt_index = row + col;
                if (_rightTop[rt_index])
                    continue;
                _queens[row] = col;
                _columns[col] = true;
                _leftTop[lt_index] = true;
                _rightTop[rt_index] = true;
                place(row + 1);
                _columns[col] = false;
                _leftTop[lt_index] = false;
                _rightTop[rt_index] = false;
            }
        }
    }

    void show() {
        for (size_t row = 0; row < _n; row++) {
            for (size_t col = 0; col < _n; col++) {
                if (_queens[row] == col)
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
            _n = n;
            int len = (n << 1) - 1;
            _queens = new int[n]{};
            _columns = new bool[n]{};
            _leftTop = new bool[len]{};
            _rightTop = new bool[len]{};
            place(0);
            cout << n << "皇后一共有" << _ways << "种摆法\n";
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