// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <assert.h>
#include <functional>
#include <stdio.h>
#include <float.h>
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
#include <ctime>
#include <random>

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

class Graph{
public:
	vector<vector<int>> g; 
	int n; 
	vector<int> dist; 
	vector<int> parent; 

	Graph(vector<vector<int>>& x) :g(x), n(x.size()), dist(n, INT_MAX), parent(n, -1) {}

	int shortestLength(int from, int to){
		dist[from] = 0; 

		typedef int len; 
		typedef int idx; 
		typedef pair<len, idx> node; 
		set<pair<len, idx>> pq; 
		pq.insert({ 0, from }); 

		while (!pq.empty()){
			node front = *(pq.begin()); 
			pq.erase(pq.begin()); 

			int curDist = front.first,
				curIdx = front.second; 
			for (int ii = 0; ii < n; ++ii){
				if (g[curIdx][ii]>-1 && (dist[ii] > dist[curIdx] + g[curIdx][ii])){
					int old = dist[ii]; 
					dist[ii] = dist[curIdx] + g[curIdx][ii];
					parent[ii] = curIdx; 
					if (pq.count({ old, ii }))
						pq.erase({ old, ii });
					// else
					// after deleting the duplicate node, you need to update it and push it back!!!
					pq.insert({ old, ii });
				}
			}
		}

		return dist[to]; 
	}
	
	vector<int> path(int from, int to){
		if (dist[from] != 0)
			shortestLength(from, to); 

		vector<int> res; 
		while (to != -1){
			res.push_back(to); 
			to = parent[to]; 
		}
		reverse(res.begin(), res.end()); 
		return res; 
	}

};


class Dijkstra{
public:
	vector<vector<int>> g;
	vector<int> parent; 

	Dijkstra(vector<vector<int>> x) :g(x),parent(g.size(), -1) {}

	int distance(int from, int to){
		int n = g.size(); 
		vector<int> dist(n, INT_MAX); 
		dist[from] = 0; 

		set<pair<int, int>, greater<pair<int, int>>> que; 
		que.insert({ 0, from }); 

		while (!que.empty()){
			int d = (*(--que.end())).first,
				i = (*(--que.end())).second; 
			que.erase(--que.end());

			for (int j = 0; j < n; ++j){
				if (g[i][j] > -1 && dist[j] > d + g[i][j]){
					if (que.count({ dist[j], j }))
						que.erase({ dist[j], j });
					dist[j] = d + g[i][j]; 
					que.insert({ dist[j], j }); 
					parent[j] = i; 
				}
			}
		}
		return dist[to]; 
	}

	vector<int> path(int from, int to){
		distance(from, to);

		vector<int> res; 
		while (to != -1){
			res.push_back(to); 
			to = parent[to]; 
		}
		reverse(res.begin(), res.end());
		return res; 
	}
};


class Dijkstra5{
	vector<vector<int>> g; 
	vector<int> dist;
	vector<int> parent; 
	int n; 
public:
	Dijkstra5(vector<vector<int>>& x) :g(x),n(x.size()),dist(x.size(), INT_MAX),parent(x.size(), -1) {}

	int path(int i, int k){
		dist[i] = 0; 
		multiset<pair<int, int>> que; 
		que.insert({ 0, i }); 

		while (!que.empty()){
			int curDist = que.begin()->first; 
			int curIdx = que.begin()->second; 
			que.erase(que.begin()); 

			for (int j = 0; j < n; ++j){
				if (g[curIdx][j] > 0 && curDist + g[curIdx][j] < dist[j]){
					int oldDist = dist[j]; 
					dist[j] = curDist + g[curIdx][j]; 
					parent[j] = curIdx; 
					if (que.count({ oldDist, j }))
						que.erase(que.find({ oldDist, j })); 
					que.insert({ dist[j], j }); 
				}
			}
		}

		return dist[k];
	}

};


int main(){
	vector<vector<int>> x(7, vector<int>(7, -1)); 
	int n = x.size(); 
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if (i == j){
				x[i][j] = 0; 
				continue;
			}
			if (rand() % 2)
				x[i][j] = rand() % 10 + 1; 
		}
	}


	vector<vector<int>> y = {
		{ -1, 1, 10, -1, -1},
		{ -1, -1, -1, 1, -1 },
		{ -1, -1, -1, -1, 5 },
		{ -1, -1, 1, -1, -1 },
		{ -1, -1, -1, -1, -1 },
	};

	Dijkstra5 a(y); 

	cout << a.path(0, 4)<<endl; 

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

