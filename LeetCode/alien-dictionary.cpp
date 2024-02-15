/**
 * @file alien-dictionary.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 269. 火星词典
 * @version 0.1
 * @date 2022-07-28
 * @link https://leetcode.cn/problems/alien-dictionary/
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
	vector<pair<char, char>> pairs;
	unordered_set<char> set;
	list<char> chars;

	list<char>::iterator findList(char val) {
		for (auto iter = chars.begin(); iter != chars.end(); ++iter)
			if (*iter == val)
				return iter;
		return chars.end();
	}

public:
	string alienOrder(vector<string>& words) {
		if (words.size() == 1) {
			for (char c : words[0])
				set.emplace(c);
			for (char c : set)
				chars.emplace_back(c);
		}
		else {
			for (size_t wd = 0; wd < words.size() - 1; wd++) {
				string words0 = words[wd], words1 = words[wd + 1];
				size_t minLen = min(words0.size(), words1.size()), i = 0;
				while (i < minLen) {
					set.emplace(words0[i]);
					set.emplace(words1[i]);
					if (words0[i] != words1[i]) {
						bool had = false;
						for (auto p : pairs) {
							if (p.first == words0[i] && p.second == words1[i]) {
								had = true;
								break;
							}
						}
						if (had)
							i++;
						else
							pairs.emplace_back(words0[i], words1[i]);
						break;
					}
					else {
						if (++i == minLen)
							if (i < words0.size())
								return "";
					}
				}
				for (size_t j = i; j < words0.size(); j++)
					set.emplace(words0[j]);
				for (size_t k = i; k < words1.size(); k++)
					set.emplace(words1[k]);
			}
			size_t strLen = set.size(), pairLen = pairs.size();
			while (set.size() > 0) {
				if (pairLen == 0) {
					for (char c : set) {
						chars.emplace_back(c);
						set.erase(c);
						break;
					}
				}
				else if (chars.size() == 0) {
					chars.emplace_back(pairs[0].first);
					chars.emplace_back(pairs[0].second);
					set.erase(pairs[0].first);
					set.erase(pairs[0].second);
					pairLen--;
				}
				char left = chars.front(), right = chars.back();
				bool place = false;
				for (size_t i = 1; i < pairs.size(); i++) {
					if (pairs[i].first == right) {
						if (set.find(pairs[i].second) == set.end())
							return "";
						right = pairs[i].second;
						chars.emplace_back(right);
						set.erase(right);
						pairLen--;
						place = true;
					}
					else if (set.find(pairs[i].first) == set.end() &&
						set.find(pairs[i].second) != set.end()) {
						auto iter = next(findList(pairs[i].first));
						while (iter != chars.end()) {
							for (auto p : pairs) {
								if (p.first == pairs[i].second && *iter == p.second) {
									chars.emplace(prev(iter), pairs[i].second);
									set.erase(pairs[i].second);
									pairLen--;
									place = true;
									break;
								}
							}
							++iter;
						}
						if (iter == chars.end()) {
							right = pairs[i].second;
							chars.emplace_back(right);
							set.erase(right);
							pairLen--;
							place = true;
						}
					}

					if (pairs[i].second == left) {
						if (set.find(pairs[i].first) == set.end())
							return "";
						left = pairs[i].first;
						chars.emplace_front(left);
						set.erase(left);
						pairLen--;
						place = true;
					}
					else if (set.find(pairs[i].first) != set.end() &&
						set.find(pairs[i].second) == set.end()) {
						auto iter = prev(findList(pairs[i].second));
						while (iter != prev(chars.begin())) {
							for (auto p : pairs) {
								if (p.second == pairs[i].first && *iter == p.first) {
									chars.emplace(next(iter), pairs[i].first);
									set.erase(pairs[i].first);
									pairLen--;
									place = true;
									break;
								}
							}
							--iter;
						}
						if (iter == prev(chars.begin())) {
							left = pairs[i].first;
							chars.emplace_front(left);
							set.erase(left);
							pairLen--;
							place = true;
						}
					}
				}
				if (!place)
					pairLen = 0;
			}
		}
		string res;
		for (char c : chars)
			res += c;
		return res;
	}
};

int main(int argc, char const* argv[]) {
	vector<string> words1 = { "wrt", "wrf", "er", "ett", "rftt" };
	cout << Solution().alienOrder(words1) << "\n";
	vector<string> words2 = { "z", "x" };
	cout << Solution().alienOrder(words2) << "\n";
	vector<string> words3 = { "z", "x", "z" };
	cout << Solution().alienOrder(words3) << "\n";
	vector<string> words4 = { "z", "z" }; //"z"
	cout << Solution().alienOrder(words4) << "\n";
	vector<string> words5 = { "zy", "zx" }; //"zyx"
	cout << Solution().alienOrder(words5) << "\n";
	vector<string> words6 = { "ab", "adc" }; //"cbda"
	cout << Solution().alienOrder(words6) << "\n";
	vector<string> words7 = { "ac", "ab", "b" };
	cout << Solution().alienOrder(words7) << "\n"; //"acb"
	vector<string> words8 = { "abc", "ab" };
	cout << Solution().alienOrder(words8) << "\n"; //""
	vector<string> words9 = { "aac", "aabb", "aaba" };
	cout << Solution().alienOrder(words9) << "\n"; //"cba"
	vector<string> words10 = { "z", "x", "a", "zb", "zx" };
	cout << Solution().alienOrder(words10) << "\n"; //""
	vector<string> words11 = { "c", "b", "ac", "aa" };
	cout << Solution().alienOrder(words11) << "\n"; //"cba"
	vector<string> words12 = { "a", "b", "ca", "cc" };
	cout << Solution().alienOrder(words12) << "\n"; //"abc"
	vector<string> words13 = { "ac", "ab", "zc", "zb" };
	cout << Solution().alienOrder(words13) << "\n"; //"cbaz"
	vector<string> words14 = { "qb", "qts", "qs", "qa", "s" };
	cout << Solution().alienOrder(words14) << "\n"; //"bqtsa"
	vector<string> words15 = { "vlxpwiqbsg", "cpwqwqcd" };
	cout << Solution().alienOrder(words15) << "\n"; //"bdgilpqsvcwx"
	vector<string> words16 = { "wrt", "wrf", "er", "ett", "rftt", "te" };
	cout << Solution().alienOrder(words16) << "\n"; //"bdgilpqsvcwx"
	vector<string> words17 = { "wnlb" };
	cout << Solution().alienOrder(words17) << "\n"; //"bdgilpqsvcwx"
	vector<string> words18 = { "pp", "pocccevp", "vuavnz" };
	cout << Solution().alienOrder(words18) << "\n"; //"acenpouvz"
	vector<string> words19 = { "eebdjprtjb", "exfjbwzamj", "dzjlqzb", "mfdj",
							  "k",          "blvtggjw",   "znpdnze", "mf",
							  "lotbeuoyho", "lplkxjdg" };
	cout << Solution().alienOrder(words19) << "\n"; //""
	return 0;
}
