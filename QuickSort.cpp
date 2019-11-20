#include <iostream>
#include <vector>

using namespace std;

// data index range [low, high]
int Partition(vector<int> & vec, int low, int high)
{
	int priovt = vec[high];
	int i = low - 1;
	for (int j = low; j < high; ++j)
	{
		if (vec[j] < priovt)
		{
			swap(vec[++i], vec[j]);
		}
	}

	swap(vec[++i], vec[high]);
	return i;
}

// data index range [low, high]
void QuickSort(vector<int> & vec, int low, int high)
{
	if (low < high)
	{
		int mid = Partition(vec, low, high);
		QuickSort(vec, low, mid - 1);
		QuickSort(vec, mid + 1, high);
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

	QuickSort(vec, 0, vec.size() - 1);

	for (int item : vec)
	{
		cout << item << " ";
	}
	cout << endl;
}