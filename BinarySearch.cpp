#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// return -1 if not found, or one of index where value is equal to the target if found
int BinarySearch(const vector<int> & vec, const int target)
{
	if (vec.empty())
	{
		return -1;
	}
	int low = 0, high = vec.size() - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (target == vec[mid])
		{
			return mid;
		}
		else if (target < vec[mid])
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;
}

// the result is in [0, n], where n = vec.size()
int LowerBoundIndex(const vector<int> & vec, const int target)
{	
	// here target search scope is in [low, high)
	int low = 0, high = vec.size();
	while (low < high)
	{
		int mid = low + (high - low) / 2;
		if (target <= vec[mid])
		{
			high = mid;
		}
		else
		{
			low = mid + 1;
		}
	}
	return high;
}

// the result is in [0, n], where n = vec.size()
int UpperBoundIndex(const vector<int> & vec, int target)
{
	int low = 0, high = vec.size();
	while (low < high)
	{
		int mid = low + (high - low) / 2;
		if (target < vec[mid])
		{
			high = mid;
		}
		else
		{
			low = mid + 1;
		}
	}
	return high;
}


int main()
{
	vector<int> vec = { 1, 2, 2, 3, 3, 3, 5, 6, 6, 7, 7, 9, 10, 14 };

	cout << "BinarySearch the index of 5 is " << BinarySearch(vec, 5) << endl;
	cout << "BinarySearch the index of 8 is " << BinarySearch(vec, 8) << endl;

	int index = lower_bound(vec.begin(), vec.end(), 99) - vec.begin();
	cout << "STL lower_bound 99 the index is "  << index << endl;
	cout << "LowerBoundIndex 99 the index is " << LowerBoundIndex(vec, 99) << endl;
	index = lower_bound(vec.begin(), vec.end(), 3) - vec.begin();
	cout << "STL lower_bound 3 the index is " << index << endl;
	cout << "LowerBoundIndex 3 the index is " << LowerBoundIndex(vec, 3) << endl;

	index = upper_bound(vec.begin(), vec.end(), 99) - vec.begin();
	cout << "STL upper_bound 99 the index is " << index << endl;
	cout << "UpperBoundIndex 99 the index is " << UpperBoundIndex(vec, 99) << endl;
	index = upper_bound(vec.begin(), vec.end(), 3) - vec.begin();
	cout << "STL upper_bound 3 the index is " << index << endl;
	cout << "UpperBoundIndex 3 the index is " << UpperBoundIndex(vec, 3) << endl;
}