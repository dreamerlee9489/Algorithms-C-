/**
 * @file implement-trie-prefix-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 208. 实现 Trie (前缀树)
 * @version 0.1
 * @date 2022-08-08
 * @link https://leetcode.cn/problems/implement-trie-prefix-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie {
	struct Node {
		bool _exist = false;
		bool _end = false;
		vector<Node>* _next = nullptr;
	};

	vector<Node>* inits = new vector<Node>(26);

public:
	Trie() {}

	void insert(string word) {
		vector<Node>* tail = inits;
		for (int i = 0; i < word.size(); ++i) {
			int idx = word[i] - 'a';
			(*tail)[idx]._exist = true;
			if (i == word.size() - 1)
				(*tail)[idx]._end = true;
			if ((*tail)[idx]._next == nullptr)
				(*tail)[idx]._next = new vector<Node>(26);
			tail = (*tail)[idx]._next;
		}
	}

	bool search(string word) {
		vector<Node>* tail = inits;
		for (int i = 0; i < word.size(); ++i) {
			int idx = word[i] - 'a';
			if (!(*tail)[idx]._exist)
				return false;
			if (i == word.size() - 1 && !(*tail)[idx]._end)
				return false;
			tail = (*tail)[idx]._next;
		}
		return true;
	}

	bool startsWith(string prefix) {
		vector<Node>* tail = inits;
		for (int i = 0; i < prefix.size(); ++i) {
			int idx = prefix[i] - 'a';
			if (!(*tail)[idx]._exist)
				return false;
			tail = (*tail)[idx]._next;
		}
		return true;
	}
};

int main(int argc, char const* argv[]) {
	Trie trie;
	trie.insert("apple");
	cout << trie.search("apple") << "\n";   // 返回 True
	cout << trie.search("app") << "\n";     // 返回 False
	cout << trie.startsWith("app") << "\n"; // 返回 True
	trie.insert("app");
	cout << trie.search("app") << "\n"; // 返回 True
	return 0;
}
