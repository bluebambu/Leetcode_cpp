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
#include <string> 
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


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
		for (int i = 0; i<n; ++i){
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



// You want to build a house on an empty land which reaches all buildings in the shortest amount of distance.You can only move up, down, left and right.You are given a 2D grid of values 0, 1 or 2, where:
// 
// Each 0 marks an empty land which you can pass by freely.
// Each 1 marks a building which you cannot pass through.
// Each 2 marks an obstacle which you cannot pass through.
// 
// For example, given three buildings at(0, 0), (0, 4), (2, 2), and an obstacle at(0, 2) :
// 
// 1 - 0 - 2 - 0 - 1
// | | | | |
// 0 - 0 - 0 - 0 - 0
// | | | | |
// 0 - 0 - 1 - 0 - 0
// 
// The point(1, 2) is an ideal empty land to build a house, as the total travel distance of 3 + 3 + 1 = 7 is minimal.So return 7.
// 
// Note:
// There will be at least one building.If it is not possible to build such house according to the above rules, return -1.




// 做法是错误的， 因为距离场不适合用dfs ！！  

// 	  1 0 0		   0 5 6
// 	  0	0 0	  ->   1 4 7
// 	  0	0 0		   2 3 8
// 按一般写法得到的距离场是这个样子， 明显是错误的！ 
// 
// 所以这道题只能用 bfs 来做。 

class Solution2 {
public:
	int shortestDistance(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size(); 
		vector<vector<int>> dist(n, vector<int>(m, 0)); 

		int lab = 0; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] == 1){
					dfs(grid, i + 1, j, dist, 1, lab);
					dfs(grid, i - 1, j, dist, 1, lab);
					dfs(grid, i, j + 1, dist, 1, lab);
					dfs(grid, i, j - 1, dist, 1, lab);
					--lab; 
				}
			}
		}

		int res = INT_MAX; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				res = min(res, dist[i][j]); 
			}
		}

		return res; 
	}																			

	void dfs(vector<vector<int>>& grid, int r, int c, vector<vector<int>>& dist, int curdist, int lab){
		if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] != lab)
			return;

		grid[r][c] = lab - 1;
		dist[r][c] += curdist; 

		dfs(grid, r + 1, c, dist, curdist+1, lab);
		dfs(grid, r - 1, c, dist, curdist + 1, lab);
		dfs(grid, r , c+1, dist, curdist + 1, lab);
		dfs(grid, r , c-1, dist, curdist + 1, lab);
	}
};



// BFS, 大体思路是对的， 但是细节方面不对。 一个例子
// 
// 	1 1
// 	0 1     
// 
// 	当扫到第二个1 （0，1） 的时候， 和其他0无法联通， 这时候label变成-2， 但是实际上grid中没有任何-2.  
// 	这样再扫到第三个  1（1, 1)的时候， 判断条件找的是 - 2， 但(1,0)只有 -1， 所以就不可能找到 empty land了
// 
// 	比较好的方法是用一个 count[n][m] 记录每个点的联通数，最后再做比较。 
// 
// 	还有一个方法是每层自己单独开一个 visited[n][m]， 然后每层res 都初始化成 INT_MAX， 要是没有联通到任何的empty
// 	land， 这一层之后， 所有层的 grid[x][y] 和 label 都会mismatch，导致res一直等于 INT_MAX, 结果就是 -1. 有点太巧妙了。 
//  记得每一层中都不断更新 res， 而不是最后再开一个两层循环专门找 res， 这会导致问题， 和这个思路不搭。 

class Solution3 {
public:
	int shortestDistance(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size(); 
		vector<vector<int>> dist(n, vector<int>(m, 0)); 

		int lab = 0;
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] == 1){
					bfs(grid, i, j, dist, lab--); 
				}
			}
		}

		int res = INT_MAX;
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] < 0){
					res = min(res, dist[i][j]);
				}
			}
		}

		return res==INT_MAX ? -1 : res; 
	}

	void bfs(vector<vector<int>>& grid, int r, int c, vector<vector<int>>& dist, int lab){
		queue<pair<int, int>> q; 
		q.push(make_pair(r, c)); 

		vector<vector<int>> dir{ { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

		int init = 1; 
		while (!q.empty()){
			int sz = q.size(); 

			for (int i = 0; i < sz; ++i){
				auto front = q.front();
				q.pop();

				for (auto d : dir){
					int x = front.first + d[0],
						y = front.second + d[1]; 
					if (x<0 || x >= grid.size() || y<0 || y >= grid[0].size() || grid[x][y]!=lab)
						continue;
					grid[x][y] = lab - 1; 
					dist[x][y] += init;
					q.push(make_pair(x, y)); 
				}
			}
			++init; 
		}
	}
}; 



// Finally passed!!!! BFS + building num matrix + double loop in BFS
class Solution {
public:
	int shortestDistance(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size(); 
		int lab = 0, buildnums=0; 
		vector<vector<int>> dist(n, vector<int>(m, 0)); 
		vector<vector<int>> count = dist; 

		vector<vector<int>> dir{ { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] == 1){
					buildnums++; 
					queue<pair<int, int>> q; 
					q.push(make_pair(i, j)); 
					int d = 1; 

					while (!q.empty()){
						int sz = q.size(); 

						for (int k = 0; k < sz; ++k){
							pair<int, int> tmp = q.front();
							q.pop();

							for (auto i : dir){
								int x = tmp.first + i[0],
									y = tmp.second + i[1];
								if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == lab){
									--grid[x][y];
									dist[x][y] += d;
									count[x][y]++;
									q.push(make_pair(x, y));
								}
							}
						}

						++d;
					}

					--lab; 
				}
			}
		}


		int res = INT_MAX; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] < 0 && count[i][j] == buildnums)
					res = min(res, dist[i][j]);
			}
		}

		return res == INT_MAX ? -1 : res; 
	}
};


class Solution4 {
public:
	int shortestDistance(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty()) 
			return 0; 

		vector<vector<int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } }; 

		int n = grid.size(), m = grid[0].size(); 
		vector<vector<int>> dist(n, vector<int>(m, 0)); 

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] == 1){
					queue<int> q; 
					vector<vector<bool>> visited(n, vector<bool>(m, false)); 
					q.push(i*m + j); 
					visited[i][j] = true; 

					int len = 1; 
					while (!q.empty()){
						int sz = q.size(); 
						for (int k = 0; k < sz; ++k){
							int f = q.front();
							q.pop();
							int x = f / m, y = f%m;

							for (auto& d : dirs){
								int xx = x + d[0], yy = y + d[1];
								if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!visited[xx][yy]){
									visited[xx][yy] = true;
									q.push(xx*m + yy);
									dist[xx][yy] += len; 
								}
							}
						}
						++len; 
					}
				}
			}
		}

		int res = INT_MAX, fi, fj; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] == 0 && dist[i][j] < res){
					res = dist[i][j]; 
					fi = i; fj = j; 
				}
			}
		}

		return res; 
	}
};



int main() {
	Solution a;
	Solution4 a2;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9
	*/

	vector<vector<int>> map{ { 1, 1 }, { 0, 1 } }; 
	vector<vector<int>> map{ { 1, 1 }, { 0, 1 } }; 
	cout << a.shortestDistance(map) << endl; 
	cout << a2.shortestDistance(map) << endl; 

}

