#include <iostream>
#include <vector>

using namespace std;

// data index range [low, high]
void SelectSort(vector<int> & vec, int low, int high)
{
	for (int i = low; i <= high; ++i)
	{
		int minIndex = i;
		for (int j = i + 1; j <= high; ++j)
		{
			if (vec[minIndex] > vec[j])
			{
				minIndex = j;
			}
		}
		swap(vec[i], vec[minIndex]);
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

	SelectSort(vec, 0, vec.size() - 1);

	for (int item : vec)
	{
		cout << item << " ";
	}
	cout << endl;
}