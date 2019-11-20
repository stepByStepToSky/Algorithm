#include <iostream>
#include <vector>

using namespace std;

// data index range [low, high]
void InsertSort(vector<int> & vec, int low, int high)
{
	for (int i = low + 1; i <= high; ++i)
	{
		int j = i, value = vec[i];
		while (low < j && vec[j - 1] > value)
		{
			vec[j] = vec[j - 1];
			--j;
		}

		vec[j] = value;
	}
}

int main()
{
	vector<int> vec;
	vec.reserve(32);
	for (int i = 10; 0 < i; --i)
	{
		for (int j = 2; 0 < j; --j)
		{
			vec.push_back(i);
		}
	}

	InsertSort(vec, 0, vec.size() - 1);

	for (int item : vec)
	{
		cout << item << " ";
	}
	cout << endl;
}