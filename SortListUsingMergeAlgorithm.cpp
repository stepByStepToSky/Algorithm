#include <iostream>

using namespace std;

struct ListNode
{
	ListNode(int value) : val(value), next(nullptr) {}
	int val;
	ListNode * next;
};

ListNode * MergeTwoSortedList(ListNode * aHead, ListNode * bHead)
{
	if (nullptr == aHead)
	{
		return bHead;
	}
	else if (nullptr == bHead)
	{
		return aHead;
	}

	ListNode * retHead = nullptr, * lastNode = nullptr;
	if (aHead->val < bHead->val)
	{
		retHead = aHead;
		lastNode = retHead;
		aHead = aHead->next;
	}
	else
	{
		retHead = bHead;
		lastNode = retHead;
		bHead = bHead->next;
	}

	while (nullptr != aHead && nullptr != bHead)
	{
		if (aHead->val < bHead->val)
		{
			lastNode->next = aHead;
			lastNode = aHead;
			aHead = aHead->next;
		}
		else
		{
			lastNode->next = bHead;
			lastNode = bHead;
			bHead = bHead->next;
		}
	}

	if (nullptr != aHead)
	{
		lastNode->next = aHead;
	}

	if (nullptr != bHead)
	{
		lastNode->next = bHead;
	}

	return retHead;
}

// list must contain two or more nodes
void SplitList(ListNode * head, ListNode ** firstHead, ListNode ** secondHead)
{
	*firstHead = head;
	ListNode * fast = head->next, * slow = head;
	while (fast)
	{
		fast = fast->next;
		if (nullptr != fast)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}

	*secondHead = slow->next;
	slow->next = nullptr;	// split the whole list into two lists
}

ListNode * ListSortedByMerge(ListNode * head)
{
	if (nullptr == head || nullptr == head->next)
	{
		return head;
	}

	ListNode * firstHead = nullptr, * secondHead = nullptr;
	SplitList(head, &firstHead, &secondHead);
	ListNode * firstSortedHead = ListSortedByMerge(firstHead);
	ListNode * secondSortedHead = ListSortedByMerge(secondHead);
	return MergeTwoSortedList(firstSortedHead, secondSortedHead);
}

void PushNode(ListNode ** head, ListNode ** lastNode, int value)
{
	if (nullptr == *head)
	{
		*head = new ListNode(value);
		*lastNode = *head;
		return;
	}

	(*lastNode)->next = new ListNode(value);
	*lastNode = (*lastNode)->next;
}

void PrintList(ListNode *head)
{
	while (nullptr != head)
	{
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

void DestoryList(ListNode *head)
{
	while (nullptr != head)
	{
		ListNode * next = head->next;
		delete head;
		head = next;
	}
}

int main()
{
	ListNode * head = nullptr, * lastNode = nullptr;
	PushNode(&head, &lastNode, 1);
	PushNode(&head, &lastNode, 3);
	PushNode(&head, &lastNode, 1);
	PushNode(&head, &lastNode, 4);
	PushNode(&head, &lastNode, 0);
	PushNode(&head, &lastNode, 8);
	PushNode(&head, &lastNode, 1);
	PushNode(&head, &lastNode, 2);
	PushNode(&head, &lastNode, 0);
	PushNode(&head, &lastNode, 9);
	PushNode(&head, &lastNode, 1);
	PushNode(&head, &lastNode, 4);
	cout << "before sort" << endl;
	PrintList(head);
	head = ListSortedByMerge(head);
	cout << "after sort" << endl;
	PrintList(head);
	DestoryList(head);
}