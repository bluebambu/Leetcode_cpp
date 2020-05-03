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
//  Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to return the root node of any one of them.

// Two trees are duplicate if they have the same structure with same node values.

// Example 1:

//         1
//        / \
//       2   3
//      /   / \
//     4   2   4
//        /
//       4

// The following are two duplicate subtrees:

//       2
//      /
//     4

// and

//     4

// Therefore, you need to return above trees' root in the form of a list.

// pass AC
class Solution {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		unordered_map<string, int> strMap; 
		vector<TreeNode*> res; 
		getDup(root, strMap, res); 
		return res; 
	}

	string getDup(TreeNode* root, unordered_map<string, int>& strMap, vector<TreeNode*>& res){
		if (root == nullptr)
			return "#"; 
		string cur = to_string(root->val) + getDup(root->left, strMap, res) + getDup(root->right, strMap, res); 
		if (strMap[cur] == 1)
			res.push_back(root); 
		strMap[cur] += 1; 
		return cur; 
	}
};

// CANNOT pass AC
class Solution {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		unordered_map<string, int> strMap; 
		vector<TreeNode*> res; 
		getDup(root, strMap, res); 
		return res; 
	}

	string getDup(TreeNode* root, unordered_map<string, int>& strMap, vector<TreeNode*>& res){
		if (root == nullptr)
			return "#"; 
		string cur = getDup(root->left, strMap, res);
		cur += to_string(root->val);
		cur += getDup(root->right, strMap, res); 		
		if (strMap[cur] == 1)
			res.push_back(root); 
		strMap[cur] += 1; 
		return cur; 
	}
};


// passAC, with "()" around each node when in-order traversing. 
class Solution {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		unordered_map<string, int> strMap;
		vector<TreeNode*> res;
		getDup(root, strMap, res);
		return res;
	}

	string getDup(TreeNode* root, unordered_map<string, int>& strMap, vector<TreeNode*>& res){
		if (root == nullptr)
			return "#";
		string cur = "(" + getDup(root->left, strMap, res);
		cur += to_string(root->val);
		cur += getDup(root->right, strMap, res) + ")";
		if (strMap[cur] == 1)
			res.push_back(root);
		strMap[cur] += 1;
		return cur;
	}
};

class Solution {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		unordered_set<TreeNode*> res; 
		unordered_map<string, TreeNode*> m; 
		post(root, m, res); 
		return vector<TreeNode*>(res.begin(), res.end());
	}

	string post(TreeNode* node, unordered_map<string, TreeNode*>& m, unordered_set<TreeNode*>& res){
		if (!node)
			return "#"; 

		string cur = to_string(node->val) + "," + post(node->left, m, res) + "," + post(node->right, m, res);
		if (m.count(cur))
			res.insert(m[cur]);
		else
			m[cur] = node; 

		return cur; 
	}
}; 


class Solution02 {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		vector<TreeNode*> res; 
		unordered_map<string, unordered_set<TreeNode*>> m; 
		serialize(root, m, res); 
		return res; 
	}

	string serialize(TreeNode* node, unordered_map<string, unordered_set<TreeNode*>>& m, vector<TreeNode*>& res){
		if (!node)
			return "#"; 
		string r = to_string(node->val) + ',' + serialize(node->left, m, res) + ',' + serialize(node->right, m, res); 
		m[r].insert(node); 
		if (m[r].size() == 2)
			res.push_back(node); 
		return r; 
	}
}

class Solution5 {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		unordered_map<string, vector<TreeNode*>> cache; 
		vector<TreeNode*> res; 
		dfs(root, cache, res); 
		return res; 
	}
	string dfs(TreeNode* root, unordered_map<string, vector<TreeNode*>>& cache, vector<TreeNode*>& res){
		if (!root) return "#"; 
		string l = dfs(root->left, cache, res),
			r = dfs(root->right, cache, res);
		string cur = to_string(root->val) + "," + l + "," + r; 
		if (cache[cur].size()==1){
			res.push_back(root); 
		}
		cache[cur].push_back(root); 
		return cur;
	}
};


int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

