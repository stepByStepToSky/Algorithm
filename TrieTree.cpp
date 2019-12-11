#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Trie {
public:
	struct TrieNode
	{
		TrieNode() : val(0), isword(false), next(256, nullptr)
		{
		}

		TrieNode(char value) : val(value), isword(false), next(256, nullptr)
		{
		}

		char val;
		bool isword;
		vector<TrieNode *> next;
	};

	typedef struct TrieNode TrieNode;

	/** Initialize your data structure here. */
	Trie() : m_root(new TrieNode()){
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		TrieNode * node = m_root;
		for (int i = 0; i < word.size(); ++i)
		{
			if (nullptr == node->next[word[i]])
			{
				node->next[word[i]] = new TrieNode(word[i]);
			}
			node = node->next[word[i]];
		}
		node->isword = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		TrieNode * node = m_root;
		for (int i = 0; i < word.size(); ++i)
		{
			if (nullptr == node || nullptr == node->next[word[i]])
			{
				return false;
			}
			node = node->next[word[i]];
		}
		return node->isword;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		TrieNode * node = m_root;
		for (int i = 0; i < prefix.size(); ++i)
		{
			if (nullptr == node || nullptr == node->next[prefix[i]])
			{
				return false;
			}
			node = node->next[prefix[i]];
		}
		return true;
	}

private:
	TrieNode * m_root;
};

int main()
{
	Trie trie;
	trie.insert("apple");
	cout << trie.search("apple") << endl;   // 返回 true
	cout << trie.search("app") << endl;     // 返回 false
	cout << trie.startsWith("app") << endl; // 返回 true
	trie.insert("app");
	cout << trie.search("app") << endl;     // 返回 trues
}