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


struct TreeNode {
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
typedef vector<vector<int>> VII; 


class Solution {
public:
	// 1 - inside, -1 - outside, 0 - on polygon
	int cross(VII vertices, VI point){
		int crossCnt = 0;
		int n = vertices.size();
		for (int i = 0; i < vertices.size(); ++i){
			int nxt = (i + 1) % n;
			VI edge = { vertices[nxt][0] - vertices[i][0], vertices[nxt][1] - vertices[i][1] };

			if (ptOnLine(point, vertices[i], vertices[nxt]))
				return 0;

			if (raycross(point, vertices[i], vertices[nxt]))
				crossCnt += 1;
		}

		return crossCnt % 2 ? 1 : -1;
	}

	bool ptOnLine(VI& p, VI& st, VI& ed){
		if (p == st || p == ed)
			return true;

		return ((ed[1] - p[1]) / (ed[0] - p[0]) == (ed[1] - st[1]) / (ed[0] - st[0])) && (p[0] >= st[0] && p[0] <= ed[0]);
	}

	bool raycross(VI point, VI& st, VI& ed){
		// VI vec1 = { st[0] - point[0], st[1] - point[1] },
		// 	vec2 = { ed[0] - point[0], ed[1] - point[1] }; 

		// if ((vec1[1] >= 0 && vec2[1] >= 0) || (vec1[1] < 0 && vec2[1] < 0))
		// 	return false;
		// else
		// 	return true; 

		int ys = st[1] - point[1], ye = ed[1] - point[1]; 
		return ((ys >= 0 && ye < 0) || (ys < 0 && ye >= 0));  // I think it is wrong, cuz you need to check x value range as well 
	}
};


class Solution2 {
public:
	// 1 - inside, -1 - outside, 0 - on polygon
	int cross(VII vertices, VI point){
		int n = vertices.size(); 
		int cross_cnt = 0; 
		for (int i = 0; i < n; ++i){
			int nxt = (i + 1) % n; 
			
			if (point_on_edge(point, vertices[i], vertices[nxt]))
				return 0; 

			if (ray_cross_edge(point, vertices[i], vertices[nxt]))
				cross_cnt += 1; 
		}

		return cross_cnt % 2 ? 1 : -1; 
	}

	bool point_on_edge(VI& point, VI& start, VI& end){
		if (start[0] == end[0])
			return point[0] == 0 && (point[1] - start[1])*(end[1] - point[1]) >= 0; 
		if (point == start || point == end)
			return true; 

		return (point[1] - start[1])*(end[0] - point[0]) == (point[0] - start[0]) *(end[1] - point[1]); 
	}

	bool ray_cross_edge(VI& point, VI& start, VI& end){
		int crosspoint = 0; 
		if (crosspoint < point[0])
			return false; 
		// return (start[1] - point[1])*(end[1] - point[1]) < 0;  
		// up line IS WRONG! you need to consider "ray pass vertical" case!!! 
		int y1 = start[1] - point[1], y2 = end[1] - point[1]; 
		return (y1 >= 0 && y2 < 0) || (y1 < 0 && y2 >= 0); 
	}
}; 


int main(){
	Solution a; 

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

