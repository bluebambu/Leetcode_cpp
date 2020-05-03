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
#include <chrono>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


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
		for (int i = 0; i < n; ++i){
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


template <typename C>
void prt1Layer(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void prt2Layer(C v){
	for (auto i : v){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
	}
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////




class Solution {
public:
	list<int> flatten(TreeNode* root){
		if (!root)
			return{}; 
		
		list<int> left = flatten(root->left); 
		list<int> right = flatten(root->right); 

		left.push_back(root->val); 
		left.insert(left.end(), right.begin(), right.end()); 

		return left;
	}

	TreeNode* inplace(TreeNode* root){
		auto res =helper(root); 
		return res.first; 
	}

	pair<TreeNode*, TreeNode*> helper(TreeNode* node){
		if (!node)
			return{ node, node }; 

		auto left = helper(node->left), right = helper(node->right); 

		TreeNode *mostL, *mostR; 
		if (left.first){
			left.second->right = node; 
			node->left = left.second; 
			mostL = left.first; 
		}
		else{
			mostL = node; 
		}

		if (right.first){
			right.first->left = node; 
			node->right = right.first; 
			mostR = right.second;
		}
		else{
			mostR = node; 
		}
		
		return{ mostL, mostR }; 
	}
};

class Solution2 {
public:
	TreeNode* inplace(TreeNode* root){
		TreeNode *head=nullptr, *tail=nullptr; 
		inplace(root, head, tail); 
		return head; 
	}

	void inplace(TreeNode*node, TreeNode*&head, TreeNode*&tail){
		if (!node)
			return; 

		inplace(node->left, head, tail); 

		if (tail == nullptr){
			head = node;
			tail = node;
		}
		else{
			tail->right = node; 
			node->left = tail; 
			tail = node; 
		}

		inplace(node->right, head, tail); 
	}
};


class Solution3{
public:
	TreeNode* stacksolution(TreeNode* root){
		stack<TreeNode*> stk; 
		TreeNode*cur = root;

		TreeNode *pre = nullptr; 
		TreeNode *head = nullptr; 

		while (!stk.empty() || cur){
			while (cur){
				stk.push(cur);
				cur = cur->left; 
			}

			TreeNode* top = stk.top(); 
			stk.pop(); 

			if (pre){
				pre->right = top;
				top->left = pre;
			}
			else
				head = top;

			pre = top;

			if (top->right)
				cur = top->right; 
		}
		return head;
	}
};


class Solution4{
public:
	TreeNode* toLL(TreeNode* root){
		dfs(root); 
		while (root->left) root = root->left; 
		return root; 
	}
	void dfs(TreeNode *n){
		if (!n)
			return; 

		TreeNode *prevl = n->left, *prevr = n->right; 
		dfs(prevl); 
		dfs(prevr); 


		if (n->left){
			TreeNode *l = n->left; 
			while (l->right) l = l->right; 
			l->right = n; 
			n->left = l; 
		}
		if (n->right){
			TreeNode *r = n->right; 
			while (r->left) r = r->left; 
			r->left = n; 
			n->right = r; 
		}

	}
};


class Solution5{
public:
	TreeNode *toLL(TreeNode*root){
		stack<TreeNode*> stk; 
		TreeNode *p = root, *prev = nullptr; 

		while (!stk.empty() || p){
			while (p){
				stk.push(p); 
				p = p->left; 
			}

			TreeNode *cur = stk.top(); 

			if (!cur->right || prev == cur->right){
				process(cur); 
				stk.pop(); 
				prev = cur; 
			}
			else
				p = cur->right; 
		}

		while (root->left) 
			root = root->left; 
		return root; 
	}

	void process(TreeNode *n){
		TreeNode *prevl = n->left, *prevr = n->right; 

		if (n->left){
			TreeNode *l = n->left; 
			while (l->right) l = l->right; 
			l->right = n; 
			n->left = l; 
		}
		if (n->right){
			TreeNode *r = n->right; 
			while (r->left) r = r->left; 
			r->left = n; 
			n->right = r; 
		}
	}
};

class Solution6 {
public:
	TreeNode *toLL(TreeNode*root){
		return conv(root)[0]; 
	}
	vector<TreeNode*> conv(TreeNode* node){
		if (!node)
			return{ nullptr, nullptr }; 

		auto l = conv(node->left), r = conv(node->right); 
		if (l[1])
			l[1]->right = node, node->left = l[1]; 
		if (r[0])
			r[0]->left = node, node->right = r[0]; 

		TreeNode *p = node, *q = node; 
		while (p->left)
			p = p->left; 
		while (q->right)
			q = q->right; 

		return{ p, q }; 
	}
}; 


class Solution7 {
public:
	TreeNode *toLL(TreeNode*root){
		conv(root); 
		return getHead(root); 
	}
	void conv(TreeNode* n){
		if (!n) return; 
		auto l = n->left, r = n->right; 
		auto l2 = n->left, r2 = n->right; 
		while (l->right)
			l = l->right; 
		l->right = n; 
		n->left = l; 
		while (r->left)
			r = r->left; 
		r->left = n; 
		n->right = r; 

		if (l2->left && l2->left->right!=l2)
			conv(l2);
		if (r2->right && r2->right->left!=r2)
			conv(r2);
	}
	TreeNode* getHead(TreeNode*r){
		while (r->left)
			r = r->left; 
		return r; 
	}
};

class Solution8 {
public:
	TreeNode *toLL(TreeNode*root){
		TreeNode *head=nullptr, *tail=nullptr; 
		dfs(root, head, tail); 
		return head; 
	}
	void dfs(TreeNode*cur, TreeNode*&head, TreeNode*& tail){
		if (!cur) return; 
		dfs(cur->left, head, tail); 

		if (head == nullptr){
			head = cur; 
		}
		if (tail == nullptr)
			tail = cur; 
		else{
			tail->right = cur; 
			cur->left = tail; 
			tail = cur; 
		}

		dfs(cur->right, head, tail); 
	}
}; 

int main(){
//	Solution3 a; 
	Solution8 a; 

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, nullptr,
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	auto c = a.toLL(tree); 

	while (c)
	{
		cout << c->val << " "; 
		c = c->right; 
	}


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

