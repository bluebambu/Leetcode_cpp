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

// pass
class Solution {
public:
	typedef unordered_map<TreeNode*, unordered_set<TreeNode*>> G;
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
		if(K==0)
            return {target->val}; 
		G g; 
		conn(root, g); 

		queue<TreeNode*> q; 
		unordered_set<TreeNode*> v; 
		q.push(target); 
		v.insert(target); 
		int dist = 0; 
		vector<int> res; 
		while (!q.empty()){
			int sz = q.size(); 
			++dist; 
			for (int i = 0; i < sz; ++i){
				TreeNode* f = q.front(); 
				q.pop(); 

				for (TreeNode *nxt : g[f]){
					if (!v.count(nxt) && dist == K){
						res.push_back(nxt->val); 
					}
					if (!v.count(nxt)){
						v.insert(nxt); 
						q.push(nxt);
					}
				}
			}
			if (dist == K)
				return res; 
		}

		return res;
    }
	void conn(TreeNode* node, G& g){
		if (!node)
			return; 
		if (node->left){
			g[node].insert(node->left); 
			g[node->left].insert(node); 
		}
		if (node->right){
			g[node].insert(node->right); 
			g[node->right].insert(node); 
		}
		conn(node->left, g); 
		conn(node->right, g); 
	}
};

// pass
class Solution2 {
public:
	typedef unordered_map<TreeNode*, unordered_set<TreeNode*>> G;
	vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
		G g;
		build(root, g); 

		queue<pair<TreeNode*, int>> q; 
		q.push({ target, 0 }); 
		unordered_set<TreeNode*> v; 
		v.insert(target); 

		vector<int> res; 
		while (!q.empty()){
			auto f = q.front(); 
			q.pop(); 
			TreeNode *cur = f.first; 
			int dist = f.second; 
			if (dist == K){
				res.push_back(cur->val); 
				continue;
			}

			for (TreeNode *nxt : g[cur]){
				if (!v.count(nxt)){
					q.push({ nxt, dist + 1 }); 
					v.insert(nxt); 
				}
			}
		}

		return res; 
	}

	void build(TreeNode *n, unordered_map<TreeNode*, unordered_set<TreeNode*>>& g){
		if (!n) return; 
		if (n->left){
			g[n->left].insert(n); 
			g[n].insert(n->left); 
		}
		if (n->right){
			g[n->right].insert(n); 
			g[n].insert(n->right); 
		}

		build(n->left, g); 
		build(n->right, g); 
	}
};


// pass 56%
class Solution3 {
public:
	typedef unordered_map<TreeNode*, unordered_set<TreeNode*>> G;
	vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
		G g; 
		dfs(root, g); 
		if (g.count(target) == 0) return{}; 

		queue<TreeNode*> q; 
		q.push(target); 
		vector<int> res; 
		int dist = 0; 
		unordered_set<TreeNode*> v; 
		v.insert(target); 

		while (!q.empty()){
			int sz = q.size(); 
			while (sz--){
				auto f = q.front(); 
				q.pop(); 
				if (dist == K){
					res.push_back(f->val); 
					continue;
				}

				for (auto& nxt : g[f]){
					if (!v.count(nxt)){
						v.insert(nxt); 
						q.push(nxt); 
					}
				}
			}
			++dist;
		}
		return res;
	}

	void dfs(TreeNode* n, G& g){
		if (!n) return; 
		if (n->left){
			g[n].insert(n->left); 
			g[n->left].insert(n); 
		}
		if (n->right){
			g[n].insert(n->right); 
			g[n->right].insert(n); 
		}

		dfs(n->left, g); dfs(n->right, g); 
	}
};



int main(){
	Solution3 a;

	vector<int> b = { 4, 1, -9, 0, INT_MAX };


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode *tgt = new TreeNode(1); 
	TreeNode* tree = new TreeNode(6, new TreeNode(3, tgt,
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	auto r = a.distanceK(tree, tgt, 2); 
	prt1Layer(r); 



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

