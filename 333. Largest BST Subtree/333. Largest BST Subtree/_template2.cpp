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

// passed
class Solution {
public:
	int largestBSTSubtree(TreeNode* root) {
		int res=-1; 
		helper(root, res); 
		return res; 
	}

	struct Info{
		int sz; 
		TreeNode *low, *high; 
		Info() :sz(0), low(nullptr), high(nullptr) {}
	};

	Info helper(TreeNode* node, int& largest){
		if (!node){
			return Info(); 
		}
		
		Info left = helper(node->left, largest); 
		Info right = helper(node->right, largest); 
		Info res; 

		res.low = left.low ? left.low : node; 
		res.high = right.high ? right.high : node; 
		
		if ((left.high && node->val <= left.high->val) ||
			(right.low && node->val >= right.low->val) ||
			(left.sz == -1 || right.sz == -1)
			)
			res.sz = -1;
		else
			res.sz = 1 + left.sz + right.sz; 

		if (res.sz > largest)
			largest = res.sz; 

		return res; 
	}
};


// ans without struct
class Solution2 {
public:
	int largestBSTSubtree(TreeNode* root) {

		int res = 0;
		int mini, maxi;
		bool b = isBST(root, res, mini, maxi);

		return res;
	}

	bool isBST(TreeNode* node, int& res, int& mini, int& maxi) {

		if (!node)
			return true;

		int left_size = 0, right_size = 0;
		int left_mini, left_maxi, right_mini, right_maxi;

		bool leftB = isBST(node->left, left_size, left_mini, left_maxi);
		bool rightB = isBST(node->right, right_size, right_mini, right_maxi);

		if (leftB && rightB) {
			if ((!node->left || node->val >= left_maxi) && (!node->right || node->val <= right_mini)) {
				/* The tree rooted at this node is a binary search tree */
				res = left_size + right_size + 1;

				mini = node->left ? left_mini : node->val;
				maxi = node->right ? right_maxi : node->val;
				return true;
			}
		}
		/* The tree rooted at this node is not a binary search tree, so take the maximum size of the BST in the left or right subtrees  */
		res = max(left_size, right_size);
		return false;
	}
};


class Solution3 {
public:
	struct Info {
		bool valid; 
		int low; 
		int high; 
		int size; 
		Info(bool b, int x, int y, int z) :valid(b), low(x), high(y), size(z) {}
	};

	int largestBSTSubtree(TreeNode* root) {
		auto r = dfs(root); 
		return r.size; 
	}

	Info dfs(TreeNode* n){
		if (!n)
			return Info(true, INT_MIN, INT_MAX, 0); 

		Info l = dfs(n->left),
			r = dfs(n->right); 

		if (l.valid && r.valid){
			if ((!n->left || l.high < n->val) && (!n->right || r.low > n->val)){
				int lv = n->left ? l.low : n->val,
					rv = n->right ? r.high : n->val; 
				return Info(true, lv, rv, l.size + r.size + 1); 
			}
		}

		return Info(false, n->val, n->val, max(l.size, r.size)); 
	}
}; 

class other{
public:
	bool validBST(TreeNode* root){
		return valid(root, INT_MIN, INT_MAX); 
	}
	bool valid(TreeNode* n, int min, int max){
		if (!n)
			return true; 

		if (n->val <= min || n->val >= max)
			return false; 

		return valid(n->left, min, n->val) && valid(n->right, n->val, max); 
	}

	struct Info{
		bool valid; 
		int low, high; 
		Info(bool x, int y, int z) : valid(x), low(y), high(z) {}
	}; 

	bool validBST2(TreeNode* root){
		return valid2(root).valid;
	}
	Info valid2(TreeNode* n){
		if (!n)
			return Info(true, 0, 0); 

		Info l = valid2(n->left), r = valid2(n->right); 

		if (!l.valid || !r.valid)
			return Info(false, 0, 0); 

		if ((!n->left || l.high < n->val) && (!n->right || r.low > n->val)){
			int lv = n->left ? l.low : n->val,
				rv = n->right ? r.high : n->val; 
			return Info(true, lv, rv); 
		}
		else
			return Info(false, 0, 0); 
	}
};

class Solution4{
public:
	int largestBSTSubtree(TreeNode* root){
		int largestSize = 1; 
		check(root, nullptr, nullptr, largestSize);
		return largestSize; 
	}
	vector<int> check(TreeNode*n, TreeNode*left, TreeNode*right, int& large){
		if (!n)
			return{ true, 0 }; 

		auto l = check(n->left, left, n, large),
			r = check(n->right, n, right, large); 

		if ((!left || n->val > left->val) && (!right || n->val < right->val) && l[0] && r[0]){
			int sz = l[1] + r[1] + 1; 
			large = max(large, sz); 
			return{ true, sz }; 
		}

		return{ false, 0 }; 
	}
};


// pass
class Solution5 {
public:
	int largestBSTSubtree(TreeNode* root){
		int res = 0; 
		large(root, res); 
		return res; 
	}

	vector<int> large(TreeNode *node, int& lgstSz){
		if (!node)
			return{ 0, 0, 0 }; 

		vector<int> l = large(node->left, lgstSz),
			r = large(node->right, lgstSz); 

		if (l[0] == -1 || r[0] == -1 || 
			(node->left && node->val <= l[2]) ||
			(node->right && node->val >= r[1])
			)
			return{ -1, 0, 0 }; 

		int sz = l[0] + r[0] + 1; 
		lgstSz = max(lgstSz, sz); 
		int leftboundary = node->left ? l[1] : node->val,
			rightboundary = node->right ? r[2] : node->val; 

		return{ sz, leftboundary, rightboundary }; 
	}
};


class Solution6 {
public:
	int largestBSTSubtree(TreeNode* root){
		int res = 0; 
		dfs(root, res); 
		return res; 
	}

	vector<int> dfs(TreeNode* n, int& res){
		// size, left boundary, right boundary
		if (!n) return{ 0, 0, 0 }; 
		vector<int> rl = dfs(n->left, res), rr = dfs(n->right, res); 
		if (!rl[0] || !rr[0] ||
			(n->left && n->val <= rl[2]) ||
			(n->right && n->val >= rr[1])
			)
			return{ 0, -1, -1 }; 

	}
};



int main(){
	Solution a; 
	Solution5 a3; 

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(9),
											new TreeNode(4)),
									new TreeNode(8, new TreeNode(7),
											new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/
	TreeNode* tree2 = new TreeNode(1, new TreeNode(2), nullptr); 

	cout << a.largestBSTSubtree(tree2) <<endl; 
	cout << a3.largestBSTSubtree(tree2) <<endl; 


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}