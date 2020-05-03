// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


struct TreeNode
{
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {}
	TreeNode() :val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};

void print(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);

	while (q.size()){
		int n = q.size();
		for (int i = 0; i<n; ++i){
			TreeNode* front = q.front();
			q.pop();

			if (!front)
				cout << "# ";
			else{
				cout << front->val << " ";
				q.push(front->left);
				q.push(front->right);
			}
		}
		cout << endl;
	}
}


struct ListNode{
	int val; 
	ListNode* next; 
	ListNode(int x) :val(x) {}
};

class Solution
{
public:
	ListNode* sortList(ListNode* a){
		return sort(a, nullptr);
	}
	ListNode* sort(ListNode* head, ListNode* tail){
		if (head == tail || head->next == tail)
			return head; 
		ListNode* slow = head, *fast = slow->next; 
		while (fast && fast->next){
			slow = slow->next; 
			fast = fast->next->next; 
		}

		fast = slow->next; 
		slow->next = nullptr; 
		slow = head; 

		slow = sort(slow, nullptr);
		fast = sort(fast, nullptr);

		return merge(slow, fast); 
	}
	ListNode* merge(ListNode* a, ListNode* b){
		if (!a && !b)
			return a ? a : b; 
		ListNode* dummy = new ListNode(0), *p = dummy; 

		while (a&&b){
			if (a->val < b->val){
				p->next = a; 
				a = a->next; 
			}
			else{
				p->next = b; 
				b = b->next; 
			}
			p = p->next;
		}
		
		p->next = a ? a : b; 
		p = dummy->next; 
		delete dummy;
		return p; 
	}
};

int main()
{
	Solution a;



}

