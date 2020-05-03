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
	bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
		unordered_map<int, unordered_set<int>> g; 
		unordered_map<int, int> indegree; 
		for (auto& s : seqs){
			for (int i = 0; i < s.size(); ++i){
				g[s[i]]; 
				if (i + 1 < s.size()){
					if (g[s[i]].count(s[i+1])==0) // important and tricky!
						indegree[s[i + 1]] += 1;
					g[s[i]].insert(s[i + 1]);
					g[s[i + 1]]; 
				}
			}
		}

		if (g.size() != org.size())
			return false; 

		queue<int> q; 
		vector<int> topo; 
		for (auto p : g){
			if (indegree[p.first] == 0){
				q.push(p.first);
				topo.push_back(p.first); 
			}
		}

		if (topo.size() != 1) return false; 

		while (!q.empty()){
			// right statement
			if (q.size() != 1)
				return false; 

			int cur = q.front(); 
			q.pop(); 

			int cnt = 0; 
			for (auto nxt : g[cur]){
				indegree[nxt] -= 1; 
				if (indegree[nxt] == 0){
					cnt += 1; 
					q.push(nxt); 
					topo.push_back(nxt); 
				}
			}
			// wrong statement!! 
			// if (topo.size()!=org.size() && cnt != 1) 
			// 	return false; 
		}

		return topo == org; 
	}
};

int main(){
	Solution a; 

	vector<int> b = { 1, 2, 3 }; 
	vector<vector<int>> c = { { 1, 2 }, { 1, 3 } };

	vector<int> d = { 4, 1, 5, 2, 6, 3 }; 
	vector<vector<int>> e = { { 5, 2, 6, 3 }, { 4, 1, 5, 2 } };
	cout << a.sequenceReconstruction(d, e) << endl; 


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

