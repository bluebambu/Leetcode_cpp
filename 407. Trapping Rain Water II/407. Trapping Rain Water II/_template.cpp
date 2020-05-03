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
#include <functional> // for greater<pair<int,int>>

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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given an m x n matrix of positive integers representing the height of each unit cell in a 2D 
// elevation map, compute the volume of water it is able to trap after raining.

// Note:
// Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20, 000.
// Example :
// 		Given the following 3x6 height map :
// [
// 	[1, 4, 3, 1, 3, 2],
// 	[3, 2, 1, 3, 2, 4],
// 	[2, 3, 3, 2, 3, 1]
// ]

// Return 4.



vector<pair<int, int>> dir = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

// pass AC
class Solution {
public:
	int trapRainWater(vector<vector<int>>& heightMap) {
		if (heightMap.empty() || heightMap[0].empty())
			return 0; 
		int m = heightMap.size(), n = heightMap[0].size(), res = 0, lastMax = INT_MIN;
		priority_queue< pair<int, int>, vector < pair<int, int>>, greater<pair<int, int>> >  pq;
		vector<vector<bool>> visited(m, vector<bool>(n, false));

		for (size_t i = 0; i < m; ++i){
			for (size_t j = 0; j < n; ++j){
				if (i == 0 || j == 0 || i == m - 1 || j == n - 1){
					pq.push(pair<int, int>(heightMap[i][j], i*n + j));
					visited[i][j] = true; 
				}
			}
		}

		while (pq.size()){
			int h = pq.top().first, x = pq.top().second / n, y = pq.top().second % n;
			pq.pop();
			// 这个lastMax非常关键， 可以想象一个最外围最高，水能在整个内部积累的例子。之前我觉得不需要lastmax， 直接
			// 用h去和 newx，newy 就可以， 其实是不行的， 因为 pq 推出来的水位总是局部最高水位， 需要洼地所有的高度都去match！！
			lastMax = max(h, lastMax); 

			for (auto& d : dir){
				int newx = x + d.first, newy = y + d.second;
				if (newx<0 || newx>m - 1 || newy<0 || newy>n - 1 || visited[newx][newy])
					continue;
				if (heightMap[newx][newy] < lastMax){
					res += lastMax - heightMap[newx][newy]; 
				}
				pq.push(pair<int, int>(heightMap[newx][newy], newx * n + newy)); 
				visited[newx][newy] = true; 
			}
		}

		return res;
	}

};


class Solution2 {
public:
	int trapRainWater(vector<vector<int>>& heightMap) {
		if (heightMap.empty() || heightMap[0].empty())
			return 0; 

		int n = heightMap.size(), m = heightMap[0].size(); 
		set<vector<int>> q; 
		unordered_set<int> v; 
		for (int i = 0; i < n; ++i){
			q.insert({ heightMap[i][0], i*m }); 
			v.insert(i*m); 
			q.insert({ heightMap[i][m - 1], i*m + m - 1 }); 
			v.insert(i*m+m-1); 
		}
		for (int j = 0; j < m; ++j){
			q.insert({ heightMap[0][j], j }); 
			v.insert(j); 
			q.insert({ heightMap[n - 1][j], (n - 1)*m + j }); 
			v.insert((n - 1)*m + j); 
		}

		int res = 0; 

		while (!q.empty()){
			vector<int> f = *(q.begin()); 
			q.erase(q.begin()); 

			int curH = f[0], x = f[1] / m, y = f[1] % m; 
			for (auto& d : dir){
				int xx = x + d.first, yy = y + d.second; 
				int idx = xx*m + yy; 
				if (xx >= 0 && xx < n && yy >= 0 && yy < m && !v.count(idx)){
					if (heightMap[xx][yy] < curH){
						res += curH - heightMap[xx][yy]; 
						q.insert({ curH, idx }); 
					}
					else
						q.insert({ heightMap[xx][yy], idx }); 

					v.insert(idx); 
				}
			}
		}

		return res; 
	}
};

typedef pair<int, int> PII;
class Solution3 {
public:

	int trapRainWater(vector<vector<int>>& heightMap) {
		int n = heightMap.size(), m = heightMap[0].size(); 
		vector<vector<bool>> visited(n, vector<bool>(m, false)); 
		priority_queue<pair<int, int>> q; 
		for (int i = 0; i < n; ++i){
			q.push({i, 0});
			visited[i][0] = true;
			q.push({ i, m - 1 });
			visited[i][m - 1] = true;
		}
		for (int j = 1; j < m-1; ++j){
			q.push({ 0, j }); 
			visited[0][j] = true;
			q.push({ n - 1 , j });
			visited[n - 1][j] = true;
		}

		int res = 0; 

		while (!q.empty()){
			auto f = q.top(); 
			q.pop(); 
			int x = f.first, y = f.second; 

			for (auto d : dir){
				int xx = x + d.first, yy = y + d.second; 
				if (xx >= 0 && xx < n && yy >= 0 && yy < m && !visited[xx][yy]){
					if (heightMap[xx][yy] < heightMap[x][y]){
						res += heightMap[x][y] - heightMap[xx][yy]; 
						heightMap[xx][yy] = heightMap[x][y]; 
					}
					q.push({ xx, yy }); 
					visited[xx][yy] = true; 
				}
			}
		}

		return res; 
	}
}; 


int main() {
	Solution2 a;
	Solution3 a2;

	vector<vector<int>> b = {
		{ 1, 4, 3, 1, 3, 2 },
		{ 3, 2, 1, 3, 2, 4 },
		{ 2, 3, 3, 2, 3, 1 },
	};

	vector<vector<int>> bb = b; 

	cout << a.trapRainWater(b) << endl; 
	cout << a2.trapRainWater(bb) << endl; 

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/


}

