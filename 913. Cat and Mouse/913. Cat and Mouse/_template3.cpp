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

// 44/45 test cases passed. this is the typical DFS logic. Not sure if it is correct. 
class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
		int n = graph.size(); 
		vector<VVI> m(n, VVI(n, VI(2, -1))); 
		// 0 - mouse move, 1 - cat move
		return dfs(1, 2, 0, graph, m, 0); 
    }

	int dfs(int m_pos, int c_pos, int cur_p, VVI& graph, vector<VVI>& m, int mouse_steps){
		if (m[m_pos][c_pos][cur_p] != -1)
			return m[m_pos][c_pos][cur_p];

		if (m_pos == 0)
			return 1; // mouse win
		if (c_pos == m_pos)
			return 2; // cat win
		if (mouse_steps == graph.size() + 1) // draw 
			return 0; 

		// mouse move
		if (cur_p == 0){
			bool is_draw_possible = false; 
			for (int nxt : graph[m_pos]){
				int nxt_res = dfs(nxt, c_pos, 1, graph, m, mouse_steps+1); 
				if (nxt_res == 1){ // if cat result is Mouse Win, then mouse indeed win in this round as well. 
					m[m_pos][c_pos][cur_p] = 1; 
					return 1; 
				}
				if (nxt_res == 0)
					is_draw_possible = true; 
			}
			m[m_pos][c_pos][cur_p] = is_draw_possible ? 0 : 2; 
			return m[m_pos][c_pos][cur_p]; 
		}
		else{
			bool is_draw_possible = false; 
			for (int nxt : graph[c_pos]){
				int nxt_res = dfs(m_pos, nxt, 0, graph, m, mouse_steps);
				if (nxt_res == 2){
					m[m_pos][c_pos][cur_p] = 2; 
					return 2; 
				}
				if (nxt_res == 0)
					is_draw_possible = true;
			}
			m[m_pos][c_pos][cur_p] = is_draw_possible ? 0 : 1; 
			return m[m_pos][c_pos][cur_p]; 
		}
	}
};





int main(){
	Solution a;

	VVI g = {
		{2,5},{3},{0,4,5},{1,4,5},{2,3},{0,2,3}
	};

	cout << a.catMouseGame(g) << endl; 

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

