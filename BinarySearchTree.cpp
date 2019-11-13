#include <iostream>
#include <stack>

using namespace std;

struct TreeNode
{
	TreeNode(int val) :value(val), left(nullptr), right(nullptr)
	{
	}

	int value;
	TreeNode * left, *right;
};

TreeNode * Find(TreeNode *root, int val)
{
	if (nullptr == root)
	{
		return nullptr;
	}

	if (root->value == val)
	{
		return root;
	}
	else if (root->value < val)
	{
		return Find(root->right, val);
	}
	else
	{
		return Find(root->left, val);
	}
}

TreeNode * Insert(TreeNode * root, int val)
{
	if (nullptr == root)
	{
		return new TreeNode(val);
	}

	if (root->value < val)
	{
		root->right = Insert(root->right, val);
	}
	else if (root->value > val)
	{
		root->left = Insert(root->left, val);
	}
	return root;
}

TreeNode * FindMaxInLeftTree(TreeNode * root)
{
	while (nullptr != root->right)
	{
		root = root->right;
	}
	return root;
}

TreeNode * Remove(TreeNode * root, int val)
{
	if (nullptr == root)
	{
		return nullptr;
	}

	if(root->value == val)
	{
		if (nullptr == root->left)
		{
			return root->right;
		}
		else if (nullptr == root->right)
		{
			return root->left;
		}
		else
		{
			TreeNode * leftMax = FindMaxInLeftTree(root->left);
			int replaceValue = leftMax->value;
			root->left = Remove(root->left, replaceValue);
			root->value = replaceValue;
			return root;
		}
	}
	else if (root->value < val)
	{
		root->right = Remove(root->right, val);
	}
	else	//root->value > val
	{
		root->left = Remove(root->left, val);
	}
	return root;
}

void PrintTreePrevOrder(TreeNode * root)
{
	if (nullptr == root)
	{
		return;
	}

	cout << root->value << " ";
	PrintTreePrevOrder(root->left);
	PrintTreePrevOrder(root->right);
}

void PrintTreePrevOrderNonRecursion(TreeNode * root)
{
	stack<TreeNode*> sta;
	TreeNode * p = root;
	while (nullptr != p || !sta.empty())
	{
		while (nullptr != p)
		{
			cout << p->value << " ";
			sta.push(p);
			p = p->left;
		}

		if (!sta.empty())
		{
			p = sta.top()->right;
			sta.pop();
		}
	}

	cout << endl;
}

void PrintTreeMidOrder(TreeNode * root)
{
	if (nullptr == root)
	{
		return;
	}

	PrintTreeMidOrder(root->left);
	cout << root->value << " ";
	PrintTreeMidOrder(root->right);
}


void PrintTreeMidOrderNonRecursion(TreeNode * root)
{
	stack<TreeNode *> sta;
	TreeNode * p = root;
	while (nullptr != p || !sta.empty())
	{
		while (nullptr != p)
		{
			sta.push(p);
			p = p->left;
		}

		if (!sta.empty())
		{
			p = sta.top();
			sta.pop();
			cout << p->value << " ";
			p = p->right;
		}
	}
	cout << endl;
}

void PrintTreePostOrder(TreeNode * root)
{
	if (nullptr == root)
	{
		return;
	}

	PrintTreePostOrder(root->left);
	PrintTreePostOrder(root->right);
	cout << root->value << " ";
}

void PrintTreePostOrderNonRecursion(TreeNode * root)
{
	stack<TreeNode *> sta;
	TreeNode * prev = nullptr;

	sta.push(root);
	while (!sta.empty())
	{
		TreeNode * cur = sta.top();
		if ((nullptr == cur->left && nullptr == cur->right) || (nullptr != prev && (prev == cur->left || prev == cur->right)))
		{
			cout << cur->value << " ";
			prev = cur;
			sta.pop();
		}
		else
		{
			if (nullptr != cur->right)
			{
				sta.push(cur->right);
			}
			if (nullptr != cur->left)
			{
				sta.push(cur->left);
			}
		}
	}
	cout << endl;
}

int main()
{
	TreeNode * root = Insert(nullptr, 1);
	root = Insert(root, 3);
	root = Insert(root, 2);
	root = Insert(root, 4);
	root = Insert(root, 5);
	root = Insert(root, 6);

	PrintTreePrevOrder(root);
	cout << endl;

	//root = Remove(root, 10);
	//root = Remove(root, 2);
	//root = Remove(root, 3);
	//root = Remove(root, 4);
	
	PrintTreePrevOrder(root);
	cout << endl;
	PrintTreePrevOrderNonRecursion(root);


	PrintTreeMidOrder(root);
	cout << endl;
	PrintTreeMidOrderNonRecursion(root);
	
	PrintTreePostOrder(root);
	cout << endl;
	PrintTreePostOrderNonRecursion(root);
}