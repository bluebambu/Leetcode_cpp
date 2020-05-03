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

// 输入一些 parent-child pairs, 然后给一个pair, 判断他们是否genetically related. 
// 比如(p1, c1)表示p1生了c1, c1有p1的gene. 输入(p1, c1), (p2, c1), (p1, c2), (p2, c2). 
class Solution {
public:
	int dist_of_relation(vector<vector<string>> family, string p1, string p2){
		// family[i]: <parent, child> 
		unordered_map<string, unordered_set<string>> c2p; 
		for (auto& v : family){
			c2p[v[1]].insert(v[0]); 
		}

		unordered_map<string, int> processed_name; 
		queue<pair<string, int>> q; 
		q.push({ p1, 0 }); 
		q.push({ p2, 0 }); 

		while (!q.empty()){
			auto f = q.front(); 
			q.pop(); 
			string curp = f.first; 
			int d = f.second; 
			if (processed_name.count(curp)){
				return processed_name[curp] + d; 
			}

			processed_name[curp] = d; 

			for (string nxt : c2p[curp]){
				q.push({nxt, d+1});
			}
		}

		return -1; 
	}
};


class Solution2 {
public:
	vector<string> dist_of_relation(vector<vector<string>> family, string p1, string p2){
		// family[i]: <parent, child> 
		unordered_map<string, unordered_set<string>> c2p;
		for (auto& v : family){
			c2p[v[1]].insert(v[0]);
		}

		unordered_map<string, int> processed_name;
		queue<pair<string, int>> q;
		q.push({ p1, 0 });
		q.push({ p2, 0 });
		processed_name[p1] = 0;
		processed_name[p2] = 0;

		vector<string> lca;
		while (!q.empty()){
			auto f = q.front();
			q.pop();
			string curp = f.first;
			int d = f.second;

			bool foundLCA = false;
			for (string nxt : c2p[curp]){
				if (processed_name.count(nxt)){
					lca.push_back(nxt);
					foundLCA = true;
				}
				else{
					processed_name[nxt] = d + 1;
				}
				q.push({ nxt, d + 1 });
			}

			if (foundLCA)
				return lca;
		}

		return{};
	}
};

int main(){
	Solution a;

	vector<vector<string>> f = {
		{ "mom", "david" },
		{ "dad", "david" },
		{ "dad", "mary" },
		{ "mom", "mary" },
		{ "grandpa", "dad" },
		{ "grandma", "dad" },
	}; 

	cout << a.dist_of_relation(f, "david", "dad") << endl; 



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

