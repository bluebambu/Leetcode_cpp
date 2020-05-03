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

// wrong ans!!
class Solution {
public:
	void solveSudoku(vector<vector<char>>& board) {
		dfs(board); 
	}
	bool dfs(vector<vector<char>>& board){
		bool full = true; 
		int n = board.size(), m = board[0].size(); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (board[i][j] == '.'){
					full = false; 
					for (char c = '0'; c <= '9'; ++c){
						board[i][j] = c; 
						if (dfs(board))
							return true; 
						else{
							board[i][j] = '.'; 
						}
					}
				}
			}
		}
		if (full && valid(board))
			return true; 
		return false; 
	}
	bool valid(vector<vector<char>>& board){
		int b = 0; 
		return true; 
	}
};

class Solution2 {
public:
	void solveSudoku(vector<vector<char>>& board) {
		backtrack(board);
	}
	bool backtrack(vector<vector<char>>& board){
		int n = board.size(), m = board[0].size();
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (board[i][j] == '.'){
					for (char c = '1'; c <= '9'; ++c){
						board[i][j] = c;
						prt2Layer(board); 
						if (validCell(board, i, j) && backtrack(board)){
							prt2Layer(board); 
							return true;
						}
						board[i][j] = '.';
					}
					return false;
				}
			}
		}
		return true;
	}

	bool validCell(vector<vector<char>>& board, int i, int j){
		int n = board.size(), m = board[0].size();
		char c = board[i][j];
		for (int ii = 0; ii < n; ++ii)
			if (ii != i && board[ii][j] == c)
				return false;
		for (int ii = 0; ii < n; ++ii)
			if (ii != j && board[i][ii] == c)
				return false;

		int blockx = i / 3 * 3, blocky = j / 3 * 3;
		for (int rcnt = 0; rcnt < 3; ++rcnt){
			for (int ccnt = 0; ccnt < 3; ++ccnt){
				if ((blockx + rcnt != i || blocky + ccnt != j) && board[blockx + rcnt][blocky + ccnt] == c)
					return false;
			}
		}
		return true;
	}
};

class Solution3 {
public:
	void solveSudoku(vector<vector<char>>& board) {
		solveSudoku2(board);
	}
	bool solveSudoku2(vector<vector<char>>& board) {
		for (int i = 0; i < 9; ++i){
			for (int j = 0; j < 9; ++j) {
				if (board[i][j] == '.') {
					for (int k = 0; k < 9; ++k) {
						board[i][j] = '1' + k;
						if (isValid(board, i, j) && solveSudoku2(board))
							return true;
						board[i][j] = '.';
					}
					return false;
				}
			}
		}
		return true;
	}
private:
	// 检查 (x, y) 是否合法
	bool isValid(const vector<vector<char> > &board, int x, int y) {
		int i, j;
		for (i = 0; i < 9; i++) // 检查 y 列
			if (i != x && board[i][y] == board[x][y])
				return false;
		for (j = 0; j < 9; j++) // 检查 x 行
			if (j != y && board[x][j] == board[x][y])
				return false;
		for (i = 3 * (x / 3); i < 3 * (x / 3 + 1); i++)
			for (j = 3 * (y / 3); j < 3 * (y / 3 + 1); j++)
				if ((i != x || j != y) && board[i][j] == board[x][y])
					return false;
		return true;
	}
};


// 
class Solution4 {
public:
	void solveSudoku(vector<vector<char>>& board) {
		solve(board); 
	}
	bool solve(vector<vector<char>>& board){
		int n = board.size(), m = board[0].size(); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (board[i][j] == ','){
					for (char c = '0'; c <= '9'; ++c){
						board[i][j] = c; 
						if (valid(board, i, j) && solve(board))
							return true; 
					}
					board[i][j] = ','; 
				}
			}
		}
		return false; 
	}
	bool valid(vector<vector<char>>& board, int i, int j){
		int n = board.size(), m = board[0].size(); 
		vector<bool> cache(n, false); 
		for (int k = 0; k < n; ++k){
			if (board[k][j] != ','){
				char c = board[k][j]; 
				if (cache[c - '0'])
					return false; 
				cache[c - '0'] = true; 
			}
		}

		cache = vector<bool>(n, false); 
		for (int k = 0; k < n; ++k){
			if (board[i][k] != ','){
				char c = board[i][k]; 
				if (cache[c - '0'])
					return false; 
				cache[c - '0'] = true; 
			}
		}

		cache = vector<bool>(n, false); 
		int blockx = i / 3 * 3, blocky = j / 3 * 3; 
		for (int rdelta = 0; rdelta < 3; ++rdelta){
			for (int cdelta = 0; cdelta < 3; ++cdelta){
				int cellx = blockx + rdelta, celly = blocky + cdelta; 
				if (cellx != i || celly != j){
					if (board[cellx][celly] == board[i][j])
						return false; 
				}
			}
		}

		return true; 
	}
};




int main(){
	Solution2 a;

	vector<vector<char>> b = {
		{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}
	}; 

	a.solveSudoku(b); 

	prt2Layer(b); 


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

