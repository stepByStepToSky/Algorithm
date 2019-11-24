#include <iostream>
#include <vector>
#include <string>

using namespace std;

// reference https://blog.csdn.net/v_july_v/article/details/7041827

class Kmp
{
public:
	// -1 failed, or index of the first char
	static int Search(const string & src, const string & pat)
	{
		vector<int> next;
		GetNext(pat, next);

		int srcSize = src.size(), patSize = pat.size();
		int i = 0, j = 0;
		for (; i < srcSize && j < patSize;)
		{
			if (-1 == j || src[i] == pat[j])
			{
				++i;
				++j;
			}
			else
			{
				j = next[j];
			}
		}

		if (j == patSize)
		{
			return i - j;
		}
		else
		{
			return -1;
		}
	}

	static void GetNext(const string & pat, vector<int> & next)
	{
		size_t patSize = pat.size();
		next.resize(patSize + 1);
		next[0] = -1;
		int k = -1;
		for (size_t i = 0; i < patSize;)
		{
			if (-1 == k || pat[k] == pat[i])
			{
				next[++i] = ++k;
			}
			else
			{
				k = next[k];
			}
		}
	}
};


int main()
{
	string src("hello world"), pat("ll");
	cout << Kmp::Search(src, pat) << endl;
}