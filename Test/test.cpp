#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

std::vector<std::string> split(const std::string& str, const char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);

	// 从 tokenStream 中读取字符，直到遇到 delimiter，每次读取的子字符串存储在 token 中
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

int main() {
	int val;
	cin >> val;
	string str;
	getline(cin, str);
	getline(cin, str);
	vector<string> strs = split(str, ' ');
	vector<int> coins;
	for (string& s : strs)
		coins.push_back(atoi(s.c_str()));
	sort(coins.begin(), coins.end());
	int count = 0, i = coins.size() - 1;
	while (i >= 0) {
		if (val >= coins[i]) {
			val -= coins[i];
			count++;
		}
		else {
			i--;
		}
	}
	cout << (val > 0 ? -1 : count);
	return 0;
}
// 64 位输出请用 printf("%lld")