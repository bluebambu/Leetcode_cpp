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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


// 0-empty, 1-obstacle, 2-people, 3-bikes
class Solution {
public:
	int kpeople_bf(VVI& people, VVI& bikes){
		int res = INT_MAX; 
		unordered_set<int> vp, vb; 
		dfs(people, bikes, vp, vb, 0, res); 
		return res;
	}

	void dfs(VVI& p, VVI& b, unordered_set<int>& vp, unordered_set<int>& vb, int sum, int& res){
		if (vp.size() == p.size()){
			res = min(res, sum); 
			return; 
		}
	
		for (int i = 0; i < p.size(); ++i){
			if (vp.count(i))
				continue;

			vp.insert(i);
			for (int j = 0; j < b.size(); ++j){
				if (vb.count(j))
					continue;

				int d = dist(p[i], b[j]);
				vb.insert(j); 
				sum += d; 
				dfs(p, b, vp, vb, sum, res); 
				sum -= d; 
				vb.erase(j); 
			}
			vp.erase(i); 
		}
	}

	int dist(vector<int>& a, vector<int>& b){
		return abs(a[0] - b[0]) + abs(a[1] - b[1]); 
	}
};

// use PQ 
class Solution2 {
public:
	int dist(vector<int>& a, vector<int>& b){
		return abs(a[0] - b[0]) + abs(a[1] - b[1]); 
	}

	VVI bikeMatch(VVI& people, VVI& bikes){ 
		unordered_set<int> vp, vb; 
		set<vector<int>> pq; 
		for (int i = 0; i < people.size(); ++i){
			for (int j = 0; j < bikes.size(); ++j){
				pq.insert({ dist(people[i], bikes[j]), i, j }); 
			}
		}

		VVI res; 
		int tot = 0; 
		while (!pq.empty() && vp.size() < people.size()){
			vector<int> f = *(pq.begin()); 
			int d = f[0], pid = f[1], bid = f[2]; 
			if (!vp.count(pid) && !vb.count(bid)){
				res.push_back({ pid, bid }); 
				tot += dist(people[pid], bikes[bid]);
				vp.insert(pid); 
				vb.insert(bid); 
			}
			pq.erase(pq.begin()); 
		}
		return res; 
	}
};

class Solution4 {
public:
	VVI bikeMatch(VVI& people, VVI& bikes){
		VVI res; 
		unordered_set<int> vp, vb; 
		int mindist = INT_MAX; 
		dfs(people, bikes, vp, vb, 0, {}, mindist,res);
		return res; 
	}
	void dfs(VVI& peoples, VVI& bikes, unordered_set<int>& vp, unordered_set<int>& vb, int tot, VVI path, int& mindist, VVI& res){
		int n = peoples.size(), m = bikes.size(); 
		if (vp.size() == n || vb.size() == m){
			if (tot < mindist){
				mindist = tot; 
				res = path; 
				return; 
			}
		}

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (!vp.count(i) && !vb.count(j)){
					vp.insert(i), vb.insert(j); 
					VVI copy = path; 
					copy.push_back({ i, j }); 
					int curdist = dist(peoples[i], bikes[j]); 
					dfs(peoples, bikes, vp, vb, tot + curdist, copy, mindist, res); 
					vp.erase(i), vb.erase(j); 
				}
			}
		}
	}
	int dist(vector<int>& a, vector<int>& b){
		return abs(a[0] - b[0]) + abs(a[1] - b[1]); 
	}
}; 

class Solution5 {
public:
	int dist(vector<int>& a, vector<int>& b){
		return abs(a[0] - b[0]) + abs(a[1] - b[1]); 
	}
	VVI bikeMatch(VVI& people, VVI& bikes){
		int n = people.size(), m = bikes.size(); 
		vector<set<vector<int>>> p_dists(n); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				p_dists[i].insert({ dist(people[i], bikes[j]), i, j }); 
			}
		}

		VVI res; 
		unordered_set<int> vp, vb; 
		int mindist = INT_MAX; 
		dfs(people, bikes, p_dists, vp, vb, 0, {}, mindist,res);
		return res; 
	}
	void dfs(VVI& peoples, VVI& bikes, vector<set<vector<int>>>& p_dists, unordered_set<int>& vp, unordered_set<int>& vb, int tot, VVI path, int& mindist, VVI& res){
		int n = peoples.size(), m = bikes.size(); 
		while (vp.size() < n && vb.size() < m){
			set<vector<int>> closest;
			for (int i = 0; i < p_dists.size(); ++i){
				closest.insert(*p_dists[i].begin());
			}
			vector<int> farthest = *(--closest.end());
			closest.erase(--closest.end());
			if (!vp.count(farthest[1] && !vb.count(farthest[2]))){
				vp.insert(farthest[1]);
				vb.insert(farthest[2]);
				closest.insert(next(p_dists[farthest[1]].begin()));
				p_dists[farthest[1]].erase(p_dists[farthest[1]].begin());
				path.emplace_back(farthest.begin() + 1, farthest.end());
			}
		}
		res = path; 
	}
}; 

// 10020000000
// 00000001000
// 20000200000
// 00000000200
// 00000100000
int main(){
	Solution4 a;

	vector<vector<int>> p = { { 0, 0 }, { 4, 5 }, {1, 7} },
		b = { { 0, 3 }, { 2, 0 }, { 3, 8 }, {2, 5} };

	auto c = a.bikeMatch(p, b); 
	prt2Layer(c); 

	// orig coord
	cout << "======= Orig Coord =============\n"; 
	set<VVI> test; 
	test.insert(p); 
	test.insert(b); 

	for (auto i : test)
		prt2Layer(i);

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

