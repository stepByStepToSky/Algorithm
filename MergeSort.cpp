#include <iostream>
#include <vector>

using namespace std;

// merge data index [low, mid] and (mid, high]
void Merge(vector<int> & vec, int low, int mid, int high)
{
	vector<int> lth(vec.begin() + low, vec.begin() + mid + 1), rth(vec.begin() + mid + 1, vec.begin() + high + 1);
	int lindex = 0, rindex = 0, index = low;
	while (lindex < lth.size() && rindex < rth.size())
	{
		if (lth[lindex] < rth[rindex])
		{
			vec[index++] = lth[lindex++];
		}
		else
		{
			vec[index++] = rth[rindex++];
		}
	}

	while (lindex < lth.size())
	{
		vec[index++] = lth[lindex++];
	}
	while (rindex < rth.size())
	{
		vec[index++] = rth[rindex++];
	}
}

// data index range [low, high]
void MergeSort(vector<int> & vec, int low, int high)
{
	if (low < high)
	{
		int mid = low + (high - low) / 2;
		MergeSort(vec, low, mid);
		MergeSort(vec, mid + 1, high);
		Merge(vec, low, mid, high);
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

	MergeSort(vec, 0, vec.size() - 1);

	for (int item : vec)
	{
		cout << item << " ";
	}
	cout << endl;
}