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
	vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
		int n = graph.size(); 
		vector<int> outdegree(n, 0); 
		vector<vector<int>> inNodes(n, vector<int>()); 
		queue<int> q; 
		unordered_set<int> v;

		for (int i = 0; i < n; ++i){
			outdegree[i] = graph[i].size(); 
			for (int j = 0; j < graph[i].size(); ++j){
				inNodes[graph[i][j]].push_back(i); 
			}
			if (outdegree[i] == 0){
				q.push(i);
				v.insert(i);
			}
		}

		while (!q.empty()){
			int sz = q.size(); 
			for (int i = 0; i < sz; ++i){
				int cur = q.front(); 
				q.pop(); 

				for (int j = 0; j < inNodes[cur].size(); ++j){
					int in = inNodes[cur][j]; 
					outdegree[in] -= 1; 
					if (outdegree[in] == 0 && !v.count(in)){
						q.push(in); 
						v.insert(in); 
					}
				}
			}
		}

		vector<int> res(v.begin(), v.end()); 
		sort(res.begin(), res.end()); 

		return res; 
	}
};

class Solution2 {
public:
	vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
		int n = graph.size(); 
		vector<int> outdegree(n, 0); 
		vector<vector<int>> inNodes(n, vector<int>()); 
		queue<int> q; 
		unordered_set<int> v;

		for (int i = 0; i < n; ++i){
			outdegree[i] = graph[i].size(); 
			for (int j = 0; j < graph[i].size(); ++j){
				inNodes[graph[i][j]].push_back(i); 
			}
			if (outdegree[i] == 0){
				q.push(i);
				v.insert(i);
			}
		}

		while (!q.empty()){
			int cur = q.front(); 
			q.pop(); 

			for (int i = 0; i < inNodes[cur].size(); ++i){
				int in = inNodes[cur][i]; 
				outdegree[in] -= 1; 
				if (outdegree[in] == 0){
					q.push(in); 
					v.insert(in); 
				}
			}
		}

		vector<int> res(v.begin(), v.end()); 
		sort(res.begin(), res.end()); 

		return res; 
	}
};


class Solution3 {
public:
	vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
					
	}
}; 


int main(){
	Solution a; 

	vector<vector<int>> b = { { 1, 2 }, { 2, 3 }, { 5 }, { 0 }, { 5 }, {}, {} }; 

	auto c = a.eventualSafeNodes(b); 

	prt1Layer(c); 


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

