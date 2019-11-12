#include <iostream>
#include <vector>
#include <queue>

#pragma warning(disable:4996) 

using namespace std;

struct Cmp
{
	bool operator()(const pair<int, int> & lth, const pair<int, int> & rth)
	{
		return lth.first > rth.first;
	}
};
class Graph
{
public:
	Graph(int nv) :m_v(nv), m_vec(nv, vector<int>(nv, 0))
	{
	}

	void AddEdge(int from, int to, int weight)
	{
		m_vec[from][to] = weight;
		m_vec[to][from] = weight;
	}

	void Dijkstra(int src)
	{
		// weight, v
		priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> que;
		vector<bool> visited(m_v, false);
		vector<int> dist(m_v, INT_MAX);
		dist[src] = 0;

		que.push(make_pair(0, src));
		while (!que.empty())
		{
			pair<int, int> top = que.top();
			que.pop();
			int from = top.second;
			if (visited[from])
			{
				continue;
			}

			visited[from] = true;
			for (int to = 0; to < m_v; ++to)
			{
				if (!visited[to] && 0 != m_vec[from][to] && dist[from] + m_vec[from][to] < dist[to])
				{
					dist[to] = dist[from] + m_vec[from][to];
					que.push(make_pair(dist[to], to));
				}
			}
		}
		Print(dist);
	}

	void Print(const vector<int> & dist)
	{
		for (int i = 0; i < m_v; ++i)
		{
			cout << dist[i];
			if (i + 1 == m_v)
			{
				cout << endl;
			}
			else
			{
				cout << " ";
			}
		}
	}
private:
	int m_v;
	vector<vector<int>> m_vec;
};

int main()
{
	Graph g(9);
	g.AddEdge(0, 1, 4);
	g.AddEdge(0, 7, 8);
	g.AddEdge(1, 2, 8);
	g.AddEdge(1, 7, 11);
	g.AddEdge(2, 3, 7);
	g.AddEdge(2, 8, 2);
	g.AddEdge(2, 5, 4);
	g.AddEdge(3, 4, 9);
	g.AddEdge(3, 5, 14);
	g.AddEdge(4, 5, 10);
	g.AddEdge(5, 6, 2);
	g.AddEdge(6, 7, 1);
	g.AddEdge(6, 8, 6);
	g.AddEdge(7, 8, 7);
	g.Dijkstra(0);
}