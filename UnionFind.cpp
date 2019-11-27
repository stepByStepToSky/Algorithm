#include <iostream>
#include <vector>

using namespace std;

// reference https://github.com/CyC2018/CS-Notes/blob/master/notes/%E7%AE%97%E6%B3%95%20-%20%E5%B9%B6%E6%9F%A5%E9%9B%86.md

class UnionFind
{
public:
	UnionFind(int n) : m_id(n)
	{
		for (int i = 0; i < n; ++i)
		{
			m_id[i] = i;
		}
	}

	// user should guareent that a, and b is in range [0, n)
	void Union(int aid, int bid)
	{
		m_id[bid] = aid;
	}

	// user should guareent that id is in range [0, n)
	int FindRootId(int id)
	{
		while (id != m_id[id])
		{
			id = m_id[id];
		}
		return id;
	}

	// user should guareent that a, and b is in range [0, n)
	bool IsConnected(int aid, int bid)
	{
		return FindRootId(aid) == FindRootId(bid);
	}

private:
	vector<int> m_id;
};

int main()
{
	UnionFind unionfind(1000);
	unionfind.Union(0, 100);
	unionfind.Union(0, 200);
	unionfind.Union(0, 300);
	unionfind.Union(0, 400);
	unionfind.Union(0, 500);
	unionfind.Union(500, 600);
	unionfind.Union(500, 700);
	unionfind.Union(1, 800);
	unionfind.Union(1, 900);

	cout << unionfind.IsConnected(200, 800) << endl;
	cout << unionfind.IsConnected(200, 700) << endl;
}