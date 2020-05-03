// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>

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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
/**
* Definition for singly-linked list.
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// not comply with the requirements. Don't swap if length is less than k. 
class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (k < 1)
			return nullptr; 

		ListNode *pre=nullptr, *i=nullptr, *j, *post=nullptr; 
		pre = new ListNode(0); 
		ListNode *dummy = pre; 
		dummy->next = head; 
		j = head; 

		while (j != nullptr){
			for (int n = 0; n < k && j != nullptr; ++n){
				if (i == nullptr){
					i = j;
					j = j->next;
					continue;
				}
				ListNode *tmp = j->next;
				j->next = i;
				i = j;
				j = tmp;
			}

			ListNode *oldhead = pre->next; 
			oldhead->next = j; 
			pre->next = i; 
			pre = oldhead; 
			i = nullptr; 

			
			// for (ListNode*p = dummy; p; p = p->next){
			// 	cout << p->val << "->";
			// }
			// cout << endl;
		}
		
		return dummy->next; 
	}
};


// pass AC
class Solution2 {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode *dummy = new ListNode(0); 
		dummy->next = head; 
		ListNode *pre = dummy, *i = nullptr, *j = head, *post = nullptr; 
		bool isEnd = false; 

		while (j){
			post = j; 
			for (int idx = 0; idx < k && post; ++idx){
				post = post->next; 
				if (idx<k-1 && post == nullptr){
					isEnd = true; 
					break;
				}
			}

			if (isEnd)
				break;

			while (j!=post){
				if (i == nullptr){
					i = j; 
					j = j->next; 
					continue;
				}
				ListNode* tmp = j->next; 
				j->next = i; 
				i = j; 
				j = tmp; 
			}

			ListNode *tmp = pre->next; 
			pre->next->next = post; 
			pre->next = i; 
			pre = tmp; 
			i = nullptr; 

			// for (ListNode* p = dummy->next; p; p = p->next){
			// 	cout << p->val << "->";
			// }
			// cout << endl;
		}

		return dummy->next; 
		
	}
};


int main()
{
	Solution2 a;

	ListNode *b = new ListNode(1); 
	ListNode *p = b;

	for (int i = 2; i < 12; ++i){
		p->next = new ListNode(i); 
		p = p->next; 
	}

	ListNode* newhead = a.reverseKGroup(b, 3); 

	for (ListNode*p = newhead; p; p=p->next){
		cout << p->val << "->"; 
	}
	cout << endl; 

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/


}

