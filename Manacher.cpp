#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
 refrence https://zhuhongcheng.wordpress.com/2009/08/02/a-simple-linear-time-algorithm-for-finding-longest-palindrome-sub-string/
 time complexity O(n)
 */

string LongestPalindrome(string s) {
	size_t n = s.size();
	if (0 == n)
	{
		return s;
	}

	string str;
	str.reserve(2 * n + 1);
	str.push_back('#');
	for (size_t i = 0; i < n; ++i)
	{
		str.push_back(s[i]);
		str.push_back('#');
	}

	size_t strSize = str.size();
	vector<int> vecLen(strSize, 1);
	int maxIndex = 0, maxRightIndex = 0;
	for (int i = 1; i < strSize; ++i)
	{
		int j = 2 * maxIndex - i;
		if (0 <= j && maxIndex + vecLen[j] <= maxRightIndex)
		{
			vecLen[i] = min(vecLen[j], maxRightIndex - i);
		}

		while (0 <= (i - vecLen[i]) && (i + vecLen[i]) < strSize && str[i - vecLen[i]] == str[i + vecLen[i]])
		{
			++vecLen[i];
		}

		if (i + vecLen[i] >= maxRightIndex)
		{
			maxIndex = i;
			maxRightIndex = i + vecLen[i];
		}
	}

	int maxLenIndex = 0;
	for (int i = 1; i < strSize; ++i)
	{
		if (vecLen[i] > vecLen[maxLenIndex])
		{
			maxLenIndex = i;
		}
	}


	string ret;
	int orgMidIndex = maxLenIndex / 2, maxLen = vecLen[maxLenIndex] - 1;
	if (0x01 & maxLenIndex)
	{
		ret.assign(s.begin() + orgMidIndex - (maxLen / 2), s.begin() + orgMidIndex + (maxLen / 2) + 1);
	}
	else
	{
		ret.assign(s.begin() + orgMidIndex - (maxLen / 2), s.begin() + orgMidIndex + (maxLen / 2));
	}
	return ret;
}

int main()
{
	string s("babadada");
	cout << LongestPalindrome(s) << endl;
}