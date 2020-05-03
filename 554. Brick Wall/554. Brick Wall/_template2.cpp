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
// ////////////////////////////////////////////////////////////////
// There is a brick wall in front of you. The wall is rectangular and has several rows of bricks
// . The bricks have the same height but different width. You want to draw a vertical line from
// the top to the bottom and cross the least bricks. 
// The brick wall is represented by a list of rows. Each row is a list of integers representing 
// the width of each brick in this row from left to right. 
// If your line go through the edge of a brick, then the brick is not considered as crossed. You 
// need to find out how to draw the line to cross the least bricks and return the number of crossed bricks. 
// You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks. 

// Example:
// Input: 
// [[1,2,2,1],
//  [3,1,2],
//  [1,3,2],
//  [2,4],
//  [3,1,2],
//  [1,3,1,1]]
// Output: 2
// Explanation: 


// Note:
// The width sum of bricks in different rows are the same and won't exceed INT_MAX.
// The number of bricks in each row is in range [1,10,000]. The height of wall is in range [1,10,000]. 
// Total number of bricks of the wall won't exceed 20,000. 



// pass AC
class Solution {
public:
	int leastBricks(vector<vector<int>>& wall) {
		unordered_map<int, int> edges; 

		for (int i = 0; i < wall.size(); ++i){
			int cum = 0; 
			/// the range can only go to  wall[i].size()-1 !!!! because the last line is the final boundary!
			for (int j = 0; j < wall[i].size()-1; ++j){
				cum += wall[i][j]; 
				edges[cum] += 1; 
			}
		}

		int res = 0; 
		for (auto it = edges.begin(); it != edges.end(); ++it){
			res = max(res, it->second); 
		}
		return wall.size() - res; 
	}
};






int main(){
	Solution a;

	vector<vector<int>> b = { { 1, 2, 2, 1 },
	{ 3, 1, 2 },
	{ 1, 3, 2 },
	{ 2, 4 },
	{ 3, 1, 2 },
	{ 1, 3, 1, 1 } };

	a.leastBricks(b); 


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

