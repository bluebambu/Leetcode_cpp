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

struct UndirectedGraphNode{
	int label; 
	vector<UndirectedGraphNode*> neighbors; 
	UndirectedGraphNode(int x) : label(x) {}
};

class Solution{
public:
	Solution(){}
	unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> m; 
	// dfs
	UndirectedGraphNode* cloneGraph(UndirectedGraphNode* orig){
		if (!orig)
			return nullptr; 
		if (m.count(orig) != 0)
			return m[orig]; 

		UndirectedGraphNode* copy = new UndirectedGraphNode(orig->label); 
		m[orig] = copy; 
		vector<UndirectedGraphNode*>& chref = orig->neighbors; 
		for (int i = 0; i < chref.size(); ++i){
			(copy->neighbors).push_back(cloneGraph(chref[i])); 
		}
		return copy; 
	}

	//bfs
	UndirectedGraphNode* cloneGraph2(UndirectedGraphNode* orig){
		if (!orig)
			return nullptr; 

		queue<UndirectedGraphNode*> q; 
		UndirectedGraphNode* copyroot = new UndirectedGraphNode(orig->label); 
		q.push(orig); 
		m[orig] = copyroot; 

		while (!q.empty()){
			UndirectedGraphNode* front = q.front(); 
			q.pop(); 

			vector<UndirectedGraphNode*>& chref = front->neighbors; 
			for (int i = 0; i < chref.size(); ++i){
				if (m.count(chref[i]) == 0){
					m[chref[i]] = new UndirectedGraphNode(chref[i]->label); 
					m[front]->neighbors.push_back(m[chref[i]]); 
					q.push(chref[i]); 
				}
				else{
					m[front]->neighbors.push_back(m[chref[i]]); 
				}
			}
		}
		return copyroot; 
	}
};

class Solution2{
public:
	Solution2(){}
	unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> m;
	// dfs
	UndirectedGraphNode* cloneGraph(UndirectedGraphNode* orig){
		if (!orig)
			return nullptr; 
		if (m.count(orig))
			return m[orig]; 

		auto cur = new UndirectedGraphNode(orig->label); 
		m[orig] = cur; 

		for (int i = 0; i < orig->neighbors.size(); ++i){
			(cur->neighbors).push_back(cloneGraph(orig->neighbors[i])); 
		}

		return cur; 
	}

	// not best BFS
	UndirectedGraphNode* cloneGraph2(UndirectedGraphNode* orig){
		typedef UndirectedGraphNode node; 
		node *head = new node(orig->label);; 
		queue<pair<node*, node*>> q; 
		q.push({ orig, head }); 
		m[orig] = head; 

		while (!q.empty()){
			pair<node*, node*> f = q.front(); 
			q.pop(); 

			node *old = f.first, *sec = f.second; 

			for (int i = 0; i < old->neighbors.size(); ++i){
				node *tmp; 
				if (!old->neighbors[i]){
					f.second->neighbors.push_back(nullptr); 
					continue;
				}
				if (m.count(old->neighbors[i])){
					tmp = m[old->neighbors[i]]; 
					sec->neighbors.push_back(tmp);
					continue;
				}
				else{
					tmp = new node(old->neighbors[i]->label); 
					m[old->neighbors[i]] = tmp; 
				}

				sec->neighbors.push_back(tmp); 

				q.push({ old->neighbors[i], tmp }); 
			}
		}

		return head;	
	}

	// best BFS
	UndirectedGraphNode* cloneGraph3(UndirectedGraphNode* orig){
		typedef UndirectedGraphNode node;
		node *head = new node(orig->label);;
		m[orig] = head; 

		queue<node*> q; 
		q.push(orig); 

		while (!q.empty()){
			node *f = q.front(); 
			q.pop(); 

			node *f_new = m[f]; 
			for (int i = 0; i < f->neighbors.size(); ++i){
				node *n = f->neighbors[i]; 
				if (!n)
					f_new->neighbors.push_back(nullptr); 
				else{
					if (m.count(n))
						f_new->neighbors.push_back(m[n]); 
					else{
						node *n_new = new node(n->label); 
						m[n] = n_new; 
						f_new->neighbors.push_back(m[n]); 
						q.push(n);
					}
				}
			}
		}

		return head;
	}

}; 


class Solution2{
public:
	Solution2(){}
	unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> m;
	// dfs
	UndirectedGraphNode* cloneGraph(UndirectedGraphNode* orig){
		if (!orig)
			return nullptr; 
		if (m[orig])
			return m[orig]; 

		UndirectedGraphNode *n = new UndirectedGraphNode(orig->label); 
		m[orig] = n; 
		for (auto& nxt : orig->neighbors){
			UndirectedGraphNode *copy = cloneGraph(nxt); 
			n->neighbors.push_back(copy); 
		}
		return n; 
	}

	UndirectedGraphNode *bfs(UndirectedGraphNode* orig){
		unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> hist; 
		
		queue<UndirectedGraphNode*> q; 
		UndirectedGraphNode *nroot = new UndirectedGraphNode(orig->label);
		hist[orig] = nroot; 
		q.push(orig); 

		while (!q.empty()){
			UndirectedGraphNode* f = q.front(); 
			q.pop(); 
			if (!f) continue;; 
			UndirectedGraphNode *corresp = hist[f]; 

			for (auto& nxt : f->neighbors){
				if (!nxt)
					corresp->neighbors.push_back(nullptr); 
				else if (hist[nxt])
					corresp->neighbors.push_back(hist[nxt]); 
				else{
					UndirectedGraphNode *copy = new UndirectedGraphNode(nxt->label); 
					corresp->neighbors.push_back(copy); 
				}
				q.push(nxt); 
			}
		}

		return nroot; 
	}
};



int main(int m, int k){

	Solution2 a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	UndirectedGraphNode c(0); 
	c.neighbors.push_back(&c); 
	c.neighbors.push_back(&c); 


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

