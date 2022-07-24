#include<iostream>
#include<stdc++.h>
using namespace std;
/*
ѧϰʹ��VSstudio2019����leetcode����
leetcode 19. ɾ������ĵ����� N �����

����һ������ɾ������ĵ����� n ����㣬���ҷ��������ͷ��㡣
ʾ����
���룺head = [1,2,3,4,5], n = 2
�����[1,2,3,5]
*/


//Definition for singly - linked list.
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//��һ����λ��1��ʼ�����������������,��ɾ���ڵ��λ��ΪL-n+1,����ͷ�ڵ㷵����Ԫ��㣬����ͷ�ڵ㣨λ��0����ʼ����L-n+1�Σ�Ҳ����L-n��λ�ã����ҵ���ɾ���ڵ��ǰ����ɾ���ڵ㼴��

//ʱ�临�Ӷȣ�O(L)������ L ������ĳ��ȡ�
//�ռ临�Ӷȣ�O(1)��

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
//	ListNode* removeNthFromEnd(ListNode* head, int n)//headָ����Ԫ�ڵ�
//	{
//		ListNode* dummy = new ListNode(0, head); //����һ��ͷ�ڵ㣬����ָ����Ԫ�ڵ�
//		int length = getLength(head); //�ܳ���ΪL��λ�ô�1��ʼ,��ɾ���ڵ��λ��ΪL-n+1
//		ListNode* cur = dummy;//cur��ͷ�ڵ㣨λ��0����ʼ����
//		for (int i = 0; i < length - n ; ++i)
//		{//�ҵ���ɾ���ڵ��ǰ��
//			cur = cur->next;
//		}
//		cur->next = cur->next->next;//������ɾ���ڵ�
//		ListNode* ans = dummy->next;
//		delete dummy;//ɾ��ͷ�ڵ�
//		return ans;
//	}
//};


/*
������ջ�����ڱ��������ͬʱ�����нڵ�������ջ������ջ���Ƚ��������ԭ�����ǵ���ջ�ĵ� n ���ڵ������Ҫɾ���Ľڵ㣬����Ŀǰջ���Ľڵ���Ǵ�ɾ���ڵ��ǰ���ڵ㡣
ʱ�临�Ӷȣ�O(L)������ L������ĳ��ȡ�
�ռ临�Ӷȣ�O(L)������ L������ĳ��ȡ���ҪΪջ�Ŀ�����
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
������˫ָ�룩�����ֹ��ɣ������ĩβ����ָ�룩�뱻ɾ���ڵ�֮�� ���n-1���ڵ㣬�뱻ɾ���ڵ�� ǰ���ڵ����n���ڵ㡣

�趨��ʼʱ�� second ָ��ͷ�ڵ㣨λ��0������ first ָ����Ԫ�ڵ�(λ��1)������ʹ��first ��������б���n�Ρ���ʱ��first(λ��n+1) �� second(λ��0) ֮������ n���ڵ�
����֮������ͬʱʹ�� first �� second ��������б������� first �����������ĩβ���� first Ϊ��ָ�룩ʱ��second ǡ��ָ������ n ���ڵ��ǰ���ڵ�.
ʱ�临�Ӷȣ�O(L)������ L ������ĳ��ȡ�
�ռ临�Ӷȣ�O(1)��

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