// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <bitset>
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
	vector<int> closestKValues(TreeNode* root, double target, int k) {
		//vector<TreeNode*> arr; 
		//inorder(root, arr); 
		//int i = findTarget(arr, target); 
		//return findK(arr, i, k); 
		return{}; 
	}

};

class Solution2 {
public:
	vector<int> closestKValues(TreeNode* root, double target, int k) {
		deque<int> arr; 
		helper(root, target, k, arr); 
		return vector<int>(arr.begin(), arr.end()); 
	}

	void helper(TreeNode* root, double target, int k, deque<int>& arr){
		if (!root)
			return; 

		helper(root->left, target, k, arr); 

		if (arr.size() < k){
			arr.push_back(root->val); 
		}
		else if (fabs(root->val - target) < fabs(arr.front() - target)){
			arr.pop_front(); 
			arr.push_back(root->val); 
		}
		else
			return; 

		helper(root->right, target, k, arr); 
	}

};


class Solution3 {
public:
	vector<int> closestKValues(TreeNode* root, double target, int k) {
		deque<int> res; 
		dfs(root, target, k, res); 
		return vector<int>(res.begin(), res.end()); 
	}
	void dfs(TreeNode*n, double target, int k, deque<int>& res){
		if (!n)
			return; 

		dfs(n->left, target, k, res); 
		
		if (res.size() < k)
			res.push_back(n->val); 
		else if (res.size() == k && fabs(target - n->val) < fabs(target - res.front())){
			res.pop_front(); 
			res.push_back(n->val); 
		}

		dfs(n->right, target, k, res); 
	}
};

// // unfinished. 
// class Solution4 {
// public:
// 	vector<int> closestKValues(TreeNode* root, double target, int k) {
// 		stack<TreeNode*> pred, succ; 
// 		TreeNode *p = root; 
// 		while (p){
// 			if (p->val > target){
// 				succ.push(p); 
// 				p = p->left; 
// 			}
// 			else{
// 				pred.push(p); 
// 				p = p->right; 
// 			}
// 		}

// 		vector<int> res; 
// 		// pred: <= target,  succ: >= target
// 		while (k > 0){
// 			if (pred.empty()){
// 				res.push_back(get_succ_next());
// 			}
// 			else if (succ.empty()){
// 				res.push_back(get_succ_next());
// 				pred.pop();
// 			}
// 			else if (.....){

// 			}

// 			--k; 
// 		}

// 		return res; 
// 	}

// 	int get_succ_next(stack<TreeNode*>& succ){
// 		TreeNode* top = succ.top(); 
// 		succ.pop(); 
// 		if (top->right){
// 			TreeNode *p = top->right; 
// 			while (p){
// 				succ.push(p); 
// 				p = p->right; 
// 			}
// 		}
// 		return top->val;
// 	}
// };

class Solution5 {
public:
	vector<int> closestKValues(TreeNode* root, double target, int k) {
		stack<TreeNode*> prec, succ; 
		TreeNode *p = root; 
		while (p){
			if (p->val > target){
				succ.push(p); 
				p = p->left; 
			}
			else{
				prec.push(p); 
				p = p->right; 
			}
		}

		vector<int> res; 
		while (k--){
			if (succ.empty() && prec.empty()) break;
			else if (succ.empty() || (prec.size() && abs(succ.top()->val - target) > abs(prec.top()->val - target))) { 
				res.push_back(prec.top()->val);  
				auto t = prec.top(); 
				prec.pop(); 
				if (t->left){
					TreeNode *q = t->left; 
					while (q){
						prec.push(q); 
						q = q->right; 
					}
				}
					
			}
			else{
				res.push_back(succ.top()->val); 
				auto t = succ.top(); 
				succ.pop(); 
				if (t->right){
					TreeNode *q = t->right; 
					while (q){
						succ.push(q); 
						q = q->left; 
					}
				}

			}
		}

		return res; 
	}
}; 


class Solution6 {
public:
	vector<int> closestKValues(TreeNode* root, double target, int k) {
		deque<int> container; 
		dfs(root, target, k, container); 
		return vector<int>(container.begin(), container.end()); 
	}

	void dfs(TreeNode *n, double tgt, int k, deque<int>& cont){
		if (!n) return; 
		dfs(n->left, tgt, k, cont); 

		if (cont.size() < k)
			cont.push_back(n->val); 
		else if (abs(cont.front() - tgt) > abs(n->val - tgt)){
			cont.pop_front(); 
			cont.push_back(n->val);
		}

		dfs(n->right, tgt, k, cont); 
	}
};


class Solution7 {
public:
	vector<int> closestKValues(TreeNode* root, double target, int k) {
		stack<TreeNode*> succ, prec; 
		TreeNode *p = root; 
		while (p){
			if (p->val > target){
				prec.push(p);
				p = p->left; 
			}
			else{
				succ.push(p); 
				p = p->right; 
			}
		}

		while (k--){

		}
	}
};


class TEST{
public:
	struct Itor{
		TreeNode* root; 
		stack<TreeNode*> stk; 
		Itor(TreeNode* n) :root(n) {
			TreeNode *p = root; 
			while (p){
				stk.push(p); 
				p = p->left; 
			}
		}

		bool empty(){ return stk.empty(); }

		TreeNode* next(){
			TreeNode *top = stk.top(); 
			stk.pop(); 
			if (top->right){
				TreeNode *p = top->right; 
				while (p){
					stk.push(p); 
					p = p->left; 
				}
			}
			return top; 
		}
	};

	void iterate(TreeNode* root){
		Itor it(root); 
		while (!it.empty()){
			cout << it.next()->val<<' ';
		}
	}
};



int main(){
	Solution2 a; 
	Solution5 a2; 

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	double target = 6; 
	auto r1 = a.closestKValues(tree, target, 4); 
	auto r2 = a2.closestKValues(tree,target, 4); 

	prt1Layer(r1); 
	cout << "2nd\n"; 
	prt1Layer(r2); 

	TEST t; 
	t.iterate(tree); 

	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

