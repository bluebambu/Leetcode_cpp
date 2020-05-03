// _template4.cpp : Defines the entry point for the console application.
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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		unordered_map<int, unordered_map<int, int>> g; 
		for (auto& f : flights){
			g[f[0]][f[1]] = f[2]; 
		}

		queue<vector<int>>	q; 
		q.push({src, 0}); 
		unordered_map<int, int> v; 
		v.insert({ src, 0 });
		int stops = 0;

		int res = INT_MAX; 

		while (!q.empty()){
			int sz = q.size(); 
			++stops;
			if (stops > K + 1) break;

			for (int i = 0; i < sz; ++i){
				auto f = q.front(); 
				q.pop(); 

				for (auto& p: g[f[0]]){
					int nxt = p.first; 
					int curdist = g[f[0]][nxt]; 
					if (nxt == dst){
						res = min(res, f[1] + curdist); 
						continue;
					}
					if (f[1] + curdist > res)
						continue;
					if (!v.count(nxt) || v[nxt]>curdist + f[1]){
						v[nxt] = curdist + f[1]; 
						q.push({ nxt, v[nxt] }); 
					}
				}
			}
		}

		return res == INT_MAX ? -1 : res;
    }
};

// wrong ans
class Solution2 {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		unordered_map<int, unordered_map<int, int>> graph; 
		for (int i = 0; i < flights.size(); ++i){
			graph[flights[i][0]][flights[i][1]] = flights[i][2]; 
		}

		int steps = 0; 
		vector<int> dist(n, INT_MAX); 
		dist[src] = 0; 

		queue<int> q; 
		q.push(src); 

		while (!q.empty() && steps < K+1){
			int sz = q.size(); 
			for (int i = 0; i < sz; ++i){
				int top = q.front(); 
				q.pop(); 

				for (auto& p: graph[top]){
					int curDist = p.second, nxt = p.first; 
					if (curDist + dist[top] < dist[nxt]){
						dist[nxt] = curDist + dist[top]; 
						q.push(nxt);
					}
				}
			}

			++steps; 
		}

		return dist[dst] == INT_MAX ? -1 : dist[dst]; 
	}
};


class Solution3 {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		unordered_map<int, unordered_map<int, int>> graph; 
		for (auto& v : flights){
			graph[v[0]][v[1]] = v[2]; 
		}

		int steps = 0; 
		queue<vector<int>> q; 
		q.push({ src, 0 }); 
		int res = INT_MAX; 
		unordered_map<int, int> cache; 

		while (!q.empty() && steps < K+1){
			int sz = q.size(); 
			while (sz--){
				vector<int> f = q.front(); 
				q.pop(); 
				int cur = f[0], d = f[1]; 

				for (auto& p : graph[cur]){
					int nxt = p.first, dist = p.second; 
					if (nxt == dst)
						res = min(res, d + dist); 
					if (!cache.count(nxt) || cache[nxt] > d + dist){
						cache[nxt] = d + dist; 
						q.push({ nxt, d + dist });
					}
				}
			}
			++steps; 
		}

		return res == INT_MAX ? -1 : res; 
	}
}; 

class Solution4 {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		unordered_map<int, unordered_map<int, int>> graph; 
		for (auto& v : flights)
			graph[v[0]][v[1]] = v[2]; 

		vector<int> dist(n, INT_MAX); 
		dist[src] = 0; 
		set<vector<int>> pq; 
		pq.insert({ 0, src, 0 }); 
		int res = INT_MAX; 

		while (!pq.empty()){
			auto f = *(pq.begin()); 
			pq.erase(pq.begin()); 
			int d = f[0], cur = f[1], step = f[2]; 
			if (cur == dst) return d; 
			if (step==K+1)continue;
			
			for (auto& p : graph[cur]){
				int nxt = p.first, dist = p.second; 
				pq.insert({ d + dist, nxt, step + 1 }); 
			}
		}

		return res == INT_MAX ? -1 : res; 
	}
};

class Solution5 {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		unordered_map<int, unordered_map<int, int>> g; 
		for (auto& f : flights)
			g[f[0]][f[1]] = f[2]; 

		queue<vector<int>> q; // [step, sum, vertice]
		q.push({ 0, src, 0 }); 

		int res = INT_MAX; 
		while (!q.empty()){
			auto f = q.front(); 
			q.pop(); 
			if (f[0] == K) continue;; 
			int step = f[0], sum = f[1], cur = f[2]; 

			for (auto& p : g[cur]){
				int nxt = p.first, dist = p.second; 
				if (nxt == dst)
					res = min(res, sum + dist); 
				q.push({ step + 1, sum + dist, nxt }); 
			}
		}

		return res==INT_MAX ? 0: res; 
	}
};

int main(){
	Solution a;
	Solution5 a2;

	vector<vector<int>> edge = {
		{ 0, 1, 100 },
		{ 1, 2, 100 },
		{ 0, 2, 500 }
	};

	cout << a.findCheapestPrice(3, edge, 0, 2, 1) << endl; 
	cout << a2.findCheapestPrice(3, edge, 0, 2, 1) << endl; 

	cout << a.findCheapestPrice(3, edge, 0, 2, 0) << endl; 
	cout << a2.findCheapestPrice(3, edge, 0, 2, 0) << endl; 

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9,
		                               new TreeNode(10),
		                               nullptr)));
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

