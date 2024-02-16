/**
 * @file brick-wall.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 554. 砖墙
 * @version 0.1
 * @date 2024-02-16
 * @link https://leetcode.cn/problems/brick-wall/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
	int leastBricks(vector<vector<int>>& wall) {
		int maxEdges = 0;
		unordered_map<int, int> edgeCnts;
		for (vector<int>& row : wall) {
			int edgePos = 0;
			for (int i = 0; i < row.size() - 1; i++) {	//不包括最后一个边缘
				edgePos += row[i];
				edgeCnts[edgePos]++;
				maxEdges = max(maxEdges, edgeCnts[edgePos]);
			}
		}
		return wall.size() - maxEdges;	//总行数减去最多边缘数
	}
};