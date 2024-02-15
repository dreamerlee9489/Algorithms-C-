/**
 * @file design-circular-deque.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 641. 设计循环双端队列
 * @version 0.1
 * @date 2024-02-14
 * @link https://leetcode.cn/problems/design-circular-deque/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
using namespace std;

class MyCircularDeque {
	vector<int> arr;
	int front = 0, rear = 0, capacity = 0;

public:
	MyCircularDeque(int k) {
		arr = vector<int>(k + 1);
		capacity = k + 1;
		front = rear = 0;
	}

	bool insertFront(int value) {
		if (isFull()) return false;
		front = (front - 1 + capacity) % capacity;
		arr[front] = value;
		return true;
	}

	bool insertLast(int value) {
		if (isFull()) return false;
		arr[rear] = value;
		rear = (rear + 1) % capacity;
		return true;
	}

	bool deleteFront() {
		if (isEmpty()) return false;
		front = (front + 1) % capacity;
		return true;
	}

	bool deleteLast() {
		if (isEmpty()) return false;
		rear = (rear - 1 + capacity) % capacity;
		return true;
	}

	int getFront() {
		if (isEmpty()) return -1;
		return arr[front];
	}

	int getRear() {
		if (isEmpty()) return -1;
		return arr[(rear - 1 + capacity) % capacity];
	}

	bool isEmpty() {
		return front == rear;
	}

	bool isFull() {
		return (rear + 1) % capacity == front;
	}
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */