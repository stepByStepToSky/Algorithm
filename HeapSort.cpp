#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;


// index start from 1
void MaxHeapify(vector<int> & vec, int index, int n)
{
    if (0 == vec.size() || n < index)
    {
        return;
    }

    int value = vec[index];
    while(2 * index <= n)
    {
        int j = 2 * index;
        if (j + 1 <= n && vec[j + 1] > vec[j])
        {
            ++j;
        }

        if (vec[j] < value)
        {
            break;
        }

        vec[index] = vec[j];
        index = j;
    }
    vec[index] = value;
}

// index start from 1
void BuildHeap(vector<int> & vec)
{
    int n = vec.size();
    for (int i = n / 2; 0 < i; --i)
    {
        MaxHeapify(vec, i, n);
    }
}


// index start from 0
void HeapSort(vector<int> & vec)
{
    if (vec.empty())
    {
        return;
    }

    int n = vec.size();
    vector<int> temp(n+1, 0);
    memcpy(&temp[1], &vec[0], sizeof(int) * n);

    BuildHeap(temp);

    for (int i = n; 1 < i; --i)
    {
        swap(temp[1], temp[i]);
        MaxHeapify(temp, 1, i-1);
    }

    memcpy(&vec[0], &temp[1], sizeof(int) * n);
}


int main()
{
    vector<int> vec;
    vec.reserve(128);
    for (int i = 10; 0 < i; --i)
    {
        for (int j = 2; 0 < j; --j)
        {
            vec.push_back(i);
        }
    }

    vector<int> vecHeap(vec), vecSTL(vec);
    
    sort(vecSTL.begin(), vecSTL.end());
    HeapSort(vecHeap);

    cout << "STL sort" << endl;
    for (int item : vecSTL)
    {
        cout << item << " ";
    }
    cout << endl;


    cout << endl << "Heap sort" << endl;
    for (int item : vecHeap)
    {
        cout << item << " ";
    }
    cout << endl;
}