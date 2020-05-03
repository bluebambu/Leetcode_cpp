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

// Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.

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

// Output: 12
// Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
//              The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.

// Example 2

// Input 1: a maze represented by a 2D array

// 0 0 1 0 0
// 0 0 0 0 0
// 0 0 0 1 0
// 1 1 0 1 1
// 0 0 0 0 0

// Input 2: start coordinate (rowStart, colStart) = (0, 4)
// Input 3: destination coordinate (rowDest, colDest) = (3, 2)

// Output: -1
// Explanation: There is no way for the ball to stop at the destination.

// Note:

//     There is only one ball and one destination in the maze.
//     Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
//     The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
//     The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.


// foundamentally, this is a Dijkstra problem!!! So using BFS is less efficient, priority queue should be used. 


// pass
typedef pair<int, int> PII; 
vector<vector<int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } }; 

class Solution {
public:
	int shortestDistance(vector<vector<int>>& maze, vector<int> start, vector<int> destination) {
		if (maze.empty() || maze[0].empty())
			return 0; 
		int n = maze.size(), m = maze[0].size(); 

		set<PII> q; 
		q.insert({ 0, start[0] * m + start[1]}); 
		unordered_map<int, int> distance; 
		distance[start[0] * m + start[1]] = 0; 
		unordered_set<int> excluded; 

		while (!q.empty()){
			PII f = *(q.begin()); 
			q.erase(q.begin()); 

			int dist = f.first, i = f.second / m, j = f.second%m; 
			if (vector<int>({ i, j }) == destination)
					return dist; 

			excluded.insert(f.second); 

			for (auto& d : dirs){
				int curd = dist; 
				int x = i + d[0], y = j + d[1]; 
				curd += 1; 
				while (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0) x += d[0], y += d[1], curd += 1; 
				x -= d[0], y -= d[1], curd -= 1; 

				int idx = x*m + y; 

				if (excluded.count(idx))
					continue; 

				if (distance.count(idx)){
					if (curd < distance[idx]){
						q.erase(q.find({ distance[idx], idx }));
						distance[idx] = curd; 
					}
				}
				q.insert({ curd, idx}); 
			}
		}
		
		return -1; 
	}
};


class Solution2 {
public:
	int shortestDistance(vector<vector<int>>& maze, vector<int> start, vector<int> destination) {
		int n = maze.size(), m = maze[0].size(); 
		vector<vector<int>> dist(n, vector<int>(m, -1)); 

		queue<vector<int>> q; 
		q.push(start); 
		dist[start[0]][start[1]] = 0; 

		while (!q.empty()){
			vector<int> f = q.front(); 
			q.pop(); 
			int i = f[0], j = f[1], d = dist[i][j]; 

			for (auto d : dirs){
				vector<int> endpos = getEnd(maze, i, j, d); 
				int len = abs(endpos[0] - i) + abs(endpos[1] - j); 
				if (dist[endpos[0]][endpos[1]] <= d+len)
					continue;; 
				dist[endpos[0]][endpos[1]] = d + len; 
				if (endpos != destination)
					q.push(endpos);
			}
		}

		return dist[destination[0]][destination[1]]; 
	}
};


int main(){
	Solution a; 

	vector<vector<int>> m = {
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 1, 1, 0, 1, 1 },
		{ 0, 0, 0, 0, 0 },
	}; 

	cout << a.shortestDistance(m, { 0, 4 }, { 4, 4 }); 


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

