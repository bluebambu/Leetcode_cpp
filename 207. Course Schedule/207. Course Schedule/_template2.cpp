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


//pass AC

// cycle detection needs more than normal dfs, more than 0,1 two status. 

// DFS
class Solution {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<int> status(numCourses, 0);

		bool res = false;
		for (int i = 0; i < numCourses; ++i){
			if (status[i] == 0){
				res |= dfs(i, status, prerequisites);
			}
		}
		return res == false;
	}

	bool dfs(int cur, vector<int>& status, vector<pair<int, int>>& pre){
		if (status[cur] == -1)
			return false;
		if (status[cur] == 1)
			return true;

		bool res = false;

		status[cur] = 1;
		for (auto i : pre){
			if (i.first == cur){
				res |= dfs(i.second, status, pre);
			}
		}
		status[cur] = -1;
		return res;
	}
};

// wrong ans
class Solution2 {
public:
	typedef pair<int, int> PII; 

	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<int> status(numCourses, 0); 

		bool res = false;
		for (int i = 0; i < numCourses; ++i){
			if (status[i] == 0){
				res |= bfs(i, status, prerequisites); 

				for (int j = 0; j < numCourses; ++j){
					if (status[j] == 1)
						status[j] = -1; 
				}
			}
		}
		return res == false; 
	}

	bool bfs(int start, vector<int>& status, vector<PII>& pre){
		queue<int> q; 
		q.push(start); 
		status[start] = 1; 

		while (!q.empty()){
			int front = q.front(); 
			q.pop(); 

			for (auto i : pre){
				if (i.first == front){
					if (status[i.second] == 1)
						return true; 
					if (status[i.second]==-1)
						continue;

					status[i.second] = 1; 
					q.push(i.second); 
				}
			}
		}
		return false; 
	}
};


class Solution3 {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		unordered_map<int, unordered_set<int>> prerq; 
		unordered_map<int, int> inorder; 
		unordered_map<int, int> status; 
		for (auto& p : prerequisites){
			prerq[p.second].insert(p.first); 
			inorder[p.second]; 
			inorder[p.first] += 1; 
			status[p.first] = 0; 
			status[p.second] = 0; 
		}

		for (auto& i : inorder){
			int course = i.first, cnt = i.second; 
			if (status[course] == 0){
				if (!noCycle(prerq, status, course))
					return false; 
			}
		}

		return true; 
	}

	bool noCycle(unordered_map<int, unordered_set<int>>& prerq,
		unordered_map<int, int>& status,
		int course
		) {
		if (status[course] == 1)
			return true; 
		if (status[course] == -1)
			return false; 

		status[course] = -1; 

		for (auto& next : prerq[course]){
			if (!noCycle(prerq, status, next))
				return false; 
		}

		status[course] = 1; 

		return true;
	}
}; 


class Solution4 {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		unordered_map<int, unordered_set<int>> m; 
		unordered_map<int, int> inorder; 

		for (auto& p : prerequisites){
			m[p.second].insert(p.first); 
			inorder[p.first] += 1; 
			inorder[p.second]; 
		}

		queue<int> q; 
		int visited = 0; 
		for (auto& p : inorder){
			int course = p.first, cnt = p.second; 
			if (cnt == 0)
				q.push(course); 
		}

		while (!q.empty()){
			int f = q.front(); 
			q.pop(); 
			++visited; 

			for (auto& next : m[f]){
				inorder[next] -= 1; 
				if (inorder[next] == 0)
					q.push(next); 
			}
		}

		return q.empty() && visited == inorder.size(); 
	}
}; 


class Solution5 {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		unordered_map<int, unordered_set<int>> g; 
		unordered_map<int, int> indegree; 
		for (auto p : prerequisites){
			g[p.second].insert(p.first); 
			indegree[p.first] += 1; 
		}

		queue<int> q; 
		for (int i = 0; i < numCourses; ++i)
			if (indegree[i] == 0)
				q.push(i); 

		int cnt = 0; 
		while (!q.empty()){
			int f = q.front(); 
			q.pop(); 
			++cnt; 

			for (int next : g[f]){
				indegree[next] -= 1; 
				if (indegree[next] == 0){
					q.push(next); 
				}
			}
		}

		return cnt == numCourses; 
	}
}; 

class Solution6 {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		unordered_map<int, unordered_set<int>> g; 
		vector<int> status(numCourses, 0); 
		for (auto v : prerequisites){
			g[v.second].insert(v.first); 
		}

		for (int i = 0; i < numCourses; ++i){
			if (status[i] == 0){
				if (!no_cycle(g, i, status))
					return false; 
			}
		}

		return true; 
	}
	typedef vector<int> VI; 

	bool no_cycle(unordered_map<int, unordered_set<int>>& g, int i, VI& status){
		status[i] = -1; 
		for (int next : g[i]){
			if (status[next]==1)
				continue;
			if (status[next] == -1)
				return false; 
			if (!no_cycle(g, next, status))
				return false; 
		}
		status[i] = 1; 
		return true; 
	}
}; 


class Solution7 {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		unordered_map<int, unordered_set<int>> g; 
		for (auto& p : prerequisites)
			g[p.first].insert(p.second); 

		vector<int> status(numCourses, 0); 
		for (int i = 0; i < numCourses; ++i){
			if (status[i] == 0 && !dfs(i, g, status))
				return false; 
		}
		return true; 
	}
	bool dfs(int i, unordered_map<int, unordered_set<int>>& g, vector<int>& status){
		status[i] = -1; 
		for (int nxt : g[i]){
			if (status[nxt] == -1)
				return false; 
			if (status[nxt])
				continue;
			else if (!dfs(nxt, g, status))
				return false; 
		}
		status[i] = 1; 
		return true; 
	}
}; 


class Solution8 {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		unordered_map<int, unordered_set<int>> g; 
		unordered_map<int, int> indegree; 
		for (auto& p : prerequisites){
			g[p.first].insert(p.second); 
			indegree[p.second] += 1; 
			indegree[p.first]; 
		}

		vector<int> topo; 
		queue<int> q; 
		for (int i = 0; i < numCourses; ++i){
			if (indegree[i] == 0)
				q.push(i); 
		}

		while (!q.empty()){
			int f = q.front(); 
			q.pop(); 
			topo.push_back(f); 

			for (int nxt : g[f]){
				indegree[nxt] -= 1; 
				if (indegree[nxt] == 0){
					q.push(nxt); 
				}
			}
		}

		return topo.size() == numCourses; 
	}
};



int main(){
	Solution a; 
	Solution6 a2; 
	vector<pair<int, int>> b = { { 0, 1 }, { 0, 2 }, { 3, 4 }, { 1, 4 }, { 2, 3 }, { 4, 0 } };
	vector<pair<int, int>> c = { { 0, 1 }, { 0, 2 }, { 1, 2 } }; 
	vector<pair<int, int>> d = { { 0, 1 }, { 1, 0 } };

	cout << a.canFinish(5, b)<<endl; 
	cout << a2.canFinish(5, b)<<endl; 

	cout << a.canFinish(3, c)<<endl; 
	cout << a2.canFinish(3, c)<<endl; 

	cout << a.canFinish(3, d)<<endl; 
	cout << a2.canFinish(3, d)<<endl; 
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

