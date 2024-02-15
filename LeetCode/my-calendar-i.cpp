/**
 * @file my-calendar-i.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 729. 我的日程安排表 I
 * @version 0.1
 * @date 2024-02-15
 * @link https://leetcode.cn/problems/my-calendar-i/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <set>
using namespace std;

class MyCalendar {
	set<pair<int, int>> books;

public:
	MyCalendar() {}

	bool book(int start, int end) {
		auto iter = books.lower_bound({ start, end });
		if (iter != books.end() && iter->first < end)
			return false;
		if (iter != books.begin() && prev(iter)->second > start)
			return false;
		books.insert({ start, end });
		return true;
	}
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */