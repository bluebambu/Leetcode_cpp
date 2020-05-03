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

// UF not finished. 
// class Solution {
// public:
// 	bool tunnel(vector<vector<string>> board){
// 		map<vector<double>, vector<double>> parent; 
// 		int n = board.size(), m = board[0].size(); 
// 		for (double i = 0; i < n; ++i){
// 			for (double j = 0; j < m; ++j){
// 				if (i==0 && j==0) continue;
// 				if (i == 0 && i==n-1) set_boundary(board, i, j, parent); 
// 				if (j == 0 && j==m-1) set_boundary(board, i, j, parent); 

// 				string pattern = board[i][j]; 
// 				if (!connect(i, j, pattern, parent))
// 					return false; 
// 			}
// 		}

// 		return isConnect(board, 0, 0, n - 1, m - 1); 
// 	}

// 	bool connect(double i, double j, string p, map<vector<double>, vector<double>>& parent){
// 		vector<double> left = { i, j - 0.5 }, right = { i, j + 0.5 },
// 			up = { i - 0.5, j }, down = { i + 0.5, j }; 
// 		vector<double> cur = { i, j }; 

// 		if (p == "T"){
// 			vector<double> rl = find(parent, left),
// 				rr = find(parent, right),
// 				rd = find(parent, down); 
// 			if (rl == {-1, -1} || rr == {-1, -1} || rd == {-1, -1})
// 				return false; 

// 			if (rl == rr && rr == rd) return true; 
// 			unify(parent, rr, cur); 
// 			unify(parent, rl, cur); 
// 			unify(parent, rd, cur); 
// 			return true; 
// 		}
// 		else if (p == ""){
// 			
// 		}
// 		return false; 
// 	}
// };

//   0
// 3   1
//   2
class Solution {
public:
	unordered_map<int, unordered_map<int, int>> v; 

	bool tunnel(vector<vector<string>> board){
		int n = board.size(), m = board[0].size(); 
		return dfs(board, 0, 0, n - 1, m - 1, 0) == 1; 
	}

	int dfs(vector<vector<string>>& board, int i, int j, int ti, int tj,
		int from_dir
		){
		if (v[i][j] == 1 ) return 1; 
		if (v[i][j] == 2 ) return 2; 
		v[i][j] = 2; 

		int n = board.size(), m = board[0].size(); 
		if (i < 0 || i >= n || j < 0 || j >= m || board[i][j]=="") return false; 
		if (i == ti && j == tj) return 1; 
		
		string pattern = board[i][j]; 
		vector<int> to_dir = proc_pattern(i, j, from_dir, pattern); 
		if (to_dir[0] == -1)
			return false; 

		cout << pattern << " "; 
		prt1Layer(to_dir); 

		int res = 2;
		for (auto& d : to_dir){
			int x, y, to;
			switch (d){
			case 0:x = -1, y = 0, to = 2; break;
			case 1:x = 0, y = 1, to = 3; break;
			case 2:x = 1, y = 0, to = 0; break;
			case 3:x = 0, y = -1, to = 1; break;
			}
			int rr = dfs(board, i+x, j+y, ti, tj, to);
			if (rr == 0)
				return false;
			else if (rr == 1)
				res = 1;
		}
		v[i][j] = res; 
		return res; 
	}
	
	vector<int> proc_pattern(int i, int j, int from, string pattern){
		if (i == 0 && j == 0){
			if (pattern == "-"){
				return{ 1 };
			}
			else if (pattern == "|"){
				return{ 2 };
			}
			else if (pattern == "T"){
				return{ 1, 2 };
			}
			else if (pattern == "X"){
				return{ 1, 2 };
			}
			else if (pattern == "")
				return{ -1 };
		}

		if (pattern == "-"){
			if (from == 0 || from == 2) 
				return{ -1 };
			return from == 1 ? vector<int>({3}) : vector<int>({1});
		}
		else if (pattern == "|"){
			if (from == 1 || from == 3) 
				return{ -1 };
			return from == 2 ? vector<int>({0}) : vector<int>({2});
		}
		else if (pattern == "T"){
			if (from == 0) 
				return{ -1 };
			switch (from){
			case 1:return{ 2, 3 };
			case 2:return{ 1, 3 };
			case 3:return{ 1, 2 };
			}
		}
		else if (pattern == "X"){
			switch (from){
			case 1:return{ 0, 2, 3 };
			case 2:return{ 0, 1, 3 };
			case 3:return{ 0, 1, 2 };
			case 0:return{ 1, 2, 3 };
			}
		}
		else if (pattern == "\\"){
			if (from == 1 || from == 0) 
				return from == 1 ? vector<int>({ 0 }) : vector<int>({ 1 });
			return from == 2 ? vector<int>({3}) : vector<int>({2});
		}
		else if (pattern == "/"){
			if (from == 1 || from == 2) 
				return from == 1 ? vector<int>({ 2 }) : vector<int>({ 1 });
			return from == 0 ? vector<int>({3}) : vector<int>({0});
		}
	}
};

//   0
// 3   1
//   2
class Solution {
public:
	unordered_map<int, unordered_map<int, int>> v;

	bool tunnel(vector<vector<string>> board){
		return dfs(board, 0, 0, 0) == 1; 
	}
	int dfs(vector<vector<string>>& board, int i, int j, int in_dir){
		int n = board.size(), m = board[0].size(); 
		if (i < 0 || i >= n || j < 0 || j >= m || board[i][j] == "") return 0; 
		if (i == n - 1 && j == m - 1) return 1; 

		string tube = board[i][j]; 
		vector<int> outlets = calc_outlets(i, j, in_dir, pattern); 
		if (outlets.empty()) return 0; 

		int res = 2; 

		for (int out : outlets){
			int deltax, deltay, next_in; 
			switch (out){
			case 0:
				deltax = -1, deltay = 0, next_in=2; 
				break;
			case 1:
				deltax = 0, deltay = 1, next_in=3; 
				break;
			case 2:
				deltax = 1, deltay = 0, next_in=0; 
				break;
			case 3:
				deltax = 0, deltay = -1, next_in=1; 
				break;
			}
			int r = dfs(board, i + deltax, j + deltay, next_in); 
			if (!r)
				return false; 
			if (r == 1)
				res == 1; 
		}

		return res; 
	}

	vector<int> calc_outlets(int i, int j, int in_dir, string pattern){
		if (i == 0 && j == 0){
			if (pattern == "-")
				return{ 1 }; 
		}

		if (pattern.empty()) return{}; 
		if (pattern == "-"){
			return in_dir % 2 ? vector<int>({ (in_dir + 2) % 4 }) : vector<int>({});
		}
	}
};


int main(){
	Solution a;

	vector<vector<string>> b = {
		{ "-", "T", "-", "\\" },
		{ "", "|", "", "|" },
		{ "", "|", "", "|" },
		{ "", "\\", "-", "/" },
	}; 

	cout << a.tunnel(b) << endl; 


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

