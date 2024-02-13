#include <string>
#include <iostream>

bool hasDuplication(const std::string& str, int position[])
{
	for (int i = 0; i < 26; ++i)
		position[i] = -1;

	for (int i = 0; i < str.length(); ++i)
	{
		int indexInPosition = str[i] - 'a';
		if (position[indexInPosition] >= 0)
			return true;

		position[indexInPosition] = indexInPosition;
	}

	return false;
}

int longestSubstringWithoutDuplication_1(const std::string& str)
{
	int longest = 0;
	int* position = new int[26];
	for (int start = 0; start < str.length(); ++start)
	{
		for (int end = start; end < str.length(); ++end)
		{
			int count = end - start + 1;
			const std::string& substring = str.substr(start, count);
			if (!hasDuplication(substring, position))
			{
				if (count > longest)
					longest = count;
			}
			else
				break;

		}
	}

	delete[] position;
	return longest;
}

int longestSubstringWithoutDuplication_2(const std::string& str)
{
	int curLength = 0;
	int maxLength = 0;

	int* position = new int[26];
	for (int i = 0; i < 26; ++i)
		position[i] = -1;

	for (int i = 0; i < str.length(); ++i)
	{
		int prevIndex = position[str[i] - 'a'];
		if (prevIndex < 0 || i - prevIndex > curLength)
			++curLength;
		else
		{
			if (curLength > maxLength)
				maxLength = curLength;

			curLength = i - prevIndex;
		}
		position[str[i] - 'a'] = i;
	}

	if (curLength > maxLength)
		maxLength = curLength;

	delete[] position;
	return maxLength;
}