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
// There are a total of n courses you have to take, labeled from 0 to n - 1.
// Some courses may have prerequisites, for example to take course 0 you have to first take 
// course 1, which is expressed as a pair : [0, 1]
// Given the total number of courses and a list of prerequisite pairs, return the ordering 
// of courses you should take to finish all courses.
// There may be multiple correct orders, you just need to return one of them.If it is impossible 
// to finish all courses, return an empty array.

// For example :
// 2, [[1, 0]]
// There are a total of 2 courses to take.To take course 1 you should have finished course 0. 
// So the correct course order is[0, 1]

// 4, [[1, 0], [2, 0], [3, 1], [3, 2]]
// There are a total of 4 courses to take.To take course 3 you should have finished both courses 1 
// and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order 
// is[0, 1, 2, 3].Another correct ordering is[0, 2, 1, 3].

// Note :
// 	 The input prerequisites is a graph represented by a list of edges, not adjacency matrices.Read 
// 		 more about how a graph is represented.
// 	 You may assume that there are no duplicate edges in the input prerequisites


// dfs, pass AC
class Solution {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<bool> visited(numCourses, false); 

		vector<vector<bool>> g(numCourses, vector<bool>(numCourses, false)); 
		for (auto i : prerequisites){
			g[i.first][i.second] = true; 
		}

		vector<bool> path(numCourses, false); 
		vector<int> res; 

		for (int i = 0; i < numCourses; ++i){
			if (!visited[i]){
				if (!helper(g, i, visited, path, res))
					return vector<int>(); 
			}
		}

		return res; 
	}

	// princeton algo 的dfs是没有return的， 这里有个return， 可以用来判断 “i 之后的路径是不是circle”， 从而递归
	bool helper(vector<vector<bool>>& g, int i, vector<bool>& visited, vector<bool>& path, vector<int>& res){
		// 从递归的条件出发推断， 这里不需要一个递归终止条件， helper本身的代码就可以终止递归
		visited[i] = true; 
		path[i] = true; 
		bool result = true; 

		for (int j = 0; j < visited.size(); ++j){
			if (j == i || g[i][j]==false)
				continue;
			if (path[j] == true)
				return false; 
			if (!visited[j])
				// 要保证所有的分叉路径都没有circle
				result = result && helper(g, j, visited, path, res);
		}
		path[i] = false; 
		res.push_back(i); 
		return result; 
	}
};



int main() {
	Solution a;
	vector<pair<int, int>> b = { { 1, 0 }, { 2, 0 }, { 3, 1 }, { 3, 2 } };
	auto c = a.findOrder(4, b);

	setprt(c); 

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

