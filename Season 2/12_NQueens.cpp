#include <iostream>

using namespace std;

/**
 * @brief N皇后问题
 * @date 2022-06-06
 */
class NQueens {
	int _n = 0;
	/**
	 * @brief 共有多少种摆法
	 */
	int _ways = 0;
	/**
	 * @brief 存放每一个皇后的列号
	 */
	int* _queens = nullptr;
	/**
	 * @brief 标记某一列是否已有皇后
	 */
	bool* _cols = nullptr;
	/**
	 * @brief 标记对角线是否已有皇后
	 */
	bool* _leftTop = nullptr;
	/**
	 * @brief 标记对角线是否已有皇后
	 */
	bool* _rightTop = nullptr;

	/**
	 * @brief 从row行开始摆放皇后
	 * @param row
	 */
	void place(int row) {
		if (row == _n) {
			_ways++;
			show();
		}
		else {
			for (size_t col = 0; col < _n; col++) {
				if (!_cols[col]) {
					int lt = row - col + _n - 1; // 主对角线索引
					int rt = row + col;          // 副对角线索引
					if (_leftTop[lt] || _rightTop[rt])
						continue;
					_queens[row] = col;
					_cols[col] = _leftTop[lt] = _rightTop[rt] = true;
					place(row + 1);
					_cols[col] = _leftTop[lt] = _rightTop[rt] = false;
				}
			}
		}
	}

	void show() {
		for (size_t row = 0; row < _n; row++) {
			for (size_t col = 0; col < _n; col++) {
				cout << (_queens[row] == col ? "1 " : "0 ");
			}
			cout << "\n";
		}
		cout << "----------------------------------" << endl;
	}

public:
	NQueens() = default;

	~NQueens() = default;

	/**
	 * @brief 摆放n个皇后
	 * @param n
	 */
	void place_queens(int n) {
		if (n >= 1) {
			_n = n;
			int len = (n << 1) - 1;
			_queens = new int[n] {};
			_cols = new bool[n] {};
			_leftTop = new bool[len] {};
			_rightTop = new bool[len] {};
			place(0);
			cout << n << "皇后一共有" << _ways << "种摆法\n";
		}
	}
};

int main(int argc, char const* argv[]) {
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