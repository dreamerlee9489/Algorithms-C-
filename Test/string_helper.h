#include <bits/stdc++.h>

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

std::vector<std::string> split(const std::string& str, const char* delimiters) {
	std::vector<std::string> tokens;
	std::string token;
	size_t prev = 0, pos = 0;

	do {
		pos = str.find_first_of(delimiters, prev);
		if (pos == std::string::npos) pos = str.length();
		token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + 1;
	} while (pos < str.length() && prev < str.length());

	return tokens;
}