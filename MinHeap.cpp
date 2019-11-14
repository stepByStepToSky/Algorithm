#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


class MinHeap
{
public:
	MinHeap() :m_data(nullptr), m_size(0), m_capacity(0)
	{

	}

	~MinHeap()
	{
		if (nullptr != m_data)
		{
			free(m_data);
		}
	}

	void Push(int val)
	{
		if (m_size + 1 >= m_capacity)
		{
			int newCapacity = max(kInitCapacity, 2 * m_capacity);
			int * newData = static_cast<int*> (realloc(m_data, (sizeof(int)* newCapacity)));
			
			// if no memory access, ignore the input val
			if (nullptr == newData)
			{
				return;
			}
			// realloc does not need free old memory
			m_data = newData;
			m_capacity = newCapacity;
		}
		
		++m_size;
		m_data[m_size] = val;
		ShiftUp(m_size);
	}

	// need the user to guarent that the heap is not empty
	void Pop()
	{
		swap(m_data[1], m_data[m_size]);
		--m_size;
		ShiftDown(1);
	}

	// need the user to guarent that the heap is not empty
	int Top()
	{
		return m_data[1];
	}

	int Size()
	{
		return m_size;
	}

	bool Empty()
	{
		return (0 == m_size);
	}

	// should user guarent that index < m_size
	void Change(int index, int val)
	{
		int oldValue = m_data[index];
		m_data[index] = val;
		if (oldValue < val)
		{
			ShiftDown(index);
		}
		else if (oldValue > val)
		{
			ShiftUp(index);
		}
	}

	void LevelPrint()
	{
		if (0 != m_size)
		{
			queue<int> que;
			que.push(1);
			while (!que.empty())
			{
				int front = que.front();
				cout << m_data[front] << " ";
				que.pop();

				if (2 * front <= m_size)
				{
					que.push(2 * front);
					if (2 * front + 1 <= m_size)
					{
						que.push(2 * front + 1);
					}
				}
			}
			cout << endl;
		}
	}

private:
	void ShiftUp(int index)
	{
		while (1 < index && m_data[index / 2] > m_data[index])
		{
			swap(m_data[index / 2], m_data[index]);
			index /= 2;
		}
	}

	void ShiftDown(int index)
	{
		while (2 * index <= m_size)
		{
			int minIndex = 2 * index;
			if (minIndex < m_size && m_data[minIndex] > m_data[minIndex + 1])
			{
				++minIndex;
			}

			if (m_data[index] < m_data[minIndex])
			{
				break;
			}

			swap(m_data[index], m_data[minIndex]);
			index = minIndex;
		}
	}

private:
	static const int kInitCapacity;
	// index starts from 1
	int * m_data;
	int m_size;
	int m_capacity;
};

const int MinHeap::kInitCapacity = 16;

int main()
{
	MinHeap minHeap;
	for (int i = 1; 16 > i; ++i)
	{
		minHeap.Push(i);
	}

	minHeap.Change(5, 100);
	minHeap.Change(5, 0);
	minHeap.LevelPrint();

	/*
	while (!minHeap.Empty())
	{
		cout << minHeap.Top() << " ";
		minHeap.Pop();
	}
	cout << endl;
	*/
}