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


// my solution, not the best one. Use routes graph to solve the problem.  
class Solution {
public:
	int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
		if (S == T)
			return 0; 

		int n = routes.size(); 

		// this is the graph of routes. I hope to use stops connectivity to obtain routes connectivity, and 
		// solve the question based on routes connectivity. 
		vector<vector<bool>> g(n, vector<bool>(n, false)); 
		unordered_map<int, unordered_set<int>> stop_route; 

		for (int i = 0; i < routes.size(); ++i){
			for (auto j : routes[i]){
				stop_route[j].insert(i); 
				if (j == S || j == T){
					int other = (j == S ? T : S); 
					if (stop_route[other].count(i))
						return 1; 
				}
			}
		}

		for (int i = 0; i < routes.size(); ++i){
			for (auto j : routes[i]){
				unordered_set<int> j_group = stop_route[j]; 
				for (auto k : j_group)
					g[i][k] = g[k][i] = true; // build the routes graph.
			}
		}

		auto s_contnr = stop_route[S], t_contnr = stop_route[T]; 

		queue<int> q; 
		unordered_set<int> v; 
		for (auto e : s_contnr){
			q.push(e); 
			v.insert(e); 
		}

		prt2Layer(g); 

		int res = 1; 
		while (!q.empty()){
			int sz = q.size(); 
			for (int i = 0; i < sz; ++i){
				int cur = q.front(); 
				q.pop(); 

				for (int j = 0; j < g[cur].size(); ++j) {
					if (g[cur][j] && !v.count(j)){
						if (stop_route[T].count(j))
							return res + 1; 
						q.push(j); 
						v.insert(j);
					}
				}
			}
			++res; 
		}

		return -1; 
	}
}; 


// use buses connectivity to solve the problems. 
// pass, but only beat 4% .....
class Solution2 {
public:
	int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
		int res = 0; 
		if (S == T)
			return res; 
		queue<int> q; 
		q.push(S); 
		unordered_set<int> visited; 
		visited.insert(S); 

		unordered_map<int, unordered_set<int>> bus_route_map; 
		for (int i = 0; i < routes.size(); ++i){
			for (int j = 0; j < routes[i].size(); ++j){
				bus_route_map[routes[i][j]].insert(i); 
			}
		}

		while (!q.empty()){
			int sz = q.size(); 
			++res; 
			for (int i = 0; i < sz; ++i){
				int bus = q.front(); 
				q.pop(); 

				for (auto& rid : bus_route_map[bus]){
					for (auto& next_bus : routes[rid]){
						if (visited.count(next_bus) == 0){
							if (next_bus == T)
								return res;  
							visited.insert(next_bus); 
							q.push(next_bus); 
						}
					}
				}
			}
		}
		return -1; 
		
	}
}; 


// dijkstra, TLE when big data
class Solution3 {
public:
	int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
		unordered_map<int, unordered_set<int>> g; 
		for (auto& r : routes){
			for (int i = 0; i < r.size(); ++i){
				for (int j = i + 1; j < r.size(); ++j){
					g[r[i]].insert(r[j]); 
					g[r[j]].insert(r[i]); 
				}
			}
		}

		unordered_map<int, int> dist; 
		for (auto p : g)
			dist[p.first] = INT_MAX; 
		dist[S] = 0; 
		set<vector<int>> q; 
		q.insert({ 0, S }); 

		while (!q.empty()){
			auto f = *(q.begin()); 
			q.erase(q.begin()); 
			int d = f[0], stop = f[1]; 

			for (int nxt : g[stop]){
				int nxt_d = d + 1; 
				if (dist[nxt] > nxt_d){
					if (q.count({dist[nxt], nxt}) > 0)
						q.erase({dist[nxt], nxt});
					dist[nxt] = nxt_d; 
					q.insert({ nxt_d, nxt }); 
				}
			}
		}

		return dist[T]; 
	}
};


// pass
class Solution4 {
public:
	int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
		unordered_map<int, unordered_set<int>> bus_to_rt; 
		for (int i=0; i<routes.size(); ++i){
			for (int bus : routes[i]){
				bus_to_rt[bus].insert(i); 
			}
		}

		queue<int> q; 
		unordered_set<int> v; 
		int step = 0; 
		v.insert(S); 
		q.push(S); 

		while (!q.empty()){
			int sz = q.size(); 
			++step; 
			while (sz--){
				int f = q.front(); 
				q.pop(); 

				for (auto& route : bus_to_rt[f]){
					for (auto& nxtbus : routes[route]){
						if (nxtbus == T)
							return step; 
						if (v.count(nxtbus) == 0){
							v.insert(nxtbus); 
							q.push(nxtbus); 
						}
					}
				}
			}
		}

		return -1; 
	}
};


int main(){
	Solution a; 
	Solution4 a2; 

	vector<vector<int>> b = { { 1, 2, 7 }, { 3, 6, 7 } }; 
	vector<vector<int>> c = { { 7, 12 }, { 4, 5, 15 }, { 6 }, { 15, 19 }, { 9, 12, 15 } };

	cout << a.numBusesToDestination(c, 7, 4) << endl; 
	cout << a2.numBusesToDestination(c, 7, 4) << endl; 


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

