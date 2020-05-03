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


struct TreeNode {
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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


class Solution {
public:
	int BellmanFord(VVI graph, int k, int s){
		int n = graph.size();
		vector<int> dist(n, INT_MAX);
		dist[k] = 0;

		for (int i = 0; i < n; ++i){
			bool changed = false;
			for (int i = 0; i < graph.size(); ++i){
				for (int j = 0; j < graph[i].size(); ++j){
					if (graph[i][j]){
						// dist[i] != INT_MAX is used to pass those unprocessed from nodes. 
						if (dist[i] != INT_MAX && dist[j] > dist[i] + graph[i][j]){
							dist[j] = dist[i] + graph[i][j];
							changed = true;
						}
					}
				}

				if (!changed) return dist[s];
				if (i == graph.size() - 1 && changed) return -1;
			}
		}

		return -1;
	}


	int SPFA(VVI graph, int k, int s){
		queue<int> q; 
		int n = graph.size(); 
		vector<int> status(n, 0), dist(n, INT_MAX), cnt(n, 0); 
		dist[k] = 0; 

		status[k] = 1; 
		cnt[k] = 1;
		q.push(k); 

		while (!q.empty()){
			int f = q.front(); 
			q.pop();
			status[f] = 0; 
			
			for (int i = 0; i < graph[f].size(); ++i){
				if (graph[f][i] && dist[i] > dist[f] + graph[f][i]){
					dist[i] = dist[f] + graph[f][i]; 
					if (!status[i]){
						q.push(i); 
						status[i] = 1; 
						cnt[i] += 1; 
						if (cnt[i] > n)
							return -1; 
					}
				}
			}
		}

		return dist[s]; 
	}

	int dag(VVI graph, int k, int s){
		int n = graph.size(); 
		vector<int> dist(n, INT_MAX), indegree(n, 0); 
		dist[k] = 0; 

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if (graph[i][j])
					indegree[j] += 1; 
			}
		}

		queue<int> q;
		for (int i = 0; i < n; ++i)
			if (!indegree[i])
				q.push(i); 

		while (!q.empty()){
			int f = q.front(); 
			q.pop(); 

			for (int j = 0; j < graph[f].size(); ++j){
				if (graph[f][j]){
					if (dist[f] != INT_MAX && dist[j] > dist[f] + graph[f][j]){
						dist[j] = dist[f] + graph[f][j]; 
					}
					indegree[j]--; 
					if (indegree[j] == 0){
						q.push(j); 
					}
				}
			}
		}

		return dist[s]; 
	}

	int floyd(VVI graph, int s, int t){
		int n = graph.size(); 
		VVI dist(n, VI(n, INT_MAX)); 

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				for (int k = 0; k < n; ++k){
					if (dist[j][i] != INT_MAX && dist[i][k] != INT_MAX && dist[j][k] > dist[j][i] + dist[i][k]){
						dist[j][k] = dist[j][i] + dist[i][k]; 
						if (j == k && dist[j][k]<0){ // this means negative ring exist. 
							return false; 
						}
					}
				}
			}
		}

		return dist[s][t]; 
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

