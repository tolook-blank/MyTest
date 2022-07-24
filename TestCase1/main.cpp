#include<iostream>
#include<stdc++.h>
using namespace std;
/*
学习使用VSstudio2019运行leetcode代码
leetcode 19. 删除链表的倒数第 N 个结点

给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
示例：
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
*/


//Definition for singly - linked list.
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//法一：从位置1开始遍历，计算出链表长度,待删除节点的位置为L-n+1,申请头节点返回首元结点，并从头节点（位置0）开始遍历L-n+1次，也即第L-n的位置，即找到待删除节点的前驱，删除节点即可

//时间复杂度：O(L)，其中 L 是链表的长度。
//空间复杂度：O(1)。

//class Solution {
//public:
//	int getLength(ListNode* head)
//	{
//		int length = 0;
//		while (head)
//		{
//			++length;
//			head = head->next;
//		}
//		return length;
//	}
//
//	ListNode* removeNthFromEnd(ListNode* head, int n)//head指向首元节点
//	{
//		ListNode* dummy = new ListNode(0, head); //申请一个头节点，用来指向首元节点
//		int length = getLength(head); //总长度为L，位置从1开始,待删除节点的位置为L-n+1
//		ListNode* cur = dummy;//cur从头节点（位置0）开始遍历
//		for (int i = 0; i < length - n ; ++i)
//		{//找到待删除节点的前驱
//			cur = cur->next;
//		}
//		cur->next = cur->next->next;//断链，删除节点
//		ListNode* ans = dummy->next;
//		delete dummy;//删除头节点
//		return ans;
//	}
//};


/*
法二（栈）：在遍历链表的同时将所有节点依次入栈。根据栈「先进后出」的原则，我们弹出栈的第 n 个节点就是需要删除的节点，并且目前栈顶的节点就是待删除节点的前驱节点。
时间复杂度：O(L)，其中 L是链表的长度。
空间复杂度：O(L)，其中 L是链表的长度。主要为栈的开销。
*/
//class Solution {
//public:
//	ListNode* removeNthFromEnd(ListNode* head, int n)
//	{
//		ListNode* dummy = new ListNode(0, head);
//		stack<ListNode*> stk;
//		ListNode* cur = dummy;
//		while (cur)
//		{
//			stk.push(cur);
//			cur = cur->next;
//		}
//		for (int i = 0; i < n; ++i)
//		{
//			stk.pop();
//		}
//		ListNode* prev = stk.top();
//		prev->next = prev->next->next;
//		ListNode* ans = dummy->next;
//		delete dummy;
//		return ans;
//	}
//};

/*
法三（双指针）：发现规律：链表的末尾（空指针）与被删除节点之间 相隔n-1个节点，与被删除节点的 前驱节点相隔n个节点。

设定初始时将 second 指向头节点（位置0），将 first 指向首元节点(位置1)。首先使用first 对链表进行遍历n次。此时，first(位置n+1) 和 second(位置0) 之间间隔了 n个节点
在这之后，我们同时使用 first 和 second 对链表进行遍历。当 first 遍历到链表的末尾（即 first 为空指针）时，second 恰好指向倒数第 n 个节点的前驱节点.
时间复杂度：O(L)，其中 L 是链表的长度。
空间复杂度：O(1)。

*/
class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		ListNode* dummy = new ListNode(0, head);
		ListNode* first = head;
		ListNode* second = dummy;
		for (int i = 0; i < n; ++i)
		{
			first = first->next;
		}
		while (first)
		{
			first = first->next;
			second = second->next;
		}
		second->next = second->next->next;
		ListNode* ans = dummy->next;
		delete dummy;
		return ans;
	}
};


void trimLeftTrailingSpaces(string & input)
{
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
		return !isspace(ch);
		}));
}

void trimRightTrailingSpaces(string & input)
{
	input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
		return !isspace(ch);
		}).base(), input.end());
}

vector<int> stringToIntegerVector(string input)
{
	vector<int> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	char delim = ',';
	while (getline(ss, item, delim))
	{
		output.push_back(stoi(item));
	}
	return output;
}

ListNode* stringToListNode(string input)
{
	// Generate list from the input
	vector<int> list = stringToIntegerVector(input);

	// Now convert that list into linked list
	ListNode* dummyRoot = new ListNode(0);
	ListNode* ptr = dummyRoot;
	for (int item : list)
	{
		ptr->next = new ListNode(item);
		ptr = ptr->next;
	}
	ptr = dummyRoot->next;
	delete dummyRoot;
	return ptr;
}

int stringToInteger(string input)
{
	return stoi(input);
}

string listNodeToString(ListNode * node)
{
	if (node == nullptr)
	{
		return "[]";
	}

	string result;
	while (node)
	{
		result += to_string(node->val) + ", ";
		node = node->next;
	}
	return "[" + result.substr(0, result.length() - 2) + "]";
}

int main()
{
	string line;
	while (getline(cin, line))
	{
		ListNode* head = stringToListNode(line);
		getline(cin, line);
		int n = stringToInteger(line);

		ListNode* ret = Solution().removeNthFromEnd(head, n);

		string out = listNodeToString(ret);
		cout << out << endl;
	}
	return 0;
}