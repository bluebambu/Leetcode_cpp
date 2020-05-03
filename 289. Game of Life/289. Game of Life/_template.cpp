// _template.cpp : Defines the entry point for the console application.
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


// 
// According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
// 
// Given a board with m by n cells, each cell has an initial state live(1) or dead(0).Each cell interacts with its eight neighbors(horizontal, vertical, diagonal) using the following four rules(taken from the above Wikipedia article) :
// 
// Any live cell with fewer than two live neighbors dies, as if caused by under - population.
// Any live cell with two or three live neighbors lives on to the next generation.
// Any live cell with more than three live neighbors dies, as if by over - population..
// Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
// 
// Write a function to compute the next state(after one update) of the board given its current state.
// 
// Follow up :
// 
// Could you solve it in - place ? Remember that the board needs to be updated at the same time : You cannot update some cells first and then use their updated values to update other cells.
// In this question, we represent the board using a 2D array.In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array.How would you address these problems ?
// 
// Credits :
// 		Special thanks to @jianchao.li.fighter for adding this problem and creating all test cases.


// status   状态机， 用 > 0, 1 的int 来表示各种状态， 同时状态的数值最后又能够用 x%2 来还原新的结果。 关键还是在于状态数值的设计！！
// 1->0		2
// 1->1		3
// 1->0		4
// 0->1		5
// 0->0		6

// pass
class Solution {
public:
	void gameOfLife(vector<vector<int>>& board) {
		if (board.empty() || board[0].empty())
			return;

		for (int i = 0; i < board.size(); ++i){
			for (int j = 0; j < board[0].size(); ++j){
				first(board, i, j);
			}
		}

		for (int i = 0; i < board.size(); ++i){
			for (int j = 0; j < board[0].size(); ++j){
				board[i][j] = board[i][j] % 2; 
			}
		}
	}

	vector<pair<int, int>> dir{ { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };

	void first(vector<vector<int>>& board, int i, int j){
		int ones = 0;
		for (int k = 0; k < dir.size(); ++k){
			int x = dir[k].first + i,
				y = dir[k].second + j; 
			if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() && (board[x][y] >= 1 && board[x][y] < 5))
				++ones;
		}
		origToNext(board[i][j], ones); 
	}



	void origToNext(int& data, int ones){
		if (data == 1){
			if (ones < 2)
				data = 2;
			else if (ones == 2 || ones == 3)
				data = 3;
			else if (ones > 3)
				data = 4; 
		}
		else{
			if (ones == 3)
				data = 5;
			else
				data = 6;
		}
	}


};





int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	a.flatten(tree);


}

