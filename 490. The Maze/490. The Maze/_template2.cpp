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
// There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

// Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.

// The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

// Example 1

// Input 1: a maze represented by a 2D array

// 0 0 1 0 0
// 0 0 0 0 0
// 0 0 0 1 0
// 1 1 0 1 1
// 0 0 0 0 0

// Input 2: start coordinate (rowStart, colStart) = (0, 4)
// Input 3: destination coordinate (rowDest, colDest) = (4, 4)

// Output: true
// Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.

// Example 2

// Input 1: a maze represented by a 2D array

// 0 0 1 0 0
// 0 0 0 0 0
// 0 0 0 1 0
// 1 1 0 1 1
// 0 0 0 0 0

// Input 2: start coordinate (rowStart, colStart) = (0, 4)
// Input 3: destination coordinate (rowDest, colDest) = (3, 2)

// Output: false
// Explanation: There is no way for the ball to stop at the destination.

// Note:

//     There is only one ball and one destination in the maze.
//     Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
//     The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
//     The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.

// key point: stop at destination, not pass by!!

// pass AC
vector<pair<int, int>> dirs = {
	{1,0}, 
	{-1,0}, 
	{0,1}, 
	{0,-1}, 
}; 

class Solution {
public:

	bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
		if (maze.empty() || maze[0].empty())
			return true; // attention!

		set<vector<int>> visited; // weirdly, set have hash func for vector, but unordered_set doesn't
		int n = maze.size(), m = maze[0].size(); 
		vector<vector<int>> dp(n, vector<int>(m, 2)); 
		return helper(maze, visited, dp, start, destination); 
	}
	bool helper(vector<vector<int>>& maze,
		set<vector<int>>& visited,
		vector<vector<int>>& dp,
		vector<int> start,
		vector<int>& dest
		){
		if (start == dest)
			return true; 
		if (dp[start[0]][start[1]]<2)
			return dp[start[0]][start[1]]; 

		int n = maze.size(), m = maze[0].size(); 

		visited.insert(start); // remember!!

		int res = false; 

		for (auto d : dirs){
			int x = start[0], y = start[1]; 
			while (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] != 1){ // find the end point
				x += d.first;
				y += d.second; 
			}
			x -= d.first; y -= d.second; 

			if (visited.count({ x, y }) == 0){
				res |= helper(maze, visited, dp, { x, y }, dest); 
			}
		}

		dp[start[0]][start[1]] = res;
		return res;
	}
};


// pass AC
class Solution2 {
public:
	bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
		if (maze.empty() || maze[0].empty())
			return true; 

		int n = maze.size(), m = maze[0].size(); 

		queue<vector<int>> que; 
		que.push(start); 
		set<vector<int>> visited; 
		visited.insert(start); 

		while (!que.empty()){
			auto tmp = que.front(); 
			que.pop(); 

			int x = tmp[0], y = tmp[1]; 
			for (auto d : dirs){
				vector<int> newPos = toEdge(x, y, maze, d); 
				if (newPos == destination)
					return true; 
				if (visited.count(newPos))
					continue;
				
				visited.insert(newPos); 
				que.push(newPos); 
			}
		}
		return false; 
	}

	vector<int> toEdge(int x, int y, vector<vector<int>>& maze, pair<int, int>& d){
		int n = maze.size(), m = maze[0].size(); 
		while (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] != 1){
			x += d.first; 
			y += d.second;
		}
		x -= d.first; 
		y -= d.second; 
		return{ x, y }; 
	}
};

// pass
vector<vector<int>> dirs2{ { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;


class Solution3 {
public:
	bool hasPath(vector<vector<int>>& maze, vector<int> start, vector<int> destination) {
		if (maze.empty() || maze[0].empty())
			return false;
		int n = maze.size(), m = maze[0].size();

		if (maze[start[0]][start[1]])
			return false;

		unordered_set<int> v;
		return dfs(maze, start[0], start[1], destination, v);
	}

	bool dfs(vector<vector<int>>& m, int i, int j, vector<int>& dest, unordered_set<int>& v){
		if (vector<int>({ i, j }) == dest)
			return true;

		int n = m.size(), k = m[0].size();
		v.insert(i*k + j);
		for (auto& d : dirs2){
			int x = i + d[0], y = j + d[1];
			while (x >= 0 && x < n && y >= 0 && y < k && m[x][y] == 0) x += d[0], y += d[1];
			x -= d[0], y -= d[1];
			if (!v.count(x*k + y))
				if (dfs(m, x, y, dest, v))
					return true;
		}
		return false;
	}
};


// pass
class Solution4 {
public:

	bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
		if (maze.empty() || maze[0].empty())
			return true; 
		if (start == destination)
			return true; 
		set<vector<int>> v; 
		return dfs(maze, start, destination, v); 
	}
	bool dfs(vector<vector<int>>& maze, vector<int>&start, vector<int>& dest, set<vector<int>>& v){
		int n = maze.size(), m = maze[0].size(); 

		for (auto d : dirs2){
			int x = start[0], y = start[1];
			while (x >= 0 && x < n && y>=0 && y<m && maze[x][y]==0) x += d[0], y += d[1];
			x -= d[0], y -= d[1]; 
			if (x == dest[0] && y == dest[1])
				return true; 
			if (v.count({x, y}))
				continue;
			vector<int> cur({ x, y }); 
			v.insert(cur);
			if (dfs(maze, cur, dest, v))
				return true; 
		}
		return false; 
	}
};



int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


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

