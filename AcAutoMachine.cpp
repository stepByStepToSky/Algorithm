#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory>
#include <string.h>

using namespace std;


class AcAutoMachine
{
public:
	AcAutoMachine() : m_buffer(nullptr), m_size(0), m_capacity(0)
	{
	}

	struct AcNode
	{
		AcNode(char value) : fail(nullptr), val(value), len(0)
		{
			memset(next, 0, sizeof(next));
		}

		AcNode * next[256];
		AcNode * fail;
		int len;
		char val;

		bool isWord()
		{
			return 0 != len;
		}
	};

	struct SearchResult
	{
		SearchResult(int s, int l) : startIndex(s), curLen(l)
		{
		}

		// the index of the first char in the search string
		int startIndex;
		// the length of the result string
		int curLen;
	};

	AcNode * GetAcNode(char val)
	{
		//return new AcNode(val);
		char * p = m_buffer.get();
		p += (m_size * sizeof(AcNode));
		++m_size;
		new (p) AcNode(val);
		return (reinterpret_cast<AcNode*>(p));
	}

	void AllocMemory(const vector<string> & vec)
	{
		m_size = 0;
		m_capacity = 5;
		for (size_t i = 0; i < vec.size(); ++i)
		{
			m_capacity += vec[i].size();
		}
		
		m_buffer.reset(static_cast<char *>(malloc(m_capacity * sizeof(AcNode))));
	}

	AcNode * BuildTrieTree(const vector<string> & vec)
	{
		AllocMemory(vec);
		AcNode * root = GetAcNode(0);
		for (size_t i = 0; i < vec.size(); ++i)
		{
			AcNode * cur = root;
			const string & str = vec[i];
			for (size_t k = 0; k < str.size(); ++k)
			{
				char val = str[k];
				if (nullptr == cur->next[val])
				{
					cur->next[val] = GetAcNode(val);
				}
				cur = cur->next[val];
			}
			cur->len = static_cast<int>(str.size());
		}

		return root;
	}

	AcNode * BuildAcTreeFromTrieTree(AcNode * root)
	{
		queue<AcNode *> que;
		for (size_t i = 0; i < 256; ++i)
		{
			if (nullptr != root->next[i])
			{
				// point the fail node of root's child to root
				root->next[i]->fail = root;
				que.push(root->next[i]);
			}
		}

		while (!que.empty())
		{
			AcNode * parent = que.front();
			que.pop();

			for (size_t i = 0; i < 256; ++i)
			{
				if (nullptr != parent->next[i])
				{
					AcNode *parentFail = parent->fail, *child = parent->next[i];
					// push child node into the que
					que.push(child);

					while (true)
					{
						// if no prefix the same as the postfix when ends with cur char, point the fail to the root
						if (nullptr == parentFail)
						{
							child->fail = root;
							break;
						}

						// parent fail node has the same child as current node, just point it to the parent fail node's child
						if (nullptr != parentFail->next[i])
						{
							child->fail = parentFail->next[i];
							break;
						}
						else	// continue go the parent's fail node
						{
							parentFail = parentFail->fail;
						}
					}
				}
			}
		}

		return root;
	}

	void Search(AcNode * root, const string & text, vector<SearchResult> & vecRes)
	{
		vecRes.clear();

		AcNode * cur = root;
		for (size_t i = 0; i < text.size();)
		{
			char val = text[i];

			// current char is ok, go ahead
			if (nullptr != cur->next[val])
			{
				cur = cur->next[val];

				if (cur->isWord())
				{
					vecRes.push_back(SearchResult(i - cur->len + 1, cur->len));
				}

				// find this substring is whether another string
				// such as ["aaabaa", "aa", "a"]
				AcNode * curFail = cur->fail;
				while (nullptr != curFail)
				{
					if (curFail->isWord())
					{
						vecRes.push_back(SearchResult(i - curFail->len + 1, curFail->len));
					}
					curFail = curFail->fail;
				}

				++i;
			}
			else	// not ok, should go to the fail node
			{
				cur = cur->fail;

				if (nullptr == cur)
				{
					cur = root;
					++i;
				}
			}
		}
	}

private:
	unique_ptr<char> m_buffer;
	int m_size;
	int m_capacity;
};

int main()
{
	typedef AcAutoMachine::AcNode  AcNode;
	typedef AcAutoMachine::SearchResult SearchResult;

	vector<string> vec = { "this", "test", "sing" };
	string text = "this is just a single test";

	AcAutoMachine acmechine;
	AcNode * root = acmechine.BuildTrieTree(vec);
	root = acmechine.BuildAcTreeFromTrieTree(root);
	vector<SearchResult> vecRes;
	acmechine.Search(root, text, vecRes);


	// occurs string
	for (size_t i = 0; i < vecRes.size(); ++i)
	{
		cout << text.substr(vecRes[i].startIndex, vecRes[i].curLen) << endl;
	}
}